/*
    -- clMAGMA (version 1.1.0) --
       Univ. of Tennessee, Knoxville
       Univ. of California, Berkeley
       Univ. of Colorado, Denver
       @date January 2014

       @generated from zgetrf_gpu.cpp normal z -> d, Fri Jan 10 15:51:17 2014

*/

#include <cstdio>
#include "common_magma.h"

magma_err_t
magma_dgetrf_gpu(magma_int_t m, magma_int_t n,
                 magmaDouble_ptr dA, size_t dA_offset, magma_int_t ldda,
                 magma_int_t *ipiv, magma_int_t *info,
                 magma_queue_t queue )
{
/*  -- clMAGMA (version 1.1.0) --
       Univ. of Tennessee, Knoxville
       Univ. of California, Berkeley
       Univ. of Colorado, Denver
       @date January 2014

    Purpose
    =======
    DGETRF computes an LU factorization of a general M-by-N matrix A
    using partial pivoting with row interchanges.

    The factorization has the form
       A = P * L * U
    where P is a permutation matrix, L is lower triangular with unit
    diagonal elements (lower trapezoidal if m > n), and U is upper
    triangular (upper trapezoidal if m < n).

    This is the right-looking Level 3 BLAS version of the algorithm.

    Arguments
    =========

    M       (input) INTEGER
            The number of rows of the matrix A.  M >= 0.

    N       (input) INTEGER
            The number of columns of the matrix A.  N >= 0.

    A       (input/output) DOUBLE_PRECISION array on the GPU, dimension (LDDA,N).
            On entry, the M-by-N matrix to be factored.
            On exit, the factors L and U from the factorization
            A = P*L*U; the unit diagonal elements of L are not stored.

    LDDA     (input) INTEGER
            The leading dimension of the array A.  LDDA >= std::max(1,M).

    IPIV    (output) INTEGER array, dimension (std::min(M,N))
            The pivot indices; for 1 <= i <= std::min(M,N), row i of the
            matrix was interchanged with row IPIV(i).

    INFO    (output) INTEGER
            = 0:  successful exit
            < 0:  if INFO = -i, the i-th argument had an illegal value
                  if INFO = -7, internal GPU memory allocation failed.
            > 0:  if INFO = i, U(i,i) is exactly zero. The factorization
                  has been completed, but the factor U is exactly
                  singular, and division by zero will occur if it is used
                  to solve a system of equations.
    =====================================================================    */

#define inAT(i,j) dAT, dAT_offset + (i)*nb*lddat + (j)*nb

    double c_one     = MAGMA_D_MAKE(  1.0, 0.0 );
    double c_neg_one = MAGMA_D_MAKE( -1.0, 0.0 );

    magma_int_t iinfo, nb;
    magma_int_t maxm, maxn, mindim;
    magma_int_t i, rows, cols, s, lddat, lddwork;
    
    magmaDouble_ptr dAT, dAP;
    double *work;

    magma_err_t err;

    *info = 0;
    if (m < 0)
        *info = -1;
    else if (n < 0)
        *info = -2;
    else if (ldda < std::max(1,m))
        *info = -4;

    if (*info != 0) {
        magma_xerbla( __func__, -(*info) );
        return *info;
    }

    if (m == 0 || n == 0)
        return MAGMA_SUCCESS;

    mindim = std::min(m, n);
    nb     = magma_get_dgetrf_nb(m);
    s      = mindim / nb;

    if (nb <= 1 || nb >= std::min(m,n))
      {
        // use CPU code
        err = magma_dmalloc_cpu(  &work, m*n );
        if ( err != MAGMA_SUCCESS ) {
          *info = MAGMA_ERR_HOST_ALLOC;
          return *info;
        }

        chk( magma_dgetmatrix( m, n, dA, dA_offset, ldda, work, 0, m, queue ));
        lapackf77_dgetrf(&m, &n, work, &m, ipiv, info);
        chk( magma_dsetmatrix( m, n, work, 0, m, dA, dA_offset, ldda, queue ));

        magma_free_cpu(work);
      }
    else
      {
        size_t dAT_offset;

        // use hybrid blocked code
        maxm = ((m + 31)/32)*32;
        maxn = ((n + 31)/32)*32;

        lddat   = maxn;
        lddwork = maxm;

        if ( MAGMA_SUCCESS != magma_dmalloc( &dAP, nb*maxm )) {
          *info = MAGMA_ERR_DEVICE_ALLOC;
          return *info;
        }

        if ((m == n) && (m % 32 == 0) && (ldda%32 == 0))
          {
            dAT = dA;
            dAT_offset = dA_offset;
            magma_dtranspose_inplace( dAT, dAT_offset, ldda, lddat, queue );
          }
        else
          {
            dAT_offset = 0;
            if ( MAGMA_SUCCESS != magma_dmalloc( &dAT, maxm*maxn )) {
              magma_free( dAP );
              *info = MAGMA_ERR_DEVICE_ALLOC;
              return *info;
            }

            magma_dtranspose2( dAT, dAT_offset, lddat, dA, dA_offset,  ldda, m, n, queue );
        }

        if ( MAGMA_SUCCESS != magma_dmalloc_cpu( &work, maxm*nb ) ) {
          magma_free( dAP );
          if (! ((m == n) && (m % 32 == 0) && (ldda%32 == 0)) )
            magma_free( dAT );

          *info = MAGMA_ERR_HOST_ALLOC;
          return *info;
        }

        for( i=0; i<s; i++ )
            {
                // download i-th panel
                cols = maxm - i*nb;
                magma_dtranspose( dAP, 0, cols, inAT(i,i), lddat, nb, cols, queue );
                magma_dgetmatrix(m-i*nb, nb, dAP, 0, cols, work, 0, lddwork, queue);

                if ( i>0 ){
                    magma_dtrsm( MagmaRight, MagmaUpper, MagmaNoTrans, MagmaUnit,
                                 n - (i+1)*nb, nb,
                                 c_one, inAT(i-1,i-1), lddat,
                                 inAT(i-1,i+1), lddat, queue );
                    magma_dgemm( MagmaNoTrans, MagmaNoTrans,
                                 n-(i+1)*nb, m-i*nb, nb,
                                 c_neg_one, inAT(i-1,i+1), lddat,
                                            inAT(i,  i-1), lddat,
                                 c_one,     inAT(i,  i+1), lddat, queue );
                }

                // do the cpu part
                rows = m - i*nb;
                lapackf77_dgetrf( &rows, &nb, work, &lddwork, ipiv+i*nb, &iinfo);
                if ( (*info == 0) && (iinfo > 0) )
                    *info = iinfo + i*nb;

                magma_dpermute_long2(n, dAT, dAT_offset, lddat, ipiv, nb, i*nb, queue );

                // upload i-th panel
                magma_dsetmatrix(m-i*nb, nb, work, 0, lddwork, dAP, 0, maxm, queue);
                magma_dtranspose(inAT(i,i), lddat, dAP, 0, maxm, cols, nb, queue );

                // do the small non-parallel computations
                if ( s > (i+1) ) {
                    magma_dtrsm( MagmaRight, MagmaUpper, MagmaNoTrans, MagmaUnit,
                                 nb, nb,
                                 c_one, inAT(i, i  ), lddat,
                                 inAT(i, i+1), lddat, queue);
                    magma_dgemm( MagmaNoTrans, MagmaNoTrans,
                                 nb, m-(i+1)*nb, nb,
                                 c_neg_one, inAT(i,   i+1), lddat,
                                            inAT(i+1, i  ), lddat,
                                 c_one,     inAT(i+1, i+1), lddat, queue );
                }
                else {
                    magma_dtrsm( MagmaRight, MagmaUpper, MagmaNoTrans, MagmaUnit,
                                 n-s*nb, nb,
                                 c_one, inAT(i, i  ), lddat,
                                 inAT(i, i+1), lddat, queue);
                    magma_dgemm( MagmaNoTrans, MagmaNoTrans,
                                 n-(i+1)*nb, m-(i+1)*nb, nb,
                                 c_neg_one, inAT(i,   i+1), lddat,
                                            inAT(i+1, i  ), lddat,
                                 c_one,     inAT(i+1, i+1), lddat, queue );
                }
            }

        magma_int_t nb0 = std::min(m - s*nb, n - s*nb);
        rows = m - s*nb;
        cols = maxm - s*nb;

        magma_dtranspose2( dAP, 0, maxm, inAT(s,s), lddat, nb0, rows, queue);
        magma_dgetmatrix(rows, nb0, dAP, 0, maxm, work, 0, lddwork, queue);

        // do the cpu part
        lapackf77_dgetrf( &rows, &nb0, work, &lddwork, ipiv+s*nb, &iinfo);
        if ( (*info == 0) && (iinfo > 0) )
            *info = iinfo + s*nb;
        magma_dpermute_long2(n, dAT, dAT_offset, lddat, ipiv, nb0, s*nb, queue );

        // upload i-th panel
        magma_dsetmatrix(rows, nb0, work, 0, lddwork, dAP, 0, maxm, queue);
        magma_dtranspose2( inAT(s,s), lddat, dAP, 0, maxm, rows, nb0, queue );

        magma_dtrsm( MagmaRight, MagmaUpper, MagmaNoTrans, MagmaUnit,
                     n-s*nb-nb0, nb0,
                     c_one, inAT(s,s),     lddat,
                     inAT(s,s)+nb0, lddat, queue);

        if ((m == n) && (m % 32 == 0) && (ldda%32 == 0)) {
          magma_dtranspose_inplace( dAT, dAT_offset, lddat, ldda, queue );
        }
        else {
          magma_dtranspose2( dA, dA_offset, ldda, dAT, dAT_offset, lddat, n, m, queue );
          magma_free( dAT );
        }

        magma_free( dAP );
        magma_free_cpu( work );
    }

    return *info;
    /* End of MAGMA_DGETRF_GPU */
}

#undef inAT

/*
    -- clMAGMA (version 1.1.0) --
       Univ. of Tennessee, Knoxville
       Univ. of California, Berkeley
       Univ. of Colorado, Denver
       
       @date January 2014
       
       @precisions normal z -> s d c
*/

#include <cstdio>
#include "common_magma.h"

extern "C" magma_err_t
magma_zgeqrs_gpu(magma_int_t m, magma_int_t n, magma_int_t nrhs,
                 magmaDoubleComplex_ptr dA, size_t dA_offset, magma_int_t ldda,
                 magmaDoubleComplex *tau,   magmaDoubleComplex_ptr dT, size_t dT_offset,
                 magmaDoubleComplex_ptr dB, size_t dB_offset, magma_int_t lddb,
                 magmaDoubleComplex *hwork, magma_int_t lwork,
                 magma_int_t *info, magma_queue_t queue)
{
/*  -- clMagma (version 0.1) --
       Univ. of Tennessee, Knoxville
       Univ. of California, Berkeley
       Univ. of Colorado, Denver
       @date January 2014

    Purpose
    =======
    Solves the least squares problem
           min || A*X - C ||
    using the QR factorization A = Q*R computed by ZGEQRF_GPU.

    Arguments
    =========
    M       (input) INTEGER
            The number of rows of the matrix A. M >= 0.

    N       (input) INTEGER
            The number of columns of the matrix A. M >= N >= 0.

    NRHS    (input) INTEGER
            The number of columns of the matrix C. NRHS >= 0.

    A       (input) COMPLEX_16 array on the GPU, dimension (LDDA,N)
            The i-th column must contain the vector which defines the
            elementary reflector H(i), for i = 1,2,...,n, as returned by
            ZGEQRF_GPU in the first n columns of its array argument A.

    LDDA    (input) INTEGER
            The leading dimension of the array A, LDDA >= M.

    TAU     (input) COMPLEX_16 array, dimension (N)
            TAU(i) must contain the scalar factor of the elementary
            reflector H(i), as returned by MAGMA_ZGEQRF_GPU.

    DB      (input/output) COMPLEX_16 array on the GPU, dimension (LDDB,NRHS)
            On entry, the M-by-NRHS matrix C.
            On exit, the N-by-NRHS solution matrix X.

    DT      (input) COMPLEX_16 array that is the output (the 6th argument)
            of magma_zgeqrf_gpu of size
            2*MIN(M, N)*NB + ((N+31)/32*32 )* MAX(NB, NRHS).
            The array starts with a block of size MIN(M,N)*NB that stores
            the triangular T matrices used in the QR factorization,
            followed by MIN(M,N)*NB block storing the diagonal block
            inverses for the R matrix, followed by work space of size
            ((N+31)/32*32 )* MAX(NB, NRHS).

    LDDB    (input) INTEGER
            The leading dimension of the array DB. LDDB >= M.

    HWORK   (workspace/output) COMPLEX_16 array, dimension (LWORK)
            On exit, if INFO = 0, WORK(1) returns the optimal LWORK.

    LWORK   (input) INTEGER
            The dimension of the array WORK, LWORK >= std::max(1,NRHS).
            For optimum performance LWORK >= (M-N+NB)*(NRHS + 2*NB), where
            NB is the blocksize given by magma_get_zgeqrf_nb( M ).

            If LWORK = -1, then a workspace query is assumed; the routine
            only calculates the optimal size of the HWORK array, returns
            this value as the first entry of the WORK array.

    INFO    (output) INTEGER
            = 0:  successful exit
            < 0:  if INFO = -i, the i-th argument had an illegal value
    =====================================================================    */

   #define a_ref(a_1,a_2)  dA, (dA_offset + (a_1) + (a_2)*(ldda))
   #define d_ref(a_1)      dT, (dT_offset + (lddwork+(a_1))*nb)

    magmaDoubleComplex c_zero    = MAGMA_Z_ZERO;
    magmaDoubleComplex c_one     = MAGMA_Z_ONE;
    magmaDoubleComplex c_neg_one = MAGMA_Z_NEG_ONE;
    magmaDoubleComplex_ptr dwork;
    magma_int_t i, k, lddwork, rows, ib;
    magma_int_t ione = 1;

    magma_int_t nb     = magma_get_zgeqrf_nb(m);
    magma_int_t lwkopt = (m-n+nb)*(nrhs+2*nb);
    long int lquery = (lwork == -1);

    hwork[0] = MAGMA_Z_MAKE( (double)lwkopt, 0. );

    *info = 0;
    if (m < 0)
        *info = -1;
    else if (n < 0 || m < n)
        *info = -2;
    else if (nrhs < 0)
        *info = -3;
    else if (ldda < std::max(1,m))
        *info = -5;
    else if (lddb < std::max(1,m))
        *info = -8;
    else if (lwork < lwkopt && ! lquery)
        *info = -10;

    if (*info != 0) {
        magma_xerbla( __func__, -(*info) );
        return *info;
    }
    else if (lquery)
        return *info;

    k = std::min(m,n);
    if (k == 0) {
        hwork[0] = c_one;
        return *info;
    }

    /* B := Q' * B */
    magma_zunmqr_gpu( MagmaLeft, MagmaConjTrans,
                      m, nrhs, n,
                      a_ref(0,0), ldda, tau,
                      dB, dB_offset, lddb, hwork, lwork, dT, dT_offset, nb, info, queue );
    if ( *info != 0 ) {
        return *info;
    }

    /* Solve R*X = B(1:n,:) */
    lddwork= k;

    int ldtwork;
    size_t dwork_offset = 0;
    if (nb < k)
      {
        dwork = dT;
        dwork_offset = dT_offset+2*lddwork*nb;
      }
    else
      {
        ldtwork = ( 2*k + ((n+31)/32)*32 )*nb;
        magma_zmalloc( &dwork, ldtwork );
      }
    // To do: Why did we have this line originally; seems to be a bug (Stan)?
    //dwork = dT;

    i    = (k-1)/nb * nb;
    ib   = n-i;
    rows = m-i;

    if ( nrhs == 1 ) {
        blasf77_ztrsv( MagmaUpperStr, MagmaNoTransStr, MagmaNonUnitStr,
                       &ib, hwork,         &rows,
                            hwork+rows*ib, &ione);
    } else {
        blasf77_ztrsm( MagmaLeftStr, MagmaUpperStr, MagmaNoTransStr, MagmaNonUnitStr,
                       &ib, &nrhs,
                       &c_one, hwork,         &rows,
                               hwork+rows*ib, &rows);
    }
      
    // update the solution vector
    magma_zsetmatrix( ib, nrhs, hwork+rows*ib, 0, rows, dwork, dwork_offset+i, lddwork, queue );

    // update c
    if (nrhs == 1)
        magma_zgemv( MagmaNoTrans, i, ib,
                     c_neg_one, a_ref(0, i), ldda,
                                         dwork, dwork_offset+i, 1,
                     c_one,     dB, dB_offset, 1, queue );
    else
        magma_zgemm( MagmaNoTrans, MagmaNoTrans,
                     i, nrhs, ib,
                     c_neg_one, a_ref(0, i), ldda,
                                dwork, dwork_offset + i,   lddwork,
                     c_one,     dB, dB_offset, lddb, queue );

    int start = i-nb;
    if (nb < k) {
        for (i = start; i >=0; i -= nb) {
            ib = std::min(k-i, nb);
            rows = m -i;

            if (i + ib < n) {
                if (nrhs == 1) {
                    magma_zgemv( MagmaNoTrans, ib, ib,
                                 c_one,  d_ref(i), ib,
                                 dB, dB_offset+i,      1,
                                 c_zero, dwork, dwork_offset+i,  1, queue );
                    magma_zgemv( MagmaNoTrans, i, ib,
                                 c_neg_one, a_ref(0, i), ldda,
                                 dwork, dwork_offset+i,   1,
                                 c_one,     dB, dB_offset, 1, queue );
                } else {
                    magma_zgemm( MagmaNoTrans, MagmaNoTrans,
                                 ib, nrhs, ib,
                                 c_one,  d_ref(i), ib,
                                 dB, dB_offset+i, lddb,
                                 c_zero, dwork, dwork_offset+i,  lddwork, queue );
                    magma_zgemm( MagmaNoTrans, MagmaNoTrans,
                                 i, nrhs, ib,
                                 c_neg_one, a_ref(0, i), ldda,
                                 dwork, dwork_offset+i, lddwork,
                                 c_one,     dB, dB_offset, lddb, queue );
                }
            }
        }
    }

    magma_zcopymatrix( (n), nrhs,
                       dwork, dwork_offset, lddwork,
                       dB, dB_offset,   lddb, queue );

    if (nb >= k)
      magma_free(dwork);

    magma_queue_sync( queue );

    return *info;
}

#undef a_ref
#undef d_ref

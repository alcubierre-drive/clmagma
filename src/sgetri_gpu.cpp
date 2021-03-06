/*
   -- clMAGMA (version 1.1.0) --
   Univ. of Tennessee, Knoxville
   Univ. of California, Berkeley
   Univ. of Colorado, Denver
   @date January 2014

   @generated from zgetri_gpu.cpp normal z -> s, Fri Jan 10 15:51:17 2014

 */

#include <cstdio>
#include "common_magma.h"

#define dA(i, j)    dA, (dA_offset + (i) + (j)*lda)
#define dL(i, j)    dL, (dL_offset + (i) + (j)*ldl)

extern "C" magma_int_t
magma_sgetri_gpu( magma_int_t n, magmaFloat_ptr dA, size_t dA_offset, magma_int_t lda,
        magma_int_t *ipiv, magmaFloat_ptr dwork, size_t dwork_offset, magma_int_t lwork,
        magma_int_t *info, magma_queue_t queue )
{
/*  -- clMAGMA (version 1.1.0) --
    Univ. of Tennessee, Knoxville
    Univ. of California, Berkeley
    Univ. of Colorado, Denver
    @date January 2014

    Purpose
    =======

    SGETRI computes the inverse of a matrix using the LU factorization
    computed by SGETRF. This method inverts U and then computes inv(A) by
    solving the system inv(A)*L = inv(U) for inv(A).

    Note that it is generally both faster and more accurate to use SGESV,
    or SGETRF and SGETRS, to solve the system AX = B, rather than inverting
    the matrix and multiplying to form X = inv(A)*B. Only in special
    instances should an explicit inverse be computed with this routine.

    Arguments
    =========

    N       (input) INTEGER
    The order of the matrix A.  N >= 0.

    dA      (input/output) REAL array on the GPU, dimension (LDA,N)
    On entry, the factors L and U from the factorization
    A = P*L*U as computed by SGETRF_GPU.
    On exit, if INFO = 0, the inverse of the original matrix A.

    LDA     (input) INTEGER
    The leading dimension of the array A.  LDA >= std::max(1,N).

    IPIV    (input) INTEGER array, dimension (N)
    The pivot indices from SGETRF; for 1<=i<=N, row i of the
    matrix was interchanged with row IPIV(i).

    DWORK    (workspace/output) REAL array on the GPU, dimension (MAX(1,LWORK))

    LWORK   (input) INTEGER
    The dimension of the array DWORK.  LWORK >= N*NB, where NB is
    the optimal blocksize returned by magma_get_sgetri_nb(n).

    Unlike LAPACK, this version does not currently support a
    workspace query, because the workspace is on the GPU.

    INFO    (output) INTEGER
    = 0:  successful exit
    < 0:  if INFO = -i, the i-th argument had an illegal value
    > 0:  if INFO = i, U(i,i) is exactly zero; the matrix is
    singular and its cannot be computed.

    ===================================================================== */

    /* Local variables */
    float c_one     = MAGMA_S_ONE;
    float c_neg_one = MAGMA_S_NEG_ONE;
    magmaFloat_ptr dL = dwork;
    magma_int_t     ldl = n;
    size_t dL_offset = dwork_offset;
    magma_int_t      nb = magma_get_sgetri_nb(n);
    magma_int_t j, jmax, jb, jp;

    *info = 0;
    if (n < 0)
        *info = -1;
    else if (lda < std::max(1,n))
        *info = -3;
    else if ( lwork < n*nb )
        *info = -6;

    if (*info != 0) {
        magma_xerbla( __func__, -(*info) );
        return *info;
    }

    /* Quick return if possible */
    if ( n == 0 )
        return *info;

    /* Invert the triangular factor U */
    magma_strtri_gpu( MagmaUpper, MagmaNonUnit, n, dA, 0, lda, info);
    if ( *info != 0 )
        return *info;

    jmax = ((n-1) / nb)*nb;
    for( j = jmax; j >= 0; j -= nb ) {
        jb = std::min( nb, n-j );

        // copy current block column of L to work space,
        // then replace with zeros in A.
        magmablas_slacpy( MagmaFull, n-j, jb,
                dA(j, j), lda,
                dL(j, 0), ldl, queue );
        magmablas_slaset( MagmaLower, n-j, jb, dA(j, j), lda, queue );

        // compute current block column of Ainv
        // Ainv(:, j:j+jb-1)
        //   = ( U(:, j:j+jb-1) - Ainv(:, j+jb:n) L(j+jb:n, j:j+jb-1) )
        //   * L(j:j+jb-1, j:j+jb-1)^{-1}
        // where L(:, j:j+jb-1) is stored in dL.
        if ( j+jb < n ) {
            magma_sgemm( MagmaNoTrans, MagmaNoTrans, n, jb, n-j-jb,
                    c_neg_one, dA(0, (j+jb)), lda,
                    dL((j+jb), 0), ldl,
                    c_one,     dA(0, j), lda, queue );
        }
        magma_strsm( MagmaRight, MagmaLower, MagmaNoTrans, MagmaUnit,
                n, jb, c_one,
                dL(j, 0), ldl,
                dA(0, j), lda, queue );
    }

    // Apply column interchanges
    for( j = n-2; j >= 0; --j ) {
        jp = ipiv[j] - 1;
        if ( jp != j ) {
            magmablas_sswap( n, dA(0, j), 1, dA(0, jp), 1, queue );
            magma_queue_sync(queue);
        }
    }

    return *info;
}

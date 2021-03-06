/*
    -- clMAGMA (version 1.1.0) --
       Univ. of Tennessee, Knoxville
       Univ. of California, Berkeley
       Univ. of Colorado, Denver
       @date January 2014
                                                                                                              
       @generated from zgesv_gpu.cpp normal z -> c, Fri Jan 10 15:51:17 2014
*/

#include <cstdio>
#include "common_magma.h"


extern "C" magma_err_t
magma_cgesv_gpu( magma_int_t n, magma_int_t nrhs,
                 magmaFloatComplex_ptr dA, size_t dA_offset, magma_int_t ldda,
                 magma_int_t *ipiv,
                 magmaFloatComplex_ptr dB, size_t dB_offset, magma_int_t lddb,
                 magma_err_t *info, magma_queue_t queue )
{
/*  -- clMagma (version 0.1) --
       Univ. of Tennessee, Knoxville
       Univ. of California, Berkeley
       Univ. of Colorado, Denver
       @date January 2014

    Purpose
    =======

    Solves a system of linear equations
       A * X = B
    where A is a general N-by-N matrix and X and B are N-by-NRHS matrices.
    The LU decomposition with partial pivoting and row interchanges is
    used to factor A as
       A = P * L * U,
    where P is a permutation matrix, L is unit lower triangular, and U is
    upper triangular.  The factored form of A is then used to solve the
    system of equations A * X = B.

    Arguments
    =========

    N       (input) INTEGER
            The order of the matrix A.  N >= 0.

    NRHS    (input) INTEGER
            The number of right hand sides, i.e., the number of columns
            of the matrix B.  NRHS >= 0.

    A       (input/output) COMPLEX array on the GPU, dimension (LDDA,N).
            On entry, the M-by-N matrix to be factored.
            On exit, the factors L and U from the factorization
            A = P*L*U; the unit diagonal elements of L are not stored.

    LDA     (input) INTEGER
            The leading dimension of the array A.  LDA >= std::max(1,N).

    IPIV    (output) INTEGER array, dimension (std::min(M,N))
            The pivot indices; for 1 <= i <= std::min(M,N), row i of the
            matrix was interchanged with row IPIV(i).

    B       (input/output) COMPLEX array on the GPU, dimension (LDB,NRHS)
            On entry, the right hand side matrix B.
            On exit, the solution matrix X.

    LDB     (input) INTEGER
            The leading dimension of the array B.  LDB >= std::max(1,N).

    INFO    (output) INTEGER
            = 0:  successful exit
            < 0:  if INFO = -i, the i-th argument had an illegal value
    =====================================================================    */

    magma_err_t ret;

    *info = 0;
    if (n < 0) {
        *info = -1;
    } else if (nrhs < 0) {
        *info = -2;
    } else if (ldda < std::max(1,n)) {
        *info = -4;
    } else if (lddb < std::max(1,n)) {
        *info = -7;
    }
    if (*info != 0) {
        magma_xerbla( __func__, -(*info) );
        return *info;
    }

    /* Quick return if possible */
    if (n == 0 || nrhs == 0) {
        return *info;
    }

    ret = magma_cgetrf_gpu( n, n, dA, dA_offset, ldda, ipiv, info, queue);
    if ( (ret != MAGMA_SUCCESS) || (*info != 0) ) {
        return ret;
    }

    ret = magma_cgetrs_gpu( MagmaNoTrans, n, nrhs, dA, dA_offset, ldda, ipiv, dB, dB_offset, lddb, info, queue );
    
    return ret;
}

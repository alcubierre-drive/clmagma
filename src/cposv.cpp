/*
    -- clMAGMA (version 1.1.0) --
       Univ. of Tennessee, Knoxville
       Univ. of California, Berkeley
       Univ. of Colorado, Denver
       @date January 2014

       @generated from zposv.cpp normal z -> c, Fri Jan 10 15:51:17 2014

*/
#include "common_magma.h"

extern "C" magma_int_t
magma_cposv    ( magma_uplo_t uplo, magma_int_t n, magma_int_t nrhs,
                 magmaFloatComplex *A, magma_int_t lda,
                 magmaFloatComplex *B, magma_int_t ldb, magma_int_t *info,
                 magma_queue_t *queue )
{
/*  -- clMAGMA (version 1.1.0) --
       Univ. of Tennessee, Knoxville
       Univ. of California, Berkeley
       Univ. of Colorado, Denver
       @date January 2014

    Purpose
    =======
    CPOSV computes the solution to a complex system of linear equations
       A * X = B,
    where A is an N-by-N Hermitian positive definite matrix and X and B
    are N-by-NRHS matrices.
    The Cholesky decomposition is used to factor A as
       A = U**H * U,  if UPLO = 'U', or
       A = L * L**H,  if UPLO = 'L',
    where U is an upper triangular matrix and  L is a lower triangular
    matrix.  The factored form of A is then used to solve the system of
    equations A * X = B.

    Arguments
    =========
    UPLO    (input) CHARACTER*1
            = 'U':  Upper triangle of A is stored;
            = 'L':  Lower triangle of A is stored.

    N       (input) INTEGER
            The order of the matrix A.  N >= 0.

    NRHS    (input) INTEGER
            The number of right hand sides, i.e., the number of columns
            of the matrix B.  NRHS >= 0.

    A       (input/output) COMPLEX array, dimension (LDA,N)
            On entry, the Hermitian matrix A.  If UPLO = 'U', the leading
            N-by-N upper triangular part of A contains the upper
            triangular part of the matrix A, and the strictly lower
            triangular part of A is not referenced.  If UPLO = 'L', the
            leading N-by-N lower triangular part of A contains the lower
            triangular part of the matrix A, and the strictly upper
            triangular part of A is not referenced.

            On exit, if INFO = 0, the factor U or L from the Cholesky
            factorization A = U**H*U or A = L*L**H.

    LDA     (input) INTEGER
            The leading dimension of the array A.  LDA >= std::max(1,N).

    B       (input/output) COMPLEX array, dimension (LDB,NRHS)
            On entry, the right hand side matrix B.
            On exit, the solution matrix X.

    LDB     (input) INTEGER
            The leading dimension of the array B.  LDB >= std::max(1,N).

    INFO    (output) INTEGER
            = 0:  successful exit
            < 0:  if INFO = -i, the i-th argument had an illegal value
    =====================================================================   */

    magma_int_t num_gpus, ldda, lddb;

    *info = 0 ;
    if( (uplo != MagmaUpper) && (uplo != MagmaLower) )
        *info = -1;
    if( n < 0 )
        *info = -2;
    if( nrhs < 0)
        *info = -3;
    if ( lda < std::max(1, n) )
        *info = -5;
    if ( ldb < std::max(1, n) )
        *info = -7;
    if (*info != 0) {
        magma_xerbla( __func__, -(*info) );
        return *info;
    }

    /* Quick return if possible */
    if ( (n==0) || (nrhs == 0) ) {
        return *info;
    }

    /* If single-GPU and allocation suceeds, use GPU interface. */
    num_gpus = magma_num_gpus();
    magmaFloatComplex_ptr dA, dB;
    if ( num_gpus > 1 ) {
        goto CPU_INTERFACE;
    }
    ldda = ((n+31)/32)*32;
    lddb = ldda;
    if ( MAGMA_SUCCESS != magma_cmalloc( &dA, ldda*n )) {
        goto CPU_INTERFACE;
    }
    if ( MAGMA_SUCCESS != magma_cmalloc( &dB, (lddb*nrhs) )) {
        magma_free( dA );
        goto CPU_INTERFACE;
    }
    chk( magma_csetmatrix( n, n, A, 0, lda, dA, 0, ldda, queue[0] ) );
    magma_cpotrf2_gpu( uplo, n, dA, 0, ldda, info, queue );
    if ( *info == MAGMA_ERR_DEVICE_ALLOC ) {
        magma_free( dA );
        magma_free( dB );
        goto CPU_INTERFACE;
    }
    chk ( magma_cgetmatrix( n, n, dA, 0, ldda, A, 0, lda, queue[0] ) );
    if ( *info == 0 ) {
        chk( magma_csetmatrix( n, nrhs, B, 0, ldb, dB, 0, lddb, queue[0] ));
        magma_cpotrs_gpu( uplo, n, nrhs, dA, 0, ldda, dB, 0, lddb, info, queue[0] );
        chk( magma_cgetmatrix( n, nrhs, dB, 0, lddb, B, 0, ldb, queue[0] ));
    }
    magma_free( dA );
    magma_free( dB );
    return *info;

CPU_INTERFACE:
    /* If multi-GPU or allocation failed, use CPU interface and LAPACK.
     * Faster to use LAPACK for potrs than to copy A to GPU. */
    magma_cpotrf( uplo, n, A, lda, info, queue );
    if ( *info == 0 ) {
         lapackf77_cpotrs( lapack_uplo_const(uplo), &n, &nrhs, A, &lda, B, &ldb, info );
    }

    return *info;
}

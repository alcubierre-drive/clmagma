/*
   -- clMAGMA (version 1.1.0) --
   Univ. of Tennessee, Knoxville
   Univ. of California, Berkeley
   Univ. of Colorado, Denver
   @date January 2014

   @generated from ztrtri_gpu.cpp normal z -> s, Fri Jan 10 15:51:17 2014

 */

#include <cstdio>
#include "common_magma.h"


#define dA(i, j) dA, (dA_offset + (j)*ldda + (i))

extern "C" magma_int_t
magma_strtri_gpu(magma_uplo_t uplo, magma_diag_t diag, magma_int_t n,
        magmaFloat_ptr dA, size_t dA_offset, magma_int_t ldda, magma_int_t *info)
{
/*  -- clMAGMA (version 1.1.0) --
    Univ. of Tennessee, Knoxville
    Univ. of California, Berkeley
    Univ. of Colorado, Denver
    @date January 2014

    Purpose
    =======

    STRTRI computes the inverse of a real upper or lower triangular
    matrix dA.

    This is the Level 3 BLAS version of the algorithm.

    Arguments
    =========

    UPLO    (input) CHARACTER*1
    = 'U':  A is upper triangular;
    = 'L':  A is lower triangular.

    DIAG    (input) CHARACTER*1
    = 'N':  A is non-unit triangular;
    = 'U':  A is unit triangular.

    N       (input) INTEGER
    The order of the matrix A.  N >= 0.

    dA       (input/output) REAL array ON THE GPU, dimension (LDDA,N)
    On entry, the triangular matrix A.  If UPLO = 'U', the
    leading N-by-N upper triangular part of the array dA contains
    the upper triangular matrix, and the strictly lower
    triangular part of A is not referenced.  If UPLO = 'L', the
    leading N-by-N lower triangular part of the array dA contains
    the lower triangular matrix, and the strictly upper
    triangular part of A is not referenced.  If DIAG = 'U', the
    diagonal elements of A are also not referenced and are
    assumed to be 1.
    On exit, the (triangular) inverse of the original matrix, in
    the same storage format.

    LDDA     (input) INTEGER
    The leading dimension of the array dA.  LDDA >= std::max(1,N).
    INFO    (output) INTEGER
    = 0: successful exit
    < 0: if INFO = -i, the i-th argument had an illegal value
    > 0: if INFO = i, dA(i,i) is exactly zero.  The triangular
    matrix is singular and its inverse can not be computed.

    ===================================================================== */

    /* Local variables */
    magma_uplo_t uplo_ = uplo;
    magma_diag_t diag_ = diag;
    magma_int_t         nb, nn, j, jb;
    float     c_one      = MAGMA_S_ONE;
    float     c_neg_one  = MAGMA_S_NEG_ONE;
    float     *work;

    int upper  = lapackf77_lsame(lapack_const(uplo_), lapack_const(MagmaUpper));
    int nounit = lapackf77_lsame(lapack_const(diag_), lapack_const(MagmaNonUnit));

    *info = 0;

    if ((! upper) && (! lapackf77_lsame(lapack_const(uplo_), lapack_const(MagmaLower))))
        *info = -1;
    else if ((! nounit) && (! lapackf77_lsame(lapack_const(diag_), lapack_const(MagmaUnit))))
        *info = -2;
    else if (n < 0)
        *info = -3;
    else if (ldda < std::max(1,n))
        *info = -5;

    if (*info != 0) {
        magma_xerbla( __func__, -(*info) );
        return *info;
    }

    nb = magma_get_spotrf_nb(n);

    /* Create Queues */
    magma_queue_t  queues[2];
    magma_device_t device[MagmaMaxGPUs];
    int num = 0;
    magma_err_t err;

    err = magma_get_devices( device, MagmaMaxGPUs, &num );
    if ( err != 0 || num < 1 ) {
        fprintf( stderr, "magma_get_devices failed: %d\n", err );
        exit(-1);
    }
    err = magma_queue_create( device[0], &queues[0] );
    if ( err != 0 ) {
        fprintf( stderr, "magma_queue_create 0 failed: %d\n", err );
        exit(-1);
    }
    err = magma_queue_create( device[0], &queues[1] );
    if ( err != 0 ) {
        fprintf( stderr, "magma_queue_create 1 failed: %d\n", err );
        exit(-1);
    }

    if (MAGMA_SUCCESS != magma_smalloc_cpu( &work, nb*nb )) {
        *info = MAGMA_ERR_HOST_ALLOC;
        return *info;
    }

    if (nb <= 1 || nb >= n) {
        magma_sgetmatrix( n, n, dA, dA_offset, ldda, work, 0, n, queues[0] );
        lapackf77_strtri(lapack_const(uplo_), lapack_const(diag_), &n, work, &n, info);
        magma_ssetmatrix( n, n, work, 0, n, dA, dA_offset, ldda, queues[0] );
    }
    else {
        if (upper) {
            /* Compute inverse of upper triangular matrix */
            for (j=0; j<n; j =j+ nb){
                jb = std::min(nb, (n-j));

                /* Compute rows 1:j-1 of current block column */
                magma_strmm(MagmaLeft, MagmaUpper,
                        MagmaNoTrans, MagmaNonUnit, j, jb,
                        c_one, dA(0,0), ldda, dA(0, j), ldda,
                        queues[0]);

                magma_strsm(MagmaRight, MagmaUpper,
                        MagmaNoTrans, MagmaNonUnit, j, jb,
                        c_neg_one, dA(j,j), ldda, dA(0, j), ldda,
                        queues[0]);
    
                magma_sgetmatrix_async( jb, jb,
                        dA(j, j), ldda,
                        work, 0, jb, queues[1], NULL );
                
                magma_queue_sync( queues[1] );

                /* Compute inverse of current diagonal block */
                lapackf77_strtri(MagmaUpperStr, lapack_const(diag_), &jb, work, &jb, info);
                /*
                magma_ssetmatrix_async( jb, jb,
                        work, 0, jb,
                        dA(j, j), ldda, queues[0], NULL );
                */
                magma_ssetmatrix( jb, jb,
                        work, 0, jb,
                        dA(j, j), ldda, queues[0]);
            }
        }
        else {
            /* Compute inverse of lower triangular matrix */
            nn=((n-1)/nb)*nb+1;

            for(j=nn-1; j>=0; j=j-nb){
                jb=std::min(nb,(n-j));

                if((j+jb) < n){
                    /* Compute rows j+jb:n of current block column */
                    magma_strmm(MagmaLeft, MagmaLower,
                            MagmaNoTrans, MagmaNonUnit, (n-j-jb), jb,
                            c_one, dA(j+jb,j+jb), ldda, dA(j+jb, j), ldda,
                            queues[0]);

                    magma_strsm(MagmaRight, MagmaLower,
                            MagmaNoTrans, MagmaNonUnit, (n-j-jb), jb,
                            c_neg_one, dA(j,j), ldda, dA(j+jb, j), ldda,
                            queues[0]);
                }
                magma_sgetmatrix_async( jb, jb,
                        dA(j, j), ldda,
                        work, 0, jb, queues[1], NULL );
                
                magma_queue_sync( queues[1] );

                /* Compute inverse of current diagonal block */
                lapackf77_strtri(MagmaLowerStr, lapack_const(diag_), &jb, work, &jb, info);
                /*
                magma_ssetmatrix_async( jb, jb,
                        work, 0, jb,
                        dA(j, j), ldda, queues[0], NULL );
                */
                magma_ssetmatrix( jb, jb,
                        work, 0, jb,
                        dA(j, j), ldda, queues[0] );
            }
        }
    }

    magma_free_cpu( work );
    magma_queue_destroy(queues[0]);
    magma_queue_destroy(queues[1]);
    return *info;
}

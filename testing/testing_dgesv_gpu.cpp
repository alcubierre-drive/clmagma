/*
 *  -- clMAGMA (version 1.1.0) --
 *     Univ. of Tennessee, Knoxville
 *     Univ. of California, Berkeley
 *     Univ. of Colorado, Denver
 *     @date January 2014
 *
 * @generated from testing_zgesv_gpu.cpp normal z -> d, Fri Jan 10 15:51:19 2014
 *
 **/
// includes, system
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>

// includes, project
#include "flops.h"
#include "magma.h"
#include "magma_lapack.h"
#include "testings.h"

#define PRECISION_d
// Flops formula
#if defined(PRECISION_z) || defined(PRECISION_c)
#define FLOPS_GETRF(m, n   ) ( 6.*FMULS_GETRF(m, n   ) + 2.*FADDS_GETRF(m, n   ) )
#define FLOPS_GETRS(m, nrhs) ( 6.*FMULS_GETRS(m, nrhs) + 2.*FADDS_GETRS(m, nrhs) )
#else
#define FLOPS_GETRF(m, n   ) (    FMULS_GETRF(m, n   ) +    FADDS_GETRF(m, n   ) )
#define FLOPS_GETRS(m, nrhs) (    FMULS_GETRS(m, nrhs) +    FADDS_GETRS(m, nrhs) )
#endif


/* ////////////////////////////////////////////////////////////////////////////
   -- Testing dgesv_gpu
*/
int main(int argc , char **argv)
{
    real_Double_t gflops, gpu_perf, gpu_time;
    double Rnorm, Anorm, Xnorm, *work;
    double *hA, *hB, *hX;
    magmaDouble_ptr dA, dB;
    magma_int_t     *ipiv;
    magma_int_t N = 0, n2, lda, ldb, ldda, lddb;
    magma_int_t size[7] =
        { 1024, 2048, 3072, 4032, 5184, 6048, 7000};
    
    magma_int_t i, info, szeB;
    double z_one = MAGMA_D_ONE;
    double mz_one = MAGMA_D_NEG_ONE;
    magma_int_t ione     = 1;
    magma_int_t ISEED[4] = {0,0,0,1};
    magma_int_t NRHS = 100;
    
    if (argc != 1){
        for(i = 1; i<argc; i++){
            if (strcmp("-N", argv[i])==0)
                N = atoi(argv[++i]);
            if (strcmp("-R", argv[i])==0)
                NRHS = atoi(argv[++i]);
        }
        if (N>0) size[0] = size[6] = N;
        else exit(1);
    }
    else {
        printf("\nUsage: \n");
        printf("  testing_dgesv_gpu -N <matrix size> -R <right hand sides>\n\n");
    }
    
    /* Initialize */
    magma_queue_t  queue;
    magma_device_t device[ MagmaMaxGPUs ];
    int num = 0;
    magma_err_t err;
    magma_init();
    err = magma_get_devices( device, MagmaMaxGPUs, &num );
    if ( err != 0 || num < 1 ) {
        fprintf( stderr, "magma_get_devices failed: %d\n", err );
        exit(-1);
    }
    err = magma_queue_create( device[0], &queue );
    if ( err != 0 ) {
        fprintf( stderr, "magma_queue_create failed: %d\n", err );
        exit(-1);
    }
    
    /* Allocate memory for the largest matrix */
    N    = size[6];
    n2   = N * N;
    ldda = ((N+31)/32) * 32;
   // ldda = N;
    lddb = ldda;
    TESTING_MALLOC_PIN( ipiv, magma_int_t,        N         );
    TESTING_MALLOC_PIN( hA,   double, n2        );
    TESTING_MALLOC_PIN( hB,   double, N*NRHS    );
    TESTING_MALLOC_PIN( hX,   double, N*NRHS    );
    TESTING_MALLOC_PIN( work, double,             N         );
    TESTING_MALLOC_DEV( dA,   double, ldda*N    );
    TESTING_MALLOC_DEV( dB,   double, lddb*NRHS );

    printf("\n\n");
    printf("    N   NRHS   GPU GFlop/s (sec)   ||B - AX|| / ||A||*||X||\n");
    printf("===========================================================\n");
    for( i = 0; i < 7; i++ ) {
        N   = size[i];
        lda = N;
        ldb = lda;
        n2  = lda*N;
        szeB = ldb*NRHS;
        ldda = ((N+31)/32)*32;
        //ldda = N;
        lddb = ldda;
        gflops = ( FLOPS_GETRF( (double)N, (double)N ) +
                  FLOPS_GETRS( (double)N, (double)NRHS ) ) / 1e9;

        /* Initialize the matrices */
        lapackf77_dlarnv( &ione, ISEED, &n2, hA );
        lapackf77_dlarnv( &ione, ISEED, &szeB, hB );

        /* Warm up to measure the performance */
        magma_dsetmatrix( N, N, hA, 0, lda, dA, 0, ldda, queue );
        magma_dsetmatrix( N, NRHS, hB, 0, lda, dB, 0, lddb, queue );
        magma_dgesv_gpu( N, NRHS, dA, 0, ldda, ipiv, dB, 0, lddb, &info, queue );

        //=====================================================================
        // Solve Ax = b through an LU factorization
        //=====================================================================
        magma_dsetmatrix( N, N, hA, 0, lda, dA, 0, ldda, queue );
        magma_dsetmatrix( N, NRHS, hB, 0, lda, dB, 0, lddb, queue );
        gpu_time = magma_wtime();
        magma_dgesv_gpu( N, NRHS, dA, 0, ldda, ipiv, dB, 0, lddb, &info, queue );
        gpu_time = magma_wtime() - gpu_time;
        if (info != 0)
            printf( "magma_dposv had error %d.\n", info );

        gpu_perf = gflops / gpu_time;

        /* =====================================================================
           Residual
           =================================================================== */
        magma_dgetmatrix( N, NRHS, dB, 0, lddb, hX, 0, ldb, queue );
        Anorm = lapackf77_dlange("I", &N, &N,    hA, &lda, work);
        Xnorm = lapackf77_dlange("I", &N, &NRHS, hX, &ldb, work);

        blasf77_dgemm( MagmaNoTransStr, MagmaNoTransStr, &N, &NRHS, &N,
                        &z_one,  hA, &lda,
                        hX, &ldb,
                        &mz_one, hB, &ldb );

        Rnorm = lapackf77_dlange("I", &N, &NRHS, hB, &ldb, work);

        printf( "%5d  %5d   %7.2f (%7.2f)   %8.2e\n",
                N, NRHS, gpu_perf, gpu_time, Rnorm/(Anorm*Xnorm) );

        if (argc != 1)
            break;
    }

    /* clean up */
    TESTING_FREE_PIN( hA );
    TESTING_FREE_PIN( hB );
    TESTING_FREE_PIN( hX );
    TESTING_FREE_PIN( work );
    TESTING_FREE_PIN( ipiv );
    TESTING_FREE_DEV( dA );
    TESTING_FREE_DEV( dB );
    magma_queue_destroy( queue );
    magma_finalize();
}

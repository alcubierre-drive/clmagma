/*
    -- clMAGMA (version 1.1.0) --
       Univ. of Tennessee, Knoxville
       Univ. of California, Berkeley
       Univ. of Colorado, Denver
       @date January 2014

       @precisions normal z -> s d c
*/
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

/* ////////////////////////////////////////////////////////////////////////////
   -- Testing zgeqrf
*/
int main( int argc, char** argv)
{
    real_Double_t    gflops, gpu_perf, gpu_time, cpu_perf=0, cpu_time=0;
    double           error, work[1];
    magmaDoubleComplex  c_neg_one = MAGMA_Z_NEG_ONE;
    magmaDoubleComplex *h_A, *h_R, *tau, *h_work, tmp[1];
    magma_int_t M, N, n2, lda, lwork, info, min_mn, nb;
    magma_int_t ione     = 1;
    magma_int_t ISEED[4] = {0,0,0,1}, ISEED2[4];
    
    /* Initialize */
    magma_queue_t  queue[2];
    magma_device_t devices[MagmaMaxGPUs];
    int num = 0;
    magma_err_t err;
    magma_init();

    magma_opts opts;
    parse_opts( argc, argv, &opts );

    magma_int_t status = 0;
    double tol, eps = lapackf77_dlamch("E");
    tol = opts.tolerance * eps;

    opts.lapack |= ( opts.check == 2 );  // check (-c2) implies lapack (-l)

    err = magma_get_devices( devices, MagmaMaxGPUs, &num );
    if ( err != 0 || num < 1 ) {
      fprintf( stderr, "magma_get_devices failed: %d\n", err );
      exit(-1);
    }

    // Create two queues on device opts.device
    err = magma_queue_create( devices[opts.device], &queue[0] );
    if ( err != 0 ) {
      fprintf( stderr, "magma_queue_create failed: %d\n", err );
      exit(-1);
    }
    err = magma_queue_create( devices[opts.device], &queue[1] );
    if ( err != 0 ) {
      fprintf( stderr, "magma_queue_create failed: %d\n", err );
      exit(-1);
    }
    
    printf("ngpu %d\n", (int) opts.ngpu );
    if ( opts.check == 1 ) {
        printf("  M     N     CPU GFlop/s (sec)   GPU GFlop/s (sec)   ||R-Q'A||_1 / (M*||A||_1) ||I-Q'Q||_1 / M\n");
        printf("===============================================================================================\n");
    } else {
        printf("  M     N     CPU GFlop/s (sec)   GPU GFlop/s (sec)   ||R||_F / ||A||_F\n");
        printf("=======================================================================\n");
    }
    for( int i = 0; i < opts.ntest; ++i ) {
        for( int iter = 0; iter < opts.niter; ++iter ) {
            M = opts.msize[i];
            N = opts.nsize[i];
            min_mn = std::min(M, N);
            lda    = M;
            n2     = lda*N;
            nb     = magma_get_zgeqrf_nb(M);
            gflops = FLOPS_ZGEQRF( M, N ) / 1e9;
            
            lwork = -1;
            lapackf77_zgeqrf(&M, &N, h_A, &M, tau, tmp, &lwork, &info);
            lwork = (magma_int_t)MAGMA_Z_REAL( tmp[0] );
            lwork = std::max( lwork, std::max( N*nb, 2*nb*nb ));
            
            TESTING_MALLOC_CPU( tau,    magmaDoubleComplex, min_mn );
            TESTING_MALLOC_CPU( h_A,    magmaDoubleComplex, n2     );
            TESTING_MALLOC_PIN( h_R,    magmaDoubleComplex, n2     );
            TESTING_MALLOC_CPU( h_work, magmaDoubleComplex, lwork  );
            
            /* Initialize the matrix */
            for ( int j=0; j<4; j++ ) ISEED2[j] = ISEED[j]; // saving seeds
            lapackf77_zlarnv( &ione, ISEED, &n2, h_A );
            lapackf77_zlacpy( MagmaUpperLowerStr, &M, &N, h_A, &lda, h_R, &lda );
            
            /* ====================================================================
               Performs operation using MAGMA
               =================================================================== */
            gpu_time = magma_wtime();
            magma_zgeqrf(M, N, h_R, lda, tau, h_work, lwork, &info, queue);
            gpu_time = magma_wtime() - gpu_time;
            gpu_perf = gflops / gpu_time;
            if (info != 0)
                printf("magma_zgeqrf returned error %d: %s.\n",
                       (int) info, magma_strerror( info ));
            
            if ( opts.lapack ) {
                /* =====================================================================
                   Performs operation using LAPACK
                   =================================================================== */
                magmaDoubleComplex *tau;
                TESTING_MALLOC_CPU( tau, magmaDoubleComplex, min_mn );
                cpu_time = magma_wtime();
                lapackf77_zgeqrf(&M, &N, h_A, &lda, tau, h_work, &lwork, &info);
                cpu_time = magma_wtime() - cpu_time;
                cpu_perf = gflops / cpu_time;
                if (info != 0)
                    printf("lapackf77_zgeqrf returned error %d: %s.\n",
                           (int) info, magma_strerror( info ));
                TESTING_FREE_CPU( tau );
            }

            if ( opts.check == 1 ) {
                /* =====================================================================
                   Check the result 
                   =================================================================== */
                magma_int_t lwork = n2+N;
                magmaDoubleComplex *h_W1, *h_W2, *h_W3;
                double *h_RW, results[2];

                TESTING_MALLOC_CPU( h_W1, magmaDoubleComplex, n2 ); // Q
                TESTING_MALLOC_CPU( h_W2, magmaDoubleComplex, n2 ); // R
                TESTING_MALLOC_CPU( h_W3, magmaDoubleComplex, lwork ); // WORK
                TESTING_MALLOC_CPU( h_RW, double, M );  // RWORK
                lapackf77_zlarnv( &ione, ISEED2, &n2, h_A );
                lapackf77_zqrt02( &M, &N, &min_mn, h_A, h_R, h_W1, h_W2, &lda, tau, h_W3, &lwork,
                                  h_RW, results );
                results[0] *= eps;
                results[1] *= eps;

                if ( opts.lapack ) {
                    printf("%5d %5d   %7.2f (%7.2f)   %7.2f (%7.2f)   %8.2e                  %8.2e",
                           (int) M, (int) N, cpu_perf, cpu_time, gpu_perf, gpu_time, results[0],results[1] );
                    printf("%s\n", (results[0] < tol ? "" : "  failed"));
                } else {
                    printf("%5d %5d     ---   (  ---  )   %7.2f (%7.2f)    %8.2e                  %8.2e",
                           (int) M, (int) N, gpu_perf, gpu_time, results[0],results[1] );
                    printf("%s\n", (results[0] < tol ? "" : "  failed"));
                }
                status |= ! (results[0] < tol);

                TESTING_FREE_CPU( h_W1 );
                TESTING_FREE_CPU( h_W2 );
                TESTING_FREE_CPU( h_W3 );
                TESTING_FREE_CPU( h_RW );
            } else if ( opts.check == 2 ) {
                /* =====================================================================
                   Check the result compared to LAPACK
                   =================================================================== */
                error = lapackf77_zlange("f", &M, &N, h_A, &lda, work);
                blasf77_zaxpy(&n2, &c_neg_one, h_A, &ione, h_R, &ione);
                error = lapackf77_zlange("f", &M, &N, h_R, &lda, work) / error;
                
                if ( opts.lapack ) {
                    printf("%5d %5d   %7.2f (%7.2f)   %7.2f (%7.2f)   %8.2e",
                           (int) M, (int) N, cpu_perf, cpu_time, gpu_perf, gpu_time, error );
                } else {
                    printf("%5d %5d     ---   (  ---  )   %7.2f (%7.2f)    %8.2e",
                           (int) M, (int) N, gpu_perf, gpu_time, error );
                }
                printf("%s\n", (error < tol ? "" : "  failed"));
                status |= ! (error < tol);
            }
            else {
                if ( opts.lapack ) {
                    printf("%5d %5d   %7.2f (%7.2f)   %7.2f (%7.2f)   ---\n",
                           (int) M, (int) N, cpu_perf, cpu_time, gpu_perf, gpu_time );
                } else {
                    printf("%5d %5d     ---   (  ---  )   %7.2f (%7.2f)     ---  \n",
                           (int) M, (int) N, gpu_perf, gpu_time);
                }
            }
            
            TESTING_FREE_CPU( tau );
            TESTING_FREE_CPU( h_A );
            TESTING_FREE_CPU( h_work );
            TESTING_FREE_PIN( h_R );
        }
        if ( opts.niter > 1 ) {
            printf( "\n" );
        }
    }

    magma_queue_destroy( queue[0] );
    magma_queue_destroy( queue[1] );
    magma_finalize();

    return status;
}

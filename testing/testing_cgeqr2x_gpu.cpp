/*
    -- clMAGMA (version 1.1.0) --
       Univ. of Tennessee, Knoxville
       Univ. of California, Berkeley
       Univ. of Colorado, Denver
       @date January 2014

       @generated from testing_zgeqr2x_gpu.cpp normal z -> c, Fri Jan 10 15:51:20 2014

*/

// includes, system
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cassert>
#include <cstdarg>

// includes, project
#include "flops.h"
#include "magma.h"
#include "magma_lapack.h"
#include "testings.h"
#include "common_magma.h"


// --------------------
// If condition is false, print error message and exit.
// Error message is formatted using printf, using any additional arguments.
extern "C"
void magma_assert( bool condition, const char* msg, ... )
{
    if ( ! condition ) {
        va_list va;
        va_start( va, msg );
        vprintf( msg, va );
        exit(1);
    }
}

extern "C" magma_err_t 
magma_cgeqr2x3_gpu(magma_int_t *m, magma_int_t *n, 
        magmaFloatComplex_ptr dA, size_t dA_offset, magma_int_t *ldda, 
        magmaFloatComplex_ptr dtau, size_t dtau_offset, 
        magmaFloatComplex_ptr dT, size_t dT_offset, 
        magmaFloatComplex_ptr ddA, size_t ddA_offset, 
        magmaFloat_ptr dwork, size_t dwork_offset, 
        magma_int_t *info, magma_queue_t queue);

/* ////////////////////////////////////////////////////////////////////////////
   -- Testing cgeqrf
*/
int main( int argc, char** argv)
{
    real_Double_t    gflops, gpu_perf, gpu_time, cpu_perf, cpu_time;
    float           error, work[1];
    magmaFloatComplex  c_neg_one = MAGMA_C_NEG_ONE;
    magmaFloatComplex *h_A, *h_T, *h_R, *tau, *h_work, tmp[1];
    magmaFloatComplex_ptr d_A, d_T, ddA, dtau;
    magmaFloat_ptr dwork;

    /* Matrix size */
    magma_int_t M = 0, N = 0, n2, lda, ldda, lwork;
    const int MAXTESTS = 10;
    magma_int_t msize[MAXTESTS] = { 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 8100, 8192 };
    magma_int_t nsize[MAXTESTS] = { 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 8100, 8192 };

    magma_int_t i, info, min_mn;
    magma_int_t ione     = 1;
    //magma_int_t ISEED[4] = {0,0,0,1};
    magma_int_t checkres;

    checkres = getenv("MAGMA_TESTINGS_CHECK") != NULL;

    // process command line arguments
    printf( "\nUsage: %s -N <m,n> -c\n", argv[0] );
    printf( "  -N can be repeated up to %d times. If only m is given, then m=n.\n", MAXTESTS );
    printf( "  -c or setting $MAGMA_TESTINGS_CHECK runs LAPACK and checks result.\n\n" );
    int ntest = 0;
    for( int i = 1; i < argc; ++i ) {
        if ( strcmp("-N", argv[i]) == 0 && i+1 < argc ) {
            magma_assert( ntest < MAXTESTS, "error: -N repeated more than maximum %d tests\n", MAXTESTS );
            int m, n;
            info = sscanf( argv[++i], "%d,%d", &m, &n );
            if ( info == 2 && m > 0 && n > 0 ) {
                msize[ ntest ] = m;
                nsize[ ntest ] = n;
            }
            else if ( info == 1 && m > 0 ) {
                msize[ ntest ] = m;
                nsize[ ntest ] = m;  // implicitly
            }
            else {
                printf( "error: -N %s is invalid; ensure m > 0, n > 0.\n", argv[i] );
                exit(1);
            }
            M = std::max( M, msize[ ntest ] );
            N = std::max( N, nsize[ ntest ] );
            ntest++;
        }
        else if ( strcmp("-M", argv[i]) == 0 ) {
            printf( "-M has been replaced in favor of -N m,n to allow -N to be repeated.\n\n" );
            exit(1);
        }
        else if ( strcmp("-c", argv[i]) == 0 ) {
            checkres = true;
        }
        else {
            printf( "invalid argument: %s\n", argv[i] );
            exit(1);
        }
    }
    if ( ntest == 0 ) {
        ntest = MAXTESTS;
        M = msize[ntest-1];
        N = nsize[ntest-1];
    }

    ldda   = ((M+31)/32)*32;
    n2     = M * N;
    min_mn = std::min(M, N);

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

    /* Allocate memory for the matrix */
    TESTING_MALLOC_PIN( tau, magmaFloatComplex, min_mn );
    TESTING_MALLOC_PIN( h_A, magmaFloatComplex, n2     );
    TESTING_MALLOC_PIN( h_T, magmaFloatComplex, N*N    );
    TESTING_MALLOC_PIN( h_R, magmaFloatComplex, n2     );

    TESTING_MALLOC_DEV( d_A,  magmaFloatComplex, ldda*N );
    TESTING_MALLOC_DEV( d_T,  magmaFloatComplex, N*N    );
    TESTING_MALLOC_DEV( ddA,  magmaFloatComplex, N*N    );
    TESTING_MALLOC_DEV( dtau, magmaFloatComplex, min_mn );

    TESTING_MALLOC_DEV( dwork, float, std::max(5*min_mn, (32*2+2)*min_mn) );

    magmaFloatComplex *h1 = (magmaFloatComplex*)malloc(sizeof(magmaFloatComplex)*N*N);
    memset(h1, 0, N*N*sizeof(magmaFloatComplex));

    clEnqueueWriteBuffer(queue, ddA, CL_TRUE, 0, sizeof(magmaFloatComplex)*N*N, h1, 0, NULL, NULL);
    clEnqueueWriteBuffer(queue, d_T, CL_TRUE, 0, sizeof(magmaFloatComplex)*N*N, h1, 0, NULL, NULL);
    
    lwork = -1;
    lapackf77_cgeqrf(&M, &N, h_A, &M, tau, tmp, &lwork, &info);
    lwork = (magma_int_t)MAGMA_C_REAL( tmp[0] );
    lwork = std::max(lwork, N*N);

    TESTING_MALLOC_PIN( h_work, magmaFloatComplex, lwork );

    printf("  M     N     CPU GFlop/s (ms)    GPU GFlop/s (ms)   ||R||_F/||A||_F  ||R_T||\n");
    printf("=============================================================================\n");
    for( i = 0; i < ntest; ++i ) {
        M = msize[i];
        N = nsize[i];
        min_mn= std::min(M, N);
        lda   = M;
        n2    = lda*N;
        ldda  = ((M+31)/32)*32;
        gflops = (FLOPS_CGEQRF( M, N ) + FLOPS_CGEQRT( M, N)) / 1e9;

        /* Initialize the matrix */
        magma_int_t ISEED[4] = {0,0,0,1};
        lapackf77_clarnv( &ione, ISEED, &n2, h_A );
        lapackf77_clacpy( MagmaUpperLowerStr, &M, &N, h_A, &lda, h_R, &lda );
        magma_csetmatrix( M, N, h_R, 0, lda, d_A, 0, ldda, queue );

        /* ====================================================================
           Performs operation using MAGMA
           =================================================================== */
        // warm-up
      
       // magma_cgeqr2x3_gpu(&M, &N, d_A, 0, &ldda, dtau, 0, d_T, 0, ddA, 0, dwork, 0, &info, queue);
/*
        magma_csetmatrix( M, N, h_R, 0, lda, d_A, 0, ldda, queue );

        clEnqueueWriteBuffer(queue, ddA, CL_TRUE, 0, sizeof(magmaFloatComplex)*N*N, h1, 0, NULL, NULL);
        clEnqueueWriteBuffer(queue, d_T, CL_TRUE, 0, sizeof(magmaFloatComplex)*N*N, h1, 0, NULL, NULL);
*/
       
        gpu_time = magma_wtime();
        magma_cgeqr2x3_gpu(&M, &N, d_A, 0, &ldda, dtau, 0, d_T, 0, ddA, 0, dwork, 0, &info, queue);
        gpu_time = magma_wtime() - gpu_time;
        gpu_perf = gflops / gpu_time;
        if (info != 0)
            printf("magma_cgeqrf returned error %d.\n", (int) info);

        if ( checkres ) {
            /* =====================================================================
               Performs operation using LAPACK
               =================================================================== */
            cpu_time = magma_wtime();
            lapackf77_cgeqrf(&M, &N, h_A, &lda, tau, h_work, &lwork, &info);
            lapackf77_clarft( MagmaForwardStr, MagmaColumnwiseStr,
                              &M, &N, h_A, &lda, tau, h_work, &N);

            cpu_time = magma_wtime() - cpu_time;
            cpu_perf = gflops / cpu_time;
            if (info != 0)
                printf("lapackf77_cgeqrf returned error %d.\n", (int) info);
    
            /* =====================================================================
               Check the result compared to LAPACK
               =================================================================== */
            magma_cgetmatrix( M, N, d_A, 0, ldda, h_R, 0, M, queue );
            magma_cgetmatrix( N, N, ddA, 0, N,    h_T, 0, N, queue );

            // Restore the upper triangular part of A before the check 
            for(int col=0; col<N; col++){
                for(int row=0; row<=col; row++)
                    h_R[row + col*M] = h_T[row + col*N];
            }
            
            error = lapackf77_clange("M", &M, &N, h_A, &lda, work);
            blasf77_caxpy(&n2, &c_neg_one, h_A, &ione, h_R, &ione);
            error = lapackf77_clange("M", &M, &N, h_R, &lda, work) / error;

            // Check if T is the same
            float terr = 0.;
            magma_cgetmatrix( N, N, d_T, 0, N, h_T, 0, N, queue );

            for(int col=0; col<N; col++)
                for(int row=0; row<=col; row++)
                    terr += (  MAGMA_C_ABS(h_work[row + col*N] - h_T[row + col*N])*
                               MAGMA_C_ABS(h_work[row + col*N] - h_T[row + col*N])  );
            terr = magma_ssqrt(terr);

            printf("%5d %5d   %7.2f (%7.2f)   %7.2f (%7.2f)     %8.2e     %8.2e\n",
                   (int) M, (int) N, cpu_perf, 1000.*cpu_time, gpu_perf, 1000.*gpu_time, 
                   error, terr);
        }
        else {
            printf("%5d %5d     ---   (  ---  )   %7.2f (%7.2f)     ---  \n",
                   (int) M, (int) N, gpu_perf, 1000.*gpu_time);
        }
    }
    
    /* Memory clean up */
    TESTING_FREE_PIN( tau );
    TESTING_FREE_PIN( h_A );
    TESTING_FREE_PIN( h_T );
    TESTING_FREE_PIN( h_work );
    TESTING_FREE_PIN( h_R );
    
    TESTING_FREE_DEV( d_A  );
    TESTING_FREE_DEV( d_T  );
    TESTING_FREE_DEV( ddA  );
    TESTING_FREE_DEV( dtau );

    free(h1);

    magma_queue_destroy( queue );
    magma_finalize();
}

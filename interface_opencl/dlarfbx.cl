/*
    -- clMAGMA (version 1.1.0) --
       Univ. of Tennessee, Knoxville
       Univ. of California, Berkeley
       Univ. of Colorado, Denver
       @date January 2014

       @generated from zlarfbx.cl normal z -> d, Fri Jan 10 15:51:19 2014

*/
#include "kernels_header.h"
//#define BLOCK_SIZE 768
#define BLOCK_SIZE 256

// ----------------------------------------
// Does sum reduction of array x, leaving total in x[0].
// Contents of x are destroyed in the process.
// With k threads, can reduce array up to 2*k in size.
// Assumes number of threads <= 1024 (which is max number of threads up to CUDA capability 3.0)
// Having n as template parameter allows compiler to evaluate some conditions at compile time.
void zsum_reduce(int n, int i, __local double* x )
{
    barrier(CLK_LOCAL_MEM_FENCE);
    if ( n > 1024 ) { if ( i < 1024 && i + 1024 < n ) { x[i] += x[i+1024]; }  barrier(CLK_LOCAL_MEM_FENCE); }
    if ( n >  512 ) { if ( i <  512 && i +  512 < n ) { x[i] += x[i+ 512]; }  barrier(CLK_LOCAL_MEM_FENCE); }
    if ( n >  256 ) { if ( i <  256 && i +  256 < n ) { x[i] += x[i+ 256]; }  barrier(CLK_LOCAL_MEM_FENCE); }
    if ( n >  128 ) { if ( i <  128 && i +  128 < n ) { x[i] += x[i+ 128]; }  barrier(CLK_LOCAL_MEM_FENCE); }
    if ( n >   64 ) { if ( i <   64 && i +   64 < n ) { x[i] += x[i+  64]; }  barrier(CLK_LOCAL_MEM_FENCE); }
    if ( n >   32 ) { if ( i <   32 && i +   32 < n ) { x[i] += x[i+  32]; }  barrier(CLK_LOCAL_MEM_FENCE); }
    if ( n >   16 ) { if ( i <   16 && i +   16 < n ) { x[i] += x[i+  16]; }  barrier(CLK_LOCAL_MEM_FENCE); }
    if ( n >    8 ) { if ( i <    8 && i +    8 < n ) { x[i] += x[i+   8]; }  barrier(CLK_LOCAL_MEM_FENCE); }
    if ( n >    4 ) { if ( i <    4 && i +    4 < n ) { x[i] += x[i+   4]; }  barrier(CLK_LOCAL_MEM_FENCE); }
    if ( n >    2 ) { if ( i <    2 && i +    2 < n ) { x[i] += x[i+   2]; }  barrier(CLK_LOCAL_MEM_FENCE); }
    if ( n >    1 ) { if ( i <    1 && i +    1 < n ) { x[i] += x[i+   1]; }  barrier(CLK_LOCAL_MEM_FENCE); }
}
// end sum_reduce

//magma_dgemv_kernel1
__kernel void 
magma_dgemv_kernel1(int m, __global double *V, int V_offset, int ldv, 
                    __global double *c, int c_offset,  
                    __global double *dwork, int dwork_offset)
{
        V += V_offset;
        c += c_offset;
        dwork += dwork_offset;
    
        const int i = get_local_id(0);
        //const double *dV = V + (get_group_id(0)) * ldv;
        V += (get_group_id(0)) * ldv;

        __local double sum[ BLOCK_SIZE ];
        double lsum;

        /*  lsum := v' * C  */
        lsum = MAGMA_D_ZERO;
        for( int j = i; j < m; j += BLOCK_SIZE )
           lsum += MAGMA_D_MUL( MAGMA_D_CNJG( V[j] ), c[j] );
        
        sum[i] = lsum;
        zsum_reduce( BLOCK_SIZE, i, sum );

        barrier(CLK_LOCAL_MEM_FENCE);
        if (i==0)
           dwork [get_group_id(0)] = sum[0];
}

//magma_dgemv_kernel2
__kernel void
magma_dgemv_kernel2(int m, int n, __global double *V, int V_offset, int ldv, 
                    __global double *x, int x_offset, 
                    __global double *c, int c_offset)
{
    V += V_offset;
    x += x_offset;
    c += c_offset;

    const int i = get_local_id(0);
    const int j = i + BLOCK_SIZE * get_group_id(0);
    double lsum;

    V += j;

    lsum = MAGMA_D_ZERO;
    if (j < m){
       for(int k=0; k<n; k++)
          lsum += MAGMA_D_MUL( V[k*ldv], x[k]);
       
       c[j] -= lsum;
    }
}

//magma_dgemv_kernel3

//==============================================================================

__kernel void
magma_dgemv_kernel3(int m, __global double *V, int V_offset, int ldv, 
                    __global double *c, int c_offset, 
                    __global double *dwork, int dwork_offset, 
                    __global double *tau, int tau_offset)
{
        V += V_offset;
        c += c_offset;
        dwork += dwork_offset;
        tau += tau_offset;

        const int i = get_local_id(0);
        //const double *dV = V + (get_group_id(0)) * ldv;
        V += (get_group_id(0)) * ldv;

        __local double sum[ BLOCK_SIZE ];
        sum[i] = MAGMA_D_ZERO;
        
        double lsum;

        if (i==0)
           c[0] = MAGMA_D_ONE;

        /*  lsum := v' * C  */
        lsum = MAGMA_D_ZERO;
        for( int j = i; j < m; j += BLOCK_SIZE )
           lsum += MAGMA_D_MUL( MAGMA_D_CNJG( V[j] ), c[j] );

        sum[i] = lsum;
        zsum_reduce( BLOCK_SIZE, i, sum );

        barrier(CLK_LOCAL_MEM_FENCE);
        if (i==0)
           dwork [get_group_id(0)] = -tau[0]*sum[0];
}

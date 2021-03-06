/*
    -- clMAGMA (version 1.1.0) --
       Univ. of Tennessee, Knoxville
       Univ. of California, Berkeley
       Univ. of Colorado, Denver
       @date January 2014

       @generated from zgeqrf_gpu.cpp normal z -> s, Fri Jan 10 15:51:18 2014
*/

#include <cstdio>

#include <cstdio>
#include "common_magma.h"

/* ////////////////////////////////////////////////////////////////////////////
   -- Auxiliary function: 'a' is pointer to the current panel holding the
      Householder vectors for the QR factorization of the panel. This routine
      puts ones on the diagonal and zeros in the upper triangular part of 'a'.
      The upper triangular values are stored in work. Than the inverse is
      calculated in place in work, so as final result work holds the inverse
      of the upper triangular diagonal block.
 */
void ssplit_diag_block(int ib, float *a, int lda, float *work){
    int i, j, info;
    float *cola, *colw;
    float c_zero = MAGMA_S_ZERO;
    float c_one  = MAGMA_S_ONE;

    for(i=0; i<ib; i++){
        cola = a    + i*lda;
        colw = work + i*ib;
        for(j=0; j<i; j++){
            colw[j] = cola[j];
            cola[j] = c_zero;
        }
        colw[i] = cola[i];
        cola[i] = c_one;
    }
    lapackf77_strtri( MagmaUpperStr, MagmaNonUnitStr, &ib, work, &ib, &info);
}

extern "C" magma_err_t
magma_sgeqrf_gpu( magma_int_t m, magma_int_t n,
                  magmaFloat_ptr dA, size_t dA_offset,  magma_int_t ldda,
                  float *tau, magmaFloat_ptr dT, size_t dT_offset,
                  magma_int_t *info, magma_queue_t queue)
{
/*  -- clMAGMA (version 1.1.0) --
       Univ. of Tennessee, Knoxville
       Univ. of California, Berkeley
       Univ. of Colorado, Denver
       @date January 2014

    Purpose
    =======
    SGEQRF computes a QR factorization of a REAL M-by-N matrix A:
    A = Q * R. This version stores the triangular matrices used in
    the factorization so that they can be applied directly (i.e.,
    without being recomputed) later. As a result, the application
    of Q is much faster.

    Arguments
    =========
    M       (input) INTEGER
            The number of rows of the matrix A.  M >= 0.

    N       (input) INTEGER
            The number of columns of the matrix A.  N >= 0.

    A       (input/output) REAL array on the GPU, dimension (LDDA,N)
            On entry, the M-by-N matrix A.
            On exit, the elements on and above the diagonal of the array
            contain the std::min(M,N)-by-N upper trapezoidal matrix R (R is
            upper triangular if m >= n); the elements below the diagonal,
            with the array TAU, represent the orthogonal matrix Q as a
            product of std::min(m,n) elementary reflectors (see Further
            Details).

    LDDA     (input) INTEGER
            The leading dimension of the array A.  LDDA >= std::max(1,M).
            To benefit from coalescent memory accesses LDDA must be
            dividable by 16.

    TAU     (output) REAL array, dimension (std::min(M,N))
            The scalar factors of the elementary reflectors (see Further
            Details).

    dT      (workspace/output)  REAL array on the GPU,
            dimension (2*MIN(M, N) + (N+31)/32*32 )*NB,
            where NB can be obtained through magma_get_sgeqrf_nb(M).
            It starts with MIN(M,N)*NB block that store the triangular T
            matrices, followed by the MIN(M,N)*NB block of the diagonal
            inverses for the R matrix. The rest of the array is used as workspace.

    INFO    (output) INTEGER
            = 0:  successful exit
            < 0:  if INFO = -i, the i-th argument had an illegal value
                  or another error occured, such as memory allocation failed.

    Further Details
    ===============
    The matrix Q is represented as a product of elementary reflectors

       Q = H(1) H(2) . . . H(k), where k = std::min(m,n).

    Each H(i) has the form

       H(i) = I - tau * v * v'

    where tau is a real scalar, and v is a real vector with
    v(1:i-1) = 0 and v(i) = 1; v(i+1:m) is stored on exit in A(i+1:m,i),
    and tau in TAU(i).
    =====================================================================    */

    #define a_ref(a_1,a_2) dA, (dA_offset + (a_1) + (a_2)*(ldda))
    #define t_ref(a_1)     dT, (dT_offset + (a_1)*nb)
    #define d_ref(a_1)     dT, (dT_offset + (minmn + (a_1))*nb)
    #define dd_ref(a_1)    dT, (dT_offset + (2*minmn+(a_1))*nb)
    #define work_ref(a_1)  ( work + (a_1))
    #define hwork          ( work + (nb)*(m))

    magma_int_t i, k, minmn, old_i, old_ib, rows, cols;
    magma_int_t ib, nb;
    magma_int_t ldwork, lddwork, lwork, lhwork;
    float *work, *ut;

    /* check arguments */
    *info = 0;
    if (m < 0) {
        *info = -1;
    } else if (n < 0) {
        *info = -2;
    } else if (ldda < std::max(1,m)) {
        *info = -4;
    }
    if (*info != 0) {
        magma_xerbla( __func__, -(*info) );
        return *info;
    }

    k = minmn = std::min(m,n);
    if (k == 0)
        return *info;

    nb = magma_get_sgeqrf_nb(m);

    lwork  = (m + n + nb)*nb;
    lhwork = lwork - m*nb;

    if (MAGMA_SUCCESS != magma_smalloc_cpu( &work, lwork )) {
        *info = MAGMA_ERR_HOST_ALLOC;
        return *info;
    }
    
    ut = hwork+nb*(n);
    memset( ut, 0, nb*nb*sizeof(float));

    magma_event_t event[2] = {NULL, NULL};

    ldwork = m;
    lddwork= n;

    if ( (nb > 1) && (nb < k) ) {
        /* Use blocked code initially */
        old_i = 0; old_ib = nb;
        for (i = 0; i < k-nb; i += nb) {
            ib = std::min(k-i, nb);
            rows = m -i;
            magma_sgetmatrix_async( rows, ib,
                                    a_ref(i,i),  ldda,
                                    work_ref(i), 0, ldwork, queue, &event[1] );
            if (i>0){
                /* Apply H' to A(i:m,i+2*ib:n) from the left */
                cols = n-old_i-2*old_ib;
                magma_slarfb_gpu( MagmaLeft, MagmaTrans, MagmaForward, MagmaColumnwise,
                                  m-old_i, cols, old_ib,
                                  a_ref(old_i, old_i         ), ldda, t_ref(old_i), nb,
                                  a_ref(old_i, old_i+2*old_ib), ldda, dd_ref(0),    lddwork, queue);
                
                /* store the diagonal */
                magma_ssetmatrix_async( old_ib, old_ib,
                                        ut, 0, old_ib,
                                        d_ref(old_i), old_ib, queue, &event[0] );
            }
            
            magma_event_sync(event[1]);
            lapackf77_sgeqrf(&rows, &ib, work_ref(i), &ldwork, tau+i, hwork, &lhwork, info);
            /* Form the triangular factor of the block reflector
               H = H(i) H(i+1) . . . H(i+ib-1) */
            lapackf77_slarft( MagmaForwardStr, MagmaColumnwiseStr,
                              &rows, &ib,
                              work_ref(i), &ldwork, tau+i, hwork, &ib);

            /* Put 0s in the upper triangular part of a panel (and 1s on the
               diagonal); copy the upper triangular in ut and invert it     */
            magma_event_sync(event[0]);
            ssplit_diag_block(ib, work_ref(i), ldwork, ut);
            magma_ssetmatrix( rows, ib, work_ref(i), 0, ldwork, a_ref(i,i), ldda, queue);
            
            if (i + ib < n) {
                /* Send the triangular factor T to the GPU */
                magma_ssetmatrix( ib, ib, hwork, 0, ib, t_ref(i), nb, queue );

                if (i+nb < k-nb){
                    /* Apply H' to A(i:m,i+ib:i+2*ib) from the left */
                    magma_slarfb_gpu( MagmaLeft, MagmaTrans, MagmaForward, MagmaColumnwise,
                                      rows, ib, ib,
                                      a_ref(i, i   ), ldda, t_ref(i),  nb,
                                      a_ref(i, i+ib), ldda, dd_ref(0), lddwork, queue);
                }
                else {
                    cols = n-i-ib;
                    magma_slarfb_gpu( MagmaLeft, MagmaTrans, MagmaForward, MagmaColumnwise,
                                      rows, cols, ib,
                                      a_ref(i, i   ), ldda, t_ref(i),  nb,
                                      a_ref(i, i+ib), ldda, dd_ref(0), lddwork, queue);
                    /* Fix the diagonal block */
                    magma_ssetmatrix( ib, ib, ut, 0, ib, d_ref(i), ib , queue);
                }
                old_i  = i;
                old_ib = ib;
            }
        }
    } else {
        i = 0;
    }

    /* Use unblocked code to factor the last or only block. */
    if (i < k) {
        ib   = n-i;
        rows = m-i;
        magma_sgetmatrix( rows, ib, a_ref(i, i), ldda, work, 0, rows, queue );
        lhwork = lwork - rows*ib;
        lapackf77_sgeqrf(&rows, &ib, work, &rows, tau+i, work+ib*rows, &lhwork, info);
        
        magma_ssetmatrix( rows, ib, work, 0, rows, a_ref(i, i), ldda, queue );
    }

    magma_free_cpu( work );
    return *info;
} /* magma_sgeqrf */

#undef a_ref
#undef t_ref
#undef d_ref
#undef work_ref

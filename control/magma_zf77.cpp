/*******************************************************************************
 *  This file is AUTOMATICALLY GENERATED by:
 *  ../tools/fortran_wrappers.pl ../include/magma_z.i
 *  Do not edit.
 ******************************************************************************/

#include <cstdint>  // for uintptr_t

#include "magma.h"
#include "magma_mangling.h"

/*
 * typedef comming from fortran.h file provided in CUDADIR/src directory
 * it will probably change with future release of CUDA when they use 64 bit addresses
 */
typedef size_t devptr_t;

#ifdef PGI_FORTRAN
    #define magma_idevptr(ptr_) ((int*)               (ptr_))
    #define magma_zdevptr(ptr_) ((magmaDoubleComplex*)(ptr_))
    #ifndef magma_cdevptr
    #define magma_cdevptr(ptr_) ((magmaFloatComplex*) (ptr_))
    #endif
    #ifndef magma_ddevptr
    #define magma_ddevptr(ptr_) ((double*)            (ptr_))
    #endif
    #ifndef magma_sdevptr
    #define magma_sdevptr(ptr_) ((float*)             (ptr_))
    #endif
#else
    #define magma_idevptr(ptr_) ((int*)               (uintptr_t)(*(ptr_)))
    #define magma_zdevptr(ptr_) ((magmaDoubleComplex*)(uintptr_t)(*(ptr_)))
    #ifndef magma_cdevptr
    #define magma_cdevptr(ptr_) ((magmaFloatComplex*) (uintptr_t)(*(ptr_)))
    #endif
    #ifndef magma_ddevptr
    #define magma_ddevptr(ptr_) ((double*)            (uintptr_t)(*(ptr_)))
    #endif
    #ifndef magma_sdevptr
    #define magma_sdevptr(ptr_) ((float*)             (uintptr_t)(*(ptr_)))
    #endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define magmaf_get_zpotrf_nb FORTRAN_NAME( magmaf_get_zpotrf_nb, MAGMAF_GET_ZPOTRF_NB )
magma_int_t magmaf_get_zpotrf_nb( magma_int_t *m )
{
    return magma_get_zpotrf_nb( *m );
}

#define magmaf_get_zgetrf_nb FORTRAN_NAME( magmaf_get_zgetrf_nb, MAGMAF_GET_ZGETRF_NB )
magma_int_t magmaf_get_zgetrf_nb( magma_int_t *m )
{
    return magma_get_zgetrf_nb( *m );
}

#define magmaf_get_zgetri_nb FORTRAN_NAME( magmaf_get_zgetri_nb, MAGMAF_GET_ZGETRI_NB )
magma_int_t magmaf_get_zgetri_nb( magma_int_t *m )
{
    return magma_get_zgetri_nb( *m );
}

#define magmaf_get_zgeqrf_nb FORTRAN_NAME( magmaf_get_zgeqrf_nb, MAGMAF_GET_ZGEQRF_NB )
magma_int_t magmaf_get_zgeqrf_nb( magma_int_t *m )
{
    return magma_get_zgeqrf_nb( *m );
}

#define magmaf_get_zgeqlf_nb FORTRAN_NAME( magmaf_get_zgeqlf_nb, MAGMAF_GET_ZGEQLF_NB )
magma_int_t magmaf_get_zgeqlf_nb( magma_int_t *m )
{
    return magma_get_zgeqlf_nb( *m );
}

#define magmaf_get_zgehrd_nb FORTRAN_NAME( magmaf_get_zgehrd_nb, MAGMAF_GET_ZGEHRD_NB )
magma_int_t magmaf_get_zgehrd_nb( magma_int_t *m )
{
    return magma_get_zgehrd_nb( *m );
}

#define magmaf_get_zhetrd_nb FORTRAN_NAME( magmaf_get_zhetrd_nb, MAGMAF_GET_ZHETRD_NB )
magma_int_t magmaf_get_zhetrd_nb( magma_int_t *m )
{
    return magma_get_zhetrd_nb( *m );
}

#define magmaf_get_zgelqf_nb FORTRAN_NAME( magmaf_get_zgelqf_nb, MAGMAF_GET_ZGELQF_NB )
magma_int_t magmaf_get_zgelqf_nb( magma_int_t *m )
{
    return magma_get_zgelqf_nb( *m );
}

#define magmaf_get_zgebrd_nb FORTRAN_NAME( magmaf_get_zgebrd_nb, MAGMAF_GET_ZGEBRD_NB )
magma_int_t magmaf_get_zgebrd_nb( magma_int_t *m )
{
    return magma_get_zgebrd_nb( *m );
}

#define magmaf_get_zhegst_nb FORTRAN_NAME( magmaf_get_zhegst_nb, MAGMAF_GET_ZHEGST_NB )
magma_int_t magmaf_get_zhegst_nb( magma_int_t *m )
{
    return magma_get_zhegst_nb( *m );
}

#define magmaf_get_zgesvd_nb FORTRAN_NAME( magmaf_get_zgesvd_nb, MAGMAF_GET_ZGESVD_NB )
magma_int_t magmaf_get_zgesvd_nb( magma_int_t *m )
{
    return magma_get_zgesvd_nb( *m );
}

#define magmaf_zgebrd FORTRAN_NAME( magmaf_zgebrd, MAGMAF_ZGEBRD )
void magmaf_zgebrd(
    magma_int_t *m, magma_int_t *n,
    magmaDoubleComplex *a, magma_int_t *lda,
    double *d,
    double *e,
    magmaDoubleComplex *tauq,
    magmaDoubleComplex *taup,
    magmaDoubleComplex *work, magma_int_t *lwork,
    magma_int_t *info, magma_queue_t *queue )
{
    magma_zgebrd(
        *m, *n,
        a, *lda,
        d,
        e,
        tauq,
        taup,
        work, *lwork,
        info, *queue );
}

#define magmaf_zgeqrf FORTRAN_NAME( magmaf_zgeqrf, MAGMAF_ZGEQRF )
void magmaf_zgeqrf(
    magma_int_t *m, magma_int_t *n,
    magmaDoubleComplex *A, magma_int_t *lda,
    magmaDoubleComplex *tau,
    magmaDoubleComplex *work, magma_int_t *lwork,
    magma_int_t *info,
    magma_queue_t *queue )
{
    magma_zgeqrf(
        *m, *n,
        A, *lda,
        tau,
        work, *lwork,
        info,
        queue );
}

#define magmaf_zgesv FORTRAN_NAME( magmaf_zgesv, MAGMAF_ZGESV )
void magmaf_zgesv(
    magma_int_t *n, magma_int_t *nrhs,
    magmaDoubleComplex *A, magma_int_t *lda,
    magma_int_t *ipiv,
    magmaDoubleComplex *B, magma_int_t *ldb,
    magma_int_t *info,
    magma_queue_t *queue )
{
    magma_zgesv(
        *n, *nrhs,
        A, *lda,
        ipiv,
        B, *ldb,
        info,
        queue );
}

#define magmaf_zgetrf FORTRAN_NAME( magmaf_zgetrf, MAGMAF_ZGETRF )
void magmaf_zgetrf(
    magma_int_t *m, magma_int_t *n,
    magmaDoubleComplex *A, magma_int_t *lda,
    magma_int_t *ipiv,
    magma_int_t *info,
    magma_queue_t *queue )
{
    magma_zgetrf(
        *m, *n,
        A, *lda,
        ipiv,
        info,
        queue );
}

#define magmaf_zposv FORTRAN_NAME( magmaf_zposv, MAGMAF_ZPOSV )
void magmaf_zposv(
    magma_uplo_t *uplo, magma_int_t *n, magma_int_t *nrhs,
    magmaDoubleComplex *A, magma_int_t *lda,
    magmaDoubleComplex *B, magma_int_t *ldb,
    magma_int_t *info,
    magma_queue_t *queue )
{
    magma_zposv(
        *uplo, *n, *nrhs,
        A, *lda,
        B, *ldb,
        info,
        queue );
}

#define magmaf_zpotrf FORTRAN_NAME( magmaf_zpotrf, MAGMAF_ZPOTRF )
void magmaf_zpotrf(
    magma_uplo_t *uplo, magma_int_t *n,
    magmaDoubleComplex *A, magma_int_t *lda,
    magma_int_t *info,
    magma_queue_t *queue )
{
    magma_zpotrf(
        *uplo, *n,
        A, *lda,
        info,
        queue );
}

#define magmaf_zunghr FORTRAN_NAME( magmaf_zunghr, MAGMAF_ZUNGHR )
void magmaf_zunghr(
    magma_int_t *n, magma_int_t *ilo, magma_int_t *ihi,
    magmaDoubleComplex *a, magma_int_t *lda,
    magmaDoubleComplex *tau, magmaDoubleComplex_ptr *dT, size_t *dT_offset, magma_int_t *nb,
    magma_int_t *info, magma_queue_t *queue )
{
    magma_zunghr(
        *n, *ilo, *ihi,
        a, *lda,
        tau, *dT, *dT_offset, *nb,
        info, *queue );
}

#define magmaf_zungqr FORTRAN_NAME( magmaf_zungqr, MAGMAF_ZUNGQR )
void magmaf_zungqr(
    magma_int_t *m, magma_int_t *n, magma_int_t *k,
    magmaDoubleComplex *a, magma_int_t *lda,
    magmaDoubleComplex *tau, magmaDoubleComplex_ptr *dT, size_t *dT_offset, magma_int_t *nb,
    magma_int_t *info, magma_queue_t *queue )
{
    magma_zungqr(
        *m, *n, *k,
        a, *lda,
        tau, *dT, *dT_offset, *nb,
        info, *queue );
}

#define magmaf_zunmtr FORTRAN_NAME( magmaf_zunmtr, MAGMAF_ZUNMTR )
void magmaf_zunmtr(
    magma_side_t *side, magma_uplo_t *uplo, magma_trans_t *trans, magma_int_t *m, magma_int_t *n,
    magmaDoubleComplex *a, magma_int_t *lda,
    magmaDoubleComplex *tau,
    magmaDoubleComplex *c, magma_int_t *ldc,
    magmaDoubleComplex *work, magma_int_t *lwork,
    magma_int_t *info, magma_queue_t *queue )
{
    magma_zunmtr(
        *side, *uplo, *trans, *m, *n,
        a, *lda,
        tau,
        c, *ldc,
        work, *lwork,
        info, *queue );
}

#define magmaf_zunmqr FORTRAN_NAME( magmaf_zunmqr, MAGMAF_ZUNMQR )
void magmaf_zunmqr(
    magma_side_t *side, magma_trans_t *trans, magma_int_t *m, magma_int_t *n, magma_int_t *k,
    magmaDoubleComplex *a, magma_int_t *lda,
    magmaDoubleComplex *tau,
    magmaDoubleComplex *c, magma_int_t *ldc,
    magmaDoubleComplex *work, magma_int_t *lwork,
    magma_int_t *info, magma_queue_t *queue )
{
    magma_zunmqr(
        *side, *trans, *m, *n, *k,
        a, *lda,
        tau,
        c, *ldc,
        work, *lwork,
        info, *queue );
}

#define magmaf_zunmql FORTRAN_NAME( magmaf_zunmql, MAGMAF_ZUNMQL )
void magmaf_zunmql(
    magma_side_t *side, magma_trans_t *trans, magma_int_t *m, magma_int_t *n, magma_int_t *k,
    magmaDoubleComplex *a, magma_int_t *lda,
    magmaDoubleComplex *tau,
    magmaDoubleComplex *c, magma_int_t *ldc,
    magmaDoubleComplex *work, magma_int_t *lwork,
    magma_int_t *info, magma_queue_t *queue )
{
    magma_zunmql(
        *side, *trans, *m, *n, *k,
        a, *lda,
        tau,
        c, *ldc,
        work, *lwork,
        info, *queue );
}

#define magmaf_zgeev FORTRAN_NAME( magmaf_zgeev, MAGMAF_ZGEEV )
void magmaf_zgeev(
    magma_vec_t *jobvl, magma_vec_t *jobvr, magma_int_t *n,
    magmaDoubleComplex *a, magma_int_t *lda,
    magmaDoubleComplex *geev_w_array,
    magmaDoubleComplex *vl, magma_int_t *ldvl,
    magmaDoubleComplex *vr, magma_int_t *ldvr,
    magmaDoubleComplex *work, magma_int_t *lwork,
    double *rwork,
    magma_int_t *info, magma_queue_t *queue )
{
    magma_zgeev(
        *jobvl, *jobvr, *n,
        a, *lda,
        geev_w_array,
        vl, *ldvl,
        vr, *ldvr,
        work, *lwork,
        rwork,
        info, *queue );
}

#define magmaf_zgesvd FORTRAN_NAME( magmaf_zgesvd, MAGMAF_ZGESVD )
void magmaf_zgesvd(
    char *jobu, char *jobvt, magma_int_t *m, magma_int_t *n,
    magmaDoubleComplex *a, magma_int_t *lda,
    double *s,
    magmaDoubleComplex *u, magma_int_t *ldu,
    magmaDoubleComplex *vt, magma_int_t *ldvt,
    magmaDoubleComplex *work, magma_int_t *lwork,
    double *rwork,
    magma_int_t *info, magma_queue_t *queue )
{
    magma_zgesvd(
        *jobu, *jobvt, *m, *n,
        a, *lda,
        s,
        u, *ldu,
        vt, *ldvt,
        work, *lwork,
        rwork,
        info, *queue );
}

#define magmaf_zheevd FORTRAN_NAME( magmaf_zheevd, MAGMAF_ZHEEVD )
void magmaf_zheevd(
    magma_vec_t *jobz, magma_uplo_t *uplo, magma_int_t *n,
    magmaDoubleComplex *a, magma_int_t *lda,
    double *w,
    magmaDoubleComplex *work, magma_int_t *lwork,
    double *rwork, magma_int_t *lrwork,
    magma_int_t *iwork, magma_int_t *liwork,
    magma_int_t *info, magma_queue_t *queue )
{
    magma_zheevd(
        *jobz, *uplo, *n,
        a, *lda,
        w,
        work, *lwork,
        rwork, *lrwork,
        iwork, *liwork,
        info, *queue );
}

#define magmaf_zstedx FORTRAN_NAME( magmaf_zstedx, MAGMAF_ZSTEDX )
void magmaf_zstedx(
    magma_vec_t *range, magma_int_t *n, double *vl, double *vu, magma_int_t *il, magma_int_t *iu,
    double*d,
    double*e,
    magmaDoubleComplex*z, magma_int_t *ldz,
    double*rwork, magma_int_t *lrwork,
    magma_int_t*iwork, magma_int_t *liwork, magmaDouble_ptr *dwork,
    magma_int_t*info, magma_queue_t *queue )
{
    magma_zstedx(
        *range, *n, *vl, *vu, *il, *iu,
        d,
        e,
        z, *ldz,
        rwork, *lrwork,
        iwork, *liwork, *dwork,
        info, *queue );
}

#define magmaf_zgehrd FORTRAN_NAME( magmaf_zgehrd, MAGMAF_ZGEHRD )
void magmaf_zgehrd(
    magma_int_t *n, magma_int_t *ilo, magma_int_t *ihi,
    magmaDoubleComplex *a, magma_int_t *lda,
    magmaDoubleComplex *tau,
    magmaDoubleComplex *work, magma_int_t *lwork, magmaDoubleComplex_ptr *dT, size_t *dT_offset,
    magma_int_t *info, magma_queue_t *queue )
{
    magma_zgehrd(
        *n, *ilo, *ihi,
        a, *lda,
        tau,
        work, *lwork, *dT, *dT_offset,
        info, *queue );
}

#define magmaf_zhetrd FORTRAN_NAME( magmaf_zhetrd, MAGMAF_ZHETRD )
void magmaf_zhetrd(
    char *uplo, magma_int_t *n,
    magmaDoubleComplex *a, magma_int_t *lda,
    double *d,
    double *e,
    magmaDoubleComplex *tau,
    magmaDoubleComplex *work, magma_int_t *lwork,
    magma_int_t *info, magma_queue_t *queue )
{
    magma_zhetrd(
        *uplo, *n,
        a, *lda,
        d,
        e,
        tau,
        work, *lwork,
        info, *queue );
}

#define magmaf_zprint FORTRAN_NAME( magmaf_zprint, MAGMAF_ZPRINT )
void magmaf_zprint(
    magma_int_t *m, magma_int_t *n,
    magmaDoubleComplex *A, magma_int_t *lda )
{
    magma_zprint(
        *m, *n,
        A, *lda );
}


#ifdef __cplusplus
}
#endif

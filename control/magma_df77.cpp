/*******************************************************************************
 *  This file is AUTOMATICALLY GENERATED by:
 *  ../tools/fortran_wrappers.pl ../include/magma_d.i
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

#define magmaf_get_dpotrf_nb FORTRAN_NAME( magmaf_get_dpotrf_nb, MAGMAF_GET_DPOTRF_NB )
magma_int_t magmaf_get_dpotrf_nb( magma_int_t *m )
{
    return magma_get_dpotrf_nb( *m );
}

#define magmaf_get_dgetrf_nb FORTRAN_NAME( magmaf_get_dgetrf_nb, MAGMAF_GET_DGETRF_NB )
magma_int_t magmaf_get_dgetrf_nb( magma_int_t *m )
{
    return magma_get_dgetrf_nb( *m );
}

#define magmaf_get_dgetri_nb FORTRAN_NAME( magmaf_get_dgetri_nb, MAGMAF_GET_DGETRI_NB )
magma_int_t magmaf_get_dgetri_nb( magma_int_t *m )
{
    return magma_get_dgetri_nb( *m );
}

#define magmaf_get_dgeqrf_nb FORTRAN_NAME( magmaf_get_dgeqrf_nb, MAGMAF_GET_DGEQRF_NB )
magma_int_t magmaf_get_dgeqrf_nb( magma_int_t *m )
{
    return magma_get_dgeqrf_nb( *m );
}

#define magmaf_get_dgeqlf_nb FORTRAN_NAME( magmaf_get_dgeqlf_nb, MAGMAF_GET_DGEQLF_NB )
magma_int_t magmaf_get_dgeqlf_nb( magma_int_t *m )
{
    return magma_get_dgeqlf_nb( *m );
}

#define magmaf_get_dgehrd_nb FORTRAN_NAME( magmaf_get_dgehrd_nb, MAGMAF_GET_DGEHRD_NB )
magma_int_t magmaf_get_dgehrd_nb( magma_int_t *m )
{
    return magma_get_dgehrd_nb( *m );
}

#define magmaf_get_dsytrd_nb FORTRAN_NAME( magmaf_get_dsytrd_nb, MAGMAF_GET_DSYTRD_NB )
magma_int_t magmaf_get_dsytrd_nb( magma_int_t *m )
{
    return magma_get_dsytrd_nb( *m );
}

#define magmaf_get_dgelqf_nb FORTRAN_NAME( magmaf_get_dgelqf_nb, MAGMAF_GET_DGELQF_NB )
magma_int_t magmaf_get_dgelqf_nb( magma_int_t *m )
{
    return magma_get_dgelqf_nb( *m );
}

#define magmaf_get_dgebrd_nb FORTRAN_NAME( magmaf_get_dgebrd_nb, MAGMAF_GET_DGEBRD_NB )
magma_int_t magmaf_get_dgebrd_nb( magma_int_t *m )
{
    return magma_get_dgebrd_nb( *m );
}

#define magmaf_get_dsygst_nb FORTRAN_NAME( magmaf_get_dsygst_nb, MAGMAF_GET_DSYGST_NB )
magma_int_t magmaf_get_dsygst_nb( magma_int_t *m )
{
    return magma_get_dsygst_nb( *m );
}

#define magmaf_get_dgesvd_nb FORTRAN_NAME( magmaf_get_dgesvd_nb, MAGMAF_GET_DGESVD_NB )
magma_int_t magmaf_get_dgesvd_nb( magma_int_t *m )
{
    return magma_get_dgesvd_nb( *m );
}

#define magmaf_dgebrd FORTRAN_NAME( magmaf_dgebrd, MAGMAF_DGEBRD )
void magmaf_dgebrd(
    magma_int_t *m, magma_int_t *n,
    double *a, magma_int_t *lda,
    double *d,
    double *e,
    double *tauq,
    double *taup,
    double *work, magma_int_t *lwork,
    magma_int_t *info, magma_queue_t *queue )
{
    magma_dgebrd(
        *m, *n,
        a, *lda,
        d,
        e,
        tauq,
        taup,
        work, *lwork,
        info, *queue );
}

#define magmaf_dgeqrf FORTRAN_NAME( magmaf_dgeqrf, MAGMAF_DGEQRF )
void magmaf_dgeqrf(
    magma_int_t *m, magma_int_t *n,
    double *A, magma_int_t *lda,
    double *tau,
    double *work, magma_int_t *lwork,
    magma_int_t *info,
    magma_queue_t *queue )
{
    magma_dgeqrf(
        *m, *n,
        A, *lda,
        tau,
        work, *lwork,
        info,
        queue );
}

#define magmaf_dgesv FORTRAN_NAME( magmaf_dgesv, MAGMAF_DGESV )
void magmaf_dgesv(
    magma_int_t *n, magma_int_t *nrhs,
    double *A, magma_int_t *lda,
    magma_int_t *ipiv,
    double *B, magma_int_t *ldb,
    magma_int_t *info,
    magma_queue_t *queue )
{
    magma_dgesv(
        *n, *nrhs,
        A, *lda,
        ipiv,
        B, *ldb,
        info,
        queue );
}

#define magmaf_dgetrf FORTRAN_NAME( magmaf_dgetrf, MAGMAF_DGETRF )
void magmaf_dgetrf(
    magma_int_t *m, magma_int_t *n,
    double *A, magma_int_t *lda,
    magma_int_t *ipiv,
    magma_int_t *info,
    magma_queue_t *queue )
{
    magma_dgetrf(
        *m, *n,
        A, *lda,
        ipiv,
        info,
        queue );
}

#define magmaf_dposv FORTRAN_NAME( magmaf_dposv, MAGMAF_DPOSV )
void magmaf_dposv(
    magma_uplo_t *uplo, magma_int_t *n, magma_int_t *nrhs,
    double *A, magma_int_t *lda,
    double *B, magma_int_t *ldb,
    magma_int_t *info,
    magma_queue_t *queue )
{
    magma_dposv(
        *uplo, *n, *nrhs,
        A, *lda,
        B, *ldb,
        info,
        queue );
}

#define magmaf_dpotrf FORTRAN_NAME( magmaf_dpotrf, MAGMAF_DPOTRF )
void magmaf_dpotrf(
    magma_uplo_t *uplo, magma_int_t *n,
    double *A, magma_int_t *lda,
    magma_int_t *info,
    magma_queue_t *queue )
{
    magma_dpotrf(
        *uplo, *n,
        A, *lda,
        info,
        queue );
}

#define magmaf_dorghr FORTRAN_NAME( magmaf_dorghr, MAGMAF_DORGHR )
void magmaf_dorghr(
    magma_int_t *n, magma_int_t *ilo, magma_int_t *ihi,
    double *a, magma_int_t *lda,
    double *tau, magmaDouble_ptr *dT, size_t *dT_offset, magma_int_t *nb,
    magma_int_t *info, magma_queue_t *queue )
{
    magma_dorghr(
        *n, *ilo, *ihi,
        a, *lda,
        tau, *dT, *dT_offset, *nb,
        info, *queue );
}

#define magmaf_dorgqr FORTRAN_NAME( magmaf_dorgqr, MAGMAF_DORGQR )
void magmaf_dorgqr(
    magma_int_t *m, magma_int_t *n, magma_int_t *k,
    double *a, magma_int_t *lda,
    double *tau, magmaDouble_ptr *dT, size_t *dT_offset, magma_int_t *nb,
    magma_int_t *info, magma_queue_t *queue )
{
    magma_dorgqr(
        *m, *n, *k,
        a, *lda,
        tau, *dT, *dT_offset, *nb,
        info, *queue );
}

#define magmaf_dormtr FORTRAN_NAME( magmaf_dormtr, MAGMAF_DORMTR )
void magmaf_dormtr(
    magma_side_t *side, magma_uplo_t *uplo, magma_trans_t *trans, magma_int_t *m, magma_int_t *n,
    double *a, magma_int_t *lda,
    double *tau,
    double *c, magma_int_t *ldc,
    double *work, magma_int_t *lwork,
    magma_int_t *info, magma_queue_t *queue )
{
    magma_dormtr(
        *side, *uplo, *trans, *m, *n,
        a, *lda,
        tau,
        c, *ldc,
        work, *lwork,
        info, *queue );
}

#define magmaf_dormqr FORTRAN_NAME( magmaf_dormqr, MAGMAF_DORMQR )
void magmaf_dormqr(
    magma_side_t *side, magma_trans_t *trans, magma_int_t *m, magma_int_t *n, magma_int_t *k,
    double *a, magma_int_t *lda,
    double *tau,
    double *c, magma_int_t *ldc,
    double *work, magma_int_t *lwork,
    magma_int_t *info, magma_queue_t *queue )
{
    magma_dormqr(
        *side, *trans, *m, *n, *k,
        a, *lda,
        tau,
        c, *ldc,
        work, *lwork,
        info, *queue );
}

#define magmaf_dormql FORTRAN_NAME( magmaf_dormql, MAGMAF_DORMQL )
void magmaf_dormql(
    magma_side_t *side, magma_trans_t *trans, magma_int_t *m, magma_int_t *n, magma_int_t *k,
    double *a, magma_int_t *lda,
    double *tau,
    double *c, magma_int_t *ldc,
    double *work, magma_int_t *lwork,
    magma_int_t *info, magma_queue_t *queue )
{
    magma_dormql(
        *side, *trans, *m, *n, *k,
        a, *lda,
        tau,
        c, *ldc,
        work, *lwork,
        info, *queue );
}

#define magmaf_dgeev FORTRAN_NAME( magmaf_dgeev, MAGMAF_DGEEV )
void magmaf_dgeev(
    magma_vec_t *jobvl, magma_vec_t *jobvr, magma_int_t *n,
    double *a, magma_int_t *lda,
    double *WR,
    double *WI,
    double *vl, magma_int_t *ldvl,
    double *vr, magma_int_t *ldvr,
    double *work, magma_int_t *lwork,
    magma_int_t *info, magma_queue_t *queue )
{
    magma_dgeev(
        *jobvl, *jobvr, *n,
        a, *lda,
        WR,
        WI,
        vl, *ldvl,
        vr, *ldvr,
        work, *lwork,
        info, *queue );
}

#define magmaf_dgesvd FORTRAN_NAME( magmaf_dgesvd, MAGMAF_DGESVD )
void magmaf_dgesvd(
    char *jobu, char *jobvt, magma_int_t *m, magma_int_t *n,
    double *a, magma_int_t *lda,
    double *s,
    double *u, magma_int_t *ldu,
    double *vt, magma_int_t *ldvt,
    double *work, magma_int_t *lwork,
    magma_int_t *info, magma_queue_t *queue )
{
    magma_dgesvd(
        *jobu, *jobvt, *m, *n,
        a, *lda,
        s,
        u, *ldu,
        vt, *ldvt,
        work, *lwork,
        info, *queue );
}

#define magmaf_dsyevd FORTRAN_NAME( magmaf_dsyevd, MAGMAF_DSYEVD )
void magmaf_dsyevd(
    magma_vec_t *jobz, magma_uplo_t *uplo, magma_int_t *n,
    double *a, magma_int_t *lda,
    double *w,
    double *work, magma_int_t *lwork,
    magma_int_t *iwork, magma_int_t *liwork,
    magma_int_t *info, magma_queue_t *queue )
{
    magma_dsyevd(
        *jobz, *uplo, *n,
        a, *lda,
        w,
        work, *lwork,
        iwork, *liwork,
        info, *queue );
}

#define magmaf_dstedx FORTRAN_NAME( magmaf_dstedx, MAGMAF_DSTEDX )
void magmaf_dstedx(
    magma_vec_t *range, magma_int_t *n, double *vl, double *vu, magma_int_t *il, magma_int_t *iu,
    double*d,
    double*e,
    double*z, magma_int_t *ldz,
    double*rwork, magma_int_t *lrwork,
    magma_int_t*iwork, magma_int_t *liwork, magmaDouble_ptr *dwork,
    magma_int_t*info, magma_queue_t *queue )
{
    magma_dstedx(
        *range, *n, *vl, *vu, *il, *iu,
        d,
        e,
        z, *ldz,
        rwork, *lrwork,
        iwork, *liwork, *dwork,
        info, *queue );
}

#define magmaf_dgehrd FORTRAN_NAME( magmaf_dgehrd, MAGMAF_DGEHRD )
void magmaf_dgehrd(
    magma_int_t *n, magma_int_t *ilo, magma_int_t *ihi,
    double *a, magma_int_t *lda,
    double *tau,
    double *work, magma_int_t *lwork, magmaDouble_ptr *dT, size_t *dT_offset,
    magma_int_t *info, magma_queue_t *queue )
{
    magma_dgehrd(
        *n, *ilo, *ihi,
        a, *lda,
        tau,
        work, *lwork, *dT, *dT_offset,
        info, *queue );
}

#define magmaf_dsytrd FORTRAN_NAME( magmaf_dsytrd, MAGMAF_DSYTRD )
void magmaf_dsytrd(
    char *uplo, magma_int_t *n,
    double *a, magma_int_t *lda,
    double *d,
    double *e,
    double *tau,
    double *work, magma_int_t *lwork,
    magma_int_t *info, magma_queue_t *queue )
{
    magma_dsytrd(
        *uplo, *n,
        a, *lda,
        d,
        e,
        tau,
        work, *lwork,
        info, *queue );
}

#define magmaf_dprint FORTRAN_NAME( magmaf_dprint, MAGMAF_DPRINT )
void magmaf_dprint(
    magma_int_t *m, magma_int_t *n,
    double *A, magma_int_t *lda )
{
    magma_dprint(
        *m, *n,
        A, *lda );
}


#ifdef __cplusplus
}
#endif

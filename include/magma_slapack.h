/*
 *   -- clMAGMA (version 1.1.0) --
 *      Univ. of Tennessee, Knoxville
 *      Univ. of California, Berkeley
 *      Univ. of Colorado, Denver
 *      @date January 2014
 *
 * @generated from magma_zlapack.h normal z -> s, Fri Jan 10 15:51:16 2014
 */

#ifndef MAGMA_SLAPACK_H
#define MAGMA_SLAPACK_H

#include "magma_types.h"

#define PRECISION_s

#ifdef __cplusplus
extern "C" {
#endif

/* ////////////////////////////////////////////////////////////////////////////
   -- LAPACK Externs used in MAGMA
*/

#define blasf77_saxpy      FORTRAN_NAME( saxpy,  SAXPY  )
#define blasf77_scopy      FORTRAN_NAME( scopy,  SCOPY  )

/* real versions use C wrapper to return value; no name mangling. */
#if  defined(PRECISION_z) || defined(PRECISION_c)    
#define blasf77_sdot      sdot
#else
#define blasf77_sdot      FORTRAN_NAME( sdot,  SDOT  )
#endif

#define blasf77_sgemm      FORTRAN_NAME( sgemm,  SGEMM  )
#define blasf77_sgemv      FORTRAN_NAME( sgemv,  SGEMV  )
#define blasf77_ssymm      FORTRAN_NAME( ssymm,  SSYMM  )
#define blasf77_ssymv      FORTRAN_NAME( ssymv,  SSYMV  )
#define blasf77_ssyr2k     FORTRAN_NAME( ssyr2k, SSYR2K )
#define blasf77_ssyrk      FORTRAN_NAME( ssyrk,  SSYRK  )
#define blasf77_sscal      FORTRAN_NAME( sscal,  SSCAL  )
#define blasf77_sscal     FORTRAN_NAME( sscal, SSCAL ) 
#define blasf77_ssymm      FORTRAN_NAME( ssymm,  SSYMM  )
#define blasf77_ssyr2k     FORTRAN_NAME( ssyr2k, SSYR2K )
#define blasf77_ssyrk      FORTRAN_NAME( ssyrk,  SSYRK  )
#define blasf77_sswap      FORTRAN_NAME( sswap,  SSWAP  )
#define blasf77_strmm      FORTRAN_NAME( strmm,  STRMM  )
#define blasf77_strmv      FORTRAN_NAME( strmv,  STRMV  )
#define blasf77_strsm      FORTRAN_NAME( strsm,  STRSM  )
#define blasf77_strsv      FORTRAN_NAME( strsv,  STRSV  )
#define blasf77_sger      FORTRAN_NAME( sger,  SGER  )

#define lapackf77_sbdsqr   FORTRAN_NAME( sbdsqr, SBDSQR )
#define lapackf77_sgebak   FORTRAN_NAME( sgebak, SGEBAK )
#define lapackf77_sgebal   FORTRAN_NAME( sgebal, SGEBAL )
#define lapackf77_sgebd2   FORTRAN_NAME( sgebd2, SGEBD2 )
#define lapackf77_sgebrd   FORTRAN_NAME( sgebrd, SGEBRD )
#define lapackf77_sgeev    FORTRAN_NAME( sgeev,  SGEEV  )
#define lapackf77_sgehd2   FORTRAN_NAME( sgehd2, SGEHD2 )
#define lapackf77_sgehrd   FORTRAN_NAME( sgehrd, SGEHRD )
#define lapackf77_sgelqf   FORTRAN_NAME( sgelqf, SGELQF )
#define lapackf77_sgels    FORTRAN_NAME( sgels,  SGELS  )
#define lapackf77_sgeqlf   FORTRAN_NAME( sgeqlf, SGEQLF )
#define lapackf77_sgeqrf   FORTRAN_NAME( sgeqrf, SGEQRF )
#define lapackf77_sgesv    FORTRAN_NAME( sgesv,  SGESV  )
#define lapackf77_sgesvd   FORTRAN_NAME( sgesvd, SGESVD )
#define lapackf77_sgetrf   FORTRAN_NAME( sgetrf, SGETRF )
#define lapackf77_sgetri   FORTRAN_NAME( sgetri, SGETRI )
#define lapackf77_sgetrs   FORTRAN_NAME( sgetrs, SGETRS )
#define lapackf77_ssyev    FORTRAN_NAME( ssyev,  SSYEV  )
#define lapackf77_ssyevd   FORTRAN_NAME( ssyevd, SSYEVD )
#define lapackf77_ssygs2   FORTRAN_NAME( ssygs2, SSYGS2 )
#define lapackf77_ssygvd   FORTRAN_NAME( ssygvd, SSYGVD )
#define lapackf77_ssytd2   FORTRAN_NAME( ssytd2, SSYTD2 )
#define lapackf77_ssytrd   FORTRAN_NAME( ssytrd, SSYTRD )
#define lapackf77_shseqr   FORTRAN_NAME( shseqr, SHSEQR )
#define lapackf77_slacpy   FORTRAN_NAME( slacpy, SLACPY )
#define lapackf77_slacgv   FORTRAN_NAME( slacgv, SLACGV )
#define lapackf77_slange   FORTRAN_NAME( slange, SLANGE )
#define lapackf77_slansy   FORTRAN_NAME( slansy, SLANSY )
#define lapackf77_slanst   FORTRAN_NAME( slanst, SLANST )
#define lapackf77_slansy   FORTRAN_NAME( slansy, SLANSY )
#define lapackf77_slarfb   FORTRAN_NAME( slarfb, SLARFB )
#define lapackf77_slarfg   FORTRAN_NAME( slarfg, SLARFG )
#define lapackf77_slarft   FORTRAN_NAME( slarft, SLARFT )
#define lapackf77_slarnv   FORTRAN_NAME( slarnv, SLARNV )
#define lapackf77_slartg   FORTRAN_NAME( slartg, SLARTG )
#define lapackf77_slascl   FORTRAN_NAME( slascl, SLASCL )
#define lapackf77_slaset   FORTRAN_NAME( slaset, SLASET )
#define lapackf77_slaswp   FORTRAN_NAME( slaswp, SLASWP )
#define lapackf77_slatrd   FORTRAN_NAME( slatrd, SLATRD )
#define lapackf77_slabrd   FORTRAN_NAME( slabrd, SLABRD )
#define lapackf77_slauum   FORTRAN_NAME( slauum, SLAUUM )
#define lapackf77_slavsy   FORTRAN_NAME( slavsy, SLAVSY )
#define lapackf77_sposv    FORTRAN_NAME( sposv,  SPOSV  )
#define lapackf77_spotrf   FORTRAN_NAME( spotrf, SPOTRF )
#define lapackf77_spotrs   FORTRAN_NAME( spotrs, SPOTRS )
#define lapackf77_spotri   FORTRAN_NAME( spotri, SPOTRI )
#define lapackf77_strevc   FORTRAN_NAME( strevc, STREVC )
#define lapackf77_sstebz   FORTRAN_NAME( sstebz, SSTEBZ )
#define lapackf77_slamc3   FORTRAN_NAME( slamc3, SLAMC3 )
#define lapackf77_slaed4   FORTRAN_NAME( slaed4, SLAED4 )
#define lapackf77_slamrg   FORTRAN_NAME( slamrg, SLAMRG )
#define lapackf77_strtri   FORTRAN_NAME( strtri, STRTRI )
#define lapackf77_ssteqr   FORTRAN_NAME( ssteqr, SSTEQR )
#define lapackf77_sstedc   FORTRAN_NAME( sstedc, SSTEDC )
#define lapackf77_sstein   FORTRAN_NAME( sstein, SSTEIN )
#define lapackf77_sstemr   FORTRAN_NAME( sstemr, SSTEMR )
#define lapackf77_ssymv    FORTRAN_NAME( ssymv,  SSYMV  )
#define lapackf77_sorg2r   FORTRAN_NAME( sorg2r, SORG2R )
#define lapackf77_sorgbr   FORTRAN_NAME( sorgbr, SORGBR )
#define lapackf77_sorghr   FORTRAN_NAME( sorghr, SORGHR )
#define lapackf77_sorglq   FORTRAN_NAME( sorglq, SORGLQ )
#define lapackf77_sorgql   FORTRAN_NAME( sorgql, SORGQL )
#define lapackf77_sorgqr   FORTRAN_NAME( sorgqr, SORGQR )
#define lapackf77_sorgtr   FORTRAN_NAME( sorgtr, SORGTR )
#define lapackf77_sorm2r   FORTRAN_NAME( sorm2r, SORM2R )
#define lapackf77_sormbr   FORTRAN_NAME( sormbr, SORMBR )
#define lapackf77_sormlq   FORTRAN_NAME( sormlq, SORMLQ )
#define lapackf77_sormql   FORTRAN_NAME( sormql, SORMQL )
#define lapackf77_sormqr   FORTRAN_NAME( sormqr, SORMQR )
#define lapackf77_sormtr   FORTRAN_NAME( sormtr, SORMTR )

/* testing functions */
#define lapackf77_sbdt01   FORTRAN_NAME( sbdt01, SBDT01 )
#define lapackf77_sget22   FORTRAN_NAME( sget22, SGET22 )
#define lapackf77_ssyt21   FORTRAN_NAME( ssyt21, SSYT21 )
#define lapackf77_shst01   FORTRAN_NAME( shst01, SHST01 )
#define lapackf77_sqrt02   FORTRAN_NAME( sqrt02, SQRT02 )
#define lapackf77_sort01   FORTRAN_NAME( sort01, SORT01 )
#define lapackf77_slarfy   FORTRAN_NAME( slarfy, SLARFY )
#define lapackf77_sstt21   FORTRAN_NAME( sstt21, SSTT21 )


#if defined(PRECISION_z) || defined(PRECISION_c)
#define DWORKFORZ        float *rwork,
#define DWORKFORZ_AND_LD float *rwork, magma_int_t *ldrwork,
#define WSPLIT           float *w
#else
#define DWORKFORZ 
#define DWORKFORZ_AND_LD
#define WSPLIT           float *wr, float *wi
#endif

  /*
   * BLAS functions (Alphabetical order)
   */
void     blasf77_saxpy(const int *, float *, float *, 
                       const int *, float *, const int *);
void     blasf77_scopy(const int *, float *, const int *,
                       float *, const int *);
#if defined(PRECISION_z) || defined(PRECISION_c)
void     blasf77_sdot(float *, int *, float *, int *, 
                       float *, int *);
#endif
void     blasf77_sgemm(const char *, const char *, const int *, const int *, const int *,
                       float *, float *, const int *, 
                       float *, const int *, float *,
                       float *, const int *);
void     blasf77_sgemv(const char *, const int  *, const int *, float *, 
                       float *, const int *, float *, const int *, 
                       float *, float *, const int *);
void     blasf77_sger(int *, int *, float *, float *, int *, 
                       float *, int *, float *, int *);
void     blasf77_ssymm(const char *, const char *, const int *, const int *, 
                       float *, float *, const int *, 
                       float *, const int *, float *,
                       float *, const int *);
void     blasf77_ssymv(const char *, const int  *, float *, float *,
                       const int *, float *, const int *, float *,
                       float *, const int *);
void    blasf77_ssyr2k(const char *, const char *, const int *, const int *, 
                       float *, float *, const int *, 
                       float *, const int *, float *, 
                       float *, const int *);
void    blasf77_ssyrk( const char *, const char *, const int *, const int *, float *, 
                       float *, const int *, float *, float *, 
                       const int *);
void    blasf77_sscal( const int *, float *, float *, const int *);
#if defined(PRECISION_z) || defined(PRECISION_c)
void    blasf77_sscal( const int *, float *, float *, const int *);
#endif
void    blasf77_ssymm( const char *, const char *, const int *, const int *, 
                       float *, float *, const int *, 
                       float *, const int *, float *,
                       float *, const int *);
void    blasf77_ssyr2k(const char *, const char *, const int *, const int *, 
                       float *, float *, const int *, 
                       float *, const int *, float *, 
                       float *, const int *);
void    blasf77_ssyrk( const char *, const char *, const int *, const int *, 
                       float *, float *, const int *, 
                       float *, float *, const int *);
void    blasf77_sswap( int *, float *, int *, float *, int *);
void    blasf77_strmm( const char *, const char *, const char *, const char *, 
                       const int *, const int *, float *,
                       float *, const int *, float *,const int *);
void    blasf77_strmv( const char *, const char *, const char *, const int *, 
                       float*,  const int *, float *, const int*);
void    blasf77_strsm( const char *, const char *, const char *, const char *, 
                       const int *, const int *, float *, 
                       float *, const int *, float *,const int*);
void    blasf77_strsv( const char *, const char *, const char *, const int *, 
                       float *, const int *, float *, const int*);

  /*
   * Lapack functions (Alphabetical order)
   */
void    lapackf77_sbdsqr(const char *uplo, magma_int_t *n, magma_int_t *nvct, 
                         magma_int_t *nru,  magma_int_t *ncc, float *D, float *E, 
                         float *VT, magma_int_t *ldvt, 
                         float *U, magma_int_t *ldu, 
                         float *C, magma_int_t *ldc, 
                         float *work, magma_int_t *info);
void    lapackf77_sgebak(const char *job, const char *side, magma_int_t *n, 
                         magma_int_t *ilo, magma_int_t *ihi, 
                         float *scale, magma_int_t *m,
                         float *v, magma_int_t *ldv, magma_int_t *info);
void    lapackf77_sgebal(const char *job, magma_int_t *n, float *A, magma_int_t *lda, 
                         magma_int_t *ilo, magma_int_t *ihi, float *scale, magma_int_t *info);
void    lapackf77_sgebd2(magma_int_t *m, magma_int_t *n, 
                         float *a, magma_int_t *lda, float *d, float *e,
                         float *tauq, float *taup,
                         float *work, magma_int_t *info);
void    lapackf77_sgebrd(magma_int_t *m, magma_int_t *n, 
                         float *a, magma_int_t *lda, float *d, float *e,
                         float *tauq, float *taup, 
                         float *work, magma_int_t *lwork, magma_int_t *info);
void     lapackf77_sgeev(const char *jobl, const char *jobr, magma_int_t *n, 
                         float *a, magma_int_t *lda, WSPLIT, 
                         float *vl, magma_int_t *ldvl, 
                         float *vr, magma_int_t *ldvr, 
                         float *work, magma_int_t *lwork, 
                         DWORKFORZ magma_int_t *info);
void    lapackf77_sgehd2(magma_int_t *n, magma_int_t *ilo, magma_int_t *ihi, 
                         float *a, magma_int_t *lda, float *tau, 
                         float *work, magma_int_t *info);
void    lapackf77_sgehrd(magma_int_t *n, magma_int_t *ilo, magma_int_t *ihi, 
                         float *a, magma_int_t *lda, float *tau,
                         float *work, magma_int_t *lwork, magma_int_t *info);
void    lapackf77_sgelqf(magma_int_t *m, magma_int_t *n, 
                         float *a, magma_int_t *lda, float *tau,
                         float *work, magma_int_t *lwork, magma_int_t *info);
void     lapackf77_sgels(const char *trans, 
                         magma_int_t *m, magma_int_t *n, magma_int_t *nrhs, 
                         float *a, magma_int_t *lda, 
                         float *b, magma_int_t *ldb,
                         float *work, magma_int_t *lwork, magma_int_t *info);
void    lapackf77_sgeqlf(magma_int_t *m, magma_int_t *n,
                         float *a, magma_int_t *lda, float *tau, 
                         float *work, magma_int_t *lwork, magma_int_t *info);
void    lapackf77_sgeqrf(magma_int_t *m, magma_int_t *n,
                         float *a, magma_int_t *lda, float *tau,
                         float *work, magma_int_t *lwork, magma_int_t *info);
void     lapackf77_sgesv(magma_int_t *n, magma_int_t *nrhs,
                         float *A, magma_int_t *lda,
                         magma_int_t *ipiv,
                         float *B, magma_int_t *ldb,
                         magma_int_t *info );
void    lapackf77_sgetrf(magma_int_t *m, magma_int_t *n, 
                         float *a, magma_int_t *lda, 
                         magma_int_t *ipiv, magma_int_t *info);
void    lapackf77_sgetri(magma_int_t *n,
                         float *a, magma_int_t *lda, magma_int_t *ipiv,
                         float *work, magma_int_t *lwork, magma_int_t *info);
void    lapackf77_sgetrs(const char* trans,
                         magma_int_t *n, magma_int_t *nrhs,
                         float *a, magma_int_t *lda, magma_int_t *ipiv,
                         float *b, magma_int_t *ldb, magma_int_t *info);
void    lapackf77_sgesvd(const char *jobu, const char *jobvt, 
                         magma_int_t *m, magma_int_t *n, 
                         float *a, magma_int_t *lda, 
                         float *s, float *u, magma_int_t *ldu, 
                         float *vt, magma_int_t *ldvt, 
                         float *work, magma_int_t *lwork, 
                         DWORKFORZ magma_int_t *info );
void    lapackf77_ssyev(const char *jobz, const char *uplo, magma_int_t *n, 
                         float *a, magma_int_t *lda, float *w, 
                         float *work, magma_int_t *lwork,
                         DWORKFORZ_AND_LD magma_int_t *info);
void    lapackf77_ssyevd(const char *jobz, const char *uplo, magma_int_t *n, 
                         float *a, magma_int_t *lda, float *w, 
                         float *work, magma_int_t *lwork,
                         DWORKFORZ_AND_LD magma_int_t *iwork, 
                         magma_int_t *liwork, magma_int_t *info);
void    lapackf77_ssygs2(int *itype, const char *uplo, int *n, 
                         float *a, int *lda, 
                         float *b, int *ldb, int *info);
void    lapackf77_ssygvd(magma_int_t *itype, const char *jobz, const char *uplo, 
                         magma_int_t *n, float *a, magma_int_t *lda,
                         float *b, magma_int_t *ldb, float *w,
                         float *work, magma_int_t *lwork, 
                         DWORKFORZ_AND_LD magma_int_t *iwork, magma_int_t *liwork,
                         magma_int_t *info);
void    lapackf77_ssytd2(const char *uplo, magma_int_t *n, 
                         float *a, magma_int_t *lda, 
                         float *d, float *e, float *tau, magma_int_t *info);
void    lapackf77_ssytrd(const char *uplo, magma_int_t *n, 
                         float *a, magma_int_t *lda, 
                         float *d, float *e, float *tau, 
                         float *work, magma_int_t *lwork, magma_int_t *info);
void    lapackf77_shseqr(const char *job, const char *compz, magma_int_t *n, 
                         magma_int_t *ilo, magma_int_t *ihi, 
                         float *H, magma_int_t *ldh, WSPLIT, 
                         float *Z, magma_int_t *ldz, 
                         float *work, magma_int_t *lwork, magma_int_t *info);
void    lapackf77_slacpy(const char *uplo, magma_int_t *m, magma_int_t *n, 
                         const float *a, magma_int_t *lda, 
                         float *b, magma_int_t *ldb);
void    lapackf77_slacgv(magma_int_t *n, float *x, magma_int_t *incx);
float  lapackf77_slange(const char *norm, magma_int_t *m, magma_int_t *n, 
                         const float *a, magma_int_t *lda, float *work);
float  lapackf77_slansy(const char *norm, const char *uplo, magma_int_t *n, 
                         const float *a, magma_int_t *lda, float * work);
float  lapackf77_slanst(char* norm, magma_int_t* n, 
                         const float* d, const float* e);
float  lapackf77_slansy(const char *norm, const char *uplo, magma_int_t *n, 
                         const float *a, magma_int_t *lda, float * work);
void    lapackf77_slarfb(const char *side, const char *trans, const char *direct, 
                         const char *storev, magma_int_t *m, magma_int_t *n, magma_int_t *k, 
                         const float *v, magma_int_t *ldv, 
                         const float *t, magma_int_t *ldt, 
                         float *c, magma_int_t *ldc, 
                         float *work, magma_int_t *ldwork);
void    lapackf77_slarfg(magma_int_t *n, float *alpha, 
                         float *x, magma_int_t *incx, float *tau);
void    lapackf77_slarft(const char *direct, const char *storev, magma_int_t *n, magma_int_t *k, 
                         float *v, magma_int_t *ldv, const float *tau, 
                         float *t, magma_int_t *ldt);
void    lapackf77_slarnv(magma_int_t *idist, magma_int_t *iseed, magma_int_t *n, 
                         float *x);
void    lapackf77_slartg(float *F, float *G, float *cs, 
                         float *SN, float *R);
void    lapackf77_slascl(const char *type, magma_int_t *kl, magma_int_t *ku, 
                         float *cfrom, float *cto, 
                         magma_int_t *m, magma_int_t *n, 
                         float *A, magma_int_t *lda, magma_int_t *info);
void    lapackf77_slaset(const char *uplo, magma_int_t *m, magma_int_t *n, 
                         float *alpha, float *beta,
                         float *A, magma_int_t *lda);
void    lapackf77_slaswp(magma_int_t *n, float *a, magma_int_t *lda, 
                         magma_int_t *k1, magma_int_t *k2, magma_int_t *ipiv,
                         magma_int_t *incx);
void    lapackf77_slatrd(const char *uplo, magma_int_t *n, magma_int_t *nb, 
                         float *a, magma_int_t *lda, float *e,
                         float *tau, float *work, magma_int_t *ldwork);
void    lapackf77_slabrd(magma_int_t *m, magma_int_t *n, magma_int_t *nb, 
                         float *a, magma_int_t *lda, float *d__, float *e, 
                         float *tauq, float *taup,
                         float *x, magma_int_t *ldx,
                         float *y, magma_int_t *ldy);
void    lapackf77_spotrf(const char *uplo, magma_int_t *n, 
                         float *a, magma_int_t *lda, magma_int_t *info);
void    lapackf77_spotrs(const char *uplo, magma_int_t *n, magma_int_t *nrhs,
                         float *a, magma_int_t *lda,
                         float *b, magma_int_t *ldb, magma_int_t *info);
void    lapackf77_spotri(const char *uplo, magma_int_t *n, 
                         float *a, magma_int_t *lda, magma_int_t *info);
void    lapackf77_slauum(const char *uplo, magma_int_t *n, 
                         float *a, magma_int_t *lda, magma_int_t *info);
void    lapackf77_slavsy(const char *uplo, const char *trans, const char *diag,
                         magma_int_t *n, magma_int_t *nrhs,
                         float *A, magma_int_t *lda,
                         magma_int_t *ipiv,
                         float *B, magma_int_t *ldb,
                         magma_int_t *info );
void     lapackf77_sposv(const char *uplo,
                         const magma_int_t *n, const magma_int_t *nrhs,
                         float *A, const magma_int_t *lda,
                         float *B,  const magma_int_t *ldb,
                         magma_int_t *info );
void    lapackf77_strevc(const char *side, const char *howmny, magma_int_t *select, magma_int_t *n, 
                         float *T,  magma_int_t *ldt,  float *VL, magma_int_t *ldvl,
                         float *VR, magma_int_t *ldvr, magma_int_t *MM, magma_int_t *M, 
                         float *work, DWORKFORZ magma_int_t *info);
void    lapackf77_sstebz(char *range, char *order, magma_int_t *n, float *vl, float *vu,
                         magma_int_t *il, magma_int_t *iu, float *abstol,
                         float *d__, float *e, magma_int_t *m, magma_int_t *nsplit,
                         float *w, magma_int_t *iblock, magma_int_t *isplit, float *work,
                         magma_int_t *iwork, magma_int_t *info);
float  lapackf77_slamc3(float* a, float* b);
void    lapackf77_slamrg(magma_int_t* n1, magma_int_t* n2, float* a, 
                         magma_int_t* dtrd1, magma_int_t* dtrd2, magma_int_t* index);
void    lapackf77_slaed4(magma_int_t* n, magma_int_t* i, float* d, float* z,
                         float* delta, float* rho, float* dlam, magma_int_t* info);
void    lapackf77_ssteqr(const char *compz, magma_int_t *n, float *D, float *E, 
                         float *Z, magma_int_t *ldz, 
                         float *work, magma_int_t *info);
void    lapackf77_sstedc(const char *compz, magma_int_t *n, float *D, float *E, 
                         float *Z, magma_int_t *ldz, 
                         float *work, magma_int_t *ldwork, 
                         DWORKFORZ_AND_LD magma_int_t *iwork, magma_int_t *liwork,
                         magma_int_t *info);
void    lapackf77_sstein(magma_int_t *n, float *d__, float *e, 
                         magma_int_t *m, float *w, magma_int_t *iblock, magma_int_t *isplit, 
                         float *z__, magma_int_t *ldz, float *work, magma_int_t *iwork, 
                         magma_int_t *ifail, magma_int_t *info);
void    lapackf77_sstemr(char *jobz, char *range, magma_int_t *n, float *d__, float *e, 
                         float *vl, float *vu, magma_int_t *il, magma_int_t *iu, magma_int_t *m,
                         float *w, float *z__, magma_int_t *ldz, magma_int_t *nzc, 
                         magma_int_t *isuppz, magma_int_t *tryrac, float *work, magma_int_t *lwork, 
                         magma_int_t *iwork, magma_int_t *liwork, magma_int_t *info);
void    lapackf77_strtri(const char *uplo, const char *diag, magma_int_t *n,
                         float *a, magma_int_t *lda, magma_int_t *info);
#if defined(PRECISION_z) || defined(PRECISION_c)
void    lapackf77_ssymv(const char *uplo, const magma_int_t *N, const float *alpha, 
                        const float *A, const magma_int_t *lda, 
                        const float *X, const magma_int_t *incX,
                        const float *beta, 
                        float *Y, const magma_int_t *incY);
#endif
void    lapackf77_sorg2r(magma_int_t *m, magma_int_t *n, magma_int_t *k, 
                         float *a, magma_int_t *lda,
                         const float *tau, float *work,
                         magma_int_t *info);
void    lapackf77_sorgbr(const char *vect, magma_int_t *m, magma_int_t *n, magma_int_t *k,
                         float *a, magma_int_t *lda, const float *tau,
                         float *work, magma_int_t *lwork, magma_int_t *info);
void    lapackf77_sorghr(magma_int_t *n, magma_int_t *ilo, magma_int_t *ihi, 
                         float *a, magma_int_t *lda, const float *tau,
                         float *work, magma_int_t *lwork, magma_int_t *info);
void    lapackf77_sorglq(magma_int_t *m, magma_int_t *n, magma_int_t *k, 
                         float *a, magma_int_t *lda, const float *tau, 
                         float *work, magma_int_t *ldwork, magma_int_t *info);
void    lapackf77_sorgql(magma_int_t *, magma_int_t *, magma_int_t *,
                         float *, magma_int_t *, float *, 
                         float *, magma_int_t *, magma_int_t *);
void    lapackf77_sorgqr(magma_int_t *m, magma_int_t *n, magma_int_t *k, 
                         float *a, magma_int_t *lda, const float *tau, 
                         float *work, magma_int_t *ldwork, magma_int_t *info);
void    lapackf77_sorgtr(const char *uplo, magma_int_t *n, 
                         float *a, magma_int_t *lda, const float *tau, 
                         float *work, magma_int_t *lwork, magma_int_t *info);
void    lapackf77_sorm2r(const char *side, const char *trans, 
                         magma_int_t *m, magma_int_t *n, magma_int_t *k, 
                         const float *a, magma_int_t *lda, 
                         const float *tau, float *c, magma_int_t *ldc,
                         float *work, magma_int_t *info);
void    lapackf77_sormbr(const char *vect, const char *side, const char *trans,
                         magma_int_t *M, magma_int_t *N, magma_int_t *K, 
                         float *A, magma_int_t *lda, float *Tau,
                         float *C, magma_int_t *ldc, 
                         float *work, magma_int_t *ldwork, magma_int_t *info);
void    lapackf77_sormlq(const char *side, const char *trans, 
                         magma_int_t *m, magma_int_t *n, magma_int_t *k,
                         const float *a, magma_int_t *lda, 
                         const float *tau, float *c, magma_int_t *ldc, 
                         float *work, magma_int_t *lwork, magma_int_t *info);
void    lapackf77_sormql(const char *side, const char *trans, 
                         magma_int_t *m, magma_int_t *n, magma_int_t *k,
                         const float *a, magma_int_t *lda, 
                         const float *tau, float *c, magma_int_t *ldc,
                         float *work, magma_int_t *lwork, magma_int_t *info);
void    lapackf77_sormqr(const char *side, const char *trans, 
                         magma_int_t *m, magma_int_t *n, magma_int_t *k, 
                         const float *a, magma_int_t *lda, 
                         const float *tau, float *c, magma_int_t *ldc, 
                         float *work, magma_int_t *lwork, magma_int_t *info);
void    lapackf77_sormtr(const char *side, const char *uplo, const char *trans,
                         magma_int_t *M, magma_int_t *N,
                         float *A, magma_int_t *lda, float *Tau,
                         float *C, magma_int_t *ldc, 
                         float *work, magma_int_t *ldwork, magma_int_t *info);


  /*
   * Testing functions
   */

#if defined(PRECISION_z) || defined(PRECISION_c)

void    lapackf77_sbdt01(int *m, int *n, int *kd, float *A, int *lda, 
                         float *Q, int *ldq, float *D, float *E, 
                         float *PT, int *ldpt, float *work, 
                         float *rwork, float *resid);
void    lapackf77_sget22(const char *transa, const char *transe, const char *transw, int *n,
                         float *a, int *lda, float *e, int *lde,
                         float *w, float *work,
                         float *rwork, float *result);
void    lapackf77_ssyt21(int *itype, const char *uplo, int *n, int *kband, 
                         float *A, int *lda, float *D, float *E, 
                         float *U, int *ldu, float *V, int *ldv, 
                         float *TAU, float *work,
                         float *rwork, float *result);
void    lapackf77_shst01(int *n, int *ilo, int *ihi, float *A, int *lda, 
                         float *H, int *ldh, float *Q, int *ldq,
                         float *work, int *lwork, float *rwork, float *result);
void    lapackf77_sstt21(int *n, int *kband, float *AD, float *AE, float *SD,
                         float *SE, float *U, int *ldu, 
                         float *work, float *rwork, float *result);
void    lapackf77_sort01(const char *rowcol, int *m, int *n, float *U, int *ldu,
                         float *work, int *lwork, float *rwork, float *resid);

#else

void    lapackf77_sbdt01(int *m, int *n, int *kd, float *A, int *lda, 
                         float *Q, int *ldq, float *D, float *E, 
                         float *PT, int *ldpt, 
                         float *work, float *resid);
void    lapackf77_sget22(const char *transa, const char *transe, const char *transw, int *n,
                         float *a, int *lda, float *e, int *lde,
                         float *wr, float *wi, 
                         float *work, float *result);
void    lapackf77_ssyt21(int *itype, const char *uplo, int *n, int *kband, 
                         float *A, int *lda, float *D, float *E,
                         float *U, int *ldu, float *V, int *ldv, 
                         float *TAU, float *work, float *result);
void    lapackf77_shst01(int *n, int *ilo, int *ihi, float *A, int *lda, 
                         float *H, int *ldh, float *Q, int *ldq, 
                         float *work, int *lwork, float *result);
void    lapackf77_sstt21(int *n, int *kband, float *AD, float *AE, float *SD, 
                         float *SE, float *U, int *ldu, 
                         float *work, float *result);
void    lapackf77_sort01(const char *rowcol, int *m, int *n, float *U, int *ldu,
                         float *work, int *lwork, float *resid);
#endif

void    lapackf77_slarfy(const char *uplo, int *N, float *V, int *incv, 
                         float *tau, float *C, int *ldc, 
                         float *work);
void    lapackf77_sqrt02(int *m, int *n, int *k, float *A, float *AF,
                         float *Q, float *R, int *lda, 
                         float *TAU, float *work, int *lwork,
                         float *rwork, float *result);

#ifdef __cplusplus
}
#endif

#undef DWORKFORZ 
#undef DWORKFORZ_AND_LD
#undef WSPLIT
#undef PRECISION_s
#endif /* MAGMA ZLAPACK */

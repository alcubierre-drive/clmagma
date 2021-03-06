!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!!  This file is AUTOMATICALLY GENERATED by:
!!  ../tools/fortran_wrappers.pl ../include/magma_s.i
!!  Do not edit.
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

module magma_sfortran

use magma_param

implicit none

!---- Fortran interfaces to MAGMA subroutines ----
interface

integer function magmaf_get_spotrf_nb( m )
    integer :: m
end function magmaf_get_spotrf_nb

integer function magmaf_get_sgetrf_nb( m )
    integer :: m
end function magmaf_get_sgetrf_nb

integer function magmaf_get_sgetri_nb( m )
    integer :: m
end function magmaf_get_sgetri_nb

integer function magmaf_get_sgeqrf_nb( m )
    integer :: m
end function magmaf_get_sgeqrf_nb

integer function magmaf_get_sgeqlf_nb( m )
    integer :: m
end function magmaf_get_sgeqlf_nb

integer function magmaf_get_sgehrd_nb( m )
    integer :: m
end function magmaf_get_sgehrd_nb

integer function magmaf_get_ssytrd_nb( m )
    integer :: m
end function magmaf_get_ssytrd_nb

integer function magmaf_get_sgelqf_nb( m )
    integer :: m
end function magmaf_get_sgelqf_nb

integer function magmaf_get_sgebrd_nb( m )
    integer :: m
end function magmaf_get_sgebrd_nb

integer function magmaf_get_ssygst_nb( m )
    integer :: m
end function magmaf_get_ssygst_nb

integer function magmaf_get_sgesvd_nb( m )
    integer :: m
end function magmaf_get_sgesvd_nb

subroutine magmaf_sgebrd( m, n, a, lda, d, e, tauq, taup, work, lwork, info, queue )
    integer          :: m
    integer          :: n
    real             :: a(*)
    integer          :: lda
    real             :: d(*)
    real             :: e(*)
    real             :: tauq(*)
    real             :: taup(*)
    real             :: work(*)
    integer          :: lwork
    integer          :: info
    integer          :: queue
end subroutine magmaf_sgebrd

subroutine magmaf_sgeqrf( m, n, A, lda, tau, work, lwork, info, queue )
    integer          :: m
    integer          :: n
    real             :: A(*)
    integer          :: lda
    real             :: tau(*)
    real             :: work(*)
    integer          :: lwork
    integer          :: info
    integer          :: queue(*)
end subroutine magmaf_sgeqrf

subroutine magmaf_sgesv( n, nrhs, A, lda, ipiv, B, ldb, info, queue )
    integer          :: n
    integer          :: nrhs
    real             :: A(*)
    integer          :: lda
    integer          :: ipiv(*)
    real             :: B(*)
    integer          :: ldb
    integer          :: info
    integer          :: queue(*)
end subroutine magmaf_sgesv

subroutine magmaf_sgetrf( m, n, A, lda, ipiv, info, queue )
    integer          :: m
    integer          :: n
    real             :: A(*)
    integer          :: lda
    integer          :: ipiv(*)
    integer          :: info
    integer          :: queue(*)
end subroutine magmaf_sgetrf

subroutine magmaf_sposv( uplo, n, nrhs, A, lda, B, ldb, info, queue )
    character        :: uplo
    integer          :: n
    integer          :: nrhs
    real             :: A(*)
    integer          :: lda
    real             :: B(*)
    integer          :: ldb
    integer          :: info
    integer          :: queue(*)
end subroutine magmaf_sposv

subroutine magmaf_spotrf( uplo, n, A, lda, info, queue )
    character        :: uplo
    integer          :: n
    real             :: A(*)
    integer          :: lda
    integer          :: info
    integer          :: queue(*)
end subroutine magmaf_spotrf

subroutine magmaf_sorghr( n, ilo, ihi, a, lda, tau, dT, dT_offset, nb, info, queue )
    integer          :: n
    integer          :: ilo
    integer          :: ihi
    real             :: a(*)
    integer          :: lda
    real             :: tau(*)
    magma_devptr_t :: dT
    integer          :: dT_offset
    integer          :: nb
    integer          :: info
    integer          :: queue
end subroutine magmaf_sorghr

subroutine magmaf_sorgqr( m, n, k, a, lda, tau, dT, dT_offset, nb, info, queue )
    integer          :: m
    integer          :: n
    integer          :: k
    real             :: a(*)
    integer          :: lda
    real             :: tau(*)
    magma_devptr_t :: dT
    integer          :: dT_offset
    integer          :: nb
    integer          :: info
    integer          :: queue
end subroutine magmaf_sorgqr

subroutine magmaf_sormtr( side, uplo, trans, m, n, a, lda, tau, c, ldc, work, lwork,  &
        info, queue )
    character        :: side
    character        :: uplo
    character        :: trans
    integer          :: m
    integer          :: n
    real             :: a(*)
    integer          :: lda
    real             :: tau(*)
    real             :: c(*)
    integer          :: ldc
    real             :: work(*)
    integer          :: lwork
    integer          :: info
    integer          :: queue
end subroutine magmaf_sormtr

subroutine magmaf_sormqr( side, trans, m, n, k, a, lda, tau, c, ldc, work, lwork, info,  &
        queue )
    character        :: side
    character        :: trans
    integer          :: m
    integer          :: n
    integer          :: k
    real             :: a(*)
    integer          :: lda
    real             :: tau(*)
    real             :: c(*)
    integer          :: ldc
    real             :: work(*)
    integer          :: lwork
    integer          :: info
    integer          :: queue
end subroutine magmaf_sormqr

subroutine magmaf_sormql( side, trans, m, n, k, a, lda, tau, c, ldc, work, lwork, info,  &
        queue )
    character        :: side
    character        :: trans
    integer          :: m
    integer          :: n
    integer          :: k
    real             :: a(*)
    integer          :: lda
    real             :: tau(*)
    real             :: c(*)
    integer          :: ldc
    real             :: work(*)
    integer          :: lwork
    integer          :: info
    integer          :: queue
end subroutine magmaf_sormql

subroutine magmaf_sgeev( jobvl, jobvr, n, a, lda, WR, WI, vl, ldvl, vr, ldvr, work,  &
        lwork, info, queue )
    character        :: jobvl
    character        :: jobvr
    integer          :: n
    real             :: a(*)
    integer          :: lda
    real             :: WR(*)
    real             :: WI(*)
    real             :: vl(*)
    integer          :: ldvl
    real             :: vr(*)
    integer          :: ldvr
    real             :: work(*)
    integer          :: lwork
    integer          :: info
    integer          :: queue
end subroutine magmaf_sgeev

subroutine magmaf_sgesvd( jobu, jobvt, m, n, a, lda, s, u, ldu, vt, ldvt, work, lwork,  &
        info, queue )
    character        :: jobu
    character        :: jobvt
    integer          :: m
    integer          :: n
    real             :: a(*)
    integer          :: lda
    real             :: s(*)
    real             :: u(*)
    integer          :: ldu
    real             :: vt(*)
    integer          :: ldvt
    real             :: work(*)
    integer          :: lwork
    integer          :: info
    integer          :: queue
end subroutine magmaf_sgesvd

subroutine magmaf_ssyevd( jobz, uplo, n, a, lda, w, work, lwork, iwork, liwork, info,  &
        queue )
    character        :: jobz
    character        :: uplo
    integer          :: n
    real             :: a(*)
    integer          :: lda
    real             :: w(*)
    real             :: work(*)
    integer          :: lwork
    integer          :: iwork(*)
    integer          :: liwork
    integer          :: info
    integer          :: queue
end subroutine magmaf_ssyevd

subroutine magmaf_sstedx( range, n, vl, vu, il, iu, d, e, z, ldz, rwork, lrwork, iwork,  &
        liwork, dwork, info, queue )
    character        :: range
    integer          :: n
    real             :: vl
    real             :: vu
    integer          :: il
    integer          :: iu
    real             :: d(*)
    real             :: e(*)
    real             :: z(*)
    integer          :: ldz
    real             :: rwork(*)
    integer          :: lrwork
    integer          :: iwork(*)
    integer          :: liwork
    magma_devptr_t :: dwork
    integer          :: info
    integer          :: queue
end subroutine magmaf_sstedx

subroutine magmaf_sgehrd( n, ilo, ihi, a, lda, tau, work, lwork, dT, dT_offset, info,  &
        queue )
    integer          :: n
    integer          :: ilo
    integer          :: ihi
    real             :: a(*)
    integer          :: lda
    real             :: tau(*)
    real             :: work(*)
    integer          :: lwork
    magma_devptr_t :: dT
    integer          :: dT_offset
    integer          :: info
    integer          :: queue
end subroutine magmaf_sgehrd

subroutine magmaf_ssytrd( uplo, n, a, lda, d, e, tau, work, lwork, info, queue )
    character        :: uplo
    integer          :: n
    real             :: a(*)
    integer          :: lda
    real             :: d(*)
    real             :: e(*)
    real             :: tau(*)
    real             :: work(*)
    integer          :: lwork
    integer          :: info
    integer          :: queue
end subroutine magmaf_ssytrd

subroutine magmaf_sprint( m, n, A, lda )
    integer          :: m
    integer          :: n
    real             :: A(*)
    integer          :: lda
end subroutine magmaf_sprint

end interface

!---- Fortran-only subroutines (see ../tools/fortran_wrappers.pl to edit) ----
contains

subroutine magmaf_soff1d( ptrNew, ptrOld, inc, i)
    magma_devptr_t   :: ptrNew
    magma_devptr_t   :: ptrOld
    integer          :: inc, i

    ptrNew = ptrOld + (i-1) * inc * sizeof_real
end subroutine magmaf_soff1d

subroutine magmaf_soff2d( ptrNew, ptrOld, lda, i, j)
    magma_devptr_t   :: ptrNew
    magma_devptr_t   :: ptrOld
    integer          :: lda, i, j

    ptrNew = ptrOld + ((j-1) * lda + (i-1)) * sizeof_real
end subroutine magmaf_soff2d

end module magma_sfortran

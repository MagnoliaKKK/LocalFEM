#include "blaswrap.h"
#include "f2c.h"

/* Subroutine */ int zhpcon_(char *uplo, integer *n, doublecomplex *ap, 
	integer *ipiv, doublereal *anorm, doublereal *rcond, doublecomplex *
	work, integer *info)
{
/*  -- LAPACK routine (version 3.1) --   
       Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd..   
       November 2006   

       Modified to call ZLACN2 in place of ZLACON, 10 Feb 03, SJH.   


    Purpose   
    =======   

    ZHPCON estimates the reciprocal of the condition number of a complex   
    Hermitian packed matrix A using the factorization A = U*D*U**H or   
    A = L*D*L**H computed by ZHPTRF.   

    An estimate is obtained for norm(inv(A)), and the reciprocal of the   
    condition number is computed as RCOND = 1 / (ANORM * norm(inv(A))).   

    Arguments   
    =========   

    UPLO    (input) CHARACTER*1   
            Specifies whether the details of the factorization are stored   
            as an upper or lower triangular matrix.   
            = 'U':  Upper triangular, form is A = U*D*U**H;   
            = 'L':  Lower triangular, form is A = L*D*L**H.   

    N       (input) INTEGER   
            The order of the matrix A.  N >= 0.   

    AP      (input) COMPLEX*16 array, dimension (N*(N+1)/2)   
            The block diagonal matrix D and the multipliers used to   
            obtain the factor U or L as computed by ZHPTRF, stored as a   
            packed triangular matrix.   

    IPIV    (input) INTEGER array, dimension (N)   
            Details of the interchanges and the block structure of D   
            as determined by ZHPTRF.   

    ANORM   (input) DOUBLE PRECISION   
            The 1-norm of the original matrix A.   

    RCOND   (output) DOUBLE PRECISION   
            The reciprocal of the condition number of the matrix A,   
            computed as RCOND = 1/(ANORM * AINVNM), where AINVNM is an   
            estimate of the 1-norm of inv(A) computed in this routine.   

    WORK    (workspace) COMPLEX*16 array, dimension (2*N)   

    INFO    (output) INTEGER   
            = 0:  successful exit   
            < 0:  if INFO = -i, the i-th argument had an illegal value   

    =====================================================================   


       Test the input parameters.   

       Parameter adjustments */
    /* Table of constant values */
    static integer c__1 = 1;
    
    /* System generated locals */
    integer i__1, i__2;
    /* Local variables */
    static integer i__, ip, kase;
    extern logical lsame_(char *, char *);
    static integer isave[3];
    static logical upper;
    extern /* Subroutine */ int zlacn2_(integer *, doublecomplex *, 
	    doublecomplex *, doublereal *, integer *, integer *), xerbla_(
	    char *, integer *);
    static doublereal ainvnm;
    extern /* Subroutine */ int zhptrs_(char *, integer *, integer *, 
	    doublecomplex *, integer *, doublecomplex *, integer *, integer *);


    --work;
    --ipiv;
    --ap;

    /* Function Body */
    *info = 0;
    upper = lsame_(uplo, "U");
    if (! upper && ! lsame_(uplo, "L")) {
	*info = -1;
    } else if (*n < 0) {
	*info = -2;
    } else if (*anorm < 0.) {
	*info = -5;
    }
    if (*info != 0) {
	i__1 = -(*info);
	xerbla_("ZHPCON", &i__1);
	return 0;
    }

/*     Quick return if possible */

    *rcond = 0.;
    if (*n == 0) {
	*rcond = 1.;
	return 0;
    } else if (*anorm <= 0.) {
	return 0;
    }

/*     Check that the diagonal matrix D is nonsingular. */

    if (upper) {

/*        Upper triangular storage: examine D from bottom to top */

	ip = *n * (*n + 1) / 2;
	for (i__ = *n; i__ >= 1; --i__) {
	    i__1 = ip;
	    if (ipiv[i__] > 0 && (ap[i__1].r == 0. && ap[i__1].i == 0.)) {
		return 0;
	    }
	    ip -= i__;
/* L10: */
	}
    } else {

/*        Lower triangular storage: examine D from top to bottom. */

	ip = 1;
	i__1 = *n;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    i__2 = ip;
	    if (ipiv[i__] > 0 && (ap[i__2].r == 0. && ap[i__2].i == 0.)) {
		return 0;
	    }
	    ip = ip + *n - i__ + 1;
/* L20: */
	}
    }

/*     Estimate the 1-norm of the inverse. */

    kase = 0;
L30:
    zlacn2_(n, &work[*n + 1], &work[1], &ainvnm, &kase, isave);
    if (kase != 0) {

/*        Multiply by inv(L*D*L') or inv(U*D*U'). */

	zhptrs_(uplo, n, &c__1, &ap[1], &ipiv[1], &work[1], n, info);
	goto L30;
    }

/*     Compute the estimate of the reciprocal condition number. */

    if (ainvnm != 0.) {
	*rcond = 1. / ainvnm / *anorm;
    }

    return 0;

/*     End of ZHPCON */

} /* zhpcon_ */

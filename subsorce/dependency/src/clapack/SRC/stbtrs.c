#include "blaswrap.h"
#include "f2c.h"

/* Subroutine */ int stbtrs_(char *uplo, char *trans, char *diag, integer *n, 
	integer *kd, integer *nrhs, real *ab, integer *ldab, real *b, integer 
	*ldb, integer *info  	)
{
/*  -- LAPACK routine (version 3.1) --   
       Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd..   
       November 2006   


    Purpose   
    =======   

    STBTRS solves a triangular system of the form   

       A * X = B  or  A**T * X = B,   

    where A is a triangular band matrix of order N, and B is an   
    N-by NRHS matrix.  A check is made to verify that A is nonsingular.   

    Arguments   
    =========   

    UPLO    (input) CHARACTER*1   
            = 'U':  A is upper triangular;   
            = 'L':  A is lower triangular.   

    TRANS   (input) CHARACTER*1   
            Specifies the form the system of equations:   
            = 'N':  A * X = B  (No transpose)   
            = 'T':  A**T * X = B  (Transpose)   
            = 'C':  A**H * X = B  (Conjugate transpose = Transpose)   

    DIAG    (input) CHARACTER*1   
            = 'N':  A is non-unit triangular;   
            = 'U':  A is unit triangular.   

    N       (input) INTEGER   
            The order of the matrix A.  N >= 0.   

    KD      (input) INTEGER   
            The number of superdiagonals or subdiagonals of the   
            triangular band matrix A.  KD >= 0.   

    NRHS    (input) INTEGER   
            The number of right hand sides, i.e., the number of columns   
            of the matrix B.  NRHS >= 0.   

    AB      (input) REAL array, dimension (LDAB,N)   
            The upper or lower triangular band matrix A, stored in the   
            first kd+1 rows of AB.  The j-th column of A is stored   
            in the j-th column of the array AB as follows:   
            if UPLO = 'U', AB(kd+1+i-j,j) = A(i,j) for max(1,j-kd)<=i<=j;   
            if UPLO = 'L', AB(1+i-j,j)    = A(i,j) for j<=i<=min(n,j+kd).   
            If DIAG = 'U', the diagonal elements of A are not referenced   
            and are assumed to be 1.   

    LDAB    (input) INTEGER   
            The leading dimension of the array AB.  LDAB >= KD+1.   

    B       (input/output) REAL array, dimension (LDB,NRHS)   
            On entry, the right hand side matrix B.   
            On exit, if INFO = 0, the solution matrix X.   

    LDB     (input) INTEGER   
            The leading dimension of the array B.  LDB >= max(1,N).   

    INFO    (output) INTEGER   
            = 0:  successful exit   
            < 0:  if INFO = -i, the i-th argument had an illegal value   
            > 0:  if INFO = i, the i-th diagonal element of A is zero,   
                  indicating that the matrix is singular and the   
                  solutions X have not been computed.   

    =====================================================================   


       Test the input parameters.   

       Parameter adjustments */
    /* Table of constant values */
    static integer c__1 = 1;
    
    /* System generated locals */
    integer ab_dim1, ab_offset, b_dim1, b_offset, i__1;
    /* Local variables */
    static integer j;
    extern logical lsame_(char *, char *);
    static logical upper;
    extern /* Subroutine */ int stbsv_(char *, char *, char *, integer *, 
	    integer *, real *, integer *, real *, integer *), xerbla_(char *, integer *);
    static logical nounit;


    ab_dim1 = *ldab;
    ab_offset = 1 + ab_dim1;
    ab -= ab_offset;
    b_dim1 = *ldb;
    b_offset = 1 + b_dim1;
    b -= b_offset;

    /* Function Body */
    *info = 0;
    nounit = lsame_(diag, "N");
    upper = lsame_(uplo, "U");
    if (! upper && ! lsame_(uplo, "L")) {
	*info = -1;
    } else if (! lsame_(trans, "N") && ! lsame_(trans, 
	    "T") && ! lsame_(trans, "C")) {
	*info = -2;
    } else if (! nounit && ! lsame_(diag, "U")) {
	*info = -3;
    } else if (*n < 0) {
	*info = -4;
    } else if (*kd < 0) {
	*info = -5;
    } else if (*nrhs < 0) {
	*info = -6;
    } else if (*ldab < *kd + 1) {
	*info = -8;
    } else if (*ldb < max(1,*n)) {
	*info = -10;
    }
    if (*info != 0) {
	i__1 = -(*info);
	xerbla_("STBTRS", &i__1);
	return 0;
    }

/*     Quick return if possible */

    if (*n == 0) {
	return 0;
    }

/*     Check for singularity. */

    if (nounit) {
	if (upper) {
	    i__1 = *n;
	    for (*info = 1; *info <= i__1; ++(*info)) {
		if (ab[*kd + 1 + *info * ab_dim1] == 0.f) {
		    return 0;
		}
/* L10: */
	    }
	} else {
	    i__1 = *n;
	    for (*info = 1; *info <= i__1; ++(*info)) {
		if (ab[*info * ab_dim1 + 1] == 0.f) {
		    return 0;
		}
/* L20: */
	    }
	}
    }
    *info = 0;

/*     Solve A * X = B  or  A' * X = B. */

    i__1 = *nrhs;
    for (j = 1; j <= i__1; ++j) {
	stbsv_(uplo, trans, diag, n, kd, &ab[ab_offset], ldab, &b[j * b_dim1 
		+ 1], &c__1);
/* L30: */
    }

    return 0;

/*     End of STBTRS */

} /* stbtrs_ */

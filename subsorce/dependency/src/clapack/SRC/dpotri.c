#include "blaswrap.h"
#include "f2c.h"

/* Subroutine */ int dpotri_(char *uplo, integer *n, doublereal *a, integer *
	lda, integer *info)
{
/*  -- LAPACK routine (version 3.1) --   
       Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd..   
       November 2006   


    Purpose   
    =======   

    DPOTRI computes the inverse of a real symmetric positive definite   
    matrix A using the Cholesky factorization A = U**T*U or A = L*L**T   
    computed by DPOTRF.   

    Arguments   
    =========   

    UPLO    (input) CHARACTER*1   
            = 'U':  Upper triangle of A is stored;   
            = 'L':  Lower triangle of A is stored.   

    N       (input) INTEGER   
            The order of the matrix A.  N >= 0.   

    A       (input/output) DOUBLE PRECISION array, dimension (LDA,N)   
            On entry, the triangular factor U or L from the Cholesky   
            factorization A = U**T*U or A = L*L**T, as computed by   
            DPOTRF.   
            On exit, the upper or lower triangle of the (symmetric)   
            inverse of A, overwriting the input factor U or L.   

    LDA     (input) INTEGER   
            The leading dimension of the array A.  LDA >= max(1,N).   

    INFO    (output) INTEGER   
            = 0:  successful exit   
            < 0:  if INFO = -i, the i-th argument had an illegal value   
            > 0:  if INFO = i, the (i,i) element of the factor U or L is   
                  zero, and the inverse could not be computed.   

    =====================================================================   


       Test the input parameters.   

       Parameter adjustments */
    /* System generated locals */
    integer a_dim1, a_offset, i__1;
    /* Local variables */
    extern logical lsame_(char *, char *);
    extern /* Subroutine */ int xerbla_(char *, integer *), dlauum_(
	    char *, integer *, doublereal *, integer *, integer *), 
	    dtrtri_(char *, char *, integer *, doublereal *, integer *, 
	    integer *);

    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;

    /* Function Body */
    *info = 0;
    if (! lsame_(uplo, "U") && ! lsame_(uplo, "L")) {
	*info = -1;
    } else if (*n < 0) {
	*info = -2;
    } else if (*lda < max(1,*n)) {
	*info = -4;
    }
    if (*info != 0) {
	i__1 = -(*info);
	xerbla_("DPOTRI", &i__1);
	return 0;
    }

/*     Quick return if possible */

    if (*n == 0) {
	return 0;
    }

/*     Invert the triangular Cholesky factor U or L. */

    dtrtri_(uplo, "Non-unit", n, &a[a_offset], lda, info);
    if (*info > 0) {
	return 0;
    }

/*     Form inv(U)*inv(U)' or inv(L)'*inv(L). */

    dlauum_(uplo, n, &a[a_offset], lda, info);

    return 0;

/*     End of DPOTRI */

} /* dpotri_ */

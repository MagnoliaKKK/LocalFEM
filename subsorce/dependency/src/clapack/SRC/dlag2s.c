#include "blaswrap.h"
#include "f2c.h"

/* Subroutine */ int dlag2s_(integer *m, integer *n, doublereal *a, integer *
	lda, real *sa, integer *ldsa, integer *info)
{
/*  -- LAPACK PROTOTYPE auxiliary routine (version 3.1.1) --   
       Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd..   
       January 2007   

       This is an LAPACK PROTOTYPE routine which means that the   
       interface of this routine is likely to be changed in the future   
       based on community feedback.   


    Purpose   
    =======   

    DLAG2S converts a DOUBLE PRECISION matrix, SA, to a SINGLE   
    PRECISION matrix, A.   

    RMAX is the overflow for the SINGLE PRECISION arithmetic   
    DLAG2S checks that all the entries of A are between -RMAX and   
    RMAX. If not the convertion is aborted and a flag is raised.   

    This is a helper routine so there is no argument checking.   

    Arguments   
    =========   

    M       (input) INTEGER   
            The number of lines of the matrix A.  M >= 0.   

    N       (input) INTEGER   
            The number of columns of the matrix A.  N >= 0.   

    A       (input) DOUBLE PRECISION array, dimension (LDA,N)   
            On entry, the M-by-N coefficient matrix A.   

    LDA     (input) INTEGER   
            The leading dimension of the array A.  LDA >= max(1,M).   

    SA      (output) REAL array, dimension (LDSA,N)   
            On exit, if INFO=0, the M-by-N coefficient matrix SA.   

    LDSA    (input) INTEGER   
            The leading dimension of the array SA.  LDSA >= max(1,M).   

    INFO    (output) INTEGER   
            = 0:  successful exit   
            > 0:  if INFO = k, the (i,j) entry of the matrix A has   
                  overflowed when moving from DOUBLE PRECISION to SINGLE   
                  k is given by k = (i-1)*LDA+j   

    =========   


       Parameter adjustments */
    /* System generated locals */
    integer sa_dim1, sa_offset, a_dim1, a_offset, i__1, i__2;
    /* Local variables */
    static integer i__, j;
    static doublereal rmax;
    extern doublereal slamch_(char *);

    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;
    sa_dim1 = *ldsa;
    sa_offset = 1 + sa_dim1;
    sa -= sa_offset;

    /* Function Body */
    rmax = slamch_("O");
    i__1 = *n;
    for (j = 1; j <= i__1; ++j) {
	i__2 = *m;
	for (i__ = 1; i__ <= i__2; ++i__) {
	    if (a[i__ + j * a_dim1] < -rmax || a[i__ + j * a_dim1] > rmax) {
		*info = (i__ - 1) * *lda + j;
		goto L10;
	    }
	    sa[i__ + j * sa_dim1] = a[i__ + j * a_dim1];
/* L30: */
	}
/* L20: */
    }
L10:
    return 0;

/*     End of DLAG2S */

} /* dlag2s_ */

#include "blaswrap.h"
#include "f2c.h"

/* Subroutine */ int slartg_(real *f, real *g, real *cs, real *sn, real *r__)
{
/*  -- LAPACK auxiliary routine (version 3.1) --   
       Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd..   
       November 2006   


    Purpose   
    =======   

    SLARTG generate a plane rotation so that   

       [  CS  SN  ]  .  [ F ]  =  [ R ]   where CS**2 + SN**2 = 1.   
       [ -SN  CS  ]     [ G ]     [ 0 ]   

    This is a slower, more accurate version of the BLAS1 routine SROTG,   
    with the following other differences:   
       F and G are unchanged on return.   
       If G=0, then CS=1 and SN=0.   
       If F=0 and (G .ne. 0), then CS=0 and SN=1 without doing any   
          floating point operations (saves work in SBDSQR when   
          there are zeros on the diagonal).   

    If F exceeds G in magnitude, CS will be positive.   

    Arguments   
    =========   

    F       (input) REAL   
            The first component of vector to be rotated.   

    G       (input) REAL   
            The second component of vector to be rotated.   

    CS      (output) REAL   
            The cosine of the rotation.   

    SN      (output) REAL   
            The sine of the rotation.   

    R       (output) REAL   
            The nonzero component of the rotated vector.   

    This version has a few statements commented out for thread safety   
    (machine parameters are computed on each entry). 10 feb 03, SJH.   

    =====================================================================   

       LOGICAL            FIRST   
       SAVE               FIRST, SAFMX2, SAFMIN, SAFMN2   
       DATA               FIRST / .TRUE. /   

       IF( FIRST ) THEN */
    /* System generated locals */
    integer i__1;
    real r__1, r__2;
    /* Builtin functions */
    double log(doublereal), pow_ri(real *, integer *), sqrt(doublereal);
    /* Local variables */
    static integer i__;
    static real f1, g1, eps, scale;
    static integer count;
    static real safmn2, safmx2;
    extern doublereal slamch_(char *);
    static real safmin;

    safmin = slamch_("S");
    eps = slamch_("E");
    r__1 = slamch_("B");
    i__1 = (integer) (log(safmin / eps) / log(slamch_("B")) / 2.f);
    safmn2 = pow_ri(&r__1, &i__1);
    safmx2 = 1.f / safmn2;
/*        FIRST = .FALSE.   
       END IF */
    if (*g == 0.f) {
	*cs = 1.f;
	*sn = 0.f;
	*r__ = *f;
    } else if (*f == 0.f) {
	*cs = 0.f;
	*sn = 1.f;
	*r__ = *g;
    } else {
	f1 = *f;
	g1 = *g;
/* Computing MAX */
	r__1 = dabs(f1), r__2 = dabs(g1);
	scale = dmax(r__1,r__2);
	if (scale >= safmx2) {
	    count = 0;
L10:
	    ++count;
	    f1 *= safmn2;
	    g1 *= safmn2;
/* Computing MAX */
	    r__1 = dabs(f1), r__2 = dabs(g1);
	    scale = dmax(r__1,r__2);
	    if (scale >= safmx2) {
		goto L10;
	    }
/* Computing 2nd power */
	    r__1 = f1;
/* Computing 2nd power */
	    r__2 = g1;
	    *r__ = sqrt(r__1 * r__1 + r__2 * r__2);
	    *cs = f1 / *r__;
	    *sn = g1 / *r__;
	    i__1 = count;
	    for (i__ = 1; i__ <= i__1; ++i__) {
		*r__ *= safmx2;
/* L20: */
	    }
	} else if (scale <= safmn2) {
	    count = 0;
L30:
	    ++count;
	    f1 *= safmx2;
	    g1 *= safmx2;
/* Computing MAX */
	    r__1 = dabs(f1), r__2 = dabs(g1);
	    scale = dmax(r__1,r__2);
	    if (scale <= safmn2) {
		goto L30;
	    }
/* Computing 2nd power */
	    r__1 = f1;
/* Computing 2nd power */
	    r__2 = g1;
	    *r__ = sqrt(r__1 * r__1 + r__2 * r__2);
	    *cs = f1 / *r__;
	    *sn = g1 / *r__;
	    i__1 = count;
	    for (i__ = 1; i__ <= i__1; ++i__) {
		*r__ *= safmn2;
/* L40: */
	    }
	} else {
/* Computing 2nd power */
	    r__1 = f1;
/* Computing 2nd power */
	    r__2 = g1;
	    *r__ = sqrt(r__1 * r__1 + r__2 * r__2);
	    *cs = f1 / *r__;
	    *sn = g1 / *r__;
	}
	if (dabs(*f) > dabs(*g) && *cs < 0.f) {
	    *cs = -(*cs);
	    *sn = -(*sn);
	    *r__ = -(*r__);
	}
    }
    return 0;

/*     End of SLARTG */

} /* slartg_ */

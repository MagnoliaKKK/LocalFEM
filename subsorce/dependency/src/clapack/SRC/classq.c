#include "blaswrap.h"
#include "f2c.h"

/* Subroutine */ int classq_(integer *n, complex *x, integer *incx, real *
	scale, real *sumsq)
{
/*  -- LAPACK auxiliary routine (version 3.1) --   
       Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd..   
       November 2006   


    Purpose   
    =======   

    CLASSQ returns the values scl and ssq such that   

       ( scl**2 )*ssq = x( 1 )**2 +...+ x( n )**2 + ( scale**2 )*sumsq,   

    where x( i ) = abs( X( 1 + ( i - 1 )*INCX ) ). The value of sumsq is   
    assumed to be at least unity and the value of ssq will then satisfy   

       1.0 .le. ssq .le. ( sumsq + 2*n ).   

    scale is assumed to be non-negative and scl returns the value   

       scl = max( scale, abs( real( x( i ) ) ), abs( aimag( x( i ) ) ) ),   
              i   

    scale and sumsq must be supplied in SCALE and SUMSQ respectively.   
    SCALE and SUMSQ are overwritten by scl and ssq respectively.   

    The routine makes only one pass through the vector X.   

    Arguments   
    =========   

    N       (input) INTEGER   
            The number of elements to be used from the vector X.   

    X       (input) COMPLEX array, dimension (N)   
            The vector x as described above.   
               x( i )  = X( 1 + ( i - 1 )*INCX ), 1 <= i <= n.   

    INCX    (input) INTEGER   
            The increment between successive values of the vector X.   
            INCX > 0.   

    SCALE   (input/output) REAL   
            On entry, the value  scale  in the equation above.   
            On exit, SCALE is overwritten with the value  scl .   

    SUMSQ   (input/output) REAL   
            On entry, the value  sumsq  in the equation above.   
            On exit, SUMSQ is overwritten with the value  ssq .   

   =====================================================================   


       Parameter adjustments */
    /* System generated locals */
    integer i__1, i__2, i__3;
    real r__1;
    /* Builtin functions */
    double r_imag(complex *);
    /* Local variables */
    static integer ix;
    static real temp1;

    --x;

    /* Function Body */
    if (*n > 0) {
	i__1 = (*n - 1) * *incx + 1;
	i__2 = *incx;
	for (ix = 1; i__2 < 0 ? ix >= i__1 : ix <= i__1; ix += i__2) {
	    i__3 = ix;
	    if (x[i__3].r != 0.f) {
		i__3 = ix;
		temp1 = (r__1 = x[i__3].r, dabs(r__1));
		if (*scale < temp1) {
/* Computing 2nd power */
		    r__1 = *scale / temp1;
		    *sumsq = *sumsq * (r__1 * r__1) + 1;
		    *scale = temp1;
		} else {
/* Computing 2nd power */
		    r__1 = temp1 / *scale;
		    *sumsq += r__1 * r__1;
		}
	    }
	    if (r_imag(&x[ix]) != 0.f) {
		temp1 = (r__1 = r_imag(&x[ix]), dabs(r__1));
		if (*scale < temp1) {
/* Computing 2nd power */
		    r__1 = *scale / temp1;
		    *sumsq = *sumsq * (r__1 * r__1) + 1;
		    *scale = temp1;
		} else {
/* Computing 2nd power */
		    r__1 = temp1 / *scale;
		    *sumsq += r__1 * r__1;
		}
	    }
/* L10: */
	}
    }

    return 0;

/*     End of CLASSQ */

} /* classq_ */

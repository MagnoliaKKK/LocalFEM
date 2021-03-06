#include "blaswrap.h"
#include "f2c.h"

/* Subroutine */ int slarra_(integer *n, real *d__, real *e, real *e2, real *
	spltol, real *tnrm, integer *nsplit, integer *isplit, integer *info)
{
/*  -- LAPACK auxiliary routine (version 3.1) --   
       Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd..   
       November 2006   


    Purpose   
    =======   

    Compute the splitting points with threshold SPLTOL.   
    SLARRA sets any "small" off-diagonal elements to zero.   

    Arguments   
    =========   

    N       (input) INTEGER   
            The order of the matrix. N > 0.   

    D       (input) REAL             array, dimension (N)   
            On entry, the N diagonal elements of the tridiagonal   
            matrix T.   

    E       (input/output) REAL             array, dimension (N)   
            On entry, the first (N-1) entries contain the subdiagonal   
            elements of the tridiagonal matrix T; E(N) need not be set.   
            On exit, the entries E( ISPLIT( I ) ), 1 <= I <= NSPLIT,   
            are set to zero, the other entries of E are untouched.   

    E2      (input/output) REAL             array, dimension (N)   
            On entry, the first (N-1) entries contain the SQUARES of the   
            subdiagonal elements of the tridiagonal matrix T;   
            E2(N) need not be set.   
            On exit, the entries E2( ISPLIT( I ) ),   
            1 <= I <= NSPLIT, have been set to zero   

    SPLTOL (input) REAL   
            The threshold for splitting. Two criteria can be used:   
            SPLTOL<0 : criterion based on absolute off-diagonal value   
            SPLTOL>0 : criterion that preserves relative accuracy   

    TNRM (input) REAL   
            The norm of the matrix.   

    NSPLIT  (output) INTEGER   
            The number of blocks T splits into. 1 <= NSPLIT <= N.   

    ISPLIT  (output) INTEGER array, dimension (N)   
            The splitting points, at which T breaks up into blocks.   
            The first block consists of rows/columns 1 to ISPLIT(1),   
            the second of rows/columns ISPLIT(1)+1 through ISPLIT(2),   
            etc., and the NSPLIT-th consists of rows/columns   
            ISPLIT(NSPLIT-1)+1 through ISPLIT(NSPLIT)=N.   


    INFO    (output) INTEGER   
            = 0:  successful exit   

    Further Details   
    ===============   

    Based on contributions by   
       Beresford Parlett, University of California, Berkeley, USA   
       Jim Demmel, University of California, Berkeley, USA   
       Inderjit Dhillon, University of Texas, Austin, USA   
       Osni Marques, LBNL/NERSC, USA   
       Christof Voemel, University of California, Berkeley, USA   

    =====================================================================   


       Parameter adjustments */
    /* System generated locals */
    integer i__1;
    real r__1, r__2;
    /* Builtin functions */
    double sqrt(doublereal);
    /* Local variables */
    static integer i__;
    static real tmp1, eabs;

    --isplit;
    --e2;
    --e;
    --d__;

    /* Function Body */
    *info = 0;
/*     Compute splitting points */
    *nsplit = 1;
    if (*spltol < 0.f) {
/*        Criterion based on absolute off-diagonal value */
	tmp1 = dabs(*spltol) * *tnrm;
	i__1 = *n - 1;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    eabs = (r__1 = e[i__], dabs(r__1));
	    if (eabs <= tmp1) {
		e[i__] = 0.f;
		e2[i__] = 0.f;
		isplit[*nsplit] = i__;
		++(*nsplit);
	    }
/* L9: */
	}
    } else {
/*        Criterion that guarantees relative accuracy */
	i__1 = *n - 1;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    eabs = (r__1 = e[i__], dabs(r__1));
	    if (eabs <= *spltol * sqrt((r__1 = d__[i__], dabs(r__1))) * sqrt((
		    r__2 = d__[i__ + 1], dabs(r__2)))) {
		e[i__] = 0.f;
		e2[i__] = 0.f;
		isplit[*nsplit] = i__;
		++(*nsplit);
	    }
/* L10: */
	}
    }
    isplit[*nsplit] = *n;
    return 0;

/*     End of SLARRA */

} /* slarra_ */

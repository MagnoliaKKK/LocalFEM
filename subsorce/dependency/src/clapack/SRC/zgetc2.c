#include "blaswrap.h"
#include "f2c.h"

/* Subroutine */ int zgetc2_(integer *n, doublecomplex *a, integer *lda, 
	integer *ipiv, integer *jpiv, integer *info)
{
/*  -- LAPACK auxiliary routine (version 3.1) --   
       Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd..   
       November 2006   


    Purpose   
    =======   

    ZGETC2 computes an LU factorization, using complete pivoting, of the   
    n-by-n matrix A. The factorization has the form A = P * L * U * Q,   
    where P and Q are permutation matrices, L is lower triangular with   
    unit diagonal elements and U is upper triangular.   

    This is a level 1 BLAS version of the algorithm.   

    Arguments   
    =========   

    N       (input) INTEGER   
            The order of the matrix A. N >= 0.   

    A       (input/output) COMPLEX*16 array, dimension (LDA, N)   
            On entry, the n-by-n matrix to be factored.   
            On exit, the factors L and U from the factorization   
            A = P*L*U*Q; the unit diagonal elements of L are not stored.   
            If U(k, k) appears to be less than SMIN, U(k, k) is given the   
            value of SMIN, giving a nonsingular perturbed system.   

    LDA     (input) INTEGER   
            The leading dimension of the array A.  LDA >= max(1, N).   

    IPIV    (output) INTEGER array, dimension (N).   
            The pivot indices; for 1 <= i <= N, row i of the   
            matrix has been interchanged with row IPIV(i).   

    JPIV    (output) INTEGER array, dimension (N).   
            The pivot indices; for 1 <= j <= N, column j of the   
            matrix has been interchanged with column JPIV(j).   

    INFO    (output) INTEGER   
             = 0: successful exit   
             > 0: if INFO = k, U(k, k) is likely to produce overflow if   
                  one tries to solve for x in Ax = b. So U is perturbed   
                  to avoid the overflow.   

    Further Details   
    ===============   

    Based on contributions by   
       Bo Kagstrom and Peter Poromaa, Department of Computing Science,   
       Umea University, S-901 87 Umea, Sweden.   

    =====================================================================   


       Set constants to control overflow   

       Parameter adjustments */
    /* Table of constant values */
    static integer c__1 = 1;
    static doublecomplex c_b10 = {-1.,-0.};
    
    /* System generated locals */
    integer a_dim1, a_offset, i__1, i__2, i__3;
    doublereal d__1;
    doublecomplex z__1;
    /* Builtin functions */
    double z_abs(doublecomplex *);
    void z_div(doublecomplex *, doublecomplex *, doublecomplex *);
    /* Local variables */
    static integer i__, j, ip, jp;
    static doublereal eps;
    static integer ipv, jpv;
    static doublereal smin, xmax;
    extern /* Subroutine */ int zgeru_(integer *, integer *, doublecomplex *, 
	    doublecomplex *, integer *, doublecomplex *, integer *, 
	    doublecomplex *, integer *), zswap_(integer *, doublecomplex *, 
	    integer *, doublecomplex *, integer *), dlabad_(doublereal *, 
	    doublereal *);
    extern doublereal dlamch_(char *);
    static doublereal bignum, smlnum;


    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;
    --ipiv;
    --jpiv;

    /* Function Body */
    *info = 0;
    eps = dlamch_("P");
    smlnum = dlamch_("S") / eps;
    bignum = 1. / smlnum;
    dlabad_(&smlnum, &bignum);

/*     Factorize A using complete pivoting.   
       Set pivots less than SMIN to SMIN */

    i__1 = *n - 1;
    for (i__ = 1; i__ <= i__1; ++i__) {

/*        Find max element in matrix A */

	xmax = 0.;
	i__2 = *n;
	for (ip = i__; ip <= i__2; ++ip) {
	    i__3 = *n;
	    for (jp = i__; jp <= i__3; ++jp) {
		if (z_abs(&a[ip + jp * a_dim1]) >= xmax) {
		    xmax = z_abs(&a[ip + jp * a_dim1]);
		    ipv = ip;
		    jpv = jp;
		}
/* L10: */
	    }
/* L20: */
	}
	if (i__ == 1) {
/* Computing MAX */
	    d__1 = eps * xmax;
	    smin = max(d__1,smlnum);
	}

/*        Swap rows */

	if (ipv != i__) {
	    zswap_(n, &a[ipv + a_dim1], lda, &a[i__ + a_dim1], lda);
	}
	ipiv[i__] = ipv;

/*        Swap columns */

	if (jpv != i__) {
	    zswap_(n, &a[jpv * a_dim1 + 1], &c__1, &a[i__ * a_dim1 + 1], &
		    c__1);
	}
	jpiv[i__] = jpv;

/*        Check for singularity */

	if (z_abs(&a[i__ + i__ * a_dim1]) < smin) {
	    *info = i__;
	    i__2 = i__ + i__ * a_dim1;
	    z__1.r = smin, z__1.i = 0.;
	    a[i__2].r = z__1.r, a[i__2].i = z__1.i;
	}
	i__2 = *n;
	for (j = i__ + 1; j <= i__2; ++j) {
	    i__3 = j + i__ * a_dim1;
	    z_div(&z__1, &a[j + i__ * a_dim1], &a[i__ + i__ * a_dim1]);
	    a[i__3].r = z__1.r, a[i__3].i = z__1.i;
/* L30: */
	}
	i__2 = *n - i__;
	i__3 = *n - i__;
	zgeru_(&i__2, &i__3, &c_b10, &a[i__ + 1 + i__ * a_dim1], &c__1, &a[
		i__ + (i__ + 1) * a_dim1], lda, &a[i__ + 1 + (i__ + 1) * 
		a_dim1], lda);
/* L40: */
    }

    if (z_abs(&a[*n + *n * a_dim1]) < smin) {
	*info = *n;
	i__1 = *n + *n * a_dim1;
	z__1.r = smin, z__1.i = 0.;
	a[i__1].r = z__1.r, a[i__1].i = z__1.i;
    }
    return 0;

/*     End of ZGETC2 */

} /* zgetc2_ */

#include "blaswrap.h"
#include "f2c.h"

/* Subroutine */ int cgeql2_(integer *m, integer *n, complex *a, integer *lda,
	 complex *tau, complex *work, integer *info)
{
/*  -- LAPACK routine (version 3.1) --   
       Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd..   
       November 2006   


    Purpose   
    =======   

    CGEQL2 computes a QL factorization of a complex m by n matrix A:   
    A = Q * L.   

    Arguments   
    =========   

    M       (input) INTEGER   
            The number of rows of the matrix A.  M >= 0.   

    N       (input) INTEGER   
            The number of columns of the matrix A.  N >= 0.   

    A       (input/output) COMPLEX array, dimension (LDA,N)   
            On entry, the m by n matrix A.   
            On exit, if m >= n, the lower triangle of the subarray   
            A(m-n+1:m,1:n) contains the n by n lower triangular matrix L;   
            if m <= n, the elements on and below the (n-m)-th   
            superdiagonal contain the m by n lower trapezoidal matrix L;   
            the remaining elements, with the array TAU, represent the   
            unitary matrix Q as a product of elementary reflectors   
            (see Further Details).   

    LDA     (input) INTEGER   
            The leading dimension of the array A.  LDA >= max(1,M).   

    TAU     (output) COMPLEX array, dimension (min(M,N))   
            The scalar factors of the elementary reflectors (see Further   
            Details).   

    WORK    (workspace) COMPLEX array, dimension (N)   

    INFO    (output) INTEGER   
            = 0: successful exit   
            < 0: if INFO = -i, the i-th argument had an illegal value   

    Further Details   
    ===============   

    The matrix Q is represented as a product of elementary reflectors   

       Q = H(k) . . . H(2) H(1), where k = min(m,n).   

    Each H(i) has the form   

       H(i) = I - tau * v * v'   

    where tau is a complex scalar, and v is a complex vector with   
    v(m-k+i+1:m) = 0 and v(m-k+i) = 1; v(1:m-k+i-1) is stored on exit in   
    A(1:m-k+i-1,n-k+i), and tau in TAU(i).   

    =====================================================================   


       Test the input arguments   

       Parameter adjustments */
    /* Table of constant values */
    static integer c__1 = 1;
    
    /* System generated locals */
    integer a_dim1, a_offset, i__1, i__2;
    complex q__1;
    /* Builtin functions */
    void r_cnjg(complex *, complex *);
    /* Local variables */
    static integer i__, k;
    static complex alpha;
    extern /* Subroutine */ int clarf_(char *, integer *, integer *, complex *
	    , integer *, complex *, complex *, integer *, complex *), 
	    clarfg_(integer *, complex *, complex *, integer *, complex *), 
	    xerbla_(char *, integer *);


    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;
    --tau;
    --work;

    /* Function Body */
    *info = 0;
    if (*m < 0) {
	*info = -1;
    } else if (*n < 0) {
	*info = -2;
    } else if (*lda < max(1,*m)) {
	*info = -4;
    }
    if (*info != 0) {
	i__1 = -(*info);
	xerbla_("CGEQL2", &i__1);
	return 0;
    }

    k = min(*m,*n);

    for (i__ = k; i__ >= 1; --i__) {

/*        Generate elementary reflector H(i) to annihilate   
          A(1:m-k+i-1,n-k+i) */

	i__1 = *m - k + i__ + (*n - k + i__) * a_dim1;
	alpha.r = a[i__1].r, alpha.i = a[i__1].i;
	i__1 = *m - k + i__;
	clarfg_(&i__1, &alpha, &a[(*n - k + i__) * a_dim1 + 1], &c__1, &tau[
		i__]);

/*        Apply H(i)' to A(1:m-k+i,1:n-k+i-1) from the left */

	i__1 = *m - k + i__ + (*n - k + i__) * a_dim1;
	a[i__1].r = 1.f, a[i__1].i = 0.f;
	i__1 = *m - k + i__;
	i__2 = *n - k + i__ - 1;
	r_cnjg(&q__1, &tau[i__]);
	clarf_("Left", &i__1, &i__2, &a[(*n - k + i__) * a_dim1 + 1], &c__1, &
		q__1, &a[a_offset], lda, &work[1]);
	i__1 = *m - k + i__ + (*n - k + i__) * a_dim1;
	a[i__1].r = alpha.r, a[i__1].i = alpha.i;
/* L10: */
    }
    return 0;

/*     End of CGEQL2 */

} /* cgeql2_ */

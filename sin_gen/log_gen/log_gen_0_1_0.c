#include "myhead.h"

#define BIT 0
#define BITNUM 1
#define DEGREE 1

static const long long	twop0 =
{ 0x3ff0000000000000ll }; // 1

static const double twopm0 = 1.0000000000e+00;

static const DL	log2_lead =
{ .l = 0x3fe62e42fefa4000 };

static const DL	log2_trail =
{ .l = 0xbd48432a1b0e2634 };

static const DL
C = {
	.l = 0x3caffffffffffffe
};
static const DL
logtabhi[BITNUM] = {
	{.l = 0x0000000000000000}
};

static const DL
logtablo[BITNUM] = {
	{.l = 0x0000000000000000}
};

static const DL
log_ru[BITNUM] = {
	{.l = 0x3ff0000000000000}
};

double log_gen(double x) {
	_UL ix;
	int	m, k;
	double	w, u, t, xmu, q, l_lead, l_trail, result;

	/* extract exponent and sign of x for some quick screening */

	ix = *(unsigned long long *)(&x);	/* copy arg to a long long */

	m = (ix >> DMANTWIDTH);		/* shift off mantissa	*/

	m -= DEXPBIAS;

	/* normalize x and compute the nearest 1/1th to x */

	ix &= DMANTISSA;	/* get the mantissa of x */
	ix |= twop0;	/* set exponent of x to 0 */

	w = *(double *)(&ix);
	k = w;
	u = k;

	k -= BITNUM; // the number 1 here is for zhengshu bit "1"

	xmu = twopm0*(w - u);

	t = log_ru[k].d*xmu;

	/* avoid loss of significance for values of x near two
		by adjusting index; effectively u is divided by two.
		The logtable has been adjusted for this.
	*/

	if (k > 0)
		m++;

	l_lead = logtabhi[k].d;
	l_trail = logtablo[k].d;
	l_lead += m * log2_lead.d;
	l_trail += m * log2_trail.d;

	result = l_lead + (l_trail + C.d);
if (x == 1) {
	result = 0;
}

	return result;
}

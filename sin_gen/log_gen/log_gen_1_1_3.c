#include "myhead.h"

#define BIT 1
#define BITNUM 2
#define DEGREE 4

static const long long	twop1 =
{ 0x4000000000000000ll }; // 2

static const double twopm1 = 5.0000000000e-01;

static const DL	log2_lead =
{ .l = 0x3fe62e42fefa4000 };

static const DL	log2_trail =
{ .l = 0xbd48432a1b0e2634 };

static const DL
C[DEGREE - 1] = {
	{.l = 0x3feffb7fbd3f4c4a},
	{.l = 0xbfdea9651cf11bfe},
	{.l = 0x3fca5a3ddeb9c9e1},
};
static const DL
logtabhi[BITNUM] = {
	{.l = 0x0000000000000000},
	{.l = 0x3fd9f323ecbf8000}
};

static const DL
logtablo[BITNUM] = {
	{.l = 0x0000000000000000},
	{.l = 0x3d584bf2b68d766f}
};

static const DL
log_ru[BITNUM] = {
	{.l = 0x3ff0000000000000},
	{.l = 0x3fe5555555555555}
};

double log_gen(double x) {
	_UL ix;
	int	m, k;
	double	w, u, t, xmu, q, l_lead, l_trail, result;

	/* extract exponent and sign of x for some quick screening */

	ix = *(unsigned long long *)(&x);	/* copy arg to a long long */

	m = (ix >> DMANTWIDTH);		/* shift off mantissa	*/

	m -= DEXPBIAS;

	/* normalize x and compute the nearest 1/2th to x */

	ix &= DMANTISSA;	/* get the mantissa of x */
	ix |= twop1;	/* set exponent of x to 1 */

	w = *(double *)(&ix);
	k = w;
	u = k;

	k -= BITNUM; // the number 2 here is for zhengshu bit "1"

	xmu = twopm1*(w - u);

	t = log_ru[k].d*xmu;

	/* avoid loss of significance for values of x near two
		by adjusting index; effectively u is divided by two.
		The logtable has been adjusted for this.
	*/

	if (k > 1)
		m++;

	q = (t * t) * (C[1].d + t * (C[2].d));

	l_lead = logtabhi[k].d;
	l_trail = logtablo[k].d;
	l_lead += m * log2_lead.d;
	l_trail += m * log2_trail.d;

	result = l_lead + (C[0].d * t + (q + l_trail));

	return result;
}

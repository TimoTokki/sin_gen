#include "myhead.h"

#define BIT 3
#define BITNUM 8
#define BITNUM_1 7
#define DEGREE 1

static const DL
ln2by8HI = { .l = 0x3fb62e42fee00000 },
ln2by8LO = { .l = 0x3dba39ef35793c76 },
invln2by8 = { .l = 0x40271547652b82fe };

// fpminmax: [-1/8*ln2, 1/8*ln2]
static const DL
C[DEGREE] = {
	{.l = 0x3ff0b155b2640b16},
};
static const DL
interpolate[BITNUM] = {
	{.l = 0x3ff0000000000000},
	{.l = 0x3ff172b83c7d517b},
	{.l = 0x3ff306fe0a31b715},
	{.l = 0x3ff4bfdad5362a27},
	{.l = 0x3ff6a09e667f3bcd},
	{.l = 0x3ff8ace5422aa0db},
	{.l = 0x3ffae89f995ad3ad},
	{.l = 0x3ffd5818dcfba487}
};

double exp_gen(double x) {
	double temp;
	double T;
	long int T_int;
	double r, r1, r2, rr;
	double r_poly;
	unsigned long int hi, lo;
	double result;
	double r_hi, r_lo;

	T = x * invln2by8.d;
	T_int = T;
	r_poly = C[0].d;

	lo = T_int & BITNUM_1;
	hi = T_int >> BIT;
	hi = (hi + 0x3ff) << 52;
	r_hi = *((double *)&hi);
	//r_lo = pow(2, (((double)lo) / ((double)k)));
	r_lo = interpolate[lo].d;
	result = r_hi * (r_lo * r_poly);

	return result;
}

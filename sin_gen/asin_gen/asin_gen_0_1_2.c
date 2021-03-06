#include <math.h>
#include "myhead.h"

#define BIT 0
#define TABLE_NUM 1
#define DEGREE 5
#define COEFFICIENTS_NUM 3

// static const DL Twopm28 = { .l = 0x3e30000000000000 };

// P = fpminimax(asin(x), [| 1, 3, 5| ], [| D... | ], [0, sqrt(1 - (0 / 1)^2)]); printexpansion(P);
static const DL
C[COEFFICIENTS_NUM] = {
	{.l = 0x3ff0c13f827ad40c},
	{.l = 0xbfd72fd5aff0cbd8},
	{.l = 0x3fe9fa4726b4df31},
};

/* asin value: 0~1, step = 1/128 */
static const DL
asin_tab[TABLE_NUM] = {
	{.l = 0x0000000000000000},
};

/* cos(y) = sqrt(1-[x]^2) value: 0~1, step = 1/128 */
static const DL
sk[TABLE_NUM] = 
{
	{.l = 0x0000000000000000},
};

/* sin(y) = [x] value: 0~1, step = 1/128 */
static const DL
ck[TABLE_NUM] = 
{
	{.l = 0x3ff0000000000000},
};

double asin_gen(double x) {
	double result, temp, delta, zsq;
	int order;

	temp = x * (double)TABLE_NUM;
	order = temp;
	
	// delta = x * sqrt(1 - temp * temp) - temp * sqrt(1 - x * x);
	delta = x * ck[order].d - sk[order].d * sqrt(1.0 - x + x * (1.0 - x));

	x = delta;
	// if (delta < Twopm28.d)
	//	x = 0.0;
	zsq = x * x;

	result = C[0].d * delta + (delta * zsq) * (C[1].d + zsq * (C[2].d));

	result = asin_tab[order].d + result;

	return result;
}

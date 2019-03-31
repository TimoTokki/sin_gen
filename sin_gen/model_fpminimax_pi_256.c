// �Զ����Ļ�����BIT��BITNUM���֣����Ʊ���Ķ��٣��Լ����ɶ�Ӧ�����Ķ���ʽϵ��
#include <stdio.h>
#include "myhead.h"

#define NUM 100
#define BIT 6
#define BITNUM 64
#define DEGREE 6

// ����֤���þ���Ϊdouble�¼���
static const double
invpio4 = 1.2732395447351626861510701069801,
pi_4 = 0.78539816339744830961566084581988,
pi_2 = 1.5707963267948966192313216916398,
X = 0;

// coefficient[0] is for sin; coefficient[1] is for cos;
// pi/4/64
// sin:
// 0xb9d4fc64a5efeb6a + x * (0x3ff0000000000000 + x * (0x3d0847eb23176753 + x * (0xbfc5555555599c6c + x * (0x3e1cb882e949c36c + x * 0x3f811100f32d3a83))))
static const DL
coefficient[2][DEGREE] = {
	{
		{.l = 0xb9d4fc64a5efeb6a},
		{.l = 0x3ff0000000000000},
		{.l = 0x3d0847eb23176753},
		{.l = 0xbfc5555555599c6c},
		{.l = 0x3e1cb882e949c36c},
		{.l = 0x3f811100f32d3a83}
	},
	{
		{.l = 0},
		{.l = 0},
		{.l = 0},
		{.l = 0},
		{.l = 0},
		{.l = 0}
	}
};

// interpolate[0] is for sin(x) where x is in [0, pi/4] as interpolate[1] is for cos(x)
// sin(x) OR cos(x), x = pi_4 / 64 * i, i is 0, 1, 2, ..., 64
static const double
interpolate[2][BITNUM] = {
	{
		0.00000000000000000e+00,
		1.22715382857199261e-02,
		2.45412285229122880e-02,
		3.68072229413588323e-02,
		4.90676743274180143e-02,
		6.13207363022085778e-02,
		7.35645635996674235e-02,
		8.57973123444398905e-02,
		9.80171403295606020e-02,
		1.10222207293883059e-01,
		1.22410675199216198e-01,
		1.34580708507126186e-01,
		1.46730474455361752e-01,
		1.58858143333861442e-01,
		1.70961888760301226e-01,
		1.83039887955140959e-01,
		1.95090322016128268e-01,
		2.07111376192218550e-01,
		2.19101240156869797e-01,
		2.31058108280671120e-01,
		2.42980179903263890e-01,
		2.54865659604514572e-01,
		2.66712757474898386e-01,
		2.78519689385053105e-01,
		2.90284677254462368e-01,
		3.02005949319228067e-01,
		3.13681740398891477e-01,
		3.25310292162262934e-01,
		3.36889853392220051e-01,
		3.48418680249434568e-01,
		3.59895036534988149e-01,
		3.71317193951837543e-01,
		3.82683432365089772e-01,
		3.93992040061048109e-01,
		4.05241314004989871e-01,
		4.16429560097637183e-01,
		4.27555093430282094e-01,
		4.38616238538527638e-01,
		4.49611329654606600e-01,
		4.60538710958240024e-01,
		4.71396736825997649e-01,
		4.82183772079122749e-01,
		4.92898192229784037e-01,
		5.03538383725717559e-01,
		5.14102744193221727e-01,
		5.24589682678468906e-01,
		5.34997619887097211e-01,
		5.45324988422046422e-01,
		5.55570233019602225e-01,
		5.65731810783613197e-01,
		5.75808191417845301e-01,
		5.85797857456438860e-01,
		5.95699304492433343e-01,
		6.05511041404325514e-01,
		6.15231590580626845e-01,
		6.24859488142386377e-01,
		6.34393284163645498e-01,
		6.43831542889791465e-01,
		6.53172842953776764e-01,
		6.62415777590171761e-01,
		6.71558954847018401e-01,
		6.80600997795453051e-01,
		6.89540544737066925e-01,
		6.98376249408972854e-01
	},
	{
		1.00000000000000000e+00,
		9.99924701839144541e-01,
		9.99698818696204220e-01,
		9.99322384588349501e-01,
		9.98795456205172393e-01,
		9.98118112900149207e-01,
		9.97290456678690216e-01,
		9.96312612182778013e-01,
		9.95184726672196886e-01,
		9.93906970002356042e-01,
		9.92479534598709998e-01,
		9.90902635427780025e-01,
		9.89176509964780973e-01,
		9.87301418157858382e-01,
		9.85277642388941245e-01,
		9.83105487431216327e-01,
		9.80785280403230449e-01,
		9.78317370719627633e-01,
		9.75702130038528544e-01,
		9.72939952205560145e-01,
		9.70031253194543993e-01,
		9.66976471044852109e-01,
		9.63776065795439867e-01,
		9.60430519415565811e-01,
		9.56940335732208865e-01,
		9.53306040354193837e-01,
		9.49528180593036667e-01,
		9.45607325380521326e-01,
		9.41544065183020778e-01,
		9.37339011912574923e-01,
		9.32992798834738888e-01,
		9.28506080473215566e-01,
		9.23879532511286756e-01,
		9.19113851690057744e-01,
		9.14209755703530655e-01,
		9.09167983090522377e-01,
		9.03989293123443332e-01,
		8.98674465693953843e-01,
		8.93224301195515320e-01,
		8.87639620402853948e-01,
		8.81921264348355030e-01,
		8.76070094195406607e-01,
		8.70086991108711419e-01,
		8.63972856121586738e-01,
		8.57728610000272070e-01,
		8.51355193105265142e-01,
		8.44853565249707073e-01,
		8.38224705554838043e-01,
		8.31469612302545237e-01,
		8.24589302785025264e-01,
		8.17584813151583697e-01,
		8.10457198252594792e-01,
		8.03207531480644910e-01,
		7.95836904608883536e-01,
		7.88346427626606262e-01,
		7.80737228572094478e-01,
		7.73010453362736961e-01,
		7.65167265622458926e-01,
		7.57208846506484548e-01,
		7.49136394523459325e-01,
		7.40951125354959091e-01,
		7.32654271672412835e-01,
		7.24247082951466921e-01,
		7.15730825283818654e-01
	}
};

//double sin_gen(double x) {
//	double y, xx, appro_s, appro_c;
//
//	//xx = x * x;
//	appro_s = coefficient[0][0].d + x * (coefficient[0][1].d + x * (coefficient[0][2].d + x * (coefficient[0][3].d + x * (coefficient[0][4].d + x * coefficient[0][5].d))));
//
//	y = appro_s;
//
//	return y;
//}
 
double sin_gen(double x) {
	double ix, iix, iiix, y, appro_s, appro_c;
	long int temp, table_order, status_pi_4, status_pi_2, status_pi_1, flag, sign, sin_or_cos;
	int i;

	ix = x - X;
	temp = *((long int *)(&ix));
	flag = temp >> 63; // ��Ϊ1����Ϊ0
	flag = flag & 0x0000000000000001;
	temp = temp & 0x7fffffffffffffff;
	ix = *((double *)(&temp)); // ��ʱ ix Ϊ����ֵ

	// ix��С����return ix;
	if (temp < 0x3e40000000000000) {
		return (1 - flag * 2) * ix;
	}

	// new
	// iix = ix - [ix * invpio4] * pi_4
	// iiix = iix - i / 128* pi_4
	temp = (long int)(ix * invpio4 * BITNUM); // why not ix * invpio_512; ??
	status_pi_4 = (temp >> BIT) & 0x1;
	status_pi_2 = (temp >> (BIT + 1)) & 0x1;
	status_pi_1 = (temp >> (BIT + 2)) & 0x1;
	iix = ix - (temp >> (BIT + 1)) * pi_2 - status_pi_4 * pi_2;
	table_order = temp & (BITNUM - 1); // ��Ӧ (2^BIT -1) ����BITλ��1
	table_order = table_order - status_pi_4 * (BITNUM - 1);
	table_order = (1 - status_pi_4 * 2) * table_order;
	temp = *((long int *)(&iix));
	temp = temp & 0x7fffffffffffffff;
	iix = *((double *)(&temp)); // ��ʱ iix Ϊ����ֵ
	iiix = iix - ((double)table_order) / BITNUM * pi_4;
	sign = flag ^ status_pi_1; // ���0Ϊ����1Ϊ��
	sin_or_cos = status_pi_2 ^ status_pi_4; // ���0Ϊsin��1Ϊcos

	// new, sin(x+x') = sin(x)cos(x') + sin(x')cos(x), x' = iiix
	// OR, cos(x+x') = cos(x)cos(x') - sin(x)sin(x'), x' = iiix
	appro_s = coefficient[0][0].d + iiix * (coefficient[0][1].d + iiix * (coefficient[0][2].d + iiix * (coefficient[0][3].d + iiix * (coefficient[0][4].d + iiix * coefficient[0][5].d))));
	appro_c = coefficient[1][0].d + iiix * (coefficient[1][1].d + iiix * (coefficient[1][2].d + iiix * (coefficient[1][3].d + iiix * (coefficient[1][4].d + iiix * coefficient[1][5].d))));

	y = interpolate[sin_or_cos][table_order] * appro_c + (1 - sin_or_cos * 2) * interpolate[1 - sin_or_cos][table_order] * appro_s;
	y = (1 - sign * 2) * y;

	return y;
}
#include <stdio.h>
#include "myhead.h"

#define NUM 100
#define DEGREE 6
#define BITNUM 128
#define	FORMAT 64

struct constraint {
	double start;
	double end;
	int precision;
	int bit;
	int fnum;
	int degree;
};

// sin & cos
// coefficient[0] is for sin; coefficient[1] is for cos;
// pi/4/128
// 6 coefficients
// sin:
// 0xb984d64a29b505c5 + x * (0x3ff0000000000000 + x * (0x3cb845aef92c1d42 + x * (0xbfc55555555599c3 + x * (0x3decb7924858362b + x * 0x3f81110d09aab89d))))
// cos:
// 0x3ff0000000000000 + x * (0xbcb61a0a5c31efb7 + x * (0xbfdfffffffffcec1 + x * (0xbe01ea30fe505df3 + x * (0x3fa5555b0928dfe9 + x * 0xbefa66ee34c3b903))))
// 5 coefficients
// sin:
// 0x3b9a24fd6f71e4f0 + x * (0x3feffffffffffcb4 + x * (0x3e00999ee5af3132 + x * (0xbfc55558a0d459da + x * 0x3f1ad2a9831248b0)))
// cos:
// 0x3ff0000000000000 + x * (0x3ce5434093bdf722 + x * (0xbfe00000000077d5 + x * (0x3e1923479c224098 + x * 0x3fa5554e47f80e37)))
// 4 coefficients
// sin:
// 0xbbca7d59979393ef + x * (0x3ff0000000000d53 + x * (0xbe1f1f04f59599b9 + x * 0xbfc555508f75ffbc))
// cos:
// 0x3fefffffffffefc4 + x * (0x3e24abb2cf0603fd + x * (0xbfe000041cc0f168 + x * 0x3f40c14fcbc76a91))
// 3 coefficients
// sin:
// 0xbd0a6081327b77eb + x * (0x3ff00000d3f2460f + x * 0xbf50c60cab8e9315)
// cos:
// 0x3ff00000000041f1 + x * (0xbe43664f6b411c35 + x * 0xbfdffff4148eb6b7)
// 2 coefficients
// sin:
// 0x3d2a51aaa4577386 + x * 0x3feffff96b389608
// cos:
// 0x3ff0000277a907c0 + x * 0xbf6921fc09879ff4
// 1 coefficient
// sin:
// 0x3e4ffffd74191a12
// cos:
// 0x3e4ffffd74191a12
static const DL
coefficient[DEGREE][2][DEGREE] = {
	// 1 coefficients
	{
		{
			{.l = 0x3e4ffffd74191a12}
		},
		{
			{.l = 0x3e4ffffd74191a12}
		}
	},
	// 2 coefficients
	{
		{
			{.l = 0x3d2a51aaa4577386},
			{.l = 0x3feffff96b389608}
		},
		{
			{.l = 0x3ff0000277a907c0},
			{.l = 0xbf6921fc09879ff4}
		}
	},
	// 3 coefficients
	{
		{
			{.l = 0xbd0a6081327b77eb},
			{.l = 0x3ff00000d3f2460f},
			{.l = 0xbf50c60cab8e9315}
		},
		{
			{.l = 0x3ff00000000041f1},
			{.l = 0xbe43664f6b411c35},
			{.l = 0xbfdffff4148eb6b7}
		}
	},
	// 4 coefficients
	{
		{
			{.l = 0xbbca7d59979393ef},
			{.l = 0x3ff0000000000d53},
			{.l = 0xbe1f1f04f59599b9},
			{.l = 0xbfc555508f75ffbc}
		},
		{
			{.l = 0x3fefffffffffefc4},
			{.l = 0x3e24abb2cf0603fd},
			{.l = 0xbfe000041cc0f168},
			{.l = 0x3f40c14fcbc76a91}
		}
	},
	// 5 coefficients
	{
		{
			{.l = 0x3b9a24fd6f71e4f0},
			{.l = 0x3feffffffffffcb4},
			{.l = 0x3e00999ee5af3132},
			{.l = 0xbfc55558a0d459da},
			{.l = 0x3f1ad2a9831248b0}
		},
		{
			{.l = 0x3ff0000000000000},
			{.l = 0x3ce5434093bdf722},
			{.l = 0xbfe00000000077d5},
			{.l = 0x3e1923479c224098},
			{.l = 0x3fa5554e47f80e37}
		}
	},
	// 6 coefficients
	{
		{
			{.l = 0xb984d64a29b505c5},
			{.l = 0x3ff0000000000000},
			{.l = 0x3cb845aef92c1d42},
			{.l = 0xbfc55555555599c3},
			{.l = 0x3decb7924858362b},
			{.l = 0x3f81110d09aab89d}
		},
		{
			{.l = 0x3ff0000000000000},
			{.l = 0xbcb61a0a5c31efb7},
			{.l = 0xbfdfffffffffcec1},
			{.l = 0xbe01ea30fe505df3},
			{.l = 0x3fa5555b0928dfe9},
			{.l = 0xbefa66ee34c3b903}

		}
	}
};

static const double
interpolate[2][BITNUM] = {
	{
		0.00000000000000000e+00,
		6.13588464915447536e-03,
		1.22715382857199261e-02,
		1.84067299058048209e-02,
		2.45412285229122880e-02,
		3.06748031766366259e-02,
		3.68072229413588323e-02,
		4.29382569349408231e-02,
		4.90676743274180142e-02,
		5.51952443496899398e-02,
		6.13207363022085778e-02,
		6.74439195636640579e-02,
		7.35645635996674235e-02,
		7.96824379714301211e-02,
		8.57973123444398905e-02,
		9.19089564971327286e-02,
		9.80171403295606020e-02,
		1.04121633872054579e-01,
		1.10222207293883059e-01,
		1.16318630911904767e-01,
		1.22410675199216198e-01,
		1.28498110793793172e-01,
		1.34580708507126186e-01,
		1.40658239332849231e-01,
		1.46730474455361752e-01,
		1.52797185258443428e-01,
		1.58858143333861442e-01,
		1.64913120489969921e-01,
		1.70961888760301226e-01,
		1.77004220412148756e-01,
		1.83039887955140959e-01,
		1.89068664149806213e-01,
		1.95090322016128268e-01,
		2.01104634842091911e-01,
		2.07111376192218550e-01,
		2.13110319916091374e-01,
		2.19101240156869797e-01,
		2.25083911359792836e-01,
		2.31058108280671120e-01,
		2.37023605994367207e-01,
		2.42980179903263890e-01,
		2.48927605745720168e-01,
		2.54865659604514572e-01,
		2.60794117915275518e-01,
		2.66712757474898386e-01,
		2.72621355449948984e-01,
		2.78519689385053105e-01,
		2.84407537211271844e-01,
		2.90284677254462367e-01,
		2.96150888243623824e-01,
		3.02005949319228067e-01,
		3.07849640041534893e-01,
		3.13681740398891476e-01,
		3.19502030816015678e-01,
		3.25310292162262934e-01,
		3.31106305759876401e-01,
		3.36889853392220051e-01,
		3.42660717311994397e-01,
		3.48418680249434569e-01,
		3.54163525420490382e-01,
		3.59895036534988149e-01,
		3.65612997804773870e-01,
		3.71317193951837543e-01,
		3.77007410216418256e-01,
		3.82683432365089772e-01,
		3.88345046698826292e-01,
		3.93992040061048108e-01,
		3.99624199845646828e-01,
		4.05241314004989871e-01,
		4.10843171057903942e-01,
		4.16429560097637182e-01,
		4.22000270799799686e-01,
		4.27555093430282094e-01,
		4.33093818853151969e-01,
		4.38616238538527637e-01,
		4.44122144570429232e-01,
		4.49611329654606600e-01,
		4.55083587126343823e-01,
		4.60538710958240024e-01,
		4.65976495767966178e-01,
		4.71396736825997649e-01,
		4.76799230063322133e-01,
		4.82183772079122748e-01,
		4.87550160148435955e-01,
		4.92898192229784037e-01,
		4.98227666972781852e-01,
		5.03538383725717559e-01,
		5.08830142543107037e-01,
		5.14102744193221726e-01,
		5.19355990165589587e-01,
		5.24589682678468906e-01,
		5.29803624686294669e-01,
		5.34997619887097211e-01,
		5.40171472729892881e-01,
		5.45324988422046422e-01,
		5.50457972936604803e-01,
		5.55570233019602224e-01,
		5.60661576197336024e-01,
		5.65731810783613198e-01,
		5.70780745886967280e-01,
		5.75808191417845300e-01,
		5.80813958095764546e-01,
		5.85797857456438861e-01,
		5.90759701858874228e-01,
		5.95699304492433343e-01,
		6.00616479383868927e-01,
		6.05511041404325514e-01,
		6.10382806276309453e-01,
		6.15231590580626845e-01,
		6.20057211763289179e-01,
		6.24859488142386377e-01,
		6.29638238914927025e-01,
		6.34393284163645498e-01,
		6.39124444863775744e-01,
		6.43831542889791465e-01,
		6.48514401022112445e-01,
		6.53172842953776764e-01,
		6.57806693297078656e-01,
		6.62415777590171761e-01,
		6.66999922303637507e-01,
		6.71558954847018400e-01,
		6.76092703575315960e-01,
		6.80600997795453050e-01,
		6.85083667772700381e-01,
		6.89540544737066925e-01,
		6.93971460889654009e-01,
		6.98376249408972853e-01,
		7.02754744457225303e-01
	},
	{
		1.00000000000000000e+00,
		9.99981175282601143e-01,
		9.99924701839144541e-01,
		9.99830581795823422e-01,
		9.99698818696204220e-01,
		9.99529417501093163e-01,
		9.99322384588349501e-01,
		9.99077727752645383e-01,
		9.98795456205172393e-01,
		9.98475580573294753e-01,
		9.98118112900149207e-01,
		9.97723066644191610e-01,
		9.97290456678690217e-01,
		9.96820299291165715e-01,
		9.96312612182778013e-01,
		9.95767414467659794e-01,
		9.95184726672196886e-01,
		9.94564570734255452e-01,
		9.93906970002356041e-01,
		9.93211949234794533e-01,
		9.92479534598709998e-01,
		9.91709753669099523e-01,
		9.90902635427780025e-01,
		9.90058210262297105e-01,
		9.89176509964780974e-01,
		9.88257567730749491e-01,
		9.87301418157858383e-01,
		9.86308097244598648e-01,
		9.85277642388941245e-01,
		9.84210092386929073e-01,
		9.83105487431216328e-01,
		9.81963869109555264e-01,
		9.80785280403230449e-01,
		9.79569765685440534e-01,
		9.78317370719627633e-01,
		9.77028142657754351e-01,
		9.75702130038528545e-01,
		9.74339382785575861e-01,
		9.72939952205560146e-01,
		9.71503890986251776e-01,
		9.70031253194543992e-01,
		9.68522094274417316e-01,
		9.66976471044852109e-01,
		9.65394441697689375e-01,
		9.63776065795439867e-01,
		9.62121404269041596e-01,
		9.60430519415565811e-01,
		9.58703474895871556e-01,
		9.56940335732208865e-01,
		9.55141168305770722e-01,
		9.53306040354193837e-01,
		9.51435020969008369e-01,
		9.49528180593036667e-01,
		9.47585591017741135e-01,
		9.45607325380521326e-01,
		9.43593458161960361e-01,
		9.41544065183020779e-01,
		9.39459223602189912e-01,
		9.37339011912574923e-01,
		9.35183509938947577e-01,
		9.32992798834738887e-01,
		9.30766961078983732e-01,
		9.28506080473215566e-01,
		9.26210242138311342e-01,
		9.23879532511286756e-01,
		9.21514039342041943e-01,
		9.19113851690057744e-01,
		9.16679059921042663e-01,
		9.14209755703530655e-01,
		9.11706032005429851e-01,
		9.09167983090522377e-01,
		9.06595704514915365e-01,
		9.03989293123443332e-01,
		9.01348847046022014e-01,
		8.98674465693953844e-01,
		8.95966249756185156e-01,
		8.93224301195515320e-01,
		8.90448723244757890e-01,
		8.87639620402853948e-01,
		8.84797098430937780e-01,
		8.81921264348355030e-01,
		8.79012226428633478e-01,
		8.76070094195406607e-01,
		8.73094978418290099e-01,
		8.70086991108711419e-01,
		8.67046245515692652e-01,
		8.63972856121586738e-01,
		8.60866938637767279e-01,
		8.57728610000272070e-01,
		8.54557988365400521e-01,
		8.51355193105265142e-01,
		8.48120344803297252e-01,
		8.44853565249707074e-01,
		8.41554977436898410e-01,
		8.38224705554838043e-01,
		8.34862874986380056e-01,
		8.31469612302545237e-01,
		8.28045045257755752e-01,
		8.24589302785025264e-01,
		8.21102514991104680e-01,
		8.17584813151583697e-01,
		8.14036329705948362e-01,
		8.10457198252594792e-01,
		8.06847553543799272e-01,
		8.03207531480644910e-01,
		7.99537269107905033e-01,
		7.95836904608883536e-01,
		7.92106577300212352e-01,
		7.88346427626606262e-01,
		7.84556597155575233e-01,
		7.80737228572094479e-01,
		7.76888465673232450e-01,
		7.73010453362736960e-01,
		7.69103337645579640e-01,
		7.65167265622458927e-01,
		7.61202385484261814e-01,
		7.57208846506484548e-01,
		7.53186799043612482e-01,
		7.49136394523459326e-01,
		7.45057785441465962e-01,
		7.40951125354959091e-01,
		7.36816568877369875e-01,
		7.32654271672412835e-01,
		7.28464390448225196e-01,
		7.24247082951466921e-01,
		7.20002507961381630e-01,
		7.15730825283818655e-01,
		7.11432195745216441e-01
	}
};

static const double
pi = 3.1415926535897932384626433832795,
pi_2 = 1.5707963267948966192313216916398,
two_pi = 6.283185307179586476925286766559,
invpio2 = 6.36619772367581382433e-01, 
// table[i] restores the correct rounding x values where the step is PI/2
table[NUM] = { //pi/2 * T, T = 0, 1, 2, ......
	0,
	1.5707963267948966192313216916398,
	3.1415926535897932384626433832795,
	4.7123889803846898576939650749193,
	6.283185307179586476925286766559,
	7.8539816339744830961566084581988,
	9.4247779607693797153879301498385,
	10.995574287564276334619251841478,
	12.566370614359172953850573533118,
	14.137166941154069573081895224758,
	15.707963267948966192313216916398,
	17.278759594743862811544538608037,
	18.849555921538759430775860299677,
	20.420352248333656050007181991317,
	21.991148575128552669238503682957,
	23.561944901923449288469825374596,
	25.132741228718345907701147066236,
	26.703537555513242526932468757876,
	28.274333882308139146163790449516,
	29.845130209103035765395112141155,
	31.415926535897932384626433832795
};
//extern double sin_gen(double);

int gen(struct constraint input_parameter) {
	double a, b;
	int precision;
	double midpoint, length;
	double a1, b1, a2, b2;
	double X;
	long int Xtemp, atemp, btemp, i;
	FILE *func;
	// init
	int num, bit, bitnum, bitnum_1, degree, fnum, format;
	num = 100;
	

	if ((func = fopen("sin_gen.c", "w")) == (FILE *)0) {
		printf("open file error!\n");
		return 1;
	}
	a = input_parameter.start;
	b = input_parameter.end;
	precision = input_parameter.precision;
	bit = input_parameter.bit;
	bit = 7;
	bitnum = 1 << bit;
	bitnum_1 = bitnum - 1;
	fnum = input_parameter.fnum;
	degree = input_parameter.degree;
	//degree = 6;
	format = 64;
	/*printf("please input [a, b]: ");
	scanf("%lf %lf", &a, &b);
	printf("please input target precision: ");
	scanf("%d", &precision);
	printf("[a,b] = [%lf, %lf]\nprecision = %d\n", a, b, precision);*/

	midpoint = (a + b) / 2;
	length = (b - a) / 2;
 	Xtemp = (long int)(midpoint / two_pi);
	// 日后需要优化，尽可能地精确
	X = ((double)(Xtemp)) * two_pi;
	a1 = (0 - length) + X - midpoint;
	b1 = (0 + length) + X - midpoint;
	atemp = (long int)(a1 / pi_2) - 1;
	btemp = (long int)(b1 / pi_2) + 1;
	a2 = ((double)atemp) * pi_2;
	b2 = ((double)btemp) * pi_2;

	// generate code for sin_gen
	{
		// comments
		fprintf(func, "/** target func:\tsin\n");
		fprintf(func, "*** target domain:\t[%lf, %lf]\n", a, b);
		fprintf(func, "*** target precision:\t%d\n", precision);
		fprintf(func, "**/\n");

		fprintf(func, "#include <stdio.h>\n");
		fprintf(func, "#include %cmyhead.h%c\n", '"', '"');
		fprintf(func, "\n");
		fprintf(func, "#define NUM %d\n", num);
		fprintf(func, "#define BIT %d\n", bit);
		fprintf(func, "#define BITNUM %d\n", bitnum);
		fprintf(func, "#define BITNUM_1 %d\n", bitnum_1);
		fprintf(func, "#define DEGREE %d\n", degree + 1);
		//fprintf(func, "#define TableNum %d\n", (btemp + 1));
		fprintf(func, "static const double\n");
		fprintf(func, "invpio4 = 1.2732395447351626861510701069801,\n");
		fprintf(func, "invpio512 = 162.97466172610082382733697369345,\n");
		fprintf(func, "pi_4 = 0.78539816339744830961566084581988,\n");
		fprintf(func, "pi_2 = 1.5707963267948966192313216916398,\n");
		fprintf(func, "pi_512 = 0.00613592315154256491887235035797,\n");
		//fprintf(func, "X = 0;\n");
		fprintf(func, "X = %.17lf;\n", X);
		/*fprintf(func, "table[TableNum] = {\t// pi_2 * T, T = 0, 1, 2, ..., %d\n", btemp);
		for (i = 0; i < btemp; i++)
		{
			fprintf(func, "\t%.17lf,\n", table[i]);
		}
		fprintf(func, "\t%.17lf\n ", table[i]);
		fprintf(func, "};\n");
		fprintf(func, "extern double k_sin(double);\n");
		fprintf(func, "extern double k_cos(double);\n");*/
		fprintf(func, "\n");

		fprintf(func, "static const double\n");
		fprintf(func, "pio2_1 = 1.57079632673412561417e+00, /* 0x3FF921FB, 0x54400000 */\n");
		fprintf(func, "pio2_1t = 6.07710050650619224932e-11; /* 0x3DD0B461, 0x1A626331 */\n");
		fprintf(func, "\n");

		fprintf(func, "static const DL\n");
		fprintf(func, "pi_4_1 = { .l = 0x3FE921FB54400000 },\n");
		fprintf(func, "pi_4_1t = { .l = 0x3DC0B4611A626331 };\n");

		// degree
		fprintf(func, "static const DL\n");
		fprintf(func, "coefficient[2][DEGREE] = {\n");
		fprintf(func, "\t{\n");
		for (i = 0; i < degree; i++) {
			fprintf(func, "\t\t{.l = 0x%lx},\n", coefficient[degree][0][i].l);
		}
		fprintf(func, "\t\t{.l = 0x%lx}\n", coefficient[degree][0][i].l);
		fprintf(func, "\t},\n");
		fprintf(func, "\t{\n");
		for (i = 0; i < degree; i++) {
			fprintf(func, "\t\t{.l = 0x%lx},\n", coefficient[degree][1][i].l);
		}
		fprintf(func, "\t\t{.l = 0x%lx}\n", coefficient[degree][1][i].l);
		fprintf(func, "\t}\n");
		fprintf(func, "};\n");

		// interpolate
		fprintf(func, "static const double\n");
		fprintf(func, "interpolate[2][BITNUM] = {\n");
		fprintf(func, "\t{\n");
		for (i = 0; i < bitnum - 1; i++) {
			fprintf(func, "\t\t%.17e,\n", interpolate[0][i]);
		}
		fprintf(func, "\t\t%.17e\n", interpolate[0][i]);
		fprintf(func, "\t},\n");
		fprintf(func, "\t{\n");
		for (i = 0; i < bitnum - 1; i++) {
			fprintf(func, "\t\t%.17e,\n", interpolate[1][i]);
		}
		fprintf(func, "\t\t%.17e\n", interpolate[1][i]);
		fprintf(func, "\t}\n");
		fprintf(func, "};\n");

		// func
		fprintf(func, "double sin_gen(double x) {\n");
		fprintf(func, "\tdouble ix, iix, iiix, y, appro_s, appro_c;\n");
		fprintf(func, "\tlong int temp, table_order, status_pi_4, status_pi_2, status_pi_1, flag, sign, sin_or_cos;\n");
		fprintf(func, "\tint i;\n");
		fprintf(func, "\n");
		fprintf(func, "\tix = x - X;\n");
		fprintf(func, "\ttemp = *((long int *)(&ix));\n");
		fprintf(func, "\tflag = temp >> %d; // - is 1, + is 0\n", format - 1);
		fprintf(func, "\tflag = flag & 0x0000000000000001;\n");
		fprintf(func, "\ttemp = temp & 0x7fffffffffffffff;\n");
		fprintf(func, "\tix = *((double *)(&temp)); // at this time, ix is absolute value\n");
		fprintf(func, "\t\n");
		fprintf(func, "\t// if ix is too little, then return ix;\n");
		fprintf(func, "\tif (temp < 0x3e40000000000000) {\n");
		fprintf(func, "\t\treturn (1 - flag * 2) * ix;\n");
		fprintf(func, "\t}\n");
		fprintf(func, "\n");
		fprintf(func, "\t// new\n");
		fprintf(func, "\t// iix = ix - [ix * invpio4] * pi_4\n");
		fprintf(func, "\t// iiix = iix - i / %d * pi_4\n", bitnum);
		fprintf(func, "\ttemp = (long int)(ix * invpio4 * BITNUM); // why not ix * invpio_512;\n");
		fprintf(func, "\tstatus_pi_4 = (temp >> BIT) & 0x1; \n");
		fprintf(func, "\tstatus_pi_2 = (temp >> (BIT + 1)) & 0x1;\n");
		fprintf(func, "\tstatus_pi_1 = (temp >> (BIT + 2)) & 0x1;\n");
		fprintf(func, "\tiix = ix - ((temp >> (BIT + 1)) + status_pi_4) * pio2_1;\n");
		fprintf(func, "\tiix = iix - ((temp >> (BIT + 1)) + status_pi_4) * pio2_1t;\n");
		fprintf(func, "\t//iix = iix - ((temp >> (BIT + 1)) + status_pi_4) * pio2_2;\n");
		fprintf(func, "\t//iix = iix - ((temp >> (BIT + 1)) + status_pi_4) * pio2_2t;\n");
		fprintf(func, "\t//iix = iix - ((temp >> (BIT + 1)) + status_pi_4) * pio2_3;\n");
		fprintf(func, "\t//iix = iix - ((temp >> (BIT + 1)) + status_pi_4) * pio2_3t;\n");
		fprintf(func, "\ttable_order = temp & (BITNUM_1); // BITNUM - 1 = (2^BIT -1)\n");
		fprintf(func, "\ttable_order = table_order - status_pi_4 * (BITNUM_1);\n");
		fprintf(func, "\ttable_order = (1 - status_pi_4 * 2) * table_order;\n");
		fprintf(func, "\ttemp = *((long int *)(&iix));\n");
		fprintf(func, "\ttemp = temp & 0x7fffffffffffffff;\n");
		fprintf(func, "\tiix = *((double *)(&temp)); // at this time, iix is absolute value\n");
		fprintf(func, "\tiiix = iix - ((double)table_order) / BITNUM * pi_4_1.d;\n");
		fprintf(func, "\tiiix = iiix - ((double)table_order) / BITNUM * pi_4_1t.d;\n");
		fprintf(func, "\t//iiix = iiix - ((double)table_order) / BITNUM * pi_4_2.d;\n");
		fprintf(func, "\t//iiix = iiix - ((double)table_order) / BITNUM * pi_4_2t.d;\n");
		fprintf(func, "\t//iiix = iiix - ((double)table_order) / BITNUM * pi_4_3.d;\n");
		fprintf(func, "\t//iiix = iiix - ((double)table_order) / BITNUM * pi_4_3t.d;\n");
		fprintf(func, "\tsign = flag ^ status_pi_1; // ornot，0 is +, 1 is -\n");
		fprintf(func, "\tsin_or_cos = status_pi_2 ^ status_pi_4; // ornot, 0 is sin, 1 is cos\n");
		fprintf(func, "\n");
		fprintf(func, "\t// new, sin(x+x') = sin(x)cos(x') + sin(x')cos(x), x' = iiix\n");
		fprintf(func, "\t// OR, cos(x+x') = cos(x)cos(x') - sin(x)sin(x'), x' = iiix\n");

		fprintf(func, "\tappro_s = coefficient[0][0].d");
		for (i = 1; i <= degree; i++) {
			fprintf(func, " + iiix * (coefficient[0][%ld].d", i);
		}
		for (i = 1; i <= degree; i++) {
			fprintf(func, ")");
		}
		fprintf(func, ";\n");
		fprintf(func, "\tappro_c = coefficient[1][0].d");
		for (i = 1; i <= degree; i++) {
			fprintf(func, " + iiix * (coefficient[1][%ld].d", i);
		}
		for (i = 1; i <= degree; i++) {
			fprintf(func, ")");
		}
		fprintf(func, ";\n");

		//fprintf(func, "\tappro_s = coefficient[0][0].d + iiix * (coefficient[0][1].d + iiix * (coefficient[0][2].d + iiix * (coefficient[0][3].d + iiix * (coefficient[0][4].d + iiix * coefficient[0][5].d))));\n");
		//fprintf(func, "\tappro_c = coefficient[1][0].d + iiix * (coefficient[1][1].d + iiix * (coefficient[1][2].d + iiix * (coefficient[1][3].d + iiix * (coefficient[1][4].d + iiix * coefficient[1][5].d))));\n");
		fprintf(func, "\n");
		fprintf(func, "\ty = interpolate[sin_or_cos][table_order] * appro_c + (1 - sin_or_cos * 2) * interpolate[1 - sin_or_cos][table_order] * appro_s;\n");
		fprintf(func, "\ty = (1 - sign * 2) * y;\n");
		fprintf(func, "\n");
		fprintf(func, "\treturn y;\n");
		fprintf(func, "}\n");
		fprintf(func, "\n");
	}
	fclose(func);

	return 0;
}

int main(int argc, char *argv[]) {
	double a, b;
	int precision;
	int bit, fnum, degree;
	struct constraint input_parameter;

	if (argc == 1) {
		printf("please input [a, b]: ");
		scanf("%lf %lf", &a, &b);
		printf("please input target precision: ");
		scanf("%d", &precision);
		printf("[a,b] = [%lf, %lf]\nprecision = %d\n", a, b, precision);
	}
	else if (argc == 7) {
		a = atof(argv[1]);
		b = atof(argv[2]);
		precision = atoi(argv[3]);
		bit = atoi(argv[4]);
		fnum = atoi(argv[5]);
		degree = atoi(argv[6]);
	}
	else {
		printf("please input 6 parameters!!\n");
		return 1;
	}
	input_parameter.start = a;
	input_parameter.end = b;
	input_parameter.precision = precision;
	input_parameter.bit = bit;
	input_parameter.fnum = fnum;
	input_parameter.degree = degree;
	gen(input_parameter);

	return 0;
}
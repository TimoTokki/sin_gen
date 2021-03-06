#include "myhead.h"

#define BIT 7
#define BITNUM 128
#define DEGREE 7

static const long long	twop7 =
{ 0x4060000000000000ll }; // 128

static const double twopm7 = 7.8125000000e-03;

static const DL	log2_lead =
{ .l = 0x3fe62e42fefa4000 };

static const DL	log2_trail =
{ .l = 0xbd48432a1b0e2634 };

static const DL
C[DEGREE - 1] = {
	{.l = 0x3ff0000000000000},
	{.l = 0xbfdffffffffff8ba},
	{.l = 0x3fd55555552260cf},
	{.l = 0xbfcfffff16c63d6a},
	{.l = 0x3fc998afe2adfada},
	{.l = 0xbfc4eaa610c545e3},
};
static const DL
logtabhi[BITNUM] = {
	{.l = 0x0000000000000000},
	{.l = 0x3f7fe02a6b200000},
	{.l = 0x3f8fc0a8b1000000},
	{.l = 0x3f97b91b07d80000},
	{.l = 0x3f9f829b0e780000},
	{.l = 0x3fa39e87ba000000},
	{.l = 0x3fa77458f6340000},
	{.l = 0x3fab42dd71180000},
	{.l = 0x3faf0a30c0100000},
	{.l = 0x3fb16536eea40000},
	{.l = 0x3fb341d7961c0000},
	{.l = 0x3fb51b073f060000},
	{.l = 0x3fb6f0d28ae60000},
	{.l = 0x3fb8c345d6320000},
	{.l = 0x3fba926d3a4a0000},
	{.l = 0x3fbc5e548f5c0000},
	{.l = 0x3fbe27076e2a0000},
	{.l = 0x3fbfec9131dc0000},
	{.l = 0x3fc0d77e7cd10000},
	{.l = 0x3fc1b72ad52f0000},
	{.l = 0x3fc29552f8200000},
	{.l = 0x3fc371fc201f0000},
	{.l = 0x3fc44d2b6ccb0000},
	{.l = 0x3fc526e5e3a20000},
	{.l = 0x3fc5ff3070a80000},
	{.l = 0x3fc6d60fe71a0000},
	{.l = 0x3fc7ab8902110000},
	{.l = 0x3fc87fa065210000},
	{.l = 0x3fc9525a9cf40000},
	{.l = 0x3fca23bc1fe30000},
	{.l = 0x3fcaf3c94e810000},
	{.l = 0x3fcbc286742e0000},
	{.l = 0x3fcc8ff7c79b0000},
	{.l = 0x3fcd5c216b500000},
	{.l = 0x3fce27076e2b0000},
	{.l = 0x3fcef0adcbdc0000},
	{.l = 0x3fcfb9186d5e0000},
	{.l = 0x3fd0402594b50000},
	{.l = 0x3fd0a324e2738000},
	{.l = 0x3fd1058bf9ae8000},
	{.l = 0x3fd1675cabab8000},
	{.l = 0x3fd1c898c1698000},
	{.l = 0x3fd22941fbcf8000},
	{.l = 0x3fd2895a13de8000},
	{.l = 0x3fd2e8e2bae10000},
	{.l = 0x3fd347dd9a988000},
	{.l = 0x3fd3a64c55698000},
	{.l = 0x3fd4043086868000},
	{.l = 0x3fd4618bc21c8000},
	{.l = 0x3fd4be5f95778000},
	{.l = 0x3fd51aad872e0000},
	{.l = 0x3fd5767717458000},
	{.l = 0x3fd5d1bdbf580000},
	{.l = 0x3fd62c82f2ba0000},
	{.l = 0x3fd686c81e9b0000},
	{.l = 0x3fd6e08eaa2b8000},
	{.l = 0x3fd739d7f6bc0000},
	{.l = 0x3fd792a55fdd8000},
	{.l = 0x3fd7eaf83b828000},
	{.l = 0x3fd842d1da1e8000},
	{.l = 0x3fd89a3386c18000},
	{.l = 0x3fd8f11e87368000},
	{.l = 0x3fd947941c210000},
	{.l = 0x3fd99d9581180000},
	{.l = 0x3fd9f323ecbf8000},
	{.l = 0xbfd214456d0e8000},
	{.l = 0xbfd1bf99635a8000},
	{.l = 0xbfd16b5ccbad0000},
	{.l = 0xbfd1178e82280000},
	{.l = 0xbfd0c42d67618000},
	{.l = 0xbfd07138604d8000},
	{.l = 0xbfd01eae56270000},
	{.l = 0xbfcf991c6cb40000},
	{.l = 0xbfcef5ade4dd0000},
	{.l = 0xbfce530effe70000},
	{.l = 0xbfcdb13db0d50000},
	{.l = 0xbfcd1037f2650000},
	{.l = 0xbfcc6ffbc6f00000},
	{.l = 0xbfcbd087383c0000},
	{.l = 0xbfcb31d8575c0000},
	{.l = 0xbfca93ed3c8b0000},
	{.l = 0xbfc9f6c407090000},
	{.l = 0xbfc95a5adcf70000},
	{.l = 0xbfc8beafeb390000},
	{.l = 0xbfc823c165520000},
	{.l = 0xbfc7898d85440000},
	{.l = 0xbfc6f0128b750000},
	{.l = 0xbfc6574ebe8c0000},
	{.l = 0xbfc5bf406b540000},
	{.l = 0xbfc527e5e4a20000},
	{.l = 0xbfc4913d83340000},
	{.l = 0xbfc3fb45a5990000},
	{.l = 0xbfc365fcb0160000},
	{.l = 0xbfc2d1610c870000},
	{.l = 0xbfc23d712a4a0000},
	{.l = 0xbfc1aa2b7e240000},
	{.l = 0xbfc1178e82280000},
	{.l = 0xbfc08598b59e0000},
	{.l = 0xbfbfe89139dc0000},
	{.l = 0xbfbec739830a0000},
	{.l = 0xbfbda72763840000},
	{.l = 0xbfbc885801bc0000},
	{.l = 0xbfbb6ac88dae0000},
	{.l = 0xbfba4e7640b20000},
	{.l = 0xbfb9335e5d5a0000},
	{.l = 0xbfb8197e2f400000},
	{.l = 0xbfb700d30aea0000},
	{.l = 0xbfb5e95a4d980000},
	{.l = 0xbfb4d3115d200000},
	{.l = 0xbfb3bdf5a7d20000},
	{.l = 0xbfb2aa04a4480000},
	{.l = 0xbfb1973bd1460000},
	{.l = 0xbfb08598b59e0000},
	{.l = 0xbfaeea31c0080000},
	{.l = 0xbfaccb73cddc0000},
	{.l = 0xbfaaaef2d0fc0000},
	{.l = 0xbfa894aa14a00000},
	{.l = 0xbfa67c94f2d40000},
	{.l = 0xbfa466aed42c0000},
	{.l = 0xbfa252f32f8c0000},
	{.l = 0xbfa0415d89e80000},
	{.l = 0xbf9c63d2ec180000},
	{.l = 0xbf98492528c80000},
	{.l = 0xbf9432a925980000},
	{.l = 0xbf90205658900000},
	{.l = 0xbf882448a3900000},
	{.l = 0xbf80101575900000},
	{.l = 0xbf70080559600000}
};

static const DL
logtablo[BITNUM] = {
	{.l = 0x0000000000000000},
	{.l = 0xbd6f30ee07912df9},
	{.l = 0xbd5fe0e183092c59},
	{.l = 0xbd62772ab6c0559c},
	{.l = 0x3d2980267c7e09e4},
	{.l = 0xbd642a056fea4dfd},
	{.l = 0xbd62303b9cb0d5e1},
	{.l = 0x3d671bec28d14c7e},
	{.l = 0x3d662a6617cc9717},
	{.l = 0xbd60a3e2f3b47d18},
	{.l = 0xbd4717b6b33e44f8},
	{.l = 0x3d383f69278e686a},
	{.l = 0xbd62968c836cc8c2},
	{.l = 0xbd5937c294d2f567},
	{.l = 0x3d6aac6ca17a4554},
	{.l = 0xbd4c5e7514f4083f},
	{.l = 0x3d6e5cbd3d50fffc},
	{.l = 0xbd354555d1ae6607},
	{.l = 0xbd6c69a65a23a170},
	{.l = 0x3d69e80a41811a39},
	{.l = 0xbd35b967f4471dfc},
	{.l = 0xbd6c22f10c9a4ea8},
	{.l = 0x3d6f4799f4f6543e},
	{.l = 0xbd62f21746ff8a47},
	{.l = 0xbd6b0b0de3077d7e},
	{.l = 0xbd56f1b955c4d1da},
	{.l = 0xbd537b720e4a694b},
	{.l = 0xbd5b77b7effb7f41},
	{.l = 0x3d65ad1d904c1d4e},
	{.l = 0xbd62a739b23b93e1},
	{.l = 0xbd600349cc67f9b2},
	{.l = 0xbd6cca75818c5dbc},
	{.l = 0xbd697794f689f843},
	{.l = 0xbd611ba91bbca682},
	{.l = 0xbd3a342c2af0003c},
	{.l = 0x3d664d948637950e},
	{.l = 0x3d5f1546aaa3361c},
	{.l = 0xbd67df928ec217a5},
	{.l = 0x3d50e35f73f7a018},
	{.l = 0xbd6a9573b02faa5a},
	{.l = 0x3d630701ce63eab9},
	{.l = 0x3d59fafbc68e7540},
	{.l = 0xbd3a6976f5eb0963},
	{.l = 0x3d3a8d7ad24c13f0},
	{.l = 0x3d5d309c2cc91a85},
	{.l = 0xbd25594dd4c58092},
	{.l = 0xbd6d0b1c68651946},
	{.l = 0x3d63f1de86093efa},
	{.l = 0xbd609ec17a426426},
	{.l = 0xbd3d7c92cd9ad824},
	{.l = 0xbd3f4bd8db0a7cc1},
	{.l = 0xbd62c9d5b2a49af9},
	{.l = 0x3d4394a11b1c1ee4},
	{.l = 0xbd6c356848506ead},
	{.l = 0x3d54aec442be1015},
	{.l = 0x3d60f1c609c98c6c},
	{.l = 0xbd67fcb18ed9d603},
	{.l = 0xbd6c2ec1f512dc03},
	{.l = 0x3d67e1b259d2f3da},
	{.l = 0x3d462e927628cbc2},
	{.l = 0xbd6ed2a52c73bf78},
	{.l = 0xbd5d3881e8962a96},
	{.l = 0x3d56faba4cdd147d},
	{.l = 0xbd5f753456d113b8},
	{.l = 0x3d584bf2b68d766f},
	{.l = 0xbd6c6a1f7ae91aec},
	{.l = 0x3d546b2255d70849},
	{.l = 0x3d323299042d74bf},
	{.l = 0x3d5b8421cc74be04},
	{.l = 0x3d5d1cee9d3862a3},
	{.l = 0x3d63cec649d22563},
	{.l = 0x3d6cb78460a42f4a},
	{.l = 0x3d6321a099af9906},
	{.l = 0x3cca211565bb8e11},
	{.l = 0xbd401212276041f4},
	{.l = 0x3d6daff2af715b03},
	{.l = 0xbd679ed606292424},
	{.l = 0xbd3ee138d3a69d43},
	{.l = 0x3d53a9788b2a8257},
	{.l = 0x3d58e1ac6a75670d},
	{.l = 0x3d530e486a0ac42d},
	{.l = 0x3d6a66fb2979a7e8},
	{.l = 0xbd07f22858a0ff6f},
	{.l = 0x3d073d54aae92cd1},
	{.l = 0x3d670f91232ce70c},
	{.l = 0xbd631ccf7c7b75e8},
	{.l = 0xbd6aaee721a63de2},
	{.l = 0xbd4339f1658785cf},
	{.l = 0xbd5ed8fdc149767e},
	{.l = 0x3d629cc171a96824},
	{.l = 0x3d62a7c86ab02498},
	{.l = 0xbd5465c4f032b956},
	{.l = 0x3d6bfa7415f72d23},
	{.l = 0x3d6fb18a4cd1f92d},
	{.l = 0x3d5eff2dc702c20a},
	{.l = 0x3d31ac38dde3b366},
	{.l = 0x3d4b8421cc74be04},
	{.l = 0xbd5d034451fecdfb},
	{.l = 0x3d454d3593e842bf},
	{.l = 0xbd311fcba80cdd10},
	{.l = 0xbd51a89401fa7173},
	{.l = 0xbd52c8da38cb559a},
	{.l = 0x3d649c84015fbb47},
	{.l = 0x3d50f215b5ca203e},
	{.l = 0x3d66ceea3c542b82},
	{.l = 0xbd6c7e0373e5bff8},
	{.l = 0xbd681c1e8da99ded},
	{.l = 0x3d5b8d20c78ba3a4},
	{.l = 0xbd5fab1769f42c78},
	{.l = 0x3d319bd0ad125895},
	{.l = 0x3d6d0b6e8ae9c698},
	{.l = 0xbd5559b4553e4c2d},
	{.l = 0xbd4d034451fecdfb},
	{.l = 0x3d647844f93f24ee},
	{.l = 0xbd6b2cb86dc13ec0},
	{.l = 0x3d5de07cb958897a},
	{.l = 0x3d432f32ba0b44d0},
	{.l = 0xbd576b08209f3283},
	{.l = 0xbd6e3e98c8a4202d},
	{.l = 0xbd6183e9ae021b68},
	{.l = 0x3d577771fd187145},
	{.l = 0x3d6aa8739c0614d1},
	{.l = 0xbd4957d173697cf3},
	{.l = 0xbd098139928637fe},
	{.l = 0xbd6ac23a4f91d083},
	{.l = 0x3d6d75577da74f64},
	{.l = 0x3d6c863b5ccce95f},
	{.l = 0x3d5dd32a0699c731}
};

static const DL
log_ru[BITNUM] = {
	{.l = 0x3ff0000000000000},
	{.l = 0x3fefc07f01fc07f0},
	{.l = 0x3fef81f81f81f820},
	{.l = 0x3fef44659e4a4271},
	{.l = 0x3fef07c1f07c1f08},
	{.l = 0x3feecc07b301ecc0},
	{.l = 0x3fee9131abf0b767},
	{.l = 0x3fee573ac901e574},
	{.l = 0x3fee1e1e1e1e1e1e},
	{.l = 0x3fede5d6e3f8868a},
	{.l = 0x3fedae6076b981db},
	{.l = 0x3fed77b654b82c34},
	{.l = 0x3fed41d41d41d41d},
	{.l = 0x3fed0cb58f6ec074},
	{.l = 0x3fecd85689039b0b},
	{.l = 0x3feca4b3055ee191},
	{.l = 0x3fec71c71c71c71c},
	{.l = 0x3fec3f8f01c3f8f0},
	{.l = 0x3fec0e070381c0e0},
	{.l = 0x3febdd2b899406f7},
	{.l = 0x3febacf914c1bad0},
	{.l = 0x3feb7d6c3dda338b},
	{.l = 0x3feb4e81b4e81b4f},
	{.l = 0x3feb2036406c80d9},
	{.l = 0x3feaf286bca1af28},
	{.l = 0x3feac5701ac5701b},
	{.l = 0x3fea98ef606a63be},
	{.l = 0x3fea6d01a6d01a6d},
	{.l = 0x3fea41a41a41a41a},
	{.l = 0x3fea16d3f97a4b02},
	{.l = 0x3fe9ec8e951033d9},
	{.l = 0x3fe9c2d14ee4a102},
	{.l = 0x3fe999999999999a},
	{.l = 0x3fe970e4f80cb872},
	{.l = 0x3fe948b0fcd6e9e0},
	{.l = 0x3fe920fb49d0e229},
	{.l = 0x3fe8f9c18f9c18fa},
	{.l = 0x3fe8d3018d3018d3},
	{.l = 0x3fe8acb90f6bf3aa},
	{.l = 0x3fe886e5f0abb04a},
	{.l = 0x3fe8618618618618},
	{.l = 0x3fe83c977ab2bedd},
	{.l = 0x3fe8181818181818},
	{.l = 0x3fe7f405fd017f40},
	{.l = 0x3fe7d05f417d05f4},
	{.l = 0x3fe7ad2208e0ecc3},
	{.l = 0x3fe78a4c8178a4c8},
	{.l = 0x3fe767dce434a9b1},
	{.l = 0x3fe745d1745d1746},
	{.l = 0x3fe724287f46debc},
	{.l = 0x3fe702e05c0b8170},
	{.l = 0x3fe6e1f76b4337c7},
	{.l = 0x3fe6c16c16c16c17},
	{.l = 0x3fe6a13cd1537290},
	{.l = 0x3fe6816816816817},
	{.l = 0x3fe661ec6a5122f9},
	{.l = 0x3fe642c8590b2164},
	{.l = 0x3fe623fa77016240},
	{.l = 0x3fe6058160581606},
	{.l = 0x3fe5e75bb8d015e7},
	{.l = 0x3fe5c9882b931057},
	{.l = 0x3fe5ac056b015ac0},
	{.l = 0x3fe58ed2308158ed},
	{.l = 0x3fe571ed3c506b3a},
	{.l = 0x3fe5555555555555},
	{.l = 0x3fe5390948f40feb},
	{.l = 0x3fe51d07eae2f815},
	{.l = 0x3fe5015015015015},
	{.l = 0x3fe4e5e0a72f0539},
	{.l = 0x3fe4cab88725af6e},
	{.l = 0x3fe4afd6a052bf5b},
	{.l = 0x3fe49539e3b2d067},
	{.l = 0x3fe47ae147ae147b},
	{.l = 0x3fe460cbc7f5cf9a},
	{.l = 0x3fe446f86562d9fb},
	{.l = 0x3fe42d6625d51f87},
	{.l = 0x3fe4141414141414},
	{.l = 0x3fe3fb013fb013fb},
	{.l = 0x3fe3e22cbce4a902},
	{.l = 0x3fe3c995a47babe7},
	{.l = 0x3fe3b13b13b13b14},
	{.l = 0x3fe3991c2c187f63},
	{.l = 0x3fe3813813813814},
	{.l = 0x3fe3698df3de0748},
	{.l = 0x3fe3521cfb2b78c1},
	{.l = 0x3fe33ae45b57bcb2},
	{.l = 0x3fe323e34a2b10bf},
	{.l = 0x3fe30d190130d190},
	{.l = 0x3fe2f684bda12f68},
	{.l = 0x3fe2e025c04b8097},
	{.l = 0x3fe2c9fb4d812ca0},
	{.l = 0x3fe2b404ad012b40},
	{.l = 0x3fe29e4129e4129e},
	{.l = 0x3fe288b01288b013},
	{.l = 0x3fe27350b8812735},
	{.l = 0x3fe25e22708092f1},
	{.l = 0x3fe2492492492492},
	{.l = 0x3fe23456789abcdf},
	{.l = 0x3fe21fb78121fb78},
	{.l = 0x3fe20b470c67c0d9},
	{.l = 0x3fe1f7047dc11f70},
	{.l = 0x3fe1e2ef3b3fb874},
	{.l = 0x3fe1cf06ada2811d},
	{.l = 0x3fe1bb4a4046ed29},
	{.l = 0x3fe1a7b9611a7b96},
	{.l = 0x3fe19453808ca29c},
	{.l = 0x3fe1811811811812},
	{.l = 0x3fe16e0689427379},
	{.l = 0x3fe15b1e5f75270d},
	{.l = 0x3fe1485f0e0acd3b},
	{.l = 0x3fe135c81135c811},
	{.l = 0x3fe12358e75d3033},
	{.l = 0x3fe1111111111111},
	{.l = 0x3fe0fef010fef011},
	{.l = 0x3fe0ecf56be69c90},
	{.l = 0x3fe0db20a88f4696},
	{.l = 0x3fe0c9714fbcda3b},
	{.l = 0x3fe0b7e6ec259dc8},
	{.l = 0x3fe0a6810a6810a7},
	{.l = 0x3fe0953f39010954},
	{.l = 0x3fe0842108421084},
	{.l = 0x3fe073260a47f7c6},
	{.l = 0x3fe0624dd2f1a9fc},
	{.l = 0x3fe05197f7d73404},
	{.l = 0x3fe0410410410410},
	{.l = 0x3fe03091b51f5e1a},
	{.l = 0x3fe0204081020408},
	{.l = 0x3fe0101010101010}
};

double log_gen(double x) {
	_UL ix;
	int	m, k;
	double	w, u, t, xmu, q, l_lead, l_trail, result;

	/* extract exponent and sign of x for some quick screening */

	ix = *(unsigned long long *)(&x);	/* copy arg to a long long */

	m = (ix >> DMANTWIDTH);		/* shift off mantissa	*/

	m -= DEXPBIAS;

	/* normalize x and compute the nearest 1/128th to x */

	ix &= DMANTISSA;	/* get the mantissa of x */
	ix |= twop7;	/* set exponent of x to 7 */

	w = *(double *)(&ix);
	k = w;
	u = k;

	k -= BITNUM; // the number 128 here is for zhengshu bit "1"

	xmu = twopm7*(w - u);

	t = log_ru[k].d*xmu;

	/* avoid loss of significance for values of x near two
		by adjusting index; effectively u is divided by two.
		The logtable has been adjusted for this.
	*/

	if (k > 64)
		m++;

	q = (t * t) * (C[1].d + t * (C[2].d + t * (C[3].d + t * (C[4].d + t * (C[5].d)))));

	l_lead = logtabhi[k].d;
	l_trail = logtablo[k].d;
	l_lead += m * log2_lead.d;
	l_trail += m * log2_trail.d;

	result = l_lead + (C[0].d * t + (q + l_trail));

	return result;
}

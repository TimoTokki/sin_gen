#include "libm.h"
#include "myhead.h"
extern	const du	_logtabhi[];
extern	const du	_logtablo[];
extern	const du	_log_ru[];

static const long long	twop7 =
{ 0x4060000000000000ll }; // 128

static	const du	twopm7 =
{ D(0x3f800000, 0x00000000) }; // 1/128

static const du	log2_lead =
{ D(0x3fe62e42, 0xfefa4000) };

static const du	log2_trail =
{ D(0xbd48432a, 0x1b0e2634) };

static const du	Scaleup =
{ D(0x43300000, 0x00000000) };

/* coefficients for polynomial approximation of log(1 + t) on +/- 1/256   */
/*
static const du	P[] =
{
{D(0x3ff00000, 0x00000000)}, // 1
{D(0xbfe00000, 0x00000001)}, // -0.5
{D(0x3fd55555, 0x55509ba5)}, // 1/3
{D(0xbfcfffff, 0xffeb6526)}, // -1/4
{D(0x3fc999b4, 0xdfed6fe4)}, // 1/5
{D(0xbfc55576, 0x66472e04)}, // -1/6
};
*/
/* coefficients for polynomial approximation of log(1 + x) on [0, 1/128] */
// absoulute is badder than the default way.
// P = fpminimax(log(1+x), [|1,2,3,4,5,6|], [|D...|], [1b-53,1/128], absolute);
// x * (0x3feffffffffffffe + x * (0xbfdfffffffffd626 + x * (0x3fd5555554c89417 + x * (0xbfcffffe52d8506d + x * (0x3fc99850fac569f1 + x * 0xbfc4d9c958a55e3b)))))
/*
static const DL
P[] =
{
	{.l = 0x3feffffffffffffe},
	{.l = 0xbfdfffffffffd626},
	{.l = 0x3fd5555554c89417},
	{.l = 0xbfcffffe52d8506d},
	{.l = 0x3fc99850fac569f1},
	{.l = 0xbfc4d9c958a55e3b},
};
*/

// just setting degree to 5 is not enough, better use the second way [|1,2,3,4,5,6|]
// P = fpminimax(log(1+x), 5, [|D...|], [1b-53,1/128]);
// P = fpminimax(log(1+x), [|1,2,3,4,5,6|], [|D...|], [1b-53,1/128]);
// x * (0x3ff0000000000000 + x * (0xbfdffffffffff8ba + x * (0x3fd55555552260cf + x * (0xbfcfffff16c63d6a + x * (0x3fc998afe2adfada + x * 0xbfc4eaa610c545e3)))))
/*
static const DL
P[] =
{
	{.l = 0x3ff0000000000000},
	{.l = 0xbfdffffffffff8ba},
	{.l = 0x3fd55555552260cf},
	{.l = 0xbfcfffff16c63d6a},
	{.l = 0x3fc998afe2adfada},
	{.l = 0xbfc4eaa610c545e3},
};
*/
// P = fpminimax(log(1+x), [|1,2,3,4,5,6,7|], [|D...|], [1b-53,1/128]);
// x * (0x3ff0000000000000 + x * (0xbfdffffffffffffc + x * (0x3fd5555555552dde + x * (0xbfcffffffefe562d + x * (0x3fc9999817d3a50f + x * (0xbfc554317b3f67a5 + x * 0x3fc1dc5c45e09c18))))))
static const DL
P[] =
{
	{.l = 0x3ff0000000000000},
	{.l = 0xbfdffffffffffffc},
	{.l = 0x3fd5555555552dde},
	{.l = 0xbfcffffffefe562d},
	{.l = 0x3fc9999817d3a50f},
	{.l = 0xbfc554317b3f67a5},
	{.l = 0x3fc1dc5c45e09c18},
};
const du	_logtabhi[] =
{
{D(0x00000000, 0x00000000)},
{D(0x3f7fe02a, 0x6b200000)}, // ln(1+1/128)
{D(0x3f8fc0a8, 0xb1000000)}, // ln(1+2/128)
{D(0x3f97b91b, 0x07d80000)},
{D(0x3f9f829b, 0x0e780000)},
{D(0x3fa39e87, 0xba000000)},
{D(0x3fa77458, 0xf6340000)},
{D(0x3fab42dd, 0x71180000)},
{D(0x3faf0a30, 0xc0100000)},
{D(0x3fb16536, 0xeea40000)},
{D(0x3fb341d7, 0x961c0000)},
{D(0x3fb51b07, 0x3f060000)},
{D(0x3fb6f0d2, 0x8ae60000)},
{D(0x3fb8c345, 0xd6320000)},
{D(0x3fba926d, 0x3a4a0000)},
{D(0x3fbc5e54, 0x8f5c0000)},
{D(0x3fbe2707, 0x6e2a0000)},
{D(0x3fbfec91, 0x31dc0000)},
{D(0x3fc0d77e, 0x7cd10000)},
{D(0x3fc1b72a, 0xd52f0000)},
{D(0x3fc29552, 0xf8200000)},
{D(0x3fc371fc, 0x201f0000)},
{D(0x3fc44d2b, 0x6ccb0000)},
{D(0x3fc526e5, 0xe3a20000)},
{D(0x3fc5ff30, 0x70a80000)},
{D(0x3fc6d60f, 0xe71a0000)},
{D(0x3fc7ab89, 0x02110000)},
{D(0x3fc87fa0, 0x65210000)},
{D(0x3fc9525a, 0x9cf40000)},
{D(0x3fca23bc, 0x1fe30000)},
{D(0x3fcaf3c9, 0x4e810000)},
{D(0x3fcbc286, 0x742e0000)},
{D(0x3fcc8ff7, 0xc79b0000)},
{D(0x3fcd5c21, 0x6b500000)},
{D(0x3fce2707, 0x6e2b0000)},
{D(0x3fcef0ad, 0xcbdc0000)},
{D(0x3fcfb918, 0x6d5e0000)},
{D(0x3fd04025, 0x94b50000)},
{D(0x3fd0a324, 0xe2738000)},
{D(0x3fd1058b, 0xf9ae8000)},
{D(0x3fd1675c, 0xabab8000)},
{D(0x3fd1c898, 0xc1698000)},
{D(0x3fd22941, 0xfbcf8000)},
{D(0x3fd2895a, 0x13de8000)},
{D(0x3fd2e8e2, 0xbae10000)},
{D(0x3fd347dd, 0x9a988000)},
{D(0x3fd3a64c, 0x55698000)},
{D(0x3fd40430, 0x86868000)},
{D(0x3fd4618b, 0xc21c8000)},
{D(0x3fd4be5f, 0x95778000)},
{D(0x3fd51aad, 0x872e0000)},
{D(0x3fd57677, 0x17458000)},
{D(0x3fd5d1bd, 0xbf580000)},
{D(0x3fd62c82, 0xf2ba0000)},
{D(0x3fd686c8, 0x1e9b0000)},
{D(0x3fd6e08e, 0xaa2b8000)},
{D(0x3fd739d7, 0xf6bc0000)},
{D(0x3fd792a5, 0x5fdd8000)},
{D(0x3fd7eaf8, 0x3b828000)},
{D(0x3fd842d1, 0xda1e8000)},
{D(0x3fd89a33, 0x86c18000)},
{D(0x3fd8f11e, 0x87368000)},
{D(0x3fd94794, 0x1c210000)},
{D(0x3fd99d95, 0x81180000)},
{D(0x3fd9f323, 0xecbf8000)},
{D(0xbfd21445, 0x6d0e8000)},
{D(0xbfd1bf99, 0x635a8000)},
{D(0xbfd16b5c, 0xcbad0000)},
{D(0xbfd1178e, 0x82280000)},
{D(0xbfd0c42d, 0x67618000)},
{D(0xbfd07138, 0x604d8000)},
{D(0xbfd01eae, 0x56270000)},
{D(0xbfcf991c, 0x6cb40000)},
{D(0xbfcef5ad, 0xe4dd0000)},
{D(0xbfce530e, 0xffe70000)},
{D(0xbfcdb13d, 0xb0d50000)},
{D(0xbfcd1037, 0xf2650000)},
{D(0xbfcc6ffb, 0xc6f00000)},
{D(0xbfcbd087, 0x383c0000)},
{D(0xbfcb31d8, 0x575c0000)},
{D(0xbfca93ed, 0x3c8b0000)},
{D(0xbfc9f6c4, 0x07090000)},
{D(0xbfc95a5a, 0xdcf70000)},
{D(0xbfc8beaf, 0xeb390000)},
{D(0xbfc823c1, 0x65520000)},
{D(0xbfc7898d, 0x85440000)},
{D(0xbfc6f012, 0x8b750000)},
{D(0xbfc6574e, 0xbe8c0000)},
{D(0xbfc5bf40, 0x6b540000)},
{D(0xbfc527e5, 0xe4a20000)},
{D(0xbfc4913d, 0x83340000)},
{D(0xbfc3fb45, 0xa5990000)},
{D(0xbfc365fc, 0xb0160000)},
{D(0xbfc2d161, 0x0c870000)},
{D(0xbfc23d71, 0x2a4a0000)},
{D(0xbfc1aa2b, 0x7e240000)},
{D(0xbfc1178e, 0x82280000)},
{D(0xbfc08598, 0xb59e0000)},
{D(0xbfbfe891, 0x39dc0000)},
{D(0xbfbec739, 0x830a0000)},
{D(0xbfbda727, 0x63840000)},
{D(0xbfbc8858, 0x01bc0000)},
{D(0xbfbb6ac8, 0x8dae0000)},
{D(0xbfba4e76, 0x40b20000)},
{D(0xbfb9335e, 0x5d5a0000)},
{D(0xbfb8197e, 0x2f400000)},
{D(0xbfb700d3, 0x0aea0000)},
{D(0xbfb5e95a, 0x4d980000)},
{D(0xbfb4d311, 0x5d200000)},
{D(0xbfb3bdf5, 0xa7d20000)},
{D(0xbfb2aa04, 0xa4480000)},
{D(0xbfb1973b, 0xd1460000)},
{D(0xbfb08598, 0xb59e0000)},
{D(0xbfaeea31, 0xc0080000)},
{D(0xbfaccb73, 0xcddc0000)},
{D(0xbfaaaef2, 0xd0fc0000)},
{D(0xbfa894aa, 0x14a00000)},
{D(0xbfa67c94, 0xf2d40000)},
{D(0xbfa466ae, 0xd42c0000)},
{D(0xbfa252f3, 0x2f8c0000)},
{D(0xbfa0415d, 0x89e80000)},
{D(0xbf9c63d2, 0xec180000)},
{D(0xbf984925, 0x28c80000)},
{D(0xbf9432a9, 0x25980000)},
{D(0xbf902056, 0x58900000)},
{D(0xbf882448, 0xa3900000)},
{D(0xbf801015, 0x75900000)},
{D(0xbf700805, 0x59600000)},
{D(0x00000000, 0x00000000)},
};

const du	_logtablo[] =
{
{D(0x00000000, 0x00000000)},
{D(0xbd6f30ee, 0x07912df9)},
{D(0xbd5fe0e1, 0x83092c59)},
{D(0xbd62772a, 0xb6c0559c)},
{D(0x3d298026, 0x7c7e09e4)},
{D(0xbd642a05, 0x6fea4dfd)},
{D(0xbd62303b, 0x9cb0d5e1)},
{D(0x3d671bec, 0x28d14c7e)},
{D(0x3d662a66, 0x17cc9717)},
{D(0xbd60a3e2, 0xf3b47d18)},
{D(0xbd4717b6, 0xb33e44f8)},
{D(0x3d383f69, 0x278e686a)},
{D(0xbd62968c, 0x836cc8c2)},
{D(0xbd5937c2, 0x94d2f567)},
{D(0x3d6aac6c, 0xa17a4554)},
{D(0xbd4c5e75, 0x14f4083f)},
{D(0x3d6e5cbd, 0x3d50fffc)},
{D(0xbd354555, 0xd1ae6607)},
{D(0xbd6c69a6, 0x5a23a170)},
{D(0x3d69e80a, 0x41811a39)},
{D(0xbd35b967, 0xf4471dfc)},
{D(0xbd6c22f1, 0x0c9a4ea8)},
{D(0x3d6f4799, 0xf4f6543e)},
{D(0xbd62f217, 0x46ff8a47)},
{D(0xbd6b0b0d, 0xe3077d7e)},
{D(0xbd56f1b9, 0x55c4d1da)},
{D(0xbd537b72, 0x0e4a694b)},
{D(0xbd5b77b7, 0xeffb7f41)},
{D(0x3d65ad1d, 0x904c1d4e)},
{D(0xbd62a739, 0xb23b93e1)},
{D(0xbd600349, 0xcc67f9b2)},
{D(0xbd6cca75, 0x818c5dbc)},
{D(0xbd697794, 0xf689f843)},
{D(0xbd611ba9, 0x1bbca682)},
{D(0xbd3a342c, 0x2af0003c)},
{D(0x3d664d94, 0x8637950e)},
{D(0x3d5f1546, 0xaaa3361c)},
{D(0xbd67df92, 0x8ec217a5)},
{D(0x3d50e35f, 0x73f7a018)},
{D(0xbd6a9573, 0xb02faa5a)},
{D(0x3d630701, 0xce63eab9)},
{D(0x3d59fafb, 0xc68e7540)},
{D(0xbd3a6976, 0xf5eb0963)},
{D(0x3d3a8d7a, 0xd24c13f0)},
{D(0x3d5d309c, 0x2cc91a85)},
{D(0xbd25594d, 0xd4c58092)},
{D(0xbd6d0b1c, 0x68651946)},
{D(0x3d63f1de, 0x86093efa)},
{D(0xbd609ec1, 0x7a426426)},
{D(0xbd3d7c92, 0xcd9ad824)},
{D(0xbd3f4bd8, 0xdb0a7cc1)},
{D(0xbd62c9d5, 0xb2a49af9)},
{D(0x3d4394a1, 0x1b1c1ee4)},
{D(0xbd6c3568, 0x48506ead)},
{D(0x3d54aec4, 0x42be1015)},
{D(0x3d60f1c6, 0x09c98c6c)},
{D(0xbd67fcb1, 0x8ed9d603)},
{D(0xbd6c2ec1, 0xf512dc03)},
{D(0x3d67e1b2, 0x59d2f3da)},
{D(0x3d462e92, 0x7628cbc2)},
{D(0xbd6ed2a5, 0x2c73bf78)},
{D(0xbd5d3881, 0xe8962a96)},
{D(0x3d56faba, 0x4cdd147d)},
{D(0xbd5f7534, 0x56d113b8)},
{D(0x3d584bf2, 0xb68d766f)},
{D(0xbd6c6a1f, 0x7ae91aec)},
{D(0x3d546b22, 0x55d70849)},
{D(0x3d323299, 0x042d74bf)},
{D(0x3d5b8421, 0xcc74be04)},
{D(0x3d5d1cee, 0x9d3862a3)},
{D(0x3d63cec6, 0x49d22563)},
{D(0x3d6cb784, 0x60a42f4a)},
{D(0x3d6321a0, 0x99af9906)},
{D(0x3cca2115, 0x65bb8e11)},
{D(0xbd401212, 0x276041f4)},
{D(0x3d6daff2, 0xaf715b03)},
{D(0xbd679ed6, 0x06292424)},
{D(0xbd3ee138, 0xd3a69d43)},
{D(0x3d53a978, 0x8b2a8257)},
{D(0x3d58e1ac, 0x6a75670d)},
{D(0x3d530e48, 0x6a0ac42d)},
{D(0x3d6a66fb, 0x2979a7e8)},
{D(0xbd07f228, 0x58a0ff6f)},
{D(0x3d073d54, 0xaae92cd1)},
{D(0x3d670f91, 0x232ce70c)},
{D(0xbd631ccf, 0x7c7b75e8)},
{D(0xbd6aaee7, 0x21a63de2)},
{D(0xbd4339f1, 0x658785cf)},
{D(0xbd5ed8fd, 0xc149767e)},
{D(0x3d629cc1, 0x71a96824)},
{D(0x3d62a7c8, 0x6ab02498)},
{D(0xbd5465c4, 0xf032b956)},
{D(0x3d6bfa74, 0x15f72d23)},
{D(0x3d6fb18a, 0x4cd1f92d)},
{D(0x3d5eff2d, 0xc702c20a)},
{D(0x3d31ac38, 0xdde3b366)},
{D(0x3d4b8421, 0xcc74be04)},
{D(0xbd5d0344, 0x51fecdfb)},
{D(0x3d454d35, 0x93e842bf)},
{D(0xbd311fcb, 0xa80cdd10)},
{D(0xbd51a894, 0x01fa7173)},
{D(0xbd52c8da, 0x38cb559a)},
{D(0x3d649c84, 0x015fbb47)},
{D(0x3d50f215, 0xb5ca203e)},
{D(0x3d66ceea, 0x3c542b82)},
{D(0xbd6c7e03, 0x73e5bff8)},
{D(0xbd681c1e, 0x8da99ded)},
{D(0x3d5b8d20, 0xc78ba3a4)},
{D(0xbd5fab17, 0x69f42c78)},
{D(0x3d319bd0, 0xad125895)},
{D(0x3d6d0b6e, 0x8ae9c698)},
{D(0xbd5559b4, 0x553e4c2d)},
{D(0xbd4d0344, 0x51fecdfb)},
{D(0x3d647844, 0xf93f24ee)},
{D(0xbd6b2cb8, 0x6dc13ec0)},
{D(0x3d5de07c, 0xb958897a)},
{D(0x3d432f32, 0xba0b44d0)},
{D(0xbd576b08, 0x209f3283)},
{D(0xbd6e3e98, 0xc8a4202d)},
{D(0xbd6183e9, 0xae021b68)},
{D(0x3d577771, 0xfd187145)},
{D(0x3d6aa873, 0x9c0614d1)},
{D(0xbd4957d1, 0x73697cf3)},
{D(0xbd098139, 0x928637fe)},
{D(0xbd6ac23a, 0x4f91d083)},
{D(0x3d6d7557, 0x7da74f64)},
{D(0x3d6c863b, 0x5ccce95f)},
{D(0x3d5dd32a, 0x0699c731)},
{D(0x00000000, 0x00000000)},
};

const du	_log_ru[] =
{
{D(0x3ff00000, 0x00000000)},
{D(0x3fefc07f, 0x01fc07f0)},
{D(0x3fef81f8, 0x1f81f820)},
{D(0x3fef4465, 0x9e4a4271)},
{D(0x3fef07c1, 0xf07c1f08)},
{D(0x3feecc07, 0xb301ecc0)},
{D(0x3fee9131, 0xabf0b767)},
{D(0x3fee573a, 0xc901e574)},
{D(0x3fee1e1e, 0x1e1e1e1e)},
{D(0x3fede5d6, 0xe3f8868a)},
{D(0x3fedae60, 0x76b981db)},
{D(0x3fed77b6, 0x54b82c34)},
{D(0x3fed41d4, 0x1d41d41d)},
{D(0x3fed0cb5, 0x8f6ec074)},
{D(0x3fecd856, 0x89039b0b)},
{D(0x3feca4b3, 0x055ee191)},
{D(0x3fec71c7, 0x1c71c71c)},
{D(0x3fec3f8f, 0x01c3f8f0)},
{D(0x3fec0e07, 0x0381c0e0)},
{D(0x3febdd2b, 0x899406f7)},
{D(0x3febacf9, 0x14c1bad0)},
{D(0x3feb7d6c, 0x3dda338b)},
{D(0x3feb4e81, 0xb4e81b4f)},
{D(0x3feb2036, 0x406c80d9)},
{D(0x3feaf286, 0xbca1af28)},
{D(0x3feac570, 0x1ac5701b)},
{D(0x3fea98ef, 0x606a63be)},
{D(0x3fea6d01, 0xa6d01a6d)},
{D(0x3fea41a4, 0x1a41a41a)},
{D(0x3fea16d3, 0xf97a4b02)},
{D(0x3fe9ec8e, 0x951033d9)},
{D(0x3fe9c2d1, 0x4ee4a102)},
{D(0x3fe99999, 0x9999999a)},
{D(0x3fe970e4, 0xf80cb872)},
{D(0x3fe948b0, 0xfcd6e9e0)},
{D(0x3fe920fb, 0x49d0e229)},
{D(0x3fe8f9c1, 0x8f9c18fa)},
{D(0x3fe8d301, 0x8d3018d3)},
{D(0x3fe8acb9, 0x0f6bf3aa)},
{D(0x3fe886e5, 0xf0abb04a)},
{D(0x3fe86186, 0x18618618)},
{D(0x3fe83c97, 0x7ab2bedd)},
{D(0x3fe81818, 0x18181818)},
{D(0x3fe7f405, 0xfd017f40)},
{D(0x3fe7d05f, 0x417d05f4)},
{D(0x3fe7ad22, 0x08e0ecc3)},
{D(0x3fe78a4c, 0x8178a4c8)},
{D(0x3fe767dc, 0xe434a9b1)},
{D(0x3fe745d1, 0x745d1746)},
{D(0x3fe72428, 0x7f46debc)},
{D(0x3fe702e0, 0x5c0b8170)},
{D(0x3fe6e1f7, 0x6b4337c7)},
{D(0x3fe6c16c, 0x16c16c17)},
{D(0x3fe6a13c, 0xd1537290)},
{D(0x3fe68168, 0x16816817)},
{D(0x3fe661ec, 0x6a5122f9)},
{D(0x3fe642c8, 0x590b2164)},
{D(0x3fe623fa, 0x77016240)},
{D(0x3fe60581, 0x60581606)},
{D(0x3fe5e75b, 0xb8d015e7)},
{D(0x3fe5c988, 0x2b931057)},
{D(0x3fe5ac05, 0x6b015ac0)},
{D(0x3fe58ed2, 0x308158ed)},
{D(0x3fe571ed, 0x3c506b3a)},
{D(0x3fe55555, 0x55555555)},
{D(0x3fe53909, 0x48f40feb)},
{D(0x3fe51d07, 0xeae2f815)},
{D(0x3fe50150, 0x15015015)},
{D(0x3fe4e5e0, 0xa72f0539)},
{D(0x3fe4cab8, 0x8725af6e)},
{D(0x3fe4afd6, 0xa052bf5b)},
{D(0x3fe49539, 0xe3b2d067)},
{D(0x3fe47ae1, 0x47ae147b)},
{D(0x3fe460cb, 0xc7f5cf9a)},
{D(0x3fe446f8, 0x6562d9fb)},
{D(0x3fe42d66, 0x25d51f87)},
{D(0x3fe41414, 0x14141414)},
{D(0x3fe3fb01, 0x3fb013fb)},
{D(0x3fe3e22c, 0xbce4a902)},
{D(0x3fe3c995, 0xa47babe7)},
{D(0x3fe3b13b, 0x13b13b14)},
{D(0x3fe3991c, 0x2c187f63)},
{D(0x3fe38138, 0x13813814)},
{D(0x3fe3698d, 0xf3de0748)},
{D(0x3fe3521c, 0xfb2b78c1)},
{D(0x3fe33ae4, 0x5b57bcb2)},
{D(0x3fe323e3, 0x4a2b10bf)},
{D(0x3fe30d19, 0x0130d190)},
{D(0x3fe2f684, 0xbda12f68)},
{D(0x3fe2e025, 0xc04b8097)},
{D(0x3fe2c9fb, 0x4d812ca0)},
{D(0x3fe2b404, 0xad012b40)},
{D(0x3fe29e41, 0x29e4129e)},
{D(0x3fe288b0, 0x1288b013)},
{D(0x3fe27350, 0xb8812735)},
{D(0x3fe25e22, 0x708092f1)},
{D(0x3fe24924, 0x92492492)},
{D(0x3fe23456, 0x789abcdf)},
{D(0x3fe21fb7, 0x8121fb78)},
{D(0x3fe20b47, 0x0c67c0d9)},
{D(0x3fe1f704, 0x7dc11f70)},
{D(0x3fe1e2ef, 0x3b3fb874)},
{D(0x3fe1cf06, 0xada2811d)},
{D(0x3fe1bb4a, 0x4046ed29)},
{D(0x3fe1a7b9, 0x611a7b96)},
{D(0x3fe19453, 0x808ca29c)},
{D(0x3fe18118, 0x11811812)},
{D(0x3fe16e06, 0x89427379)},
{D(0x3fe15b1e, 0x5f75270d)},
{D(0x3fe1485f, 0x0e0acd3b)},
{D(0x3fe135c8, 0x1135c811)},
{D(0x3fe12358, 0xe75d3033)},
{D(0x3fe11111, 0x11111111)},
{D(0x3fe0fef0, 0x10fef011)},
{D(0x3fe0ecf5, 0x6be69c90)},
{D(0x3fe0db20, 0xa88f4696)},
{D(0x3fe0c971, 0x4fbcda3b)},
{D(0x3fe0b7e6, 0xec259dc8)},
{D(0x3fe0a681, 0x0a6810a7)},
{D(0x3fe0953f, 0x39010954)},
{D(0x3fe08421, 0x08421084)},
{D(0x3fe07326, 0x0a47f7c6)},
{D(0x3fe0624d, 0xd2f1a9fc)},
{D(0x3fe05197, 0xf7d73404)},
{D(0x3fe04104, 0x10410410)},
{D(0x3fe03091, 0xb51f5e1a)},
{D(0x3fe02040, 0x81020408)},
{D(0x3fe01010, 0x10101010)},
{D(0x3fe00000, 0x00000000)},
};

static const du	Qnan =
{ D(QNANHI, QNANLO) };

static const du	Inf =
{ D(0x7ff00000, 0x00000000) };

static const du	Neginf =
{ D(0xfff00000, 0x00000000) };

#define MAXEXP	0x7ffu

#define	MINEXP	0x001u

double log_gen(double x) {
	unsigned long long ix;
	int	j;
	int	m;
	int	k;
	double	u;
	double	t;
	double	xmu;
	double	q;
	double	l_lead, l_trail;
	double	w;
	double	result;

	/* extract exponent and sign of x for some quick screening */

	ix = *(unsigned long long *)(&x);	/* copy arg to a long long */

	m = (ix >> DMANTWIDTH);		/* shift off mantissa	*/
	j = m - MINEXP;

	m -= DEXPBIAS;

	/* normalize x and compute the nearest 1/128th to x */

	ix &= (DSIGNMASK & DEXPMASK);	/* mask off sign and exponent
						* bits of x
						*/
	ix |= twop7;	/* set exponent of x to 0x406 */

	/* adjust scaled arg	*/

	//LL2DBL(ix, w);
	w = *(double *)(&ix);

	//k = ROUND(w);
	//k = w + 0.5; // !!! +0.5 !!!
	k = w;

	u = k;

	k -= 128; // the number 128 here is for zhengshu bit "1"

	xmu = twopm7.d*(w - u);

	t = _log_ru[k].d*xmu;

	/* avoid loss of significance for values of x near two
		by adjusting index; effectively u is divided by two.
		The logtable has been adjusted for this.
	*/

	if (k > 64)
		m++;
	//q = ((((P[5].d*t + P[4].d)*t + P[3].d)*t + P[2].d)*t + P[1].d)*(t*t);
	q = (((((P[6].d*t + P[5].d)*t + P[4].d)*t + P[3].d)*t + P[2].d)*t + P[1].d)*(t*t);
	//q = ((((P[5].d*t + P[4].d)*t + P[3].d)*t + P[2].d)*t + P[1].d)*(t*t) + t;
	
	l_lead = _logtabhi[k].d;
	l_trail = _logtablo[k].d;

	l_lead += m * log2_lead.d;
	l_trail += m * log2_trail.d;
	
	result = l_lead + (P[0].d * t + (q + l_trail));
	//result = l_lead + (q + l_trail);
	
	if (j >= (MAXEXP - MINEXP)) {
		result = Qnan.d;
	}	

	if (x == 0.0){
		result = Neginf.d;
	}

	if (x == Inf.d) {
		result = Inf.d;
	}
	
	if (x == 1){
		result = 0;
	}
	return result;
}

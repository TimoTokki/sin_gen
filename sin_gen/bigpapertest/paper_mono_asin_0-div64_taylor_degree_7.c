#include <stdio.h>
#include <math.h>
#include "myhead.h"

#define NUM 12
#define TABLE_NUM 128
#define M 6

static const DL
P[] =
{
{.l = 0x3ff0000000000000},
{.l = 0x3fc5555555555578},
{.l = 0x3fb33333333256c4},
{.l = 0x3fa6db6db8b92be5},
{.l = 0x3f9f1c6fdcc39d32},
{.l = 0x3f96e9407e05b546},
{.l = 0x3f91b0c9c6fc9434},
{.l = 0x3f8fb249579227f4},
};

static const DL
C[NUM] = {
	{.l = 0},
	{.l = 0x3ff0000000000000},//asin 1
	{.l = 0},
	{.l = 0x3fc5555555555555},//asin 1/6
 	{.l = 0},
	{.l = 0x3fb3333333333333},//asin 3/40
	{.l = 0},
	{.l = 0x3fa6db6db6db6db7},//asin 5/112
	{.l = 0},
	{.l = 0x3f9f1c71c71c71c7},//asin 35/1152
	{.l = 0},
	{.l = 0x3fa6e8ba2e8ba2e9},//asin 63/1408
};

static const DL
asin_tab[TABLE_NUM] = {
	{.l = 0x0000000000000000},
    {.l = 0x3f80000aaabdde0c},
    {.l = 0x3f90002aabdde94c},
    {.l = 0x3f980090091d9024},
    {.l = 0x3fa000aabde0b9c8},
    {.l = 0x3fa4014d8ffaf8af},
    {.l = 0x3fa8024091fdb0a9},
    {.l = 0x3fac0393e65c2c93},
    {.l = 0x3fb002abde953619},
    {.l = 0x3fb203ce2b380cd3},
    {.l = 0x3fb405390240e6fd},
    {.l = 0x3fb606f49730ccc5},
    {.l = 0x3fb809092913e52e},
    {.l = 0x3fba0b7f03ba78ac},
    {.l = 0x3fbc0e5e80f7172d},
    {.l = 0x3fbe11b009e269b5},
    {.l = 0x3fc00abe0c129e1e},
    {.l = 0x3fc10ce59ba4a8c4},
    {.l = 0x3fc20f530308cc20},
    {.l = 0x3fc3120a9bed2f46},
    {.l = 0x3fc41510cb011423},
    {.l = 0x3fc5186a00ade974},
    {.l = 0x3fc61c1ab9d55d30},
    {.l = 0x3fc720278094cd3c},
    {.l = 0x3fc82494ed0e78fc},
    {.l = 0x3fc92967a638db38},
    {.l = 0x3fca2ea462b4998e},
    {.l = 0x3fcb344fe9a97c4d},
    {.l = 0x3fcc3a6f13aae84b},
    {.l = 0x3fcd4106cba45b08},
    {.l = 0x3fce481c0fce7134},
    {.l = 0x3fcf4fb3f2ad079b},
    {.l = 0x3fd02be9ce0b87cd},
    {.l = 0x3fd0b04025245ccc},
    {.l = 0x3fd134dfa9805147},
    {.l = 0x3fd1b9cb12545e62},
    {.l = 0x3fd23f0523c5dc2b},
    {.l = 0x3fd2c490af8bde81},
    {.l = 0x3fd34a709597aab1},
    {.l = 0x3fd3d0a7c4c4bd9c},
    {.l = 0x3fd457393b90e2aa},
    {.l = 0x3fd4de2808dce513},
    {.l = 0x3fd565774cb66f02},
    {.l = 0x3fd5ed2a392bb50f},
    {.l = 0x3fd675441329986e},
    {.l = 0x3fd6fdc83364f719},
    {.l = 0x3fd786ba074fef93},
    {.l = 0x3fd8101d121bed2d},
    {.l = 0x3fd899f4edc962d3},
    {.l = 0x3fd924454c462cc4},
    {.l = 0x3fd9af11f89ba61c},
    {.l = 0x3fda3a5ed82d9537},
    {.l = 0x3fdac62fec0b2a92},
    {.l = 0x3fdb5289525368ab},
    {.l = 0x3fdbdf6f47ae6904},
    {.l = 0x3fdc6ce628dd132c},
    {.l = 0x3fdcfaf27460fe9f},
    {.l = 0x3fdd8998cc3e6049},
    {.l = 0x3fde18ddf7da106b},
    {.l = 0x3fdea8c6e5f5e67f},
    {.l = 0x3fdf3958aecddef4},
    {.l = 0x3fdfca989658baaf},
    {.l = 0x3fe02e46075785a1},
    {.l = 0x3fe0779c5d4df4b8},
    {.l = 0x3fe0c152382d7366},
    {.l = 0x3fe10b6a9e43942f},
    {.l = 0x3fe155e8b2a00052},
    {.l = 0x3fe1a0cfb6c3e9eb},
    {.l = 0x3fe1ec230c714a96},
    {.l = 0x3fe237e6379cdfc7},
    {.l = 0x3fe2841ce0862975},
    {.l = 0x3fe2d0cad5f90e20},
    {.l = 0x3fe31df40fbd31cd},
    {.l = 0x3fe36b9cb13786e1},
    {.l = 0x3fe3b9c90c43296d},
    {.l = 0x3fe4087da4473296},
    {.l = 0x3fe457bf318fe517},
    {.l = 0x3fe4a792a4f26152},
    {.l = 0x3fe4f7fd2bc2fb34},
    {.l = 0x3fe5490434275b92},
    {.l = 0x3fe59aad71ced00f},
    {.l = 0x3fe5ecfee31c96e7},
    {.l = 0x3fe63ffed6d198f6},
    {.l = 0x3fe693b3f244ee17},
    {.l = 0x3fe6e825383cc40b},
    {.l = 0x3fe73d5a107bde74},
    {.l = 0x3fe7935a501afa78},
    {.l = 0x3fe7ea2e42c9027a},
    {.l = 0x3fe841deb5114bb4},
    {.l = 0x3fe89a74ffcc34a4},
    {.l = 0x3fe8f3fb14e496b4},
    {.l = 0x3fe94e7b8da3cf7a},
    {.l = 0x3fe9aa01babef75e},
    {.l = 0x3fea0699b66a8718},
    {.l = 0x3fea645078c6a78c},
    {.l = 0x3feac333ef06451a},
    {.l = 0x3feb235315c680dc},
    {.l = 0x3feb84be172438ef},
    {.l = 0x3febe7866d3b6481},
    {.l = 0x3fec4bbf09e19830},
    {.l = 0x3fecb17c849c7288},
    {.l = 0x3fed18d55010f295},
    {.l = 0x3fed81e1f875ea8d},
    {.l = 0x3fedecbd6cf77786},
    {.l = 0x3fee5985567b665d},
    {.l = 0x3feec85a7ee191da},
    {.l = 0x3fef39614cbef7d4},
    {.l = 0x3fefacc258c4aaf9},
    {.l = 0x3ff0115591d29d12},
    {.l = 0x3ff04da77ac5c9e5},
    {.l = 0x3ff08b73f9af1058},
    {.l = 0x3ff0cadc3d4378b1},
    {.l = 0x3ff10c066d3e6932},
    {.l = 0x3ff14f1ec67484ed},
    {.l = 0x3ff194590de7e7f6},
    {.l = 0x3ff1dbf27dd2221a},
    {.l = 0x3ff2263461820ad8},
    {.l = 0x3ff27377b2570a1e},
    {.l = 0x3ff2c42a3a3c7a87},
    {.l = 0x3ff318d619008ed9},
    {.l = 0x3ff3722d2feb24c8},
    {.l = 0x3ff3d11b3fc3b697},
    {.l = 0x3ff436e4418e69c0},
    {.l = 0x3ff4a55ae332c7a5},
    {.l = 0x3ff51f4bd13f8591},
    {.l = 0x3ff5a96e34bc532b},
    {.l = 0x3ff64cf55148366f},
    {.l = 0x3ff721a5d8718655}
};

static const DL
sk[TABLE_NUM] = {
	{.l = 0x0000000000000000},
	{.l = 0x3f80000000000000},
	{.l = 0x3f90000000000000},
	{.l = 0x3f98000000000000},
	{.l = 0x3fa0000000000000},
	{.l = 0x3fa4000000000000},
	{.l = 0x3fa8000000000000},
	{.l = 0x3fac000000000000},
	{.l = 0x3fb0000000000000},
	{.l = 0x3fb2000000000000},
	{.l = 0x3fb4000000000000},
	{.l = 0x3fb6000000000000},
	{.l = 0x3fb8000000000000},
	{.l = 0x3fba000000000000},
	{.l = 0x3fbc000000000000},
	{.l = 0x3fbe000000000000},
	{.l = 0x3fc0000000000000},
	{.l = 0x3fc1000000000000},
	{.l = 0x3fc2000000000000},
	{.l = 0x3fc3000000000000},
	{.l = 0x3fc4000000000000},
	{.l = 0x3fc5000000000000},
	{.l = 0x3fc6000000000000},
	{.l = 0x3fc7000000000000},
	{.l = 0x3fc8000000000000},
	{.l = 0x3fc9000000000000},
	{.l = 0x3fca000000000000},
	{.l = 0x3fcb000000000000},
	{.l = 0x3fcc000000000000},
	{.l = 0x3fcd000000000000},
	{.l = 0x3fce000000000000},
	{.l = 0x3fcf000000000000},
	{.l = 0x3fd0000000000000},
	{.l = 0x3fd0800000000000},
	{.l = 0x3fd1000000000000},
	{.l = 0x3fd1800000000000},
	{.l = 0x3fd2000000000000},
	{.l = 0x3fd2800000000000},
	{.l = 0x3fd3000000000000},
	{.l = 0x3fd3800000000000},
	{.l = 0x3fd4000000000000},
	{.l = 0x3fd4800000000000},
	{.l = 0x3fd5000000000000},
	{.l = 0x3fd5800000000000},
	{.l = 0x3fd6000000000000},
	{.l = 0x3fd6800000000000},
	{.l = 0x3fd7000000000000},
	{.l = 0x3fd7800000000000},
	{.l = 0x3fd8000000000000},
	{.l = 0x3fd8800000000000},
	{.l = 0x3fd9000000000000},
	{.l = 0x3fd9800000000000},
	{.l = 0x3fda000000000000},
	{.l = 0x3fda800000000000},
	{.l = 0x3fdb000000000000},
	{.l = 0x3fdb800000000000},
	{.l = 0x3fdc000000000000},
	{.l = 0x3fdc800000000000},
	{.l = 0x3fdd000000000000},
	{.l = 0x3fdd800000000000},
	{.l = 0x3fde000000000000},
	{.l = 0x3fde800000000000},
	{.l = 0x3fdf000000000000},
	{.l = 0x3fdf800000000000},
	{.l = 0x3fe0000000000000},
	{.l = 0x3fe0400000000000},
	{.l = 0x3fe0800000000000},
	{.l = 0x3fe0c00000000000},
	{.l = 0x3fe1000000000000},
	{.l = 0x3fe1400000000000},
	{.l = 0x3fe1800000000000},
	{.l = 0x3fe1c00000000000},
	{.l = 0x3fe2000000000000},
	{.l = 0x3fe2400000000000},
	{.l = 0x3fe2800000000000},
	{.l = 0x3fe2c00000000000},
	{.l = 0x3fe3000000000000},
	{.l = 0x3fe3400000000000},
	{.l = 0x3fe3800000000000},
	{.l = 0x3fe3c00000000000},
	{.l = 0x3fe4000000000000},
	{.l = 0x3fe4400000000000},
	{.l = 0x3fe4800000000000},
	{.l = 0x3fe4c00000000000},
	{.l = 0x3fe5000000000000},
	{.l = 0x3fe5400000000000},
	{.l = 0x3fe5800000000000},
	{.l = 0x3fe5c00000000000},
	{.l = 0x3fe6000000000000},
	{.l = 0x3fe6400000000000},
	{.l = 0x3fe6800000000000},
	{.l = 0x3fe6c00000000000},
	{.l = 0x3fe7000000000000},
	{.l = 0x3fe7400000000000},
	{.l = 0x3fe7800000000000},
	{.l = 0x3fe7c00000000000},
	{.l = 0x3fe8000000000000},
	{.l = 0x3fe8400000000000},
	{.l = 0x3fe8800000000000},
	{.l = 0x3fe8c00000000000},
	{.l = 0x3fe9000000000000},
	{.l = 0x3fe9400000000000},
	{.l = 0x3fe9800000000000},
	{.l = 0x3fe9c00000000000},
	{.l = 0x3fea000000000000},
	{.l = 0x3fea400000000000},
	{.l = 0x3fea800000000000},
	{.l = 0x3feac00000000000},
	{.l = 0x3feb000000000000},
	{.l = 0x3feb400000000000},
	{.l = 0x3feb800000000000},
	{.l = 0x3febc00000000000},
	{.l = 0x3fec000000000000},
	{.l = 0x3fec400000000000},
	{.l = 0x3fec800000000000},
	{.l = 0x3fecc00000000000},
	{.l = 0x3fed000000000000},
	{.l = 0x3fed400000000000},
	{.l = 0x3fed800000000000},
	{.l = 0x3fedc00000000000},
	{.l = 0x3fee000000000000},
	{.l = 0x3fee400000000000},
	{.l = 0x3fee800000000000},
	{.l = 0x3feec00000000000},
	{.l = 0x3fef000000000000},
	{.l = 0x3fef400000000000},
	{.l = 0x3fef800000000000},
	{.l = 0x3fefc00000000000}
};

static const DL
ck[TABLE_NUM] = {
	{.l = 0x3ff0000000000000},
	{.l = 0x3fefffbfffbfff80},
	{.l = 0x3feffefffbffdfff},
	{.l = 0x3feffdbfebbe9360},
	{.l = 0x3feffbffbff7fec0},
	{.l = 0x3feff9bf63a1740b},
	{.l = 0x3feff6febba4bfea},
	{.l = 0x3feff3bda6d9c950},
	{.l = 0x3fefeffbfdfebf1f},
	{.l = 0x3fefebb993aecf99},
	{.l = 0x3fefe6f634576477},
	{.l = 0x3fefe1b1a62bddad},
	{.l = 0x3fefdbeba917c3f5},
	{.l = 0x3fefd5a3f6af6b74},
	{.l = 0x3fefceda421efdb5},
	{.l = 0x3fefc78e3817e16e},
	{.l = 0x3fefbfbf7ebc755f},
	{.l = 0x3fefb76db58a1299},
	{.l = 0x3fefae987541497f},
	{.l = 0x3fefa53f4fcc4b79},
	{.l = 0x3fef9b61d0237250},
	{.l = 0x3fef90ff7a2fd4d2},
	{.l = 0x3fef8617caabd6f6},
	{.l = 0x3fef7aaa3701a270},
	{.l = 0x3fef6eb62d27730d},
	{.l = 0x3fef623b1379a09b},
	{.l = 0x3fef553848924e81},
	{.l = 0x3fef47ad231ea746},
	{.l = 0x3fef3998f1b1886c},
	{.l = 0x3fef2afafa9380f9},
	{.l = 0x3fef1bd27b9002c4},
	{.l = 0x3fef0c1ea9bfa45f},
	{.l = 0x3feefbdeb14f4eda},
	{.l = 0x3feeeb11b5442ff1},
	{.l = 0x3feed9b6cf3c4663},
	{.l = 0x3feec7cd0f2b5ae0},
	{.l = 0x3feeb5537b1434da},
	{.l = 0x3feea2490ebdd6b8},
	{.l = 0x3fee8eacbb648910},
	{.l = 0x3fee7a7d6766784b},
	{.l = 0x3fee65b9edeba38e},
	{.l = 0x3fee50611e88d6b5},
	{.l = 0x3fee3a71bcdd63de},
	{.l = 0x3fee23ea802b4b1a},
	{.l = 0x3fee0cca12e97895},
	{.l = 0x3fedf50f124fba75},
	{.l = 0x3feddcb80ddc085b},
	{.l = 0x3fedc3c386d0ae09},
	{.l = 0x3fedaa2fefaae1d8},
	{.l = 0x3fed8ffbab9145d4},
	{.l = 0x3fed75250db9c792},
	{.l = 0x3fed59aa58c6471c},
	{.l = 0x3fed3d89be176072},
	{.l = 0x3fed20c15d14a4e5},
	{.l = 0x3fed034f42698214},
	{.l = 0x3fece5316736032e},
	{.l = 0x3fecc665b0328622},
	{.l = 0x3feca6e9ecc569b9},
	{.l = 0x3fec86bbd609a260},
	{.l = 0x3fec65d90dc509f4},
	{.l = 0x3fec443f1d4d22af},
	{.l = 0x3fec21eb7458e5cc},
	{.l = 0x3febfedb67be13b3},
	{.l = 0x3febdb0c30185485},
	{.l = 0x3febb67ae8584caa},
	{.l = 0x3feb91248c38986b},
	{.l = 0x3feb6b05f6966b9b},
	{.l = 0x3feb441bdfab5580},
	{.l = 0x3feb1c62db2564fe},
	{.l = 0x3feaf3d7561a9c43},
	{.l = 0x3feaca7594d44cbd},
	{.l = 0x3feaa039b06e926d},
	{.l = 0x3fea751f9447b724},
	{.l = 0x3fea4922fb3ac8c2},
	{.l = 0x3fea1c3f6ca01f29},
	{.l = 0x3fe9ee70390dec3d},
	{.l = 0x3fe9bfb076d236eb},
	{.l = 0x3fe98ffafe1ece2f},
	{.l = 0x3fe95f4a64decda8},
	{.l = 0x3fe92d98fa2c355e},
	{.l = 0x3fe8fae0c15ad38a},
	{.l = 0x3fe8c71b6c8c49b4},
	{.l = 0x3fe8924256bf4545},
	{.l = 0x3fe85c4e7d4a0bb1},
	{.l = 0x3fe8253878ae2e09},
	{.l = 0x3fe7ecf874b086df},
	{.l = 0x3fe7b386279d7bf3},
	{.l = 0x3fe778d8c89dc27c},
	{.l = 0x3fe73ce704fb7b23},
	{.l = 0x3fe6ffa6f4323c0d},
	{.l = 0x3fe6c10e0a9e5d65},
	{.l = 0x3fe681110a985d4d},
	{.l = 0x3fe63fa3f3c02962},
	{.l = 0x3fe5fcb9f031317b},
	{.l = 0x3fe5b8453f4ae294},
	{.l = 0x3fe572371da8f26e},
	{.l = 0x3fe52a7fa9d2f8ea},
	{.l = 0x3fe4e10dc51235a7},
	{.l = 0x3fe495ceefbdc28a},
	{.l = 0x3fe448af2027201c},
	{.l = 0x3fe3f9989320b7f7},
	{.l = 0x3fe3a87394da947b},
	{.l = 0x3fe355264082fea0},
	{.l = 0x3fe2ff9434b34639},
	{.l = 0x3fe2a79e3a2cd2e6},
	{.l = 0x3fe24d21d9bcbd2d},
	{.l = 0x3fe1eff8dd34fde3},
	{.l = 0x3fe18ff8b63353dc},
	{.l = 0x3fe12cf1c3c6a213},
	{.l = 0x3fe0c6ae6dbb479d},
	{.l = 0x3fe05cf20924c254},
	{.l = 0x3fdfdeeeea5d2084},
	{.l = 0x3fdefbdeb14f4eda},
	{.l = 0x3fde0ffbbe00c34f},
	{.l = 0x3fdd1a6f89821641},
	{.l = 0x3fdc1a3cd9862dfb},
	{.l = 0x3fdb0e35269b38f5},
	{.l = 0x3fd9f4e9f1b5859d},
	{.l = 0x3fd8cc97f2912db6},
	{.l = 0x3fd79308a1dd964a},
	{.l = 0x3fd645640568c1c3},
	{.l = 0x3fd4dfe7790ba696},
	{.l = 0x3fd35d6b2ed19148},
	{.l = 0x3fd1b6867c415166},
	{.l = 0x3fcfbfbf7ebc755f},
	{.l = 0x3fcb8cc9d3952a45},
	{.l = 0x3fc689f26c6b01d0},
	{.l = 0x3fbfeffbfdfebf1f}
};

static const DL
Twopm28 =
{.l = 0x3e30000000000000};

double asin_gen(double x) {
	double result;
	double temp;
	double delta;
	double zsq;
	int order;
	int m = 1 << M;
	int step = 1 << (7 - M);

	temp = x * (double)m;
	order = temp;
	order = order * step;
	//temp = x * (double)order;
	//temp = (double)order / m;
	//delta = x * sqrt(1 - temp * temp) - temp * sqrt(1 - x * x);
	delta = x * ck[order].d - sk[order].d * sqrt(1 - x * x);
	//delta = x * sqrt(1 - temp + (1 - temp) * temp) - temp * sqrt(1.0 - x + (1.0 - x) * x);
	// if (fabs(delta) < Twopm28.d){
		// delta = 0.0;
	// }
	x = delta;
	zsq = x * x;
	//result = C[0].d + x * (C[1].d + x * (C[2].d + x * (C[3].d + x * (C[4].d + x * (C[5].d +x * (C[6].d + x * (C[7].d + x * (C[8].d + x * (C[9].d)))))))));
	// result = x * C[1].d + x * zsq * (C[3].d + zsq * (C[5].d + zsq * (C[7].d + zsq * (C[9].d))));
	result = x * C[1].d + x * zsq * (C[3].d + zsq * (C[5].d + zsq * (C[7].d)));
	//result = x * C[1].d + x * zsq * (C[3].d + zsq * (C[5].d + zsq * (C[7].d + zsq * (C[9].d + zsq * C[11].d))));

	//result = ((((((P[7].d*zsq + P[6].d)*zsq + P[5].d)*zsq + P[4].d)*zsq + P[3].d)*zsq + P[2].d)*zsq + P[1].d)*(zsq*x) + x;
		
	result = result + asin_tab[order].d;
	return result;
}

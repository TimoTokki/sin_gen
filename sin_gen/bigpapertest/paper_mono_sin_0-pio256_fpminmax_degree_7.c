#include <stdio.h>
#include "myhead.h"
#define NUM 8
#define TABLE_NUM 128
#define M 7
static const DL
C_sin[NUM] = {
	{.l = 0x388f31424811bfa6},
	{.l = 0x3ff0000000000000},
	{.l = 0xbbc14b45eeb5d319},
	{.l = 0xbfc5555555555555},
	{.l = 0xbcf23be22b6678f5},
	{.l = 0x3f81111111184b69},
	{.l = 0xbdd6768e3f97b2c0},
	{.l = 0xbf2a0182aa4a0d41},
};
static const DL
C_cos[NUM] = {
	{.l = 0x3ff0000000000000},
	{.l = 0xbb9b6208d0f155b9},
	{.l = 0xbfe0000000000000},
	{.l = 0x3cd7b8bbb4f5e7e7},
	{.l = 0x3fa555555553b54f},
	{.l = 0x3de77523b8af586e},
	{.l = 0xbf56c18128ee3af1},
	{.l = 0x3eb2a98568bb4d24},
};

static const double
xx[TABLE_NUM] = {
	0.0000000000000000000e+00,
        1.2271846303085129359e-02,
        2.4543692606170258719e-02,
        3.6815538909255388078e-02,
        4.9087385212340517437e-02,
        6.1359231515425646797e-02,
        7.3631077818510776156e-02,
        8.5902924121595905516e-02,
        9.8174770424681034875e-02,
        1.1044661672776616423e-01,
        1.2271846303085129359e-01,
        1.3499030933393643683e-01,
        1.4726215563702155231e-01,
        1.5953400194010669555e-01,
        1.7180584824319181103e-01,
        1.8407769454627695427e-01,
        1.9634954084936206975e-01,
        2.0862138715244721299e-01,
        2.2089323345553232847e-01,
        2.3316507975861747171e-01,
        2.4543692606170258719e-01,
        2.5770877236478773042e-01,
        2.6998061866787287366e-01,
        2.8225246497095796139e-01,
        2.9452431127404310462e-01,
        3.0679615757712824786e-01,
        3.1906800388021339110e-01,
        3.3133985018329847883e-01,
        3.4361169648638362206e-01,
        3.5588354278946876530e-01,
        3.6815538909255390854e-01,
        3.8042723539563905177e-01,
        3.9269908169872413950e-01,
        4.0497092800180928274e-01,
        4.1724277430489442597e-01,
        4.2951462060797956921e-01,
        4.4178646691106465694e-01,
        4.5405831321414980017e-01,
        4.6633015951723494341e-01,
        4.7860200582032008665e-01,
        4.9087385212340517437e-01,
        5.0314569842649037312e-01,
        5.1541754472957546085e-01,
        5.2768939103266054857e-01,
        5.3996123733574574732e-01,
        5.5223308363883083505e-01,
        5.6450492994191592278e-01,
        5.7677677624500112152e-01,
        5.8904862254808620925e-01,
        6.0132046885117140800e-01,
        6.1359231515425649572e-01,
        6.2586416145734158345e-01,
        6.3813600776042678220e-01,
        6.5040785406351186992e-01,
        6.6267970036659695765e-01,
        6.7495154666968215640e-01,
        6.8722339297276724412e-01,
        6.9949523927585244287e-01,
        7.1176708557893753060e-01,
        7.2403893188202261832e-01,
        7.3631077818510781707e-01,
        7.4858262448819290480e-01,
        7.6085447079127810355e-01,
        7.7312631709436319127e-01,
        7.8539816339744827900e-01,
        7.9767000970053347775e-01,
        8.0994185600361856547e-01,
        8.2221370230670365320e-01,
        8.3448554860978885195e-01,
        8.4675739491287393967e-01,
        8.5902924121595913842e-01,
        8.7130108751904422615e-01,
        8.8357293382212931387e-01,
        8.9584478012521451262e-01,
	9.0811662642829960035e-01,
        9.2038847273138468807e-01,
        9.3266031903446988682e-01,
        9.4493216533755497455e-01,
        9.5720401164064017330e-01,
        9.6947585794372526102e-01,
        9.8174770424681034875e-01,
        9.9401955054989554750e-01,
        1.0062913968529807462e+00,
        1.0185632431560658340e+00,
        1.0308350894591509217e+00,
        1.0431069357622360094e+00,
        1.0553787820653210971e+00,
        1.0676506283684061849e+00,
        1.0799224746714914946e+00,
        1.0921943209745765824e+00,
        1.1044661672776616701e+00,
        1.1167380135807467578e+00,
        1.1290098598838318456e+00,
        1.1412817061869171553e+00,
        1.1535535524900022430e+00,
        1.1658253987930873308e+00,
        1.1780972450961724185e+00,
        1.1903690913992575062e+00,
        1.2026409377023428160e+00,
        1.2149127840054279037e+00,
        1.2271846303085129914e+00,
        1.2394564766115980792e+00,
        1.2517283229146831669e+00,
        1.2640001692177684767e+00,
        1.2762720155208535644e+00,
        1.2885438618239386521e+00,
        1.3008157081270237398e+00,
        1.3130875544301088276e+00,
        1.3253594007331939153e+00,
        1.3376312470362792251e+00,
        1.3499030933393643128e+00,
        1.3621749396424494005e+00,
        1.3744467859455344882e+00,
        1.3867186322486195760e+00,
        1.3989904785517048857e+00,
        1.4112623248547899735e+00,
        1.4235341711578750612e+00,
        1.4358060174609601489e+00,
        1.4480778637640452366e+00,
        1.4603497100671305464e+00,
        1.4726215563702156341e+00,
        1.4848934026733007219e+00,
        1.4971652489763858096e+00,
        1.5094370952794708973e+00,
        1.5217089415825562071e+00,
        1.5339807878856412948e+00,
        1.5462526341887263825e+00,
        1.5585244804918114703e+00,
};
static const double
sin_tab[TABLE_NUM] = {
	0.0000000000000000000e+00,
        1.2271538285719925387e-02,
        2.4541228522912288124e-02,
        3.6807222941358831714e-02,
        4.9067674327418014935e-02,
        6.1320736302208578294e-02,
        7.3564563599667426308e-02,
        8.5797312344439893850e-02,
        9.8017140329560603629e-02,
        1.1022220729388305938e-01,
        1.2241067519921619566e-01,
        1.3458070850712619548e-01,
        1.4673047445536174793e-01,
        1.5885814333386144570e-01,
        1.7096188876030121717e-01,
        1.8303988795514095078e-01,
        1.9509032201612827584e-01,
        2.0711137619221856032e-01,
        2.1910124015686979759e-01,
        2.3105810828067110951e-01,
        2.4298017990326389870e-01,
        2.5486565960451457169e-01,
        2.6671275747489836538e-01,
        2.7851968938505311524e-01,
        2.9028467725446238656e-01,
        3.0200594931922808417e-01,
        3.1368174039889146210e-01,
        3.2531029216226292622e-01,
        3.3688985339222005111e-01,
        3.4841868024943456472e-01,
        3.5989503653498816638e-01,
        3.7131719395183754306e-01,
        3.8268343236508978178e-01,
        3.9399204006104809883e-01,
        4.0524131400498986100e-01,
        4.1642956009763720804e-01,
        4.2755509343028208491e-01,
        4.3861623853852765853e-01,
        4.4961132965460659516e-01,
        4.6053871095824000514e-01,
        4.7139673682599764204e-01,
        4.8218377207912277438e-01,
        4.9289819222978403790e-01,
        5.0353838372571757542e-01,
        5.1410274419322177231e-01,
        5.2458968267846894928e-01,
        5.3499761988709726435e-01,
        5.4532498842204646383e-01,
        5.5557023301960217765e-01,
        5.6573181078361323149e-01,
        5.7580819141784533866e-01,
        5.8579785745643886408e-01,
        5.9569930449243335691e-01,
        6.0551104140432554512e-01,
        6.1523159058062681925e-01,
        6.2485948814238634341e-01,
        6.3439328416364548779e-01,
        6.4383154288979149715e-01,
        6.5317284295377675551e-01,
        6.6241577759017178373e-01,
        6.7155895484701844111e-01,
        6.8060099779545302212e-01,
        6.8954054473706694051e-01,
        6.9837624940897280457e-01,
        7.0710678118654757274e-01,
        7.1573082528381870571e-01,
        7.2424708295146689174e-01,
        7.3265427167241281570e-01,
        7.4095112535495910588e-01,
        7.4913639452345937020e-01,
        7.5720884650648456748e-01,
        7.6516726562245895860e-01,
        7.7301045336273699338e-01,
        7.8073722857209448822e-01,
        7.8834642762660622761e-01,
        7.9583690460888356633e-01,
        8.0320753148064494287e-01,
        8.1045719825259476821e-01,
        8.1758481315158371139e-01,
        8.2458930278502529099e-01,
        8.3146961230254523567e-01,
        8.3822470555483807875e-01,
        8.4485356524970711689e-01,
        8.5135519310526519554e-01,
        8.5772861000027211809e-01,
        8.6397285612158669643e-01,
        8.7008699110871146054e-01,
        8.7607009419540660122e-01,
        8.8192126434835504956e-01,
        8.8763962040285393496e-01,
        8.9322430119551532446e-01,
        8.9867446569395381673e-01,
        9.0398929312344333820e-01,
        9.0916798309052238025e-01,
        9.1420975570353069095e-01,
        9.1911385169005777040e-01,
        9.2387953251128673848e-01,
        9.2850608047321558924e-01,
        9.3299279883473884567e-01,
        9.3733901191257495977e-01,
        9.4154406518302080631e-01,
        9.4560732538052127971e-01,
        9.4952818059303667475e-01,
        9.5330604035419386211e-01,
        9.5694033573220882438e-01,
        9.6043051941556578655e-01,
        9.6377606579543984022e-01,
        9.6697647104485207059e-01,
        9.7003125319454397424e-01,
        9.7293995220556017678e-01,
        9.7570213003852857003e-01,
        9.7831737071962765473e-01,
        9.8078528040323043058e-01,
        9.8310548743121628501e-01,
        9.8527764238894122162e-01,
        9.8730141815785843473e-01,
        9.8917650996478101444e-01,
        9.9090263542778000971e-01,
        9.9247953459870996706e-01,
        9.9390697000235606051e-01,
        9.9518472667219692873e-01,
        9.9631261218277800129e-01,
        9.9729045667869020697e-01,
        9.9811811290014917919e-01,
        9.9879545620517240501e-01,
        9.9932238458834954375e-01,
        9.9969881869620424997e-01,
        9.9992470183914450299e-01,
};
 
static const double
cos_tab[TABLE_NUM] = {
	1.0000000000000000000e+00,
        9.9992470183914450299e-01,
        9.9969881869620424997e-01,
        9.9932238458834954375e-01,
        9.9879545620517240501e-01,
        9.9811811290014917919e-01,
        9.9729045667869020697e-01,
        9.9631261218277800129e-01,
        9.9518472667219692873e-01,
        9.9390697000235606051e-01,
        9.9247953459870996706e-01,
        9.9090263542778000971e-01,
        9.8917650996478101444e-01,
        9.8730141815785843473e-01,
        9.8527764238894122162e-01,
        9.8310548743121628501e-01,
        9.8078528040323043058e-01,
        9.7831737071962765473e-01,
        9.7570213003852857003e-01,
        9.7293995220556017678e-01,
        9.7003125319454397424e-01,
        9.6697647104485207059e-01,
        9.6377606579543984022e-01,
        9.6043051941556578655e-01,
        9.5694033573220882438e-01,
        9.5330604035419386211e-01,
        9.4952818059303667475e-01,
        9.4560732538052127971e-01,
        9.4154406518302080631e-01,
        9.3733901191257495977e-01,
        9.3299279883473884567e-01,
        9.2850608047321558924e-01,
        9.2387953251128673848e-01,
        9.1911385169005777040e-01,
        9.1420975570353069095e-01,
        9.0916798309052238025e-01,
        9.0398929312344333820e-01,
        8.9867446569395381673e-01,
        8.9322430119551532446e-01,
        8.8763962040285393496e-01,
        8.8192126434835504956e-01,
        8.7607009419540660122e-01,
        8.7008699110871146054e-01,
        8.6397285612158669643e-01,
        8.5772861000027211809e-01,
        8.5135519310526519554e-01,
        8.4485356524970711689e-01,
        8.3822470555483807875e-01,
        8.3146961230254523567e-01,
        8.2458930278502529099e-01,
        8.1758481315158371139e-01,
        8.1045719825259476821e-01,
        8.0320753148064494287e-01,
        7.9583690460888356633e-01,
        7.8834642762660622761e-01,
        7.8073722857209448822e-01,
        7.7301045336273699338e-01,
        7.6516726562245895860e-01,
        7.5720884650648456748e-01,
        7.4913639452345937020e-01,
        7.4095112535495910588e-01,
        7.3265427167241281570e-01,
        7.2424708295146689174e-01,
        7.1573082528381870571e-01,
        7.0710678118654757274e-01,
        6.9837624940897280457e-01,
        6.8954054473706694051e-01,
        6.8060099779545302212e-01,
        6.7155895484701844111e-01,
        6.6241577759017178373e-01,
        6.5317284295377675551e-01,
        6.4383154288979149715e-01,
        6.3439328416364548779e-01,
        6.2485948814238634341e-01,
        6.1523159058062681925e-01,
        6.0551104140432554512e-01,
        5.9569930449243335691e-01,
        5.8579785745643886408e-01,
        5.7580819141784533866e-01,
        5.6573181078361323149e-01,
        5.5557023301960217765e-01,
        5.4532498842204646383e-01,
        5.3499761988709726435e-01,
        5.2458968267846894928e-01,
        5.1410274419322177231e-01,
        5.0353838372571757542e-01,
        4.9289819222978403790e-01,
        4.8218377207912277438e-01,
        4.7139673682599764204e-01,
        4.6053871095824000514e-01,
        4.4961132965460659516e-01,
        4.3861623853852765853e-01,
        4.2755509343028208491e-01,
        4.1642956009763720804e-01,
        4.0524131400498986100e-01,
        3.9399204006104809883e-01,
        3.8268343236508978178e-01,
        3.7131719395183754306e-01,
        3.5989503653498816638e-01,
        3.4841868024943456472e-01,
        3.3688985339222005111e-01,
        3.2531029216226292622e-01,
        3.1368174039889146210e-01,
        3.0200594931922808417e-01,
        2.9028467725446238656e-01,
        2.7851968938505311524e-01,
        2.6671275747489836538e-01,
        2.5486565960451457169e-01,
        2.4298017990326389870e-01,
        2.3105810828067110951e-01,
        2.1910124015686979759e-01,
        2.0711137619221856032e-01,
        1.9509032201612827584e-01,
        1.8303988795514095078e-01,
        1.7096188876030121717e-01,
        1.5885814333386144570e-01,
        1.4673047445536174793e-01,
        1.3458070850712619548e-01,
        1.2241067519921619566e-01,
        1.1022220729388305938e-01,
        9.8017140329560603629e-02,
        8.5797312344439893850e-02,
        7.3564563599667426308e-02,
        6.1320736302208578294e-02,
        4.9067674327418014935e-02,
        3.6807222941358831714e-02,
        2.4541228522912288124e-02,
        1.2271538285719925387e-02,
};
 
static const double
pio256 = 1.2271846303085129359e-02;

double sin_gen(double x) {
	// init
	double result;
	double result_sin, result_cos;
	double temp;
	int order;
	int m = (1<<(7-M));

	// gui  yue
	temp = x / (pio256 * m);
	order = (int)temp;
	//x = x - order * (pio256 * m);
	x = x - xx[order*m];
	
	// bi jin
	result_sin = x * (C_sin[1].d + x * (C_sin[2].d + x * (C_sin[3].d + x * (C_sin[4].d + x * (C_sin[5].d + x * (C_sin[6].d + x * (C_sin[7].d)))))));
	result_cos = x * (C_cos[1].d + x * (C_cos[2].d + x * (C_cos[3].d + x * (C_cos[4].d + x * (C_cos[5].d + x * (C_cos[6].d + x * (C_cos[7].d)))))));
	
	//result_sin = C_sin[0].d + x * (C_sin[1].d + x * (C_sin[2].d + x * (C_sin[3].d + x * (C_sin[4].d + x * (C_sin[5].d + x * (C_sin[6].d + x * (C_sin[7].d)))))));
	//result_cos = C_cos[0].d + x * (C_cos[1].d + x * (C_cos[2].d + x * (C_cos[3].d + x * (C_cos[4].d + x * (C_cos[5].d + x * (C_cos[6].d + x * (C_cos[7].d)))))));
	// chong jian
	order = order * m;	
	result = result_sin * cos_tab[order] + result_cos * sin_tab[order];
	result += C_sin[0].d * cos_tab[order] + C_cos[0].d * sin_tab[order];

	return result;
}

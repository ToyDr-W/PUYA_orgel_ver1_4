//#define	SHDBS		//ﾃﾞﾊﾞｸﾞ信号を出力するときに宣言する
#define	SHDBG		//ﾃﾞﾊﾞｸﾞ情報を出力するときに宣言する
//#define	SHBPS	115200	//ﾃﾞﾊﾞｸﾞ情報のﾎﾞｰﾚｰﾄを宣言する(ﾃﾞﾌｫﾙﾄ値は38400bps)

//#define	I2C_SOFT	//I2Cをｿﾌﾄ実装するときに宣言する
//#define	SPI_SOFT	//SPIをｿﾌﾄ実装するときに宣言する
//#define		SHSPI2		//2線SPIのときに宣言する
//#define	SHSPI3		//3線SPIのときに宣言する
//#define	SLEEP_EN	//Sleep機能を実装するときに宣言する
//#define	KYOKU_AUTO	//ｵﾙｺﾞｰﾙ演奏を自動開始するときに宣言する
//#define	ONSEIN_AUTO	//音声N(ch0)再生を自動開始するときに宣言する
//#define	ONSEII_AUTO	//音声I再生を自動開始するときに宣言する
//#define	ONSEIC_AUTO	//音声C再生を自動開始するときに宣言する
//#define	ONSEIS_AUTO	//音声S(ch0)再生を自動開始するときに宣言する
//#define	RAND_CHSEL	0x00000010	//ﾗﾝﾀﾞﾏｲｽﾞの種にするCHSEL(PA4:ADC_IN4)
//#define	KYOKU_RAND	//曲番号をﾗﾝﾀﾞﾏｲｽﾞするときに宣言する
//#define	ONSEIN_RAND	//音声N番号をﾗﾝﾀﾞﾏｲｽﾞするときに宣言する
//#define	ONSEII_RAND	//音声I番号をﾗﾝﾀﾞﾏｲｽﾞするときに宣言する
//#define	ONSEIC_RAND	//音声C番号をﾗﾝﾀﾞﾏｲｽﾞするときに宣言する
//#define	ONSEIS_RAND	//音声S番号をﾗﾝﾀﾞﾏｲｽﾞするときに宣言する
//#define	SW_EN		//SWを実装するときに宣言する
//#define	SW_PLNG		//SWをｲﾍﾞﾝﾄではなく､ﾎﾟｰﾘﾝｸﾞするときに宣言する
//#define	CdS_EN		//CdSを実装するときに宣言する
//#define	CVD_EN		//CVDを実装するときに宣言する

//ｵﾙｺﾞｰﾙ箱への応用では以下を宣言しておくこと
//#define	CdS_FUTA	//蓋を開ける(明)とｵﾝ判定する
//#define	CdS_THR	100	//判定閾値を固定の宣言値にする

#define		VOICEN_IMA	//音声NがIMA_ADPCMｴﾝｺｰﾄﾞのときに宣言する
#define		VOICEI_IMA	//音声IがIMA_ADPCMｴﾝｺｰﾄﾞのときに宣言する
#define		VOICES_IMA	//音声SがIMA_ADPCMｴﾝｺｰﾄﾞのときに宣言する

//#define	ISP_SPIFLASH_EN	//ISP環境でSPIﾌﾗｯｼｭを書替えるときに宣言する
				//(自動的に､ﾃﾞﾊﾞｸﾞ情報のUART内蔵ﾓｼﾞｭｰﾙを230400bpsで使用する)
				//(通常のｱﾌﾟﾘは実行されない)


/*
PUYA32電子ｵﾙｺﾞｰﾙ演奏+音声再生ver1_4
これは根のｿｰｽｺｰﾄﾞ

・ISP形態でSPIﾌﾗｯｼｭを書替える機能(ISP_SPIFLASH)に対応している｡

・ﾀｰｹﾞｯﾄはPY32F002A_8ﾋﾟﾝ(内部48MHzｸﾛｯｸ)

・UARTから受信したKB演奏ﾃﾞｰﾀに従って､orgelｴﾝｼﾞﾝへ音符ｺｰﾄﾞを送って演奏させる｡

・白鍵と黒鍵をPCのｷｰﾎﾞｰﾄﾞ上に配置して演奏する｡

・UARTから受信したｵﾙｺﾞｰﾙ演奏､或いはSPI音声再生の指示ﾃﾞｰﾀに従って､それらを起動する｡

・その他の音声再生機能は､このｻﾝﾌﾟﾙｱﾌﾟﾘでは実装していない


//==============================================
//I2Cﾌﾗｯｼｭﾒﾓﾘのﾋﾟﾝ接
//==============================================
1:A0(Vssに繋ぐ)
2:A1(Vssに繋ぐ)
3:A2(Vssに繋ぐ)
4:Vss
5:SDA(1.5kで外部ﾌﾟﾙｱｯﾌﾟ)
6:SCL(1.5kで外部ﾌﾟﾙｱｯﾌﾟ)
7:WP(Vccに繋ぐ)
8:Vcc


//==============================================
//SDCのﾋﾟﾝ接(SPIﾓｰﾄﾞ)
//==============================================
9:空き(不使用)
1:CS(2線SPIでは10k*220pの時定数回路を介してCLKに繋ぐ)
2:DI
3:Vss1
4:Vdd
5:CLK
6:Vss2
7:DO(2線SPI･3線SPIでは1.5kを介してDIに繋ぐ)
8:IRQ(不使用)


//==============================================
//SPIﾌﾗｯｼｭﾒﾓﾘのﾋﾟﾝ接
//==============================================
W25Qのﾋﾟﾝ接(標準SPIﾓｰﾄﾞ)
1:CS(2線SPIでは10k*220pの時定数回路を介してCLKに繋ぐ)
2:DO(2線SPI･3線SPIではDIに繋ぐ)
3:WP(GNDに接続)
4:GND
5:DI
6:CLK
7:HOLD(Vccに接続)
8:Vcc


//==============================================
//PY32のﾋﾟﾝ接
//I2Cは使わない
//SPIは2線SPIで接続する
//UART入力はKB操作情報受信で使用する
//ISPではUART入力と出力を使用する
//==============================================
PY32F002A(8ﾋﾟﾝ)のﾎﾟｰﾄの割当て
1:Vcc
2:(PA4)
2:(PA10)/(USART1_RX)UART入力
3:(PA3)SW0､MOSI(M25QのDI･SDCのDIに繋ぐ)/(ADC_IN3)CdS､CVD0
4:(PA14-SWC)/(USART1_TX)UART出力
4:(PB3)(TIM1_CH2)正相出力
5:(PA13-SWD)SCK(M25QのCLK･SDCのCLKに繋ぐ)
6:(PA2)ﾃﾞﾊﾞｸﾞ情報出力
6:(PF2-NRST)=====>PF2はNRST機能を無効にしてGPIO機能に設定しておくこと
7:(PA1)BOOT0代替/(TIM1_CH4)ﾌﾞﾘｯｼﾞ･ﾌﾞﾚｰｷ逆相出力
8:Vss
*/


//==============================================
//ﾍｯﾀﾞﾌｧｲﾙの呼込み
//==============================================
#include "py32f0xx.h"				//ｼｽﾃﾑのﾍｯﾀﾞﾌｧｲﾙ
#include "orgel_cnf.h"				//構成情報
#include "../orgel.h"				//ｱﾌﾟﾘのﾍｯﾀﾞﾌｧｲﾙ


//==============================================
//構成情報(ｱﾌﾟﾘｹｰｼｮﾝとﾀｰｹﾞｯﾄﾃﾞﾊﾞｲｽに関わるもの)
//==============================================
//UARTのﾎﾟｰﾄ定義
#define	UART_GPIO	GPIOA			//UART出力のﾎﾟｰﾄ
#define	UART_BIT	14			//UART出力のﾋﾞｯﾄ
#define	UART_AF		1			//UART出力のUART_TX交代機能番号
#define	UART_IN_GPIO	GPIOA			//UART入力のﾎﾟｰﾄ
#define	UART_IN_BIT	10			//UART入力のﾋﾞｯﾄ
#define	UART_IN_AF	1			//UART入力のUART_RX交代機能番号

//ﾃﾞﾊﾞｸﾞ情報のﾎﾟｰﾄ定義
#define	SHDBG_SOFT				//ﾃﾞﾊﾞｸﾞ情報のUARTをｿﾌﾄ実装する
#define	DBG_GPIO	GPIOA			//ﾃﾞﾊﾞｸﾞ情報のﾎﾟｰﾄ
#define	DBG_BIT		2			//ﾃﾞﾊﾞｸﾞ情報のﾋﾞｯﾄ

//PWMのﾎﾟｰﾄ定義
#define	PWM_F_GPIO	GPIOB			//PWM正相のﾎﾟｰﾄ
#define	PWM_F_BIT	3			//PWM正相のﾋﾞｯﾄ
#define	PWM_F_AF	1			//PWM正相の交代機能番号
#define	PWM_R_GPIO	GPIOA			//PWM逆相のﾎﾟｰﾄ
#define	PWM_R_BIT	1			//PWM逆相のﾋﾞｯﾄ
#define	PWM_R_AF	13			//PWM逆相の交代機能番号
#define	PWM_C_GPIO	GPIOA			//PWM相補のﾎﾟｰﾄ
#define	PWM_C_BIT	1			//PWM相補のﾋﾞｯﾄ
#define	PWM_C_AF	14			//PWM相補の交代機能番号

//SPIのﾎﾟｰﾄ定義
#define	SPI_SOFT				//SPIをｿﾌﾄ実装する
#define	SHSPI2					//2線SPIで繋ぐ
#define	SPI_SS_TIME	10			//SSﾈｹﾞｰﾄ待ち時間[us]
#define SPI_SCK_GPIO	GPIOA			//SCKのﾎﾟｰﾄ
#define SPI_SCK_BIT	13			//SCKのﾋﾞｯﾄ
#define SPI_MOSI_GPIO	GPIOA			//MOSIのﾎﾟｰﾄ
#define SPI_MOSI_BIT	3			//MOSIのﾋﾞｯﾄ
#define SPI_SS_GPIO	SPI_SCK_GPIO		//SSのﾎﾟｰﾄ
#define SPI_SS_BIT	SPI_SCK_BIT		//SSのﾋﾞｯﾄ
#define SPI_MISO_GPIO	SPI_MOSI_GPIO		//MISOのﾎﾟｰﾄ
#define SPI_MISO_BIT	SPI_MOSI_BIT		//MISOのﾋﾞｯﾄ

//SPIのﾌﾟﾙｱｯﾌﾟ/ﾀﾞｳﾝ定義
#define	SPI_SCK_PU				//SPI_SCKをﾌﾟﾙｱｯﾌﾟする
//#define	SPI_SCK_PD			//SPI_SCKをﾌﾟﾙﾀﾞｳﾝする
#define	SPI_MOSI_PU				//SPI_MOSIをﾌﾟﾙｱｯﾌﾟする
//#define	SPI_MOSI_PD			//SPI_MOSIをﾌﾟﾙﾀﾞｳﾝする
#define	SPI_MISO_PU				//SPI_MISOをﾌﾟﾙｱｯﾌﾟする
//#define	SPI_MISO_PD			//SPI_MISOをﾌﾟﾙﾀﾞｳﾝする


#if	KB_N>0
//==============================================
//KB演奏で使う音源波形とｴﾝﾍﾞﾛｰﾌﾟ波形のextern
//song_idx.sで実体をincludeしておくこと
//==============================================
extern const struct ENVE_HDR enve_EXP;
extern const struct ENVE_HDR enve_RSN;
extern const struct ENVE_HDR enve_VIB;
extern const struct ENVE_HDR enve_TREMOLO;
extern const struct ENVE_HDR enve_ELEGANTE;
extern const struct WAVE_HDR wave_SIN14;
extern const struct WAVE_HDR wave_SHEPARD;
extern const struct WAVE_HDR wave_RING4;
#endif


#if	PART_N+KB_N>0
//==============================================
//ｿﾝｸﾞﾃﾞｰﾀのｲﾝﾃﾞｯｸｽ
//==============================================
extern const struct SONG_IDX SONG_IDX;		//曲ｲﾝﾃﾞｯｸｽ実体
#endif


#if	VOICE_N>0
//==============================================
//音声ﾃﾞｰﾀ
//==============================================
#ifdef VOICEN_IMA			//IMA-ADPCMのとき
#include	"../voice_WAN_IMA.c"
#include	"../voice_DAME_IMA.c"
#include	"../voice_CHIKO_IMA.c"

#else					//8ﾋﾞｯﾄPCMのとき
#include	"../voice_WAN.c"
#include	"../voice_DAME.c"
#include	"../voice_CHIKO.c"

#endif
//==============================================
//音声ﾃﾞｰﾀ(ﾌﾟﾛｸﾞﾗﾑﾌﾗｯｼｭ)のｲﾝﾃﾞｯｸｽ
//==============================================
static const struct VOICEN_HDR voiceN_idx[]=
{
	von_mac(voice_WAN,sizeof(voice_WAN),8000)
	von_mac(voice_DAME,sizeof(voice_DAME),8000)
	von_mac(voice_CHIKO,sizeof(voice_CHIKO),8000)
};
#define VOICEN_SU	(sizeof(voiceN_idx)/sizeof(voiceN_idx[0]))
#endif


#if	VOICE_I>0
//==============================================
//音声ﾃﾞｰﾀ(I2Cﾌﾗｯｼｭ)のｲﾝﾃﾞｯｸｽ
//==============================================
static const struct VOICEI_HDR voiceI_idx[]=
{

#ifdef VOICEI_IMA			//IMA-ADPCMのとき
	//voice_DAMEのW25Q_IMAを使う
	voi_mac(0x000000,0x0007df,8000,0xa0)	//1:WAN_1ch16bit16ksps.wav
	voi_mac(0x0007df,0x000797,8000,0xa0)	//2:DAME_1ch16bit16ksps.wav
	voi_mac(0x000f76,0x001d0b,8000,0xa0)	//3:CHIKO_1ch16bit16ksps.wav

#else					//8ﾋﾞｯﾄPCMのとき
	//voice_DAMEのW25Qを使う
	voi_mac(0x000000,0x000fbe,8000,0xa0)	//1:WAN_1ch16bit16ksps.wav
	voi_mac(0x000fbe,0x000f2f,8000,0xa0)	//2:DAME_1ch16bit16ksps.wav
	voi_mac(0x001eed,0x003a17,8000,0xa0)	//3:CHIKO_1ch16bit16ksps.wav

/*
	//voice_Mirrorna\W25Q16.hexを使う
	voi_mac(0x000000,0x002401,8000,0xa0)	//1:sharin.wav
	voi_mac(0x002401,0x004575,8000,0xa0)	//2:kirakiraomeme.wav
	voi_mac(0x006976,0x001956,8000,0xa0)	//3:aidorumitai.wav
	voi_mac(0x0082cc,0x002b18,8000,0xa0)	//4:kyounooshare.wav
	voi_mac(0x00ade4,0x001d61,8000,0xa0)	//5:egaogasuteki.wav
	voi_mac(0x00cb45,0x0033a5,8000,0xa0)	//6:kirarin.wav
*/
#endif

};
#define VOICEI_SU	(sizeof(voiceI_idx)/sizeof(voiceI_idx[0]))
#endif


#if	VOICE_C>0
//==============================================
//音声ﾃﾞｰﾀ(SDｶｰﾄﾞ)のｲﾝﾃﾞｯｸｽ
//==============================================
static const struct VOICEC_HDR voiceC_idx[]=
{

	//｢ｱﾝﾊﾟﾝﾏﾝｼｮｰ｣の音声ﾃﾞｰﾀ(SDのANPANMAN.wav)を使う
	voc_mac(0x00029e,0x00e367,8000)		//anpan
//	voc_mac(0x002000,0x000080,8000)		//anpanの一部(ﾃｽﾄ用)
//	voc_mac(0x004000,0x000080,8000)		//anpanの一部(ﾃｽﾄ用)

};
#define VOICEC_SU	(sizeof(voiceC_idx)/sizeof(voiceC_idx[0]))
#endif


#if	VOICE_S>0
//==============================================
//音声ﾃﾞｰﾀ(SPIﾌﾗｯｼｭ)のｲﾝﾃﾞｯｸｽ
//==============================================
static const struct VOICES_HDR voiceS_idx[]=
{

#ifdef VOICES_IMA			//IMA-ADPCMのとき
	//｢ｷﾃｨﾐﾗｰﾅ｣の音声ﾃﾞｰﾀ(voice_Mirrorna\W25Q_IMA.hex)を使う
	vos_mac(0x000000,0x001200,8000)	//1:sharin.wav
	vos_mac(0x001200,0x0022ba,8000)	//2:kirakiraomeme.wav
	vos_mac(0x0034ba,0x000cab,8000)	//3:aidorumitai.wav
	vos_mac(0x004165,0x00158c,8000)	//4:kyounooshare.wav
	vos_mac(0x0056f1,0x000eb0,8000)	//5:egaogasuteki.wav
	vos_mac(0x0065a1,0x0019d2,8000)	//6:kirarin.wav

#else
	//｢ｷﾃｨﾐﾗｰﾅ｣の音声ﾃﾞｰﾀ(voice_Mirrorna\W25Q.hex)を使う
	vos_mac(0x000000,0x002401,8000)		//sharin.wav
	vos_mac(0x002401,0x004575,8000)		//kirakiraomeme.wav
	vos_mac(0x006976,0x001956,8000)		//aidorumitai.wav
	vos_mac(0x0082cc,0x002b18,8000)		//kyounooshare.wav
	vos_mac(0x00ade4,0x001d61,8000)		//egaogasuteki.wav
	vos_mac(0x00cb45,0x0033a5,8000)		//kirarin.wav

/*
	//voice_ToyStory\W25Q16_12ksps8bit.hexを使う
	vos_mac(0x000000,0x0afc83,12000)	//ToyStory_12ksps8bit
*/

#endif
};
#define VOICES_SU	(sizeof(voiceS_idx)/sizeof(voiceS_idx[0]))
#endif


//==============================================
//共通ｺｰﾄﾞの呼込み
//==============================================
#ifdef ISP_SPIFLASH_EN			//ISP環境でSPIﾌﾗｯｼｭを書替えるとき
#define	UARTBPS	230400				//UARTは230400bps
#define	UART_TX					//UART送信を使う
#define	UART_RX					//UART受信を使う
#include "../dev_F002A_8.c"			//F002A_8ﾋﾟﾝﾃﾞﾊﾞｲｽｺｰﾄﾞ
#include "../apl_ISP_SPIFLASH.c"		//ISP実行ｱﾌﾟﾘｹｰｼｮﾝ
#else					//KB演奏のとき
#define	UARTBPS	38400				//UARTは38400bps
#define	UART_RX					//UART受信を使う
#include "../dev_F002A_8.c"			//F002A_8ﾋﾟﾝﾃﾞﾊﾞｲｽｺｰﾄﾞ
#include "../apl_KB.c"				//KB操作ｱﾌﾟﾘｹｰｼｮﾝ
#endif

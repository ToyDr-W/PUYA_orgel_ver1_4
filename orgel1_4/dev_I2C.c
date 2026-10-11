#ifdef I2C_SOFT				//I2Cをｿﾌﾄ実装するとき
#include "dev_I2C_SOFT.c"			//ｿﾌﾄ実装ｺｰﾄﾞを呼込む

#else					//内蔵I2Cﾓｼﾞｭｰﾙを使うとき
//==============================================
//I2Cﾌﾗｯｼｭ開始
//==============================================
static void i2c_begin(
	unsigned char s_ad,
	unsigned short r_ad)
{

	//開始
	I2C1->CR1|=I2C_CR1_PE;			//I2C有効

//DBG_C('a');
	I2C1->CR1|=I2C_CR1_START;		//ｽﾀｰﾄｺﾝﾃﾞｨｼｮﾝ
	while(!(I2C->SR1&I2C_SR1_SB)){};	//ｽﾀｰﾄｺﾝﾃﾞｨｼｮﾝを待つ
//DBG_C('b');
	I2C1->DR=s_ad;				//ｽﾚｰﾌﾞｱﾄﾞﾚｽ(W)送信
	while(!(I2C->SR1&I2C_SR1_ADDR)){};	//ｽﾚｰﾌﾞｱﾄﾞﾚｽ送信を待つ
	I2C->SR2;
	while(!(I2C->SR1&I2C_SR1_TXE)){};	//送信ﾊﾞｯﾌｧ空きを待つ
//DBG_C('c');
	I2C1->DR=r_ad>>8;			//読出しｱﾄﾞﾚｽ上位送信
	while(!(I2C->SR1&I2C_SR1_TXE)){};	//送信ﾊﾞｯﾌｧ空きを待つ
//DBG_C('d');
	I2C1->DR=r_ad&0x00ff;			//読出しｱﾄﾞﾚｽ下位送信
	while(!(I2C->SR1&I2C_SR1_TXE)){};	//送信ﾊﾞｯﾌｧ空きを待つ
//DBG_C('e');
	while(!(I2C->SR1&I2C_SR1_BTF)){};	//送信完了を待つ
//DBG_C('f');

	//読込み
	I2C1->CR1|=I2C_CR1_ACK;			//ACK有効
	I2C1->CR1|=I2C_CR1_START;		//ｽﾀｰﾄｺﾝﾃﾞｨｼｮﾝ
	while(!(I2C->SR1&I2C_SR1_SB)){};	//ｽﾀｰﾄｺﾝﾃﾞｨｼｮﾝを待つ
//DBG_C('g');
	I2C1->DR=s_ad|1;			//ｽﾚｰﾌﾞｱﾄﾞﾚｽ(R)送信
	while(!(I2C->SR1&I2C_SR1_ADDR)){};	//ｽﾚｰﾌﾞｱﾄﾞﾚｽ送信を待つ
//DBG_C('h');
	I2C->SR2;
}


//==============================================
//I2Cﾌﾗｯｼｭ読込み
//==============================================
static unsigned char i2c_read(void)
{
	unsigned char data;

	//読込み
//DBG_C('i');
	while(!(I2C->SR1&I2C_SR1_RXNE)){};	//受信を待つ
	data=I2C1->DR;
//DBG_B(data);
	return(data);
}


//==============================================
//I2Cﾌﾗｯｼｭ読込み(最後のﾃﾞｰﾀ)
//==============================================
static unsigned char i2c_read_last(void)
{
	unsigned char data;

	//読込み(最後のﾃﾞｰﾀ)
//DBG_C('j');
	while(!(I2C->SR1&I2C_SR1_RXNE)){};	//受信を待つ
	I2C1->CR1&=~I2C_CR1_ACK;		//ACK無効
	data=I2C1->DR;
//DBG_B(data);
	return(data);
}


//==============================================
//I2Cﾌﾗｯｼｭ終了
//==============================================
static void i2c_end(void)
{
	unsigned char data;

	//終了
//DBG_C('l');
	I2C1->CR1|=I2C_CR1_STOP;		//ｽﾄｯﾌﾟｺﾝﾃﾞｨｼｮﾝ
	while(I2C1->SR2&I2C_SR2_BUSY){};
	I2C1->CR1&=~I2C_CR1_PE;			//I2C無効
//DBG_C('m');
}
#endif


//==============================================
//I2初期設定
//==============================================
static void i2c_init(void)
{

//DBG_C('a');
	GPIO_H(I2C_SCL_GPIO,I2C_SCL_BIT);	//SCLをH
	GPIO_OUTOD(I2C_SCL_GPIO,I2C_SCL_BIT);	//SCLをOD出力
	GPIO_H(I2C_SDA_GPIO,I2C_SDA_BIT);	//SDAをH
	GPIO_OUTOD(I2C_SDA_GPIO,I2C_SDA_BIT);	//SDAをOD出力

//DBG_C('b');
	for(;;)					//I2Cｽﾚｰﾌﾞを同期する
	{
		wait_us(1);
		if(GPIO_R(I2C_SDA_GPIO,I2C_SDA_BIT)) break;
						//SDAがHになったら抜ける
		GPIO_H(I2C_SCL_GPIO,I2C_SCL_BIT);
						//SCLをH
		wait_us(1);
		GPIO_L(I2C_SCL_GPIO,I2C_SCL_BIT);
						//SCLをL
	}
//DBG_C('c');
	wait_us(1);
	GPIO_L(I2C_SDA_GPIO,I2C_SDA_BIT);	//SDAをL
	wait_us(1);
	GPIO_H(I2C_SCL_GPIO,I2C_SCL_BIT);	//SCLをH
	wait_us(1);
	GPIO_H(I2C_SDA_GPIO,I2C_SDA_BIT);	//SDAをH
	wait_us(1);
//DBG_C('d');
#ifndef I2C_SOFT			//内蔵I2Cﾓｼﾞｭｰﾙを使うとき
	RCC->APBENR1|=RCC_APBENR1_I2CEN;	//I2C1にｸﾛｯｸ供給
	GPIO_AF(I2C_SCL_GPIO,I2C_SCL_BIT,I2C_SCL_AF);
						//SCLを交代機能に設定
	GPIO_AF(I2C_SDA_GPIO,I2C_SDA_BIT,I2C_SDA_AF);
						//SDAを交代機能に設定
//DBG_C('e');
	I2C1->CR1=I2C_CR1_SWRST;		//I2Cｿﾌﾄﾘｾｯﾄ
	I2C1->CCR=I2C_CCR_FS|I2C_CCR_DUTY|4;	//FASTﾓｰﾄﾞ､L/H=16/9､4分周､
						//　48MHz/19/25=480kHz
//	I2C1->CCR=I2C_CCR_FS|I2C_CCR_DUTY|5;	//FASTﾓｰﾄﾞ､L/H=16/9､5分周､
						//　48MHz/19/25=384kHz
//	I2C1->CCR=I2C_CCR_FS|I2C_CCR_DUTY|19;	//FASTﾓｰﾄﾞ､L/H=16/9､19分周､
						//　48MHz/19/25=101kHz
	I2C1->CR2=48;				//ｸﾛｯｸは48MHz
	I2C->TRISE=49;				//SCLrise1000ns
	I2C1->CR1|=I2C_CR1_PE;			//I2C有効
//DBG_C('f');
#endif
}

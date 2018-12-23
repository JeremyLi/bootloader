#include "stm32f407xx.h"

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
//GPIO锟斤拷锟斤拷专锟矫宏定锟斤拷
#define GPIO_MODE_IN    	0		//锟斤拷通锟斤拷锟斤拷模式
#define GPIO_MODE_OUT		1		//锟斤拷通锟斤拷锟侥Ｊ�
#define GPIO_MODE_AF		2		//AF锟斤拷锟斤拷模式
#define GPIO_MODE_AIN		3		//模锟斤拷锟斤拷锟斤拷模式

#define GPIO_SPEED_2M		0		//GPIO锟劫讹拷2Mhz
#define GPIO_SPEED_25M		1		//GPIO锟劫讹拷25Mhz
#define GPIO_SPEED_50M		2		//GPIO锟劫讹拷50Mhz
#define GPIO_SPEED_100M		3		//GPIO锟劫讹拷100Mhz

#define GPIO_PUPD_NONE		0		//锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷
#define GPIO_PUPD_PU		1		//锟斤拷锟斤拷
#define GPIO_PUPD_PD		2		//锟斤拷锟斤拷
#define GPIO_PUPD_RES		3		//锟斤拷锟斤拷

#define GPIO_OTYPE_PP		0		//锟斤拷锟斤拷锟斤拷锟�
#define GPIO_OTYPE_OD		1		//锟斤拷漏锟斤拷锟�

//GPIO锟斤拷锟脚憋拷哦锟斤拷锟�
#define PIN0				1<<0
#define PIN1				1<<1
#define PIN2				1<<2
#define PIN3				1<<3
#define PIN4				1<<4
#define PIN5				1<<5
#define PIN6				1<<6
#define PIN7				1<<7
#define PIN8				1<<8
#define PIN9				1<<9
#define PIN10				1<<10
#define PIN11				1<<11
#define PIN12				1<<12
#define PIN13				1<<13
#define PIN14				1<<14
#define PIN15				1<<15
//////////////////////////////////////////////////////////////////////////////////

int uart_put_char(int ch)
{
	while((USART1->SR & 0X40) == 0);
	USART1->DR = (u8) ch;
	return ch;
}
//end
//////////////////////////////////////////////////////////////////

// void __attribute__ ((section(".after_vectors"),noreturn))
void __attribute__ ((section(".after_vectors")))
USART1_IRQHandler(void)
{

}

//GPIO¸´ÓÃÉèÖÃ
//GPIOx:GPIOA~GPIOI.
//BITx:0~15,´ú±íIOÒý½Å±àºÅ.
//AFx:0~15,´ú±íAF0~AF15.
//AF0~15ÉèÖÃÇé¿ö(ÕâÀï½öÊÇÁÐ³ö³£ÓÃµÄ,ÏêÏ¸µÄÇë¼û407Êý¾ÝÊÖ²á,56Ò³Table 7):
//AF0:MCO/SWD/SWCLK/RTC   AF1:TIM1/TIM2;            AF2:TIM3~5;               AF3:TIM8~11
//AF4:I2C1~I2C3;          AF5:SPI1/SPI2;            AF6:SPI3;                 AF7:USART1~3;
//AF8:USART4~6;           AF9;CAN1/CAN2/TIM12~14    AF10:USB_OTG/USB_HS       AF11:ETH
//AF12:FSMC/SDIO/OTG/HS   AF13:DCIM                 AF14:                     AF15:EVENTOUT
void GPIO_AF_Set(GPIO_TypeDef* GPIOx,u8 BITx,u8 AFx)
{
	GPIOx->AFR[BITx>>3]&=~(0X0F<<((BITx&0X07)*4));
	GPIOx->AFR[BITx>>3]|=(u32)AFx<<((BITx&0X07)*4);
}
//GPIOÍ¨ÓÃÉèÖÃ
//GPIOx:GPIOA~GPIOI.
//BITx:0X0000~0XFFFF,Î»ÉèÖÃ,Ã¿¸öÎ»´ú±íÒ»¸öIO,µÚ0Î»´ú±íPx0,µÚ1Î»´ú±íPx1,ÒÀ´ÎÀàÍÆ.±ÈÈç0X0101,´ú±íÍ¬Ê±ÉèÖÃPx0ºÍPx8.
//MODE:0~3;Ä£Ê½Ñ¡Ôñ,0,ÊäÈë(ÏµÍ³¸´Î»Ä¬ÈÏ×´Ì¬);1,ÆÕÍ¨Êä³ö;2,¸´ÓÃ¹¦ÄÜ;3,Ä£ÄâÊäÈë.
//OTYPE:0/1;Êä³öÀàÐÍÑ¡Ôñ,0,ÍÆÍìÊä³ö;1,¿ªÂ©Êä³ö.
//OSPEED:0~3;Êä³öËÙ¶ÈÉèÖÃ,0,2Mhz;1,25Mhz;2,50Mhz;3,100Mh.
//PUPD:0~3:ÉÏÏÂÀ­ÉèÖÃ,0,²»´øÉÏÏÂÀ­;1,ÉÏÀ­;2,ÏÂÀ­;3,±£Áô.
//×¢Òâ:ÔÚÊäÈëÄ£Ê½(ÆÕÍ¨ÊäÈë/Ä£ÄâÊäÈë)ÏÂ,OTYPEºÍOSPEED²ÎÊýÎÞÐ§!!
void GPIO_Set(GPIO_TypeDef* GPIOx,u32 BITx,u32 MODE,u32 OTYPE,u32 OSPEED,u32 PUPD)
{
	u32 pinpos=0,pos=0,curpin=0;
	for(pinpos=0;pinpos<16;pinpos++)
	{
		pos=1<<pinpos;	//Ò»¸ö¸öÎ»¼ì²é
		curpin=BITx&pos;//¼ì²éÒý½ÅÊÇ·ñÒªÉèÖÃ
		if(curpin==pos)	//ÐèÒªÉèÖÃ
		{
			GPIOx->MODER&=~(3<<(pinpos*2));	//ÏÈÇå³ýÔ­À´µÄÉèÖÃ
			GPIOx->MODER|=MODE<<(pinpos*2);	//ÉèÖÃÐÂµÄÄ£Ê½
			if((MODE==0X01)||(MODE==0X02))	//Èç¹ûÊÇÊä³öÄ£Ê½/¸´ÓÃ¹¦ÄÜÄ£Ê½
			{
				GPIOx->OSPEEDR&=~(3<<(pinpos*2));	//Çå³ýÔ­À´µÄÉèÖÃ
				GPIOx->OSPEEDR|=(OSPEED<<(pinpos*2));//ÉèÖÃÐÂµÄËÙ¶ÈÖµ
				GPIOx->OTYPER&=~(1<<pinpos) ;		//Çå³ýÔ­À´µÄÉèÖÃ
				GPIOx->OTYPER|=OTYPE<<pinpos;		//ÉèÖÃÐÂµÄÊä³öÄ£Ê½
			}
			GPIOx->PUPDR&=~(3<<(pinpos*2));	//ÏÈÇå³ýÔ­À´µÄÉèÖÃ
			GPIOx->PUPDR|=PUPD<<(pinpos*2);	//ÉèÖÃÐÂµÄÉÏÏÂÀ­
		}
	}
}

void __uart_init(uint32_t pclk2,uint32_t bound)
{
//	SCB->CPACR |= (0x3 << 10 * 2 | 0x3 << 11 * 2);
//	asm ("dsb;\n isb\n");
	uint32_t temp;
	uint16_t mantissa;
	uint16_t fraction;
//	temp=(float)(pclk2*1000000)/(bound*16);
//	mantissa=temp;
//	fraction=(temp-mantissa)*16;
//    mantissa<<=4;
//	mantissa+=fraction;
	mantissa = 0x02d9;
	temp = pclk2*1000000 * 10 /(bound*16);
	mantissa = temp / 10;
	fraction = (temp % 10) * 16 / 10;
	mantissa <<= 4;
	mantissa += fraction;
	RCC->AHB1ENR|=1<<0;
	RCC->APB2ENR|=1<<4;
	GPIO_Set(GPIOA,PIN9|PIN10,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_50M,GPIO_PUPD_PU);//PA9,PA10,锟斤拷锟矫癸拷锟斤拷,锟斤拷锟斤拷锟斤拷锟�
 	GPIO_AF_Set(GPIOA,9,7);	//PA9,AF7
	GPIO_AF_Set(GPIOA,10,7);//PA10,AF7

 	USART1->BRR=mantissa;
	USART1->CR1&=~(1<<15);
	USART1->CR1|=1<<3;
//#if EN_USART1_RX
//
//	USART1->CR1|=1<<2;
//	USART1->CR1|=1<<5;
//	MY_NVIC_Init(3,3,USART1_IRQn,2);
//#endif
	USART1->CR1|=1<<13;
}


//时锟斤拷锟斤拷锟矫猴拷锟斤拷
//Fvco=Fs*(plln/pllm);
//Fsys=Fvco/pllp=Fs*(plln/(pllm*pllp));
//Fusb=Fvco/pllq=Fs*(plln/(pllm*pllq));

//Fvco:VCO频锟斤拷
//Fsys:系统时锟斤拷频锟斤拷
//Fusb:USB,SDIO,RNG锟饺碉拷时锟斤拷频锟斤拷
//Fs:PLL锟斤拷锟斤拷时锟斤拷频锟斤拷,锟斤拷锟斤拷锟斤拷HSI,HSE锟斤拷.
//plln:锟斤拷PLL锟斤拷频系锟斤拷(PLL锟斤拷频),取值锟斤拷围:64~432.
//pllm:锟斤拷PLL锟斤拷锟斤拷频PLL锟斤拷频系锟斤拷(PLL之前锟侥凤拷频),取值锟斤拷围:2~63.
//pllp:系统时锟接碉拷锟斤拷PLL锟斤拷频系锟斤拷(PLL之锟斤拷姆锟狡�),取值锟斤拷围:2,4,6,8.(锟斤拷锟斤拷锟斤拷4锟斤拷值!)
//pllq:USB/SDIO/锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷鹊锟斤拷锟絇LL锟斤拷频系锟斤拷(PLL之锟斤拷姆锟狡�),取值锟斤拷围:2~15.

//锟解部锟斤拷锟斤拷为8M锟斤拷时锟斤拷,锟狡硷拷值:plln=336,pllm=8,pllp=2,pllq=7.
//锟矫碉拷:Fvco=8*(336/8)=336Mhz
//     Fsys=336/2=168Mhz
//     Fusb=336/7=48Mhz
//锟斤拷锟斤拷值:0,锟缴癸拷;1,失锟杰★拷
u8 Sys_Clock_Set(u32 plln,u32 pllm,u32 pllp,u32 pllq)
{
	u16 retry=0;
	u8 status=0;
	RCC->CR|=1<<16;				//HSE 锟斤拷锟斤拷
	while(((RCC->CR&(1<<17))==0)&&(retry<0X1FFF))retry++;//锟饺达拷HSE RDY
	if(retry==0X1FFF)status=1;	//HSE锟睫凤拷锟斤拷锟斤拷
	else
	{
		RCC->APB1ENR|=1<<28;	//锟斤拷源锟接匡拷时锟斤拷使锟斤拷
		PWR->CR|=3<<14; 		//锟斤拷锟斤拷锟斤拷模式,时锟接可碉拷168Mhz
		RCC->CFGR|=(0<<4)|(5<<10)|(4<<13);//HCLK 锟斤拷锟斤拷频;APB1 4锟斤拷频;APB2 2锟斤拷频.
		RCC->CR&=~(1<<24);	//锟截憋拷锟斤拷PLL
		RCC->PLLCFGR=pllm|(plln<<6)|(((pllp>>1)-1)<<16)|(pllq<<24)|(1<<22);//锟斤拷锟斤拷锟斤拷PLL,PLL时锟斤拷源锟斤拷锟斤拷HSE
		RCC->CR|=1<<24;			//锟斤拷锟斤拷PLL
		while((RCC->CR&(1<<25))==0);//锟饺达拷PLL准锟斤拷锟斤拷
		FLASH->ACR|=1<<8;		//指锟斤拷预取使锟斤拷.
		FLASH->ACR|=1<<9;		//指锟斤拷cache使锟斤拷.
		FLASH->ACR|=1<<10;		//锟斤拷锟斤拷cache使锟斤拷.
		FLASH->ACR|=5<<0;		//5锟斤拷CPU锟饺达拷锟斤拷锟斤拷.
		RCC->CFGR&=~(3<<0);		//锟斤拷锟斤拷
		RCC->CFGR|=2<<0;		//选锟斤拷锟斤拷PLL锟斤拷为系统时锟斤拷
		while((RCC->CFGR&(3<<2))!=(2<<2));//锟饺达拷锟斤拷PLL锟斤拷为系统时锟接成癸拷.
	}
	return status;
}

//系统时锟接筹拷始锟斤拷锟斤拷锟斤拷
//plln:锟斤拷PLL锟斤拷频系锟斤拷(PLL锟斤拷频),取值锟斤拷围:64~432.
//pllm:锟斤拷PLL锟斤拷锟斤拷频PLL锟斤拷频系锟斤拷(PLL之前锟侥凤拷频),取值锟斤拷围:2~63.
//pllp:系统时锟接碉拷锟斤拷PLL锟斤拷频系锟斤拷(PLL之锟斤拷姆锟狡�),取值锟斤拷围:2,4,6,8.(锟斤拷锟斤拷锟斤拷4锟斤拷值!)
//pllq:USB/SDIO/锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷鹊锟斤拷锟絇LL锟斤拷频系锟斤拷(PLL之锟斤拷姆锟狡�),取值锟斤拷围:2~15.
void Stm32_Clock_Init(u32 plln,u32 pllm,u32 pllp,u32 pllq)
{
	RCC->CR|=0x00000001;		//锟斤拷锟斤拷HISON,锟斤拷锟斤拷锟节诧拷锟斤拷锟斤拷RC锟斤拷
	RCC->CFGR=0x00000000;		//CFGR锟斤拷锟斤拷
	RCC->CR&=0xFEF6FFFF;		//HSEON,CSSON,PLLON锟斤拷锟斤拷
	RCC->PLLCFGR=0x24003010;	//PLLCFGR锟街革拷锟斤拷位值
	RCC->CR&=~(1<<18);			//HSEBYP锟斤拷锟斤拷,锟解部锟斤拷锟斤拷锟斤拷路
	RCC->CIR=0x00000000;		//锟斤拷止RCC时锟斤拷锟叫讹拷
	Sys_Clock_Set(plln,pllm,pllp,pllq);//锟斤拷锟斤拷时锟斤拷
	//锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷
#ifdef  VECT_TAB_RAM
	// MY_NVIC_SetVectorTable(1<<29,0x0);
	SCB->VTOR = (1<<29) | (0x0 & (u32)0xFFFFFE00);
#else
	// MY_NVIC_SetVectorTable(0,0x0);
	SCB->VTOR = 0 | (0x0 & (u32)0xFFFFFE00);
#endif
}



static u8  fac_us=0;
static u16 fac_ms=0;

void delay_init(u8 SYSCLK)
{
 	SysTick->CTRL&=~(1<<2);
	fac_us=SYSCLK/8;

	fac_ms=(u16)fac_us*1000;
}

void delay_us(u32 nus)
{
	u32 temp;
	if(nus==0)return;
	SysTick->LOAD=nus*fac_us;
	SysTick->VAL=0x00;
	SysTick->CTRL=0x01 ;
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));
	SysTick->CTRL=0x00;
	SysTick->VAL =0X00;
}

void delay_xms(u16 nms)
{
	u32 temp;
	SysTick->LOAD=(u32)nms*fac_ms;
	SysTick->VAL =0x00;
	SysTick->CTRL=0x01 ;
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));
	SysTick->CTRL=0x00;
	SysTick->VAL =0X00;
}

void delay_ms(u16 nms)
{
	u8 repeat=nms/540;

	u16 remain=nms%540;
	while(repeat)
	{
		delay_xms(540);
		repeat--;
	}
	if(remain)delay_xms(remain);
}
















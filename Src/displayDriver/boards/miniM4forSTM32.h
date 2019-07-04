/*
 *  Author: J. Bajic
 */

#ifndef MINIM4FORSTM32_H_
#define MINIM4FORSTM32_H_

#include "stm32f4xx.h"

#define BOARD_NAME "MINI_M4_FOR_STM32"

//---------------------------------------------------------------------------------------------------------
//CPU & PERIFERIAL BUS FREQUENCY
//---------------------------------------------------------------------------------------------------------

#define SYS_FREQ 168000000L 	// 168MHz - as set in Cube
#define PCLK     (SYS_FREQ/4) 	// 42MHz - as set in Cube (PCLK1-APB1)


//---------------------------------------------------------------------------------------------------------
//PORT CONFIG MACROS
//---------------------------------------------------------------------------------------------------------
#define _IN 	0 	// input
#define _OUT 	1	// output
#define _AF 	2	// alternate
#define _AN 	3	// analog

#define _PP 	0	// push-pull
#define _OD 	1	// open drain

#define _LO 	0	// low speed
#define _ME 	1	// medium speed
#define _HI 	2	// high speed
#define _VH 	3	// very high speed

#define _NO 	0	//none
#define _PU 	1	// pull up
#define _PD 	2	// pull down
#define _RS 	3	// reserved

#define SET_AS(PORT,PIN,MODE,TYPE,SPEED,PULL) {\
	/* MODE - reset, set */\
	PORT->MODER&=~(3<<(PIN<<1));\
	PORT->MODER|=(MODE<<(PIN<<1));\
	/* TYPE - reset, set */\
	PORT->OTYPER&=~(1<<(PIN));\
	PORT->OTYPER|=(TYPE<<(PIN));\
	/* SPEED - reset, set */\
	PORT->OSPEEDR&=~(3<<(PIN<<1));\
	PORT->OSPEEDR|=(SPEED<<(PIN<<1));\
	/* PULL - reset, set */\
	PORT->PUPDR&=~(3<<(PIN<<1));\
	PORT->PUPDR|=(PULL<<(PIN<<1));\
	}

#define SET_AF(PORT,PIN,AF) {\
	/* AFR - reset, set */\
	PORT->AFR[PIN>>3]&=~(0xF<<((PIN%8)<<2));\
	PORT->AFR[PIN>>3]|=(AF<<((PIN%8)<<2));\
	}

//---------------------------------------------------------------------------------------------------------
// BOARD BUILTIN LEDS
//---------------------------------------------------------------------------------------------------------

#define DATA_LED_PORT   GPIOC
#define DATA_LED_PIN	13
#define STAT_LED_PORT   GPIOC
#define STAT_LED_PIN	12

//---------------------------------------------------------------------------------------------------------
// DISPLAY PORT - CONFIGURE PINS
//---------------------------------------------------------------------------------------------------------

//color bits 1 - subpanel 1
#define R1_PORT      	GPIOA
#define R1_PIN			14
#define G1_PORT      	GPIOA
#define G1_PIN			4
#define B1_PORT      	GPIOA
#define B1_PIN			13

//color bits 2 - subpanel 2
#define R2_PORT      	GPIOC
#define R2_PIN			4
#define G2_PORT      	GPIOA
#define G2_PIN			5
#define B2_PORT      	GPIOC
#define B2_PIN			5

//color bits 3 - subpanel 3
#define R3_PORT      	GPIOB
#define R3_PIN			10
#define G3_PORT      	GPIOB
#define G3_PIN			3
#define B3_PORT      	GPIOB
#define B3_PIN			11

//color bits 4 - subpanel 4
#define R4_PORT      	GPIOC
#define R4_PIN			11
#define G4_PORT      	GPIOA
#define G4_PIN			15
#define B4_PORT      	GPIOC
#define B4_PIN			10

//selection bits
#define A_PORT      	GPIOB
#define A_PIN			9
#define B_PORT      	GPIOA
#define B_PIN			6
#define C_PORT      	GPIOB
#define C_PIN			8
#define D_PORT      	GPIOC
#define D_PIN			7

//control bits
#define CLK_PORT      	GPIOC
#define CLK_PIN			9
#define LAT_PORT      	GPIOB
#define LAT_PIN			5
#define OE_PORT      	GPIOB
#define OE_PIN			4

//---------------------------------------------------------------------------------------------------------
//PIN WRITE MACRO FUNCTIONS
//---------------------------------------------------------------------------------------------------------
#define DATA_LED(bit)	DATA_LED_PORT->BSRR=(uint32_t)((((~bit) & 0x01)<<DATA_LED_PIN)<<16)|(((bit) & 0x01)<<DATA_LED_PIN)
#define STAT_LED(bit)	STAT_LED_PORT->BSRR=(uint32_t)((((~bit) & 0x01)<<STAT_LED_PIN)<<16)|(((bit) & 0x01)<<STAT_LED_PIN)

#define R1(bit)			R1_PORT->BSRR=(uint32_t)((((~bit) & 0x01)<<R1_PIN)<<16)|(((bit) & 0x01)<<R1_PIN)
#define G1(bit)			G1_PORT->BSRR=(uint32_t)((((~bit) & 0x01)<<G1_PIN)<<16)|(((bit) & 0x01)<<G1_PIN)
#define B1(bit)			B1_PORT->BSRR=(uint32_t)((((~bit) & 0x01)<<B1_PIN)<<16)|(((bit) & 0x01)<<B1_PIN)

#define R2(bit)			R2_PORT->BSRR=(uint32_t)((((~bit) & 0x01)<<R2_PIN)<<16)|(((bit) & 0x01)<<R2_PIN)
#define G2(bit)			G2_PORT->BSRR=(uint32_t)((((~bit) & 0x01)<<G2_PIN)<<16)|(((bit) & 0x01)<<G2_PIN)
#define B2(bit)			B2_PORT->BSRR=(uint32_t)((((~bit) & 0x01)<<B2_PIN)<<16)|(((bit) & 0x01)<<B2_PIN)

#define R3(bit)			R3_PORT->BSRR=(uint32_t)((((~bit) & 0x01)<<R3_PIN)<<16)|(((bit) & 0x01)<<R3_PIN)
#define G3(bit)			G3_PORT->BSRR=(uint32_t)((((~bit) & 0x01)<<G3_PIN)<<16)|(((bit) & 0x01)<<G3_PIN)
#define B3(bit)			B3_PORT->BSRR=(uint32_t)((((~bit) & 0x01)<<B3_PIN)<<16)|(((bit) & 0x01)<<B3_PIN)

#define R4(bit)			R4_PORT->BSRR=(uint32_t)((((~bit) & 0x01)<<R4_PIN)<<16)|(((bit) & 0x01)<<R4_PIN)
#define G4(bit)			G4_PORT->BSRR=(uint32_t)((((~bit) & 0x01)<<G4_PIN)<<16)|(((bit) & 0x01)<<G4_PIN)
#define B4(bit)			B4_PORT->BSRR=(uint32_t)((((~bit) & 0x01)<<B4_PIN)<<16)|(((bit) & 0x01)<<B4_PIN)

#define A(bit)			A_PORT->BSRR=(uint32_t)((((~bit) & 0x01)<<A_PIN)<<16)|(((bit) & 0x01)<<A_PIN)
#define B(bit)			B_PORT->BSRR=(uint32_t)((((~bit) & 0x01)<<B_PIN)<<16)|(((bit) & 0x01)<<B_PIN)
#define C(bit)			C_PORT->BSRR=(uint32_t)((((~bit) & 0x01)<<C_PIN)<<16)|(((bit) & 0x01)<<C_PIN)
#define D(bit)			D_PORT->BSRR=(uint32_t)((((~bit) & 0x01)<<D_PIN)<<16)|(((bit) & 0x01)<<D_PIN)

#define CLK_LOW			CLK_PORT->BSRR=(uint32_t)((1<<CLK_PIN)<<16)
#define CLK_HIGH		{CLK_PORT->BSRR=(1<<CLK_PIN); NOP();}
#define LAT_LOW			LAT_PORT->BSRR=(uint32_t)((1<<LAT_PIN)<<16)
#define LAT_HIGH		{LAT_PORT->BSRR=(1<<LAT_PIN); NOP();}
#define OE_LOW			OE_PORT->BSRR=(uint32_t)((1<<OE_PIN)<<16)
#define OE_HIGH			{OE_PORT->BSRR=(1<<OE_PIN); NOP();}

//---------------------------------------------------------------------------------------------------------
// INITIALIZE DISPLAY PORT
//---------------------------------------------------------------------------------------------------------
#define enablePORTclocks(){\
	/* enable GPIOA */\
	RCC->AHB1ENR|=RCC_AHB1ENR_GPIOAEN;\
	/* enable GPIOB */\
	RCC->AHB1ENR|=RCC_AHB1ENR_GPIOBEN;\
	/* enable GPIOC */\
	RCC->AHB1ENR|=RCC_AHB1ENR_GPIOCEN;\
}

#define DATA_LED_IO SET_AS(DATA_LED_PORT,DATA_LED_PIN,_OUT,_PP,_LO,_NO)
#define STAT_LED_IO SET_AS(STAT_LED_PORT,STAT_LED_PIN,_OUT,_PP,_LO,_NO)

#define R1_IO SET_AS(R1_PORT,R1_PIN,_OUT,_PP,_VH,_NO)
#define G1_IO SET_AS(G1_PORT,G1_PIN,_OUT,_PP,_VH,_NO)
#define B1_IO SET_AS(B1_PORT,B1_PIN,_OUT,_PP,_VH,_NO)

#define R2_IO SET_AS(R2_PORT,R2_PIN,_OUT,_PP,_VH,_NO)
#define G2_IO SET_AS(G2_PORT,G2_PIN,_OUT,_PP,_VH,_NO)
#define B2_IO SET_AS(B2_PORT,B2_PIN,_OUT,_PP,_VH,_NO)

#define R3_IO SET_AS(R3_PORT,R3_PIN,_OUT,_PP,_VH,_NO)
#define G3_IO SET_AS(G3_PORT,G3_PIN,_OUT,_PP,_VH,_NO)
#define B3_IO SET_AS(B3_PORT,B3_PIN,_OUT,_PP,_VH,_NO)

#define R4_IO SET_AS(R4_PORT,R4_PIN,_OUT,_PP,_VH,_NO)
#define G4_IO SET_AS(G4_PORT,G4_PIN,_OUT,_PP,_VH,_NO)
#define B4_IO SET_AS(B4_PORT,B4_PIN,_OUT,_PP,_VH,_NO)

#define A_IO SET_AS(A_PORT,A_PIN,_OUT,_PP,_VH,_NO)
#define B_IO SET_AS(B_PORT,B_PIN,_OUT,_PP,_VH,_NO)
#define C_IO SET_AS(C_PORT,C_PIN,_OUT,_PP,_VH,_NO)
#define D_IO SET_AS(D_PORT,D_PIN,_OUT,_PP,_VH,_NO)

#define CLK_IO SET_AS(CLK_PORT,CLK_PIN,_OUT,_PP,_VH,_NO)
#define LAT_IO SET_AS(LAT_PORT,LAT_PIN,_OUT,_PP,_VH,_NO)
#define OE_IO  SET_AS(OE_PORT,OE_PIN,_OUT,_PP,_VH,_NO)



//---------------------------------------------------------------------------------------------------------
//SD CARD SPI PORT
//---------------------------------------------------------------------------------------------------------
#define CONFIG_SPI_EXTERNALY 		0

#if (!CONFIG_SPI_EXTERNALY)
	#define SD_SPI_PORT				GPIOB
	#define SD_MOSI_PIN				15
	#define SD_MISO_PIN				14
	#define SD_SCK_PIN				13

	#define enableSPIclocks(){\
		/* enable GPIOB */\
		RCC->AHB1ENR|=RCC_AHB1ENR_GPIOBEN;\
		/* enable SPI */\
		RCC->APB1ENR|=RCC_APB1RSTR_SPI2RST;\
	}

	#define SD_MOSI_IO 	{SET_AS(SD_SPI_PORT,SD_MOSI_PIN,_AF,_PP,_VH,_PU); SET_AF(SD_SPI_PORT,SD_MOSI_PIN,5);}
	#define SD_MISO_IO 	{SET_AS(SD_SPI_PORT,SD_MISO_PIN,_AF,_PP,_VH,_PU); SET_AF(SD_SPI_PORT,SD_MISO_PIN,5);}
	#define SD_SCK_IO  	{SET_AS(SD_SPI_PORT,SD_SCK_PIN,_AF,_PP,_VH,_PU);  SET_AF(SD_SPI_PORT,SD_SCK_PIN,5); }
#endif

#define SD_SPI_CHANNEL			SPI2
#define SD_CS_PORT      		GPIOB
#define SD_CS_PIN				0
#define SD_CS_LOW				SD_CS_PORT->BSRR=(uint32_t)((1<<SD_CS_PIN)<<16)
#define SD_CS_HIGH				SD_CS_PORT->BSRR=(1<<SD_CS_PIN)
#define SD_SPI_GO_SLOW(SPI,div)	{SPI->CR1&=~SPI_CR1_BR; SPI->CR1|=(div<<SPI_CR1_BR_Pos);}
#define SD_SPI_GO_FAST(SPI,div)	{SPI->CR1&=~SPI_CR1_BR; SPI->CR1|=(div<<SPI_CR1_BR_Pos);}
#define SD_CS_IO 	 			SET_AS(SD_CS_PORT,SD_CS_PIN,_OUT,_PP,_VH,_NO)

// div=0 - PCLK/2
// div=1 - PCLK/4
// div=2 - PCLK/8
// div=3 - PCLK/16
// div=4 - PCLK/32
// div=5 - PCLK/64
// div=6 - PCLK/128
// div=7 - PCLK/256

//---------------------------------------------------------------------------------------------------------

#endif /* MINIM4FORSTM32_H_ */

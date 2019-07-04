/*
 *  Author: J. Bajic
 */

#ifndef BOARDS_MINI32FORPIC32MX_H_
#define BOARDS_MINI32FORPIC32MX_H_

#include <p32xxxx.h>

#define BOARD_NAME "MINI_32_FOR_PIC32MX"

//---------------------------------------------------------------------------------------------------------
//CPU & PERIFERIAL BUS FREQUENCY
//---------------------------------------------------------------------------------------------------------

#define SYS_FREQ 80000000L      // 80MHz - as set in CPUConfig
#define PCLK     (SYS_FREQ/2)   // 40MHz - as set in CPUConfig

//---------------------------------------------------------------------------------------------------------
// BOARD BUILTIN LEDS
//---------------------------------------------------------------------------------------------------------

#define DATA_LED(bit) LATDbits.LATD6=bit 
//#define STAT_LED(bit) LATGbits.LATG6=bit // USED AS SCK2

//---------------------------------------------------------------------------------------------------------
//PIN WRITE MACRO FUNCTIONS
//---------------------------------------------------------------------------------------------------------

//color bits 1 - subpanel 1
#define R1(bit)      LATDbits.LATD1=bit
#define G1(bit)      LATDbits.LATD2=bit
#define B1(bit)      LATDbits.LATD10=bit

//color bits 2 - subpanel 2
#define R2(bit)      LATDbits.LATD9=bit
#define G2(bit)      LATDbits.LATD3=bit
#define B2(bit)      LATDbits.LATD8=bit

//color bits 3 - subpanel 3
#define R3(bit)      LATEbits.LATE5=bit
#define G3(bit)      LATEbits.LATE6=bit
#define B3(bit)      LATEbits.LATE4=bit

//color bits 4 - subpanel 4
#define R4(bit)      LATEbits.LATE3=bit
#define G4(bit)      LATEbits.LATE7=bit
#define B4(bit)      LATEbits.LATE2=bit

//selection bits
#define A(bit)       LATFbits.LATF1=bit
#define B(bit)       LATBbits.LATB7=bit
#define C(bit)       LATFbits.LATF0=bit
#define D(bit)       LATBbits.LATB6=bit

//control bits
#define CLK_HIGH     LATBbits.LATB14=1
#define CLK_LOW      LATBbits.LATB14=0
#define LAT_HIGH     LATDbits.LATD0=1
#define LAT_LOW      LATDbits.LATD0=0
#define OE_HIGH      LATBbits.LATB15=1
#define OE_LOW       LATBbits.LATB15=0


//---------------------------------------------------------------------------------------------------------
// INITIALIZE DISPLAY PORT
//---------------------------------------------------------------------------------------------------------

#define DATA_LED_IO TRISDbits.TRISD6=0
//#define STAT_LED_IO TRISGbits.TRISG6=0 // USED AS SCK2

#define R1_IO   TRISDbits.TRISD1=0  //R1
#define G1_IO   TRISDbits.TRISD2=0  //G1
#define B1_IO   TRISDbits.TRISD10=0 //B1

#define R2_IO   TRISDbits.TRISD9=0  //R2
#define G2_IO   TRISDbits.TRISD3=0  //G2
#define B2_IO   TRISDbits.TRISD8=0  //B2

#define R3_IO   TRISEbits.TRISE5=0  //R3
#define G3_IO   TRISEbits.TRISE6=0  //G3
#define B3_IO   TRISEbits.TRISE4=0  //B3

#define R4_IO   TRISEbits.TRISE3=0  //R4
#define G4_IO   TRISEbits.TRISE7=0  //G4
#define B4_IO   TRISEbits.TRISE2=0  //B4

#define A_IO    TRISFbits.TRISF1=0  //A
#define B_IO    TRISBbits.TRISB7=0  //B
#define C_IO    TRISFbits.TRISF0=0  //C
#define D_IO    TRISBbits.TRISB6=0  //D

#define CLK_IO  TRISBbits.TRISB14=0 //CLK
#define LAT_IO  TRISDbits.TRISD0=0  //LAT
#define OE_IO   TRISBbits.TRISB15=0 //OE

//---------------------------------------------------------------------------------------------------------
//SD CARD SPI PORT
//---------------------------------------------------------------------------------------------------------

#define SD_SPI_CHANNEL      SPI_CHANNEL2
#define SPIBUF              SPI2BUF
#define SPIBRG              SPI2BRG
#define SPISTATbits         SPI2STATbits   
#define SPICONbits          SPI2CONbits

#define SD_CS_LOW           LATEbits.LATE0 = 0
#define SD_CS_HIGH          LATEbits.LATE0 = 1
       
#define SD_SPI_GO_SLOW()    {SPIBRG=(PCLK/(2*400000) - 1);}
#define SD_SPI_GO_FAST()    {SPIBRG=(PCLK/(2*10000000) - 1);}

#define SD_CS_IO            TRISEbits.TRISE0 = 0

//---------------------------------------------------------------------------------------------------------
#endif /* BOARDS_MINI32FORPIC32MX_H_ */

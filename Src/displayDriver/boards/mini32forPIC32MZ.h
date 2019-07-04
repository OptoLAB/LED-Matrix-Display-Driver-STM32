/*
 *  Author: J. Bajic
 */

#ifndef BOARDS_MINI32FORPIC32MZ_H_
#define BOARDS_MINI32FORPIC32MZ_H_

#include <p32xxxx.h>

#define BOARD_NAME "MINI_32_FOR_PIC32MZ"

//---------------------------------------------------------------------------------------------------------
//CPU & PERIFERIAL BUS FREQUENCY
//---------------------------------------------------------------------------------------------------------

#define SYS_FREQ 200000000L      // 200MHz - as set in CPUConfig
#define PCLK     (SYS_FREQ/2)   // 100MHz - as set in main.c

//---------------------------------------------------------------------------------------------------------
// BOARD BUILTIN LEDS
//---------------------------------------------------------------------------------------------------------

#define DATA_LED(bit) LATEbits.LATE1=bit 
#define STAT_LED(bit) LATEbits.LATE0=bit //used as SCK 

//---------------------------------------------------------------------------------------------------------
//PIN WRITE MACRO FUNCTIONS
//---------------------------------------------------------------------------------------------------------

//color bits 1 - subpanel 1
#define R1(bit)      LATBbits.LATB12=bit
#define G1(bit)      LATDbits.LATD9=bit
#define B1(bit)      LATBbits.LATB10=bit

//color bits 2 - subpanel 2
#define R2(bit)      LATFbits.LATF3=bit //FUSBIDIO = OFF - USB USBID Selection (Controlled by Port Function)
#define G2(bit)      LATDbits.LATD10=bit
#define B2(bit)      LATDbits.LATD0=bit

//color bits 3 - subpanel 3
#define R3(bit)      LATFbits.LATF5=bit
#define G3(bit)      LATBbits.LATB11=bit
#define B3(bit)      LATFbits.LATF4=bit

//color bits 4 - subpanel 4
#define R4(bit)      LATFbits.LATF1=bit
#define G4(bit)      LATBbits.LATB13=bit
#define B4(bit)      LATFbits.LATF0=bit

//selection bits
#define A(bit)       LATBbits.LATB5=bit
#define B(bit)       LATDbits.LATD11=bit
#define C(bit)       LATBbits.LATB3=bit
#define D(bit)       LATBbits.LATB6=bit

//control bits
#define CLK_HIGH     LATGbits.LATG9=1
#define CLK_LOW      LATGbits.LATG9=0
#define LAT_HIGH     LATGbits.LATG8=1
#define LAT_LOW      LATGbits.LATG8=0
#define OE_HIGH      LATGbits.LATG7=1
#define OE_LOW       LATGbits.LATG7=0


//---------------------------------------------------------------------------------------------------------
// INITIALIZE DISPLAY PORT
//---------------------------------------------------------------------------------------------------------

#define DATA_LED_IO TRISEbits.TRISE1=0
#define STAT_LED_IO TRISEbits.TRISE0=0

#define R1_IO   TRISBbits.TRISB12=0 //R1
#define G1_IO   TRISDbits.TRISD9=0  //G1
#define B1_IO   TRISBbits.TRISB10=0 //B1

#define R2_IO   TRISFbits.TRISF3=0  //R2
#define G2_IO   TRISDbits.TRISD10=0 //G2
#define B2_IO   TRISDbits.TRISD0=0  //B2

#define R3_IO   TRISFbits.TRISF5=0  //R3
#define G3_IO   TRISBbits.TRISB11=0 //G3
#define B3_IO   TRISFbits.TRISF4=0  //B3

#define R4_IO   TRISFbits.TRISF1=0  //R4
#define G4_IO   TRISBbits.TRISB13=0 //G4
#define B4_IO   TRISFbits.TRISF0=0  //B4

#define A_IO    TRISBbits.TRISB5=0  //A
#define B_IO    TRISDbits.TRISD11=0 //B
#define C_IO    TRISBbits.TRISB3=0  //C
#define D_IO    TRISBbits.TRISB6=0  //D

#define CLK_IO  TRISGbits.TRISG9=0  //CLK
#define LAT_IO  TRISGbits.TRISG8=0  //LAT
#define OE_IO   TRISGbits.TRISG7=0  //OE

//---------------------------------------------------------------------------------------------------------
//SD CARD SPI PORT
//---------------------------------------------------------------------------------------------------------

#define SD_SPI_CHANNEL      SPI_CHANNEL2
#define SPIBUF              SPI2BUF
#define SPIBRG              SPI2BRG
#define SPISTATbits         SPI2STATbits   
#define SPICONbits          SPI2CONbits

#define SD_CS_LOW           LATEbits.LATE5 = 0
#define SD_CS_HIGH          LATEbits.LATE5 = 1
       
#define SD_SPI_GO_SLOW()    {SPIBRG=(PCLK/(2*400000) - 1);}
#define SD_SPI_GO_FAST()    {SPIBRG=(PCLK/(2*25000000) - 1);}

#define SD_CS_IO            TRISEbits.TRISE5 = 0
#define SPI_PPS(){\
        /*SDI on RD3*/\
        SDI2R=0b0000;\
        TRISDbits.TRISD3 = 1;\
        /*SDO on RD2*/\
        RPD2R=0b0110;\
        }
//---------------------------------------------------------------------------------------------------------
#endif /* BOARDS_MINI32FORPIC32MX_H_ */

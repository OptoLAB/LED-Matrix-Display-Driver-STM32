/* 
 * Author: J. Bajic
 */

#ifndef DISPLAYCONFIG_H
#define	DISPLAYCONFIG_H

//-------------------------------------------------------------------
//INCLUDE BOARD
//-------------------------------------------------------------------
#include <boards/miniM4forSTM32.h>
//-------------------------------------------------------------------
//REVISION
//------------------------------------------------------------------
#define REV_DATE 230519
//------------------------------------------------------------------
//COLOR FORMAT
//-------------------------------------------------------------------
#define RGB888
    // RGB111 
    // RGB332 
    // RGB565 
    // RGB888
//-------------------------------------------------------------------
//DISPLAY SIZE 
//-------------------------------------------------------------------
#define DISPLAY_WIDTH           (96)
#define DISPLAY_HEIGHT          (64)
//-------------------------------------------------------------------
//CONFIGURE PANELS
//-------------------------------------------------------------------                                   
#define PANEL_WIDTH             (32)
#define PANEL_HEIGHT            (64)
#define NUM_OF_SELECTION_BITS   (3)
#define NUM_OF_SUBPANELS        (4) // max 4 //(R1,G1,B1)&(R2,G2,B2)&(R3,G3,B3)&(R4,G4,B4)
//-------------------------------------------------------------------  
//  +-------32-------+ <----------- R1,G1,B1 color bits 1  
//  |   subpanel 1   | <-----+----- A,B,C,(D) selection bits  
//  |    2x(32x8)    | <-+---|----- CLK, LAT, OE control bits  
// 32----------------+   |   |   
//  |   subpanel 2   | <-+    
//  |    2x(32x8)    | <-----+ 
//  +----------------+ <----------- R2,G2,B2 color bits 2     
//-------------------------------------------------------------------
// CONFIGURE DELAY FUNCTION
//-------------------------------------------------------------------
#define USE_EXTERNAL_DELAY_FN	(0)
	// 0 - NO
	// 1 - YES
#if (USE_EXTERNAL_DELAY_FN)
	#define DELAY_MS(MS) delay_ms(MS) //provide external delay function for more precise timing
#endif
//-------------------------------------------------------------------
// SD_CARD
//-------------------------------------------------------------------
#define USE_SD_CARD				(1)
	// 0 - NO
	// 1 - YES
//-------------------------------------------------------------------
// DISPLAY REFRESH MODE
//-------------------------------------------------------------------
#define REFRESH_MODE			(2)
	// 0 - MANUALLY (use refreshDisplay function, displayDelay executes refreshDisplay)
	// 1 - TIMER (refresh triggered by timer, requires timer interrupt implementation to execute function refreshDisplay() with given REFRESH_RATE)
	// 2 - FREERTOS (refresh executed in separate FREERTOS task, requires separate task implementation for refreshDisplay() execution)
#if (REFRESH_MODE)
    #define REFRESH_RATE        (120)  	  //to low => flickering, to high => slow response
#endif
//-------------------------------------------------------------------
#endif	/* DISPLAYCONFIG_H */


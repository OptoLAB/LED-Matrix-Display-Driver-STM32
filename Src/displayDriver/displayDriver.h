/* 
 * Author: J. Bajic
 */

#ifndef LED_PANEL_H
#define	LED_PANEL_H

//--------------------------------------------------------------------------
// includes
//--------------------------------------------------------------------------	
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "displayConfig.h"
#include "displayTypeDefs.h"
#include "utils/fonts.h"
#include "utils/gamma.h"
#include "utils/colors.h"
#if (USE_SD_CARD)
#include "ff.h"
#endif
#if (REFRESH_MODE==2)
#include "FreeRTOS.h"
#include "task.h"
#endif

//--------------------------------------------------------------------------
// calculate based on displayConfig
//--------------------------------------------------------------------------
#define NUM_OF_PANELS_X         (DISPLAY_WIDTH/PANEL_WIDTH)
#define NUM_OF_PANELS_Y         (DISPLAY_HEIGHT/PANEL_HEIGHT) 
#define NUM_OF_PANELS           (NUM_OF_PANELS_X*NUM_OF_PANELS_Y) 
#define NUM_PIXELS_PER_PANEL    (PANEL_WIDTH*PANEL_HEIGHT) 
#define NUM_OF_ROWS             (1<<NUM_OF_SELECTION_BITS) 
#define NUM_OF_COLUMNS          (PANEL_WIDTH) 
#define NUM_OF_SEGMENTS         ((PANEL_HEIGHT/NUM_OF_SUBPANELS)>>NUM_OF_SELECTION_BITS) 
#define SUBPANEL_OFFSET         (DISPLAY_WIDTH*(PANEL_HEIGHT/NUM_OF_SUBPANELS)) 
#define VERTICAL_PANEL_OFFSET   (DISPLAY_WIDTH*PANEL_HEIGHT) 
#define SEGMENT_OFFSET          (DISPLAY_WIDTH<<NUM_OF_SELECTION_BITS) 
//--------------------------------------------------------------------------
// for scrolling direction
//--------------------------------------------------------------------------
#define DOWN    0x01
#define UP      0x02
#define RIGHT   0x04
#define LEFT    0x08
//--------------------------------------------------------------------------
// true/false flags
//--------------------------------------------------------------------------
#define TRUE    1
#define FALSE   0
//--------------------------------------------------------------------------
// axes
//--------------------------------------------------------------------------
#define X_AXIS  1
#define Y_AXIS  2
//--------------------------------------------------------------------------
// color format
//--------------------------------------------------------------------------
#if !defined(RGB111) && !defined(RGB332) && !defined(RGB565) && !defined(RGB888)
    #define RGB565 //default color format
#endif
#ifdef RGB111
    #define DEFAULT_FORMAT      (0) //less than 1 byte per pixel
    #define PPB                 (2) //2 pixels per 1 byte
    #define BPC                 (1) //1 bits per channel - R1,B1,G1
    #define rCh(c)              (c.color>>2)            // red channel
    #define gCh(c)              (c.color>>1)            // green channel
    #define bCh(c)              (c.color)               // blue channel
    #define chMask              (0x01)                  // channel mask
    #define mixCh(r,g,b)        ((b)|(g<<1)|(r<<2))     // mix channels
    #define NBL(x)              ((x&1)<<2)              // nibble shift (because if 2 pixels in same byte)
    #define getFRAMEpx(i)       (color_t){.color=(FRAME_BUFF[i>>1].color>>NBL(i))&(0x0F)}
    #define setFRAMEpx(i,v)     (FRAME_BUFF[i>>1].color=(FRAME_BUFF[i>>1].color&(0x0F0>>NBL(i))|(v.color<<NBL(i))))// sets only one nibble
    #define color2px(px)        (color_t){{px&0x01,(px>>1)&0x01,(px>>2)&0x01}}  
    #define COLOR(c)            (color_t){{(c&0x0000FF)>>7,((c&0x00FF00)>>8)>>7,((c&0xFF0000)>>16)>>7}}
#endif
#ifdef RGB332 
    #define DEFAULT_FORMAT      (1) //1 byte per pixel 
    #define PPB                 (1) //1 pixel per 1 byte
    #define BPC                 (3) //3 bits per channel - R3,G3,B3 (B is extended with lsb 0) 
    #define rCh(c)              (c.color>>5)            // red channel
    #define gCh(c)              (c.color>>2)            // green channel
    #define bCh(c)              (c.color<<1)            // blue channel
    #define chMask              (0x07)                  // channel mask
    #define mixCh(r,g,b)        ((b>>1)|(g<<2)|(r<<5))  // mix channels
    #define getFRAMEpx(i)       (FRAME_BUFF[i]) 
    #define setFRAMEpx(i,v)     (FRAME_BUFF[i]=v)
    #define color2px(px)        (color_t){{px&0x03,(px>>2)&0x07,(px>>5)&0x07}}  
    #define COLOR(c)            (color_t){{((c&0x0000FF)>>6),((c&0x00FF00)>>8)>>5,((c&0xFF0000)>>16)>>5}}
#endif
#ifdef RGB565
    #define DEFAULT_FORMAT      (2) //2 bytes per pixel 
    #define PPB                 (1) //1 pixel per 2 bytes
    #define BPC                 (5) //5 bits per channel - R5,G5,B5 (lsb for g is ignored) 
    #define rCh(c)              (c.color>>11)           // red channel
    #define gCh(c)              (c.color>>6)            // green channel
    #define bCh(c)              (c.color)               // blue channel
    #define chMask              (0x1F)                  // channel mask
    #define mixCh(r,g,b)        ((b)|(g<<6)|(r<<11))    // mix channels
    #define getFRAMEpx(i)       FRAME_BUFF[i]
    #define setFRAMEpx(i,v)     FRAME_BUFF[i]=v 
    #define color2px(px)        (color_t){{px&0x1F,(px&0x07E0)>>5,(px&0xF800)>>11}}  
    #define COLOR(c)            (color_t){{(c&0x0000FF)>>3,((c&0x00FF00)>>8)>>2,((c&0xFF0000)>>16)>>3}}
#endif
#ifdef RGB888
    #define DEFAULT_FORMAT      (3) //3 bytes per pixel  
    #define PPB                 (1) //1 pixel per 3 bytes
    #define BPC                 (8) //8 bits per channel - R8,G8,B8
    #define rCh(c)              ((c.color[2]))           // red channel
    #define gCh(c)              ((c.color[1]))           // green channel
    #define bCh(c)              ((c.color[0]))           // blue channel
    #define chMask              (0xFF)                   // channel mask
    #define mixCh(r,g,b)        ((b)|(g<<8)|(r<<16))     // mix channels
    #define getFRAMEpx(i)		FRAME_BUFF[i]
	#define setFRAMEpx(i,v)		FRAME_BUFF[i]=v
    #define color2px(px)        (color_t){{px&0xFF,(px>>8)&0xFF,(px>>16)&0xFF}}      
    #define COLOR(c)            color2px(c)
#endif

//--------------------------------------------------------------------------
//BMP header - BITMAPINFOHEADER 
//--------------------------------------------------------------------------   
#define BMP_DIB     0x0E
#define BMP_WIDTH   0x12
#define BMP_HEIGHT  0x16
#define BMP_BPP     0x1C
#define BMP_COLORS  0x2E
//--------------------------------------------------------------------------
#define NOP() asm("Nop")
#define CLKs ((SYS_FREQ/4)/1000)

#if 	(USE_EXTERNAL_DELAY_FN)
	#define dly(X) DELAY_MS(X)
#else
    #define dly(X) simpleDelay(X)
#endif

#if 	(REFRESH_MODE==0)
	#define DELAY(X) refreshDelay(X)
#else
	#define DELAY(X) dly(X)
#endif           

//--------------------------------------------------------------------------
//functions
//--------------------------------------------------------------------------
// DISPLAY REFRESH FUNCTIONS
void refreshDisplay(void); // OK
void displaySetBrightness(uint8_t brightness); //OK
// DISPLAY INIT FUNCTIONS
void displayInit(void); // OK
// DISPLAY FILL FUNCTIONS
void displayFillArea(uint16_t x1,uint16_t y1, uint16_t x2, uint16_t y2, color_t color); //OK
void displayInvertArea(uint16_t x1,uint16_t y1, uint16_t x2, uint16_t y2); // OK
void displayFill(color_t color); //OK
void displayFillNoise(void); // OK 
void displayInvert(void); //OK
void displayClear(void); // OK
// DISPLAY GAMMA FUNCTIONS
void displayGammaCorrect(); 
void displayGammaCorrectArea(uint16_t x1,uint16_t y1, uint16_t x2, uint16_t y2); 
//DISPLAY SCROLL&MIRROR FUNCTIONS
void displayScroll(uint8_t dir, uint16_t num_of_px, uint8_t speed); // OK
void displayMirror(unsigned char axis); // OK
//DISPLAY PRINT FUNCTIONS
void displayGoTo(uint16_t x, uint16_t y); // OK
void displaySetFont(font_t font); //OK
void displayNewLine(void); // OK
void displayPutChar (char c, color_t color); // OK
void displayPrint(char *text, color_t color);  // OK
//DISPLAY DRAW FUNCTIONS
void displaySetPixel(uint16_t x, uint16_t y, color_t color); // OK
void displayDrawRectangle(uint16_t width,uint16_t height, color_t line_color, color_t fill_color);// OK
void displayDrawCircle(uint16_t radius, color_t line_color, color_t fill_color); // OK
//DISPLAY IMAGE FUNCTIONS
void displayLoadImage(const image_t img, uint8_t gamma_corrected); // OK
#if (USE_SD_CARD)
uint8_t mountSD(void); // OK
void unmountSD(void); // OK
void displayLoadImageSD(TCHAR * file_path, uint8_t gamma_corrected); //OK
void displayPlayImagesSD(TCHAR * file_path, uint16_t time, uint8_t gamma_corrected); // OK
#endif
//DISPLAY COLOR FUNCTIONS
uint32_t RGB(uint8_t r, uint8_t g, uint8_t b); //OK
uint32_t HSV(uint16_t h, uint8_t s, uint8_t v);  //OK
uint32_t convertRGB(const unsigned char src, const unsigned char dst, uint32_t color); // OK
color_t gammaCorrected(color_t color);
//--------------------------------------------------------------------------
//DISPLAY DELAYS
void delay_nops(uint32_t nops); // OK
void simpleDelay(uint32_t delay); // OK
void refreshDelay(uint16_t x_times); // OK
void displayDelay(uint16_t time); // OK
//--------------------------------------------------------------------------


#endif	/* LED_PANEL_H */


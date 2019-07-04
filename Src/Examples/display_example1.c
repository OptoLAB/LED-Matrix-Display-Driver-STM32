/* 
 * Author: J. Bajic
 */

#include "displayDriver.h"
#include "RGB565/hue.h"

void setup(void)
{    
    displayInit();
    displaySetBrightness(5);

    displayGoTo(0,0);
    displaySetFont(DEFAULT_BIG);
    displayPrint("AaBbCcDd",  COLOR(RED));
    displayNewLine();
    
    displaySetFont(DEFAULT_SMALL);
    displayPrint("AaBbCcDd", COLOR(RGB(0,255,0)));
    displayNewLine();
    
    displaySetFont(DEFAULT_EXTRA_SMALL);
    displayPrint("A B C D ", COLOR(HSV(240,100,100))); // no small letters
    displayNewLine();  
    
    
    displayDelay(300); // refreshing display       
}

void loop(void)
{
    displayGoTo(5,40);
    displayDrawRectangle(10,15, COLOR(BLUE), COLOR(HSV(60,100,100)));
    
    displayGoTo(30,50);
    displayDrawCircle(10, COLOR(RGB(255,0,255)), COLOR(CYAN));
    
    displayGoTo(64,32);
    displayLoadImage(hue, TRUE);
    
    displayDelay(300);  
    
    displayScroll(UP, 64, 2);
    displayDelay(300);
    displayScroll(DOWN, 128, 1);
    displayDelay(300);
    displayScroll(LEFT, 192, 1);
    displayDelay(300);
    displayScroll(RIGHT, 96, 2);
    displayDelay(300);
    displayScroll(RIGHT|UP, 192, 1);
    displayDelay(300);  

    displayMirror(X_AXIS);
    displayDelay(300);
    displayMirror(Y_AXIS);
    displayDelay(300);
    displayMirror(X_AXIS|Y_AXIS);
    displayDelay(300);
    
    
    displayFill(COLOR(BLUE));
    displayDelay(300);    
    displayInvert();
    displayDelay(300);
    displayInvert();
    displayDelay(300);
    
    //blink
    simpleDelay(500);    // not refreshing display
    displayDelay(50);
    simpleDelay(500);
    displayDelay(50);
    simpleDelay(500);
    displayDelay(50);
    simpleDelay(500);
    displayDelay(50);   
    
    displayClear();
}

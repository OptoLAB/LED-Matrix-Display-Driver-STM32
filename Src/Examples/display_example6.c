/* 
 * Author: J. Bajic
 */

#include "displayDriver.h"

#include "FCB111.h" // RGB111
#include "FCB332.h" // RGB332
#include "FCB565.h" // RGB565
#include "FCB888.h" // RGB888

void setup(void)
{
    displayInit();
    displaySetBrightness(5);
}


void loop(void)
{ 
    //RGB111
    displayClear();
    displayGoTo(0,0);
    displayPrint("RGB111", COLOR(WHITE));
    displayDelay(200);
    
    displayGoTo(0,10);
    displayLoadImage(FCB111, TRUE);
    displayGoTo(48,10);
    displayLoadImage(FCB111, FALSE);
    displayDelay(500);

    //RGB332
    displayClear();
    displayGoTo(0,0);
    displayPrint("RGB332", COLOR(WHITE));
    displayDelay(200);
    
    displayGoTo(0,10);
    displayLoadImage(FCB332, TRUE);
    displayGoTo(48,10);
    displayLoadImage(FCB332, FALSE);
    displayDelay(500);
    
    //RGB565
    displayClear();
    displayGoTo(0,0);
    displayPrint("RGB565", COLOR(WHITE));
    displayDelay(200);
    
    displayGoTo(0,10);
    displayLoadImage(FCB565, TRUE);
    displayGoTo(48,10);
    displayLoadImage(FCB565, FALSE);    
    displayDelay(500);

    //RGB888
    displayClear();
    displayGoTo(0,0);
    displayPrint("RGB888", COLOR(WHITE));
    displayDelay(200);
    
    displayGoTo(0,10);
    displayLoadImage(FCB888, TRUE);
    displayGoTo(48,10);
    displayLoadImage(FCB888, FALSE);
    displayDelay(500);
    
    //scroll & mirror
    displayScroll(UP, 192, 1);
    displayDelay(300);
    displayScroll(RIGHT, 96, 2);
    displayDelay(300);
    
    displayMirror(X_AXIS);
    displayDelay(300);
    displayMirror(Y_AXIS);
    displayDelay(300);
    displayMirror(X_AXIS|Y_AXIS);
    displayDelay(300);
    
    displayScroll(UP, 64, 2);
    displayDelay(300);
    displayScroll(DOWN, 128, 1);
    displayDelay(300);

    displayScroll(RIGHT|UP, 192, 2);
    displayDelay(300);  
}

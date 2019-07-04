/* 
 * Author: J. Bajic
 */

#include "displayDriver.h"


void setup(void)
{
    displayInit();
    displaySetBrightness(5);
}


void loop(void)
{
    while(!mountSD());
 
    displayClear();
    displayGoTo(0,0);
    displayPrint("RGB111", COLOR(WHITE));
    displayDelay(300);
    
    displayGoTo(0,0);
    displayPlayImagesSD("images/RGB111",300, FALSE);
    displayDelay(300);   
    
    displayClear();
    displayGoTo(0,0);
    displayPrint("4bit", COLOR(WHITE));
    displayDelay(300);
    
    displayGoTo(0,0);
    displayPlayImagesSD("images/4bit",300, FALSE);
    displayDelay(300);   
    
    displayClear();
    displayGoTo(0,0);
    displayPrint("8bit", COLOR(WHITE));
    displayDelay(300);
    
    displayGoTo(0,0);
    displayPlayImagesSD("images/8bit",300, TRUE);
    displayDelay(300);  
    
    displayClear();
    displayGoTo(0,0);
    displayPrint("RGB332", COLOR(WHITE));
    displayDelay(300);
    
    displayGoTo(0,0);
    displayPlayImagesSD("images/RGB332",300, TRUE);
    displayDelay(300);
    
    displayClear();    
    displayGoTo(0,0);
    displayPrint("RGB565", COLOR(WHITE));
    displayDelay(300);
    
    displayGoTo(0,0);
    displayPlayImagesSD("images/RGB565",300, TRUE);
    displayDelay(300); 
    
    displayClear();    
    displayGoTo(0,0);
    displayPrint("RGB888", COLOR(WHITE));
    displayDelay(300);
    
    displayGoTo(0,0);
    displayPlayImagesSD("images/RGB888",300, TRUE);
    displayDelay(300); 
    
    displayClear();    
    displayGoTo(0,0);
    displayPrint("ARGB888", COLOR(WHITE));
    displayDelay(300);
    
    displayGoTo(0,0);
    displayPlayImagesSD("images/ARGB8888",300, TRUE);
    displayDelay(300);     
    unmountSD();
}

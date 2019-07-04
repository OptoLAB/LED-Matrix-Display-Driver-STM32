/* 
 * Author: J. Bajic
 */

#include "displayDriver.h"

void setup(void)
{
    displayInit();
    displaySetBrightness(5);
}
unsigned char i=0;

void loop(void)
{ 

    if(mountSD())
    {
        displayClear();
        displayFill(COLOR(WHITE));
        displayGoTo(16,0);
        for(i=0;i<5;i++)
        displayPlayImagesSD("anim/think", 1, TRUE);   
        displayDelay(1000);
        
        displayClear();
        displayGoTo(24,8);
        displayPlayImagesSD("anim/KEL", 1, TRUE);   
        displayScroll(LEFT,24,2);
        displayGoTo(48,8);
        displayPlayImagesSD("anim/DEET", 1, TRUE);  
        displayScroll(UP,8,2);
        displayGoTo(5,47);
        displayPrint("Mikroracunarska", COLOR(YELLOW));
        displayGoTo(17,55);
        displayPrint("elektronika", COLOR(YELLOW));
        displayDelay(2000);
  
        
        displayClear();
        displayGoTo(0,0);
        displayPlayImagesSD("anim/OELAB", 1, TRUE);
        displayDelay(2000);

        
        displayClear();
        displayGoTo(0,0);
        for(i=0;i<2;i++)
        displayPlayImagesSD("anim/jannis", 1, TRUE);

        
        displayClear();
        displayGoTo(16,0);
        for(i=0;i<3;i++)
        displayPlayImagesSD("anim/bisqwit", 1, TRUE);
        
        displayClear();
        displayGoTo(16,0);
        for(i=0;i<3;i++)
        displayPlayImagesSD("anim/squirrel", 1, TRUE);

        
        displayClear();
        displayGoTo(0,0);
        displayPlayImagesSD("images/ARGB8888", 1000, TRUE);
        

        displayClear();
        displayGoTo(0,0);
        displayPlayImagesSD("images/RGB888", 1000, TRUE);

        
        displayClear();
        displayGoTo(0,0);
        displayPlayImagesSD("images/RGB565", 1000, TRUE);
     

        displayFill(COLOR(WHITE));
        displayGoTo(22,0);
        for(i=0;i<5;i++)
        displayPlayImagesSD("anim/mamba", 10, TRUE);
       
        displayGoTo(0,0);
        displayPlayImagesSD("anim/printer", 0, TRUE);
        
        displayClear();
        displayGoTo(0,0);
        displayPlayImagesSD("anim/LF", 0, TRUE);
  
        unmountSD();
    }
    else
    {
        displayGoTo(0,24);
        displayPrint("Error reading", COLOR(WHITE));
    }
  
}

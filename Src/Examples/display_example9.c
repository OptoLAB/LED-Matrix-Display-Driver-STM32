/* 
 * Author: J. Bajic
 */

#include "displayDriver.h"


void setup(void)
{
    displayInit();
    displaySetBrightness(5);
}

unsigned int i=0;

void loop(void)
{
    while(!mountSD());
    
    displayGoTo(16,0);
    for(i=0;i<5;i++)
    displayPlayImagesSD("anim/bisqwit",1,TRUE);
    displayDelay(300); 
    displayClear();
    
    unmountSD();    

}

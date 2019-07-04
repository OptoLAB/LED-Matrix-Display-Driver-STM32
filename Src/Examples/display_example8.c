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
    
    displayGoTo(0,0);
    displayPlayImagesSD("images/RGB888",300,TRUE);
    displayDelay(300); 
    displayClear();
    
    unmountSD();    

}

/* 
 * Author: J. Bajic
 */

#include "displayDriver.h"


void setup(void)
{
    displayInit();
    displaySetBrightness(5);
    
    while(!mountSD());
    
    displayGoTo(0,0);
    displayLoadImageSD("images/RGB888/my_dog.bmp",TRUE);
    displayDelay(300); 
   
    unmountSD();
}


void loop(void)
{
   displayDelay(100);     
}

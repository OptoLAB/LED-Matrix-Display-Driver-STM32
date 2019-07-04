/* 
 * Author: J. Bajic
 */

#include "displayDriver.h"
#include "RGB565/FCB.h"

void setup(void)
{
    displayInit();
    displaySetBrightness(5);
    
    displayGoTo(0,0);
    displayLoadImage(FCB, FALSE);
    
    displayGoTo(48,0);
    displayLoadImage(FCB, TRUE); // gamma corrected
}


void loop(void)
{
    displayDelay(100);
}

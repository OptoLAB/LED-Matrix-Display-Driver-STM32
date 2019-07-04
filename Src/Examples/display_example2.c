/* 
 * Author: J. Bajic
 */

#include "displayDriver.h"
#include "RGB565/mario.h"

void setup(void)
{
    displayInit();
    displaySetBrightness(5);
    displayGoTo(0,0);
    displayLoadImage(mario, TRUE);
}


void loop(void)
{
    displayDelay(100);
}

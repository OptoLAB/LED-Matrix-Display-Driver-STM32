/* 
 * Author: J. Bajic
 */

#include "displayDriver.h"
#include "Courier9x13.h"
#include "Arial16x19.h"
#include "Victorian_LET16x26.h"


void setup(void)
{
    displayInit();
    displaySetBrightness(5);
    
    displayGoTo(0,0);
    displaySetFont(DEFAULT_EXTRA_SMALL);
    displayPrint("TEST", COLOR(MAGENTA));
    displayGoTo(0,8);
    displaySetFont(DEFAULT_SMALL);
    displayPrint("TEST", COLOR(CYAN));
    displayGoTo(0,16);
    displaySetFont(DEFAULT_BIG);
    displayPrint("TEST", COLOR(YELLOW));
    displayGoTo(0,29);
    displaySetFont(COURIER_9X13);
    displayPrint("TEST", COLOR(RED));
    displayGoTo(0,41);
    displaySetFont(ARIAL_16X19);
    displayPrint("TEST", COLOR(GREEN));
    displayGoTo(38,0);
    displaySetFont(VICTORIAN_LET_16X26);
    displayPrint("1234", COLOR(BLUE));
    displayGoTo(38,27);
    displaySetFont(VICTORIAN_LET_16X26);
    displayPrint("456", COLOR(BLUE));
    
}

void loop(void)
{
    displayDelay(100);
}

/* 
 * Author: J. Bajic
 */

#include "displayDriver.h"
#include "RGB565/FCB.h"
#include "RGB565/FCRM.h"

unsigned char i,j;

void setup(void)
{
    displayInit();
    displaySetFont(DEFAULT_BIG);
    displaySetBrightness(5);
}


void loop(void)
{
    displayClear();
    displayGoTo(0,0);
    displayLoadImage(FCB, TRUE);
    displayGoTo(48,0);
    displayLoadImage(FCRM, TRUE);
    displayGoTo(33,48);
    displayPrint("0-0", COLOR(ORANGE));
    displayDelay(400);
    
    j=0;
    for(i=0;i<=200;i++)
    {
        j++;
        displayFillNoise();
        if(j<10)
        {
            displayGoTo(7,24);
            displayPrint("GOALLLL!!!!", COLOR(BLACK));
        }
        if(j==20)j=0;
        displayDelay(2);
    }
    
    displayClear();
    displayGoTo(0,0);
    displayLoadImage(FCB, TRUE);
    displayGoTo(48,0);
    displayLoadImage(FCRM, TRUE);
    displayGoTo(33,48);
    displayPrint("1-0", COLOR(ORANGE));
    displayDelay(400);
    
    j=0;
    for(i=0;i<=200;i++)
    {
        j++;
        displayFillNoise();
        if(j<10)
        {
            displayGoTo(7,24);
            displayPrint("GOALLLL!!!!", COLOR(BLACK));
        }
        if(j==20)j=0;
        displayDelay(2);
    }  
    
    displayClear();
    displayGoTo(0,0);
    displayLoadImage(FCB, TRUE);
    displayGoTo(48,0);
    displayLoadImage(FCRM, TRUE);
    displayGoTo(33,48);
    displayPrint("1-1", COLOR(ORANGE));
    displayDelay(400);  
}

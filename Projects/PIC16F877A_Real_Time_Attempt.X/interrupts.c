/******************************************************************************/
/*Files to Include                                                            */
/******************************************************************************/
#include <xc.h>         /* XC8 General Include File */
#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */
#include "lcd.h"

unsigned int time = 1;
unsigned int time2 = 1;

void interrupt isr(void)
{
    if(TMR0IF==1)
    {
        TMR0 = 101;     /*Load the timer Value, (Note: Timervalue is 101 instaed of 100 as the
                          TImer0 needs two instruction Cycles to start incrementing TMR0 */
        TMR0IF=0;       // Clear timer interrupt flag
        time++;
        time2++;
        
        if(time == 250)
        {
            RB6 = !RB6;
            time = 0;
        }
        
        if(time2 == 100)
        {
            RB7 = !RB7;
            time2 = 0;   
        }
    }
    
    if (INTF==1) //External Interrupt detected
        {
            INTF = 0;          // clear the interrupt flag after done with it
        }
}



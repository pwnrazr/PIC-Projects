/******************************************************************************/
/*Files to Include                                                            */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#endif

#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */
#include "system.h"

void interrupt timer_isr()
{  
    if(TMR1IF==1)
    {
        if(LED2==0)
            {
                LED2=1;
            }
            else if(LED2==1)
            {
                LED2=0;
            }
        //value++;   // complement the value for blinking the LEDs
        TMR1H=0x0B;     // Load the time value(0xBDC) for 100ms delay
        TMR1L=0xDC;
        TMR1IF=0;       // Clear timer interrupt flag
        
    if(TMR0IF==1)
    {
        TMR0 = 101;     /*Load the timer Value, (Note: Timervalue is 101 instaed of 100 as the
                          TImer0 needs two instruction Cycles to start incrementing TMR0 */
        TMR0IF=0;       // Clear timer interrupt flag
    } 
    } 
}
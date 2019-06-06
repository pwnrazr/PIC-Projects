#include <xc.h>
#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */

unsigned int ledtime = 0;
unsigned int time = 0;
void interrupt isr(void)
{
    //Begin Timer0
    if(TMR0IF==1)
    {
        TMR0 = 101;     /*Load the timer Value, (Note: Timervalue is 101 instaed of 100 as the
                          TImer0 needs two instruction Cycles to start incrementing TMR0 */
        TMR0IF=0;       // Clear timer interrupt flag
        
        if(RC0==1)
            {
                ledtime = 1000;
                RB6 = 1;
            }
        else
            {
                RB6 = 0;
            }

        //begin led function
        if(ledtime > 0)
            { 
                RC7 = 1;
                ledtime--;
            }
        else
            {
                RC7 = 0;
            }
        //end led function  
    }
    
    //END Timer0
   
}




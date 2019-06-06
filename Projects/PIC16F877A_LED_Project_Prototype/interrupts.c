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
#include "lcd.h"
#include "uart.h"
/******************************************************************************/
/* Interrupt Routines                                                         */
/******************************************************************************/

/* Baseline devices don't have interrupts. Note that some PIC16's 
 * are baseline devices.  Unfortunately the baseline detection macro is 
 * _PIC12 */
unsigned int time;
unsigned int beep = 0;
unsigned int ledtime = 0;
char data[10];
char datarec;
unsigned int charcount = 0;
unsigned int ready = 0;

void interrupt isr(void)
{
    //Begin Timer0
    if(TMR0IF==1)
    {
        TMR0 = 101;     /*Load the timer Value, (Note: Timervalue is 101 instaed of 100 as the
                          TImer0 needs two instruction Cycles to start incrementing TMR0 */
        TMR0IF=0;       // Clear timer interrupt flag
        
        //begin buzzer function
        time++;
        if(time > 50)
        {
            if(beep > 0)
            {
                if(TMR2ON==1)
                {
                    uart_putstr("BEEP!\n");
                }

                TMR2ON = !TMR2ON;
                beep--;
            }
            time = 0;
        }
        //end buzzer function
        
        //begin led function
        if(ledtime > 0)
        {
            RB6 = 1;
            ledtime--;
        }
        else
        {
            RB6 = 0;
        }
        //end led function
    }
    
    //END Timer0
    
    if (INTF==1) //External Interrupt detected on RB0
        {

            beep = 6; //needs to be n*2
            TMR2ON = 0;
            ledtime = 5000;
            INTF = 0;          // clear the interrupt flag after done with it
        }
    
    if(RCIF== 1) //UART receive interrupt
    {
        if(uart_read() == 'A')
        {
            beep = 5000;
        }
    } 
}



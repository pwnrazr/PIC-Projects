/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#endif

#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */

#include "lcd.h"

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp */

void main(void)
{
    /* Initialize I/O and Peripherals for application */
    InitApp();
    
    PORTA = 0;				// Clear Port
	PORTB = 0;	
	PORTC = 0;
	PORTD = 0;
	
	TRISA = 0b11111111;		// set PORTA as INPUT
	TRISB = 0b00001111;		// set PORTB<7:2> as OUTPUT . PORTB<1:0> as INPUT
	TRISC = 0b00000000;		// set PORTC as OUTPUT
	TRISD = 0b00000000;		// set PORTD as OUTPUT
    
    lcd_initialize();
    
    /*
     * RB2 - Main monitor state
     * RB3 - 2nd monitor state
     * RB1 - 2nd monitor pwr btn
     * RB4(out) - to 2nd monitor on/off input
     */
    
    int main_monitor_state = RB2;
    int last_main_monitor_state = RB2;
    
    int sec_monitor_state = RB3;
    int last_sec_monitor_state = RB3;
    
    int cur_sec_monitor_state = RB3;  // Stores current monitor state away from direct polling
    
    int buttonState = RB1;
    int lastbuttonState = RB1;
    
    lcd_home();
    lcd_putstr("boot");
            
    while(1)
    {
        //__delay_ms(150);
        
        // Button
        buttonState = RB1;
        if(buttonState != lastbuttonState)
        {
            if(buttonState == 0)
            {
                RB4 = 1;
                __delay_ms(250);
                RB4 = 0;
            }
        }

        // Sec Monitor detection
        sec_monitor_state = RB3;
        if(sec_monitor_state != last_sec_monitor_state)
        {
            cur_sec_monitor_state = sec_monitor_state;
        }
        last_sec_monitor_state = sec_monitor_state; 

        // Main Monitor detection
        main_monitor_state = RB2;
        if(main_monitor_state != last_main_monitor_state)
        {
            if(main_monitor_state == 1) 
            {
                if(cur_sec_monitor_state == 0)
                {
                    RB4 = 1;
                    __delay_ms(250);
                    RB4 = 0;
                }
            }
            else
            {
                if(cur_sec_monitor_state == 1)
                {
                    RB4 = 1;
                    __delay_ms(250);
                    RB4 = 0;
                }
            }
        }
        last_main_monitor_state = main_monitor_state; 
    }
}
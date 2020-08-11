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
	TRISB = 0b00000011;		// set PORTB<7:2> as OUTPUT . PORTB<1:0> as INPUT
	TRISC = 0b00000000;		// set PORTC as OUTPUT
	TRISD = 0b00000000;		// set PORTD as OUTPUT
    
    lcd_initialize();
    
    lcd_home();
    lcd_putstr("LAW://PWNRAZR");

    unsigned int buttonState = RB1;
    unsigned int lastButtonState = RB1;
    unsigned int state = 0;
    while(1)
    {
        buttonState = RB1;
        
        if(buttonState != lastButtonState)
        {
            if(buttonState == 0) {
                if(state == 0) {
                    RB3 = 1;
                    lcd_2ndline();
                    lcd_putstr("           ");
                    lcd_2ndline();
                    lcd_putstr("Monitor ON");
                } else if(state == 1) {
                    RB3 = 0;
                    lcd_2ndline();
                    lcd_putstr("Monitor OFF");
                }
                state = !state;
            }
        }
        lastButtonState = buttonState; 
    }
}

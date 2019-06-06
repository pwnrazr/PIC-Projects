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
#include "adc.h"
#include "pwm.h"

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
    adc_initialize();
    pwm_initialize();
    adc_on();
    
    unsigned int current = 0;
    unsigned int pwm = 0;

    PR2 = 0xFF;
    
    while(1)
    {
        current = (ui_adc_read() * 4.8);
        
        
        
        if(current > 144)
        {
            if(pwm = 0)
            {
            pwm_set_duty_cycle(pwm++);
            }
            else if(pwm > 0)
            {
                pwm_set_duty_cycle(pwm--);
            }
        }
        else if(current < 144)
        {
            if(pwm = 1023)
            {
            pwm_set_duty_cycle(pwm--);
            }
            else if(pwm < 1023)
            {
                pwm_set_duty_cycle(pwm++);
            }
        }
    }

}


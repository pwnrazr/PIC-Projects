/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#endif

#include "lcd.h"
#include "adc.h"

#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp */

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/

/* i.e. uint8_t <variable_name>; */

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/
void main(void) 
{
	PORTA = 0;				// Clear Port
	PORTB = 0;	
	PORTC = 0;
	PORTD = 0;
	
	TRISA = 0b11111111;		// set PORTA as INPUT
	TRISB = 0b00000011;		// set PORTB<7:2> as OUTPUT . PORTB<1:0> as INPUT
	TRISC = 0b00000000;		// set PORTC as OUTPUT
	TRISD = 0b00000000;		// set PORTD as OUTPUT

	//ANSELH = 0; 			// SET PORTB as DIGITAL I/O for PIC16F887
    
	lcd_initialize();		// Initialise LCD

	adc_initialize();		// Initialise ADC
	
	lcd_home();
	lcd_putstr("adc0:");		
    lcd_goto(0x40);
    lcd_putstr("adc1:");
    
    unsigned int adc_value = 0;
    
     /* Enable interrupts */
    TMR0IE=1; // timer int on
    GIE=1; // interrupts on
    OPTION_REG=0x04; // prescaler bits = 100
    //v_sys_flags=0;
    //v_led_ctr=0;
while (1)
	{
    
	adc_on();
    adc_value = ui_adc_read();
	lcd_goto(0x05);									
	lcd_bcd(4,adc_value);	
    }
}
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
    PORTE = 0;
	
	TRISA = 0b11111111;		// set PORTA as INPUT
	TRISB = 0b00000011;		// set PORTB<7:2> as OUTPUT . PORTB<1:0> as INPUT
	TRISC = 0b11111111;		// set PORTC as OUTPUT
	TRISD = 0b00000000;		// set PORTD as OUTPUT
    TRISE = 0b1111;
    
    lcd_initialize();
    
    /*
     * R/C = RC0
     * 
     * Status = RE2
     * DB0  = RA0
     * DB1  = RA1
     * DB2  = RA2
     * DB3  = RA3
     * DB4  = RA4
     * DB5  = RA5
     * DB6  = RC4
     * DB7  = RC5
     * DB8  = RC6
     * DB9  = RC7
     * DB10 = RC3
     * DB11 = RC2
     * 
     */
    while(1)
    {
        lcd_home();
        lcd_bcd(1,RE2);
        
        //Display OUTPUT
        lcd_goto(0x40);
        lcd_bcd(1,RC2);        
        lcd_goto(0x41);
        lcd_bcd(1,RC3);       
        lcd_goto(0x42);
        lcd_bcd(1,RC7);        
        lcd_goto(0x43);
        lcd_bcd(1,RC6);       
        lcd_goto(0x44);
        lcd_bcd(1,RC5);       
        lcd_goto(0x45);
        lcd_bcd(1,RC4);        
        lcd_goto(0x46);
        lcd_bcd(1,RA5);        
        lcd_goto(0x47);
        lcd_bcd(1,RA4);       
        lcd_goto(0x48);
        lcd_bcd(1,RA3);        
        lcd_goto(0x49);
        lcd_bcd(1,RA2);        
        lcd_goto(0x50);
        lcd_bcd(1,RA1);
        lcd_goto(0x51);
        lcd_bcd(1,RA0);
    }

}


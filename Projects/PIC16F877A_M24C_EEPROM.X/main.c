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
//#include "adc.h"
#include "i2c.h"
#include "M24C04.h"

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp */

void main(void)
{
    /* Initialize I/O and Peripherls for application */
    InitApp();
    
    PORTA = 0;				// Clear Port
	PORTB = 0;	
	//PORTC = 0;
	PORTD = 0;
	
	TRISA = 0b11111111;		// set PORTA as INPUT
	TRISB = 0b00000011;		// set PORTB<7:2> as OUTPUT . PORTB<1:0> as INPUT
	//TRISC = 0b11111111;		// set PORTC as OUTPUT
	TRISD = 0b00000000;		// set PORTD as OUTPUT
    
    lcd_initialize();
    //adc_initialize();
    
    I2C_Master_Init(400000);      //Initialize I2C Master with 100KHz clock
    
    unsigned int add = 0;
    /*
    for(unsigned int i = 0; i < 512; i++)
    {
        romWrite(i, i);
    } 
    */
    
    while(1)
    {
        lcd_goto(0x00);
        lcd_bcd(3,romRead(169)); 
    }
}


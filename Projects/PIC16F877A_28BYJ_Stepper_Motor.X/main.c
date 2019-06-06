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

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp */

void Rotation0() //0 Degree
{
unsigned int i;
for(i=0;i<50;i++)
{
RC3 = 1;
__delay_us(800); // pulse of 800us
RC3 = 0;
__delay_us(19200);
}
}

void Rotation90() //90 Degree
{
unsigned int i;
for(i=0;i<50;i++)
{
RC3 = 1;
__delay_us(1500); // pulse of 1500us
RC3 = 0;
__delay_us(18500);
}
}

void Rotation180() //180 Degree

{
unsigned int i;
for(i=0;i<50;i++)
{
RC3 = 1;
//__delay_us(2200); // pulse of 2200us
__delay_us(2350);
RC3 = 0;
__delay_us(17800);
}
}

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

    /*
     * 1N = RC7
     * 2N = RC6
     * 3N = RC5
     * 4N = RC4
     */
    //unsigned int 
    
     //int x = 125;

    while(1)
    {
        Rotation0(); //0 Degree
        __delay_ms(1000);

        //Rotation90(); //90 Degree
        //__delay_ms(1000);
        
        Rotation180(); //180 Degree
        __delay_ms(1000);

    }

}


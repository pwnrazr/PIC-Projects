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

void shiftOut(uint8_t bitOrder, uint16_t val)
{
    int i;
    for(i = 0; i < 16; i++)  //8 or 16 bits
    {     
        //LSBFIRST = 1
        //MSBFIRST = 0
        if (bitOrder == 0)
        {
            RA0 =  !!(val & (1 << i));  //MSBFIRST
        }
        else      
        {
            RA0 = !!(val & (1 << (15 - i))); //7/15 for 8/16 bits /LSBFIRST
        }     
        
        RE1 = 1;
        RE1 = 0;
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
    PORTE = 0;
	
	TRISA = 0b00000000;		// set PORTA as INPUT
	TRISB = 0b00000011;		// set PORTB<7:2> as OUTPUT . PORTB<1:0> as INPUT
	TRISC = 0b11111111;		// set PORTC as OUTPUT
	TRISD = 0b00000000;		// set PORTD as OUTPUT
    TRISE = 0b0000;
    
    lcd_initialize();
    
    /* pin assignment list
     * _OE_13         = LOW
     * SER_14         = RA0
     * _SRCLR_10      = HIGH
     * SRCLK_11       = RE1
     * RCLK_12 latch  = RE2 
     * 
     * Qa = RC0
     * Qb = RC1
     * Qc = RC2
     * Qd = RC3
     * Qe = RC4
     * Qf = RC5
     * Qg = RC6
     * Qh = RC7
     * 
     * LSB starts on Qa
     */
    uint16_t dataArray[31];
    uint16_t dataSend;
    
    dataArray[0] = 0b0000000000000000;
    dataArray[1] = 0b1000000000000000;
    dataArray[2] = 0b1100000000000000;
    dataArray[3] = 0b1110000000000000;
    dataArray[4] = 0b1111000000000000;
    dataArray[5] = 0b0111100000000000;
    dataArray[6] = 0b0011110000000000;
    dataArray[7] = 0b0001111000000000;
    dataArray[8] = 0b0000111100000000;
    dataArray[9] = 0b0000011110000000;
    dataArray[10] = 0b0000001111000000;
    dataArray[11] = 0b0000000111100000;
    dataArray[12] = 0b0000000011110000;
    dataArray[13] = 0b0000000001111000;
    dataArray[14] = 0b0000000000111100;
    dataArray[15] = 0b0000000000011110;
    dataArray[16] = 0b0000000000001111;
    dataArray[17] = 0b0000000000000111;
    dataArray[18] = 0b0000000000000011;
    dataArray[19] = 0b0000000000000001;
    
    unsigned int j;

    while(1)
    {    
    LED1=0;
    
    lcd_home();
    
    for (j = 0; j < 19; j++)
    {
        dataSend = dataArray[j];
        RE2=0;
        shiftOut(1, dataSend);
        RE2=1;
        __delay_ms(50);
    }
    for (j = 19; j > 0; j--)
    {
        dataSend = dataArray[j];
        RE2=0;
        shiftOut(1, dataSend);
        RE2=1;
        __delay_ms(50);
    }
    LED1=1;
    }
}
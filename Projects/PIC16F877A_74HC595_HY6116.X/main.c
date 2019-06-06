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
        __delay_us(200);
        RE1 = 0;
        __delay_us(200);
    } 
}

void SRAMinit()
{
    RA1 = 0; //WE
    RA2 = 0; //OE
    RA3 = 1; //CS
}
uint8_t SRAMread(uint16_t address)
{
    uint8_t dataRecv;
    
    TRISC = 0b11111111; //set PORTC as Input
    PORTC = 0;
    __delay_us(200);
    RE2 = 0; //shift register latch
    shiftOut(1, address);
    RE2 = 1; //shift register latch
    __delay_us(200);
    RA1 = 1; //WE
    RA2 = 0; //OE
    RA3 = 0; //CS
    __delay_us(200);
    
    dataRecv = PORTC;
    return dataRecv;
    PORTC = 0;
}

void SRAMwrite(uint16_t address, uint8_t dataSend)
{
    TRISC = 0b00000000; //set PORTC as Output
    PORTC = 0;
    __delay_us(200);
    RE2 = 0; //shift register latch
    shiftOut(1, address);
    RE2 = 1; //shift register latch
    __delay_us(200);
    
    
    PORTC = dataSend;
    RA1 = 0; //WE
    //RA2 = 1; //OE
    RA3 = 0; //CS
    __delay_us(200);
    RA1 = 1; //WE
    //RA2 = 1; //OE
    RA3 = 1; //CS
    __delay_us(200);
    //PORTC = 0;
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
	TRISC = 0b11111111;		// set PORTC as input
	TRISD = 0b00000000;		// set PORTD as OUTPUT
    TRISE = 0b0000;
    
    lcd_initialize();
    
    /* pin assignment list Shift Registers x2
     * _OE_13         = LOW
     * SER_14         = RA0
     * _SRCLR_10      = HIGH
     * SRCLK_11       = RE1
     * RCLK_12 latch  = RE2 
     * 
     * LSB starts on Qa
     * 
     * HY6116
     * 
     * IO1 = RC0
     * IO2 = RC1
     * ...
     * 
     * Qa to A0
     * Qb to A1
     * ...
     * 
     * _WE = RA1
     * _OE = RA2
     * _CS = RA3
     * 
     * Write begin
     * LOW CS and LOW WE
     * 
     * Write end
     * HIGH CS and HIGH WE
     * 
     * Read
     * WE HIGH
     * CS LOW
     * OE LOW
     */
    
    //uint16_t dataSend;
    
    unsigned int j;
    uint8_t add = 69;
    SRAMinit();
    //uint8_t dataRecv;
    
    //add = SRAMread(50);
    while(1)
    {    
        add = SRAMread(50);
        lcd_home();
        lcd_bcd(5,PORTC);
        add++;
        SRAMwrite(8, add);
        PORTC = 0;
    
    }
}
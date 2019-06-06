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
	
	//TRISA = 0b11111111;		// set PORTA as INPUT
    TRISA = 0b00000000;
	//TRISB = 0b00000011;		// set PORTB<7:2> as OUTPUT . PORTB<1:0> as INPUT
    TRISB = 0b11001111; //all input 
	//TRISC = 0b00000000;		// set PORTC as OUTPUT
    TRISC = 0b00011000;
	TRISD = 0b00000000;		// set PORTD as OUTPUT !LCD!
    TRISE = 0b00000000;
    
    lcd_initialize();

    /*
     * RC7 = WE
     * RC6 = OE
     * RC5 = CS
     * 
     * RB7 = I/O 8
     * RB6 = I/O 7
     * RC4 = I/O 6
     * RC3 = I/O 5
     * RB3 = I/O 4
     * RB2 = I/O 3
     * RC0 = I/O 2
     * RB0 = I/O 1
     * 
     * 
     * 
     
    
        RA0  = A0
        RA1  = A1
        RA2  = A2
        RA3  = A3
        RA4  = A4
        RA5  = A5
        RE0  = A6
        RE1  = A7
        RE2  = A8
        RC1  = A9
        RC2  = A10
     */
                
        #define A0 RA0
        #define A1 RA1
        #define A2 RA2
        #define A3 RA3
        #define A4 RA4
        #define A5 RA5
        #define A6 RE0
        #define A7 RE1
        #define A8 RE2
        #define A9 RC1
        #define A10 RC2

        unsigned int IO1 = 0,IO2 = 0,IO3 = 0,IO4 = 0,IO5 = 0,IO6 = 0,IO7 = 0,IO8 = 0;
        
    while(1)
    {
        lcd_home();
        lcd_putstr("Writing");
        //READ
        RC5=0;  //Chip Select
        RC7=1;  //Write Enable
        RC6=0;  //Output Enable
        //ADDRESS SELECT
        A0 = 1;
        A1 = 0;
        A2 = 0;
        A3 = 0;
        A4 = 0;
        A5 = 0;
        A6 = 0;
        A7 = 0;
        A8 = 0;
        A9 = 1;
        A10 = 0;
        
        //Start of write
        
        TRISB = 0b00000000;
        TRISC = 0b00100000;
        
        //Data to write
        RB7=0;
        RB6=0;
        RC4=1;
        RC3=0;
        RB3=1;
        RB2=0;
        RC0=1;
        RB0=0;
        
        //WRITE
        RC5=0;  //Chip Select
        RC7=0;  //Write Enable
        RC6=1;  //Output Enable
        
        __delay_ms(500);
        //stop write
        RC5=1;  //Chip Select
        RC7=1;  //Write Enable
        RC6=0;  //Output Enable
        __delay_ms(250);
        RB7=0;
        RB6=0;
        RC4=0;
        RC3=0;
        RB3=0;
        RB2=0;
        RC0=0;
        RB0=0;
        __delay_ms(2500);
        lcd_home();
        lcd_putstr("Reading");
        
        lcd_home();
        
        TRISB = 0b11001111;
        TRISC = 0b00011001;
        
        //READ start
        RC5=0;  //Chip Select
        RC7=1;  //Write Enable
        RC6=0;  //Output Enable
        
        lcd_goto(0x40);
        lcd_bcd(1,RB7);
        
        lcd_goto(0x41);
        lcd_bcd(1,RB6);
        
        lcd_goto(0x42);
        lcd_bcd(1,RC4);
        
        lcd_goto(0x43);
        lcd_bcd(1,RC3);
        
        lcd_goto(0x44);
        lcd_bcd(1,RB3);
        
        lcd_goto(0x45);
        lcd_bcd(1,RB2);
        
        lcd_goto(0x46);
        lcd_bcd(1,RC0);
        
        lcd_goto(0x47);
        lcd_bcd(1,RB0);
        
        __delay_ms(5250);
    }

}


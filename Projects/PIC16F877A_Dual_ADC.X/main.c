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
#include "LCD_LIB.h"

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
    
    //lcd_initialize();
    adc_initialize();
    
    unsigned int adc_value_1 = 0;
    unsigned int data;
    unsigned int lastButtonState = 1;
    unsigned int buttonState = 0;
      
    adc_on();
    
    //lcd_goto(0x3);
    //lcd_putstr("C");
           
    //INTERRUPT Timer 1
    
    TMR1IE = 1;
    
    T1CKPS0 = 1;
    T1CKPS1 = 1;
    
    GIE = 1;
    PEIE=1;
    TMR1H=0x0B;     // Load the time value(0xBDC) for 100ms delay
    TMR1L=0xDC;
    TMR1ON = 1; 
    
    TMR0=100;       // Load the time value for 1ms delay
    TMR0IE=1;
    PS2 = 1;
    
    //read EEPROM
    EEADR = 0x0;
    EEPGD = 0;
    RD = 1;
    data = (EEDATA << 8);
    
    EEADR = 0x1;
    EEPGD = 0;
    RD = 1;
    data = data + EEDATA;

    pwm_initialize();
    
    
    unsigned int i = 0;
    while(1)
    {    
        buttonState = RB1;

    if (buttonState != lastButtonState) 
        {
        if (buttonState == 0 & WR==0) 
        {   
        data = data + 1000;
        
        //write high bits to EEPROM
        EEADR = 0x0; //High bits address
        EEDATA = (data >> 8); //Bit shift
        EEPGD = 0;
        WREN = 1;
        GIE = 0;
        EECON2 = 0b01010101;
        EECON2 = 0b10101010;
        WR = 1;
        while(WR==1); //wait until write is done
        GIE = 1;
        WREN = 0;
        
        //write low bits to EEPROM
        EEADR = 0x1; //Low bits address
        EEDATA = data;
        EEPGD = 0;
        WREN = 1;
        GIE = 0;
        EECON2 = 0b01010101;
        EECON2 = 0b10101010;
        WR = 1;
        while(WR==1);
        GIE = 1;
        WREN = 0; 
        }
        }
        lastButtonState = buttonState;
        
        //lcd_goto(0x40);
        //lcd_bcd(5,data);
        
        //Channel l ADC READ
        CHS2 = 0;			
		CHS1 = 0;				
		CHS0 = 0;
        adc_value_1 = ui_adc_read();
        
        adc_value_1 = adc_value_1 / 2;
        
            //lcd_goto(0x00);
            //lcd_bcd(3,adc_value_1);
            
        if(adc_value_1>=30)
        {
            LED1=1;
        }
        else if(adc_value_1<=29)
        {
            LED1=0; 
            LCD_SEND_STRING(ayam);
        }              
    }
}
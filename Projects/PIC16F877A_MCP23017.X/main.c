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

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp */

void extGPIOAdir(unsigned short a)
{
    I2C_Master_Start();
    I2C_Master_Write(0b01000000); //OPCODE WRITE
    I2C_Master_Write(0x00); //Register Address IODIRA
    I2C_Master_Write(a); //PORTA Direction
    I2C_Master_Stop(); 
}

void extGPIOA(unsigned short a)
{
    I2C_Master_Start();
    I2C_Master_Write(0b01000000); //OPCODE WRITE
    I2C_Master_Write(0x09); //Register Address GPIOA
    I2C_Master_Write(a); //PORTA Output
    I2C_Master_Stop();
}

void main(void)
{
    /* Initialize I/O and Peripherals for application */
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

    //MCP23017 IOCON
    I2C_Master_Start();
    I2C_Master_Write(0b01000000); //OPCODE WRITE
    I2C_Master_Write(0x0A); //Register Address IOCON
    I2C_Master_Write(0b11101000); 
    I2C_Master_Stop();
    
    extGPIOAdir(0x0);   
    
    short Array[8];
    
    Array[0] = 0b00000001;
    Array[1] = 0b00000010;
    Array[2] = 0b00000100;
    Array[3] = 0b00001000;
    Array[4] = 0b00010000;
    Array[5] = 0b00100000;
    Array[6] = 0b01000000;
    Array[7] = 0b10000000;
    
    int add = 0;
    
    while(1)
    {
        add++;
        for(int i = 0; i <= 7; i++)
        {
            extGPIOA(Array[i]);
            __delay_ms(10);
        }
        for(int i = 7; i >= 0; i--)
        {
            extGPIOA(Array[i]);
            __delay_ms(10);
        }
        
        lcd_goto(0x0);
        lcd_putstr("add:");
        lcd_goto(0x04);
        lcd_bcd(5, add);
    }
}


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
#include "i2c.h"

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
    I2C_Master_Init(400000);      //Initialize I2C Master with 100KHz clock
    
    short add1;
    short add2;
    
    lcd_goto(0x0);
    lcd_putstr("i2c MASTER");
    
    while(1)
    {
        I2C_Master_Start();         //Start condition
        I2C_Master_Write(0x30);
        I2C_Master_Write(1);
        I2C_Master_Stop();
        
        I2C_Master_Start();         //Start condition
        I2C_Master_Write(0x31);     //7 bit address + Read
        add1 = I2C_Master_Read(0); //Read + Acknowledge
        I2C_Master_Stop();          //Stop condition
        
        I2C_Master_Start();         //Start condition
        I2C_Master_Write(0x30);
        I2C_Master_Write(2);
        I2C_Master_Stop();
        
        I2C_Master_Start();         //Start condition
        I2C_Master_Write(0x31);     //7 bit address + Read
        add2 = I2C_Master_Read(0); //Read + Acknowledge
        I2C_Master_Stop();          //Stop condition
        
        lcd_goto(0x40);
        lcd_bcd(3, add1);
        lcd_goto(0x45);
        lcd_bcd(3, add2);
        
        I2C_Master_Start();         //Start condition
        I2C_Master_Write(0x30);
        I2C_Master_Write(3);
        I2C_Master_Stop();
    }
}


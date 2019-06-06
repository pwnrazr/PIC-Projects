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

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp */

#include "lcd.h"
#include "adc.h"
/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/
void main(void)
{
    InitApp();
    
    PORTA = 0;
    PORTB = 0;
    PORTC = 0;
    PORTD = 0;
    PORTE = 0;
    
    TRISA = 0b11111111;
    TRISB = 0b00000011;
    TRISC = 0b00000000;
    TRISD = 0b00000000;
    TRISE = 0b00000000;
    
    lcd_initialize();

    RB6=0;
    RB7=0;
    
    int menu = 0;
    
    int buttonState = 0;         
    int lastButtonState = 0;
    
    int buttonState1 = 0;         
    int lastButtonState1 = 0;
    
    while(1)
    {
        buttonState = RB1;
        buttonState1 = RB0;
        
        if(menu==2)
        {
            menu = 0;
        }
        
        if (buttonState != lastButtonState) 
        {
        if (buttonState == 0) 
        {  
            menu++;
        }
        }
        lastButtonState = buttonState;
        
        if (buttonState1 != lastButtonState1) 
        {
        if (buttonState1 == 0) 
        {  
            if(menu==0)
            {
                if(RB6==1)
                {
                    RB6=0;
                }
                else if(RB6==0)
                {
                    RB6=1;
                }
            }
            if(menu==1)
            {
                if(RB7==1)
                {
                    RB7=0;
                }
                else if(RB7==0)
                {
                    RB7=1;
                }
            }
        }
        }
        lastButtonState1 = buttonState1;
        
        switch(menu)
        {
            case 0:
            {
                lcd_home();
                lcd_clear();
                lcd_putstr("LED1:");
                if(RB6==1)
                {
                    lcd_goto(0x05);
                    lcd_putstr("ON");
                }
                else if(RB6==0)
                {
                    lcd_goto(0x05);
                    lcd_putstr("OFF");
                }
                break;
            }
            case 1:
            {
                lcd_home();
                lcd_clear();
                lcd_putstr("LED2:");
                if(RB7==1)
                {
                    lcd_goto(0x05);
                    lcd_putstr("ON");
                }
                else if(RB7==0)
                {
                    lcd_goto(0x05);
                    lcd_putstr("OFF");
                }
                break;
            }
           
        }
                
    }
}



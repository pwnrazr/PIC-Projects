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


/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/

/* i.e. uint8_t <variable_name>; */

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/
void main(void)
{
    
    PORTA = 0;
    PORTB = 0;
    PORTC = 0;
    PORTD = 0;
    
    TRISA = 0b00000000;
    TRISB = 0b00000011;
    TRISC = 0b00000000;
    TRISD = 0b00000000;

    /* Initialize I/O and Peripherals for application */
    InitApp();
    
    unsigned int count = 0;
    unsigned int time = 0;
    int menu = 0;
    int button1 = 0,lastbutton1 = 1;
    int button2 = 0,lastbutton2 = 1;
    
    lcd_initialize();
    lcd_home();
    lcd_putstr("Booting...");
    //__delay_ms(500);
    lcd_clear();

    //test
    
    while(1)
    {  
       
        
        count++;
        button1 = RB0;
        button2 = RB1;
        if(menu==3)
        {
            lcd_clear();
            menu=0;
        }
        
        if(lastbutton1!=button1)
        {
            if(button1==0)
            {
                lcd_clear();
                menu = menu + 1;
            }
        }
        lastbutton1 = button1;
        
            
        switch(menu)
        {
            case 0:                
                lcd_goto(0x0);
                lcd_putstr("Count:");
                lcd_goto(0x6);
                lcd_bcd(3,count);
                lcd_goto(0x40);
                lcd_putstr("Time:");
                lcd_goto(0x45);
                lcd_bcd(5,time);
                break;
            case 1:
                if(RB6==1)
                {
                    lcd_goto(0x0);
                    lcd_putstr("LED1:ON");
                }
                else if(RB6==0)
                {
                    lcd_goto(0x0);
                    lcd_putstr("LED1:OFF");
                }
                if(lastbutton2!=button2)
                {
                if(button2==0)
                {
                    if(RB6==1)
                    {
                        lcd_clear();
                        lcd_goto(0x0);
                        lcd_putstr("LED1:OFF");
                        RB6=0;
                    }
                    else if(RB6==0)
                    {
                        lcd_clear();
                        lcd_goto(0x0);
                        lcd_putstr("LED1:ON");
                        RB6=1;
                    }
                }
        }
                    lastbutton2 = button2;
                break;
                
                case 2:
                if(RB7==1)
                {
                    lcd_goto(0x0);
                    lcd_putstr("LED2:ON");
                }
                else if(RB7==0)
                {
                    lcd_goto(0x0);
                    lcd_putstr("LED2:OFF");
                }
                if(lastbutton2!=button2)
                {
                if(button2==0)
                {
                    if(RB7==1)
                    {
                        lcd_clear();
                        lcd_goto(0x0);
                        lcd_putstr("LED2:OFF");
                        RB7=0;
                    }
                    else if(RB7==0)
                    {
                        lcd_clear();
                        lcd_goto(0x0);
                        lcd_putstr("LED2:ON");
                        RB7=1;
                    }
                }
        }
                    lastbutton2 = button2;
                break;
        }

        time++;
        
    }

}


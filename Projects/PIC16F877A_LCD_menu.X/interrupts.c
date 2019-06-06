/******************************************************************************/
/*Files to Include                                                            */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#endif

#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */
#include "system.h"
#include "lcd.h"

uint32_t millis = 0;

int current;         
long millis_held;    
long secs_held;      
long prev_secs_held; 
char previous = 1;
unsigned long firstTime; 

int buttonState1 = 0;         
int lastButtonState1 = 0;  

unsigned int time1 = 0;
unsigned int menu = 0;
unsigned int menusel = 0;

void interrupt isr(void)
{
    if(TMR0IF==1) //Begin TMR0
    {
        millis++;
        time1++;
        //begin button recognition function
        
        current = RB1;

        if (current == 0 && previous == 1 && (millis - firstTime) > 200)
        {
            firstTime = millis;
        }

            millis_held = (millis - firstTime);
            secs_held = millis_held / 1000;

        if (millis_held > 50) //debounce
        {
            if (current == 1 && previous == 0) 
            {
                if (secs_held <= 0) //short press
                {
                        menu++;
                        lcd_clear();
                        if(menu == 3)
                        {
                            menu = 0;
                        }
                }

                if (secs_held >= 1) //1 second long press
                {
                    menusel = 1;
                }
            }
        }
        previous = current;
        prev_secs_held = secs_held;
        
        //END button recognition function
        
        if(time1 > 500) //BEGIN menu function
        {
            switch(menu)
            {
                case 0:
                    lcd_goto(0x0);
                    lcd_putstr("LED 1");
                    if(menusel == 1)
                    {
                        RB6 = !RB6;
                        menusel = 0;
                    }
                    break;
                
                case 1:
                    lcd_goto(0x0);
                    lcd_putstr("LED 2");
                    if(menusel == 1)
                    {
                        RB7 = !RB7;
                        menusel = 0;
                    }
                    break;
                    
                case 2:
                    lcd_goto(0x0);
                    lcd_putstr("Last menu");
                    if(menusel == 1)
                    {
                        menusel = 0;
                    }
                    break;
            }
            time1 = 0;
        }//END menu function
    }//END TMR0
}



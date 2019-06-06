/* 
 * File:   LCD_LIB.h
 * Author: James Gibbard
 * Description: Display library for operating 16x2 Hitachi HD44780 type displays
 * Created on 24 April 2013, 15:23
 */
#define _XTAL_FREQ 20000000

//Define pins used by LCD
#define LCD_RS PORTCbits.RC6    //Define Register select pin RS = 0 = command, RS = 1 = data
#define LCD_RW PORTCbits.RC7    //Define Read / Write pin. Write = 0, read =1
#define LCD_E PORTCbits.RC1     //Define enable pin, falling edge triggered
#define LCD_DATA PORTB          //Define data port
#define LCD_DATA_TRIS TRISB     //Define data port I/O
#define LCD_CONTROL_TRIS TRISC  //Define control port I/O

//Define  variables
#define LCD_LINE2  0b11000000
#define SHIFT_RIGHT 0b00000100
#define SHIFT_LEFT 0b00000000

//Function prototypes
void LCD_ENABLE(void);                  //Sends an enable pulse. Sets E high for 1us
char LCD_BUSY(void);                     //Checks busy flag. Returns 1 for bust. 0 for ready
void LCD_SEND_CMD(unsigned char);       //Sends a command to the LCD
void LCD_SEND_DATA(unsigned char);      //Sends data to the LCD
void LCD_INIT(void);                    //Initialises the LCD
void LCD_SEND_STRING(const char *var);  //Sends a string to the LCD
void LCD_SEND_NUM(unsigned char);       //Displays an 8bit number as a decimal number on the LCD
void LCD_SET_CURSOR(unsigned char, unsigned char);  //Sets the cursor position (Row 1-2, Column 1-40)
void LCD_HOME(void);                    //Sets DRAM to address 0, and returns display from being shifted
void LCD_CLEAR(void);                   //Clears all DRAM, sets DRAM address to 0
void LCD_CURSOR_SHIFT(unsigned char);   //Shifts cursor, SHIFT_LEFT shifts left, SHIFT_RIGHT shifts right
void LCD_SCREEN_SHIFT(unsigned char);   //Shifts screen, SHIFT_LEFT shifts left, SHIFT_RIGHT shifts right
void LCD_NEW_CHAR(unsigned char,unsigned char,unsigned char,unsigned char,unsigned char,unsigned char,unsigned char,unsigned char, unsigned char);
//^Saves a new character in the LCD's CGROM

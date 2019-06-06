/* 
 * File:   LCD_LIB.c
 * Author: James Gibbard
 * Description: Display library for operating 16x2 Hitachi HD44780 type displays
 * Created on 24 April 2013, 15:23
 */

#include <xc.h>
#include "LCD_LIB.h"
#include <stdio.h>

void LCD_ENABLE (void)
{
    LCD_E = 1;      //Set enable line high
    __delay_us(1);  //Wait 1us
    LCD_E = 0;      //Set enable line low
}

char LCD_BUSY(void)   //Returns 1 if busy, 0 if ready
{
    unsigned char LCD_READ_VAL;

    LCD_DATA_TRIS = 0b11111111; //Set data lines as input
    LCD_RW =  1;                //1 = Read data
    LCD_RS = 0;                 //0 = command, 1 = data
    LCD_E = 1;                  //Pulse the enable line for 1us
    __delay_us(1);
    LCD_READ_VAL = LCD_DATA;  //Read data from LCD
    LCD_E = 0;
    LCD_DATA_TRIS = 0;          //Set data lines as outputs

    LCD_READ_VAL = LCD_READ_VAL & 0b10000000;
    if(LCD_READ_VAL == 0b10000000)			//If MSB = 1 then return 1, else return 0
    {
        return 1;   //If busy return 1
    }
    else
    {
        return 0;   //else return 0
    }

}

void LCD_SEND_CMD (unsigned char CMD)
{
   while(LCD_BUSY() == 1);  //loop until LCD ready
   LCD_DATA_TRIS = 0;       //Set data lines as inputs
   LCD_RW = 0;              //Set to write mode
   LCD_RS = 0;              //0 = command, 1 = data
   LCD_DATA = CMD;          //set data lines to CMD
   LCD_ENABLE();            //Pulse the enable for 1 us
}

void LCD_SEND_DATA (unsigned char data)
{
    while(LCD_BUSY() == 1);     //wait until LCD is not busy
    LCD_DATA_TRIS = 0;          //Set data lines to inputs
    LCD_RW = 0;                 //Set to write mode
    LCD_RS = 1;                 //Set to data mode
    LCD_DATA = data;            //Set data lines to data
    LCD_ENABLE();               //Pulse the enable line for 1us

}

void LCD_INIT(void)
{
    LCD_DATA_TRIS = 0;      //Set data lines to outputs
    LCD_CONTROL_TRIS = 0;   //Set control lines to outputs
    LCD_DATA = 0;           //Clear the data lines
    LCD_E = 0;              //Clear the enable line
    LCD_RW = 0;             //Clear the R/W line
    LCD_RS = 0;             //Clear the RS line
    __delay_ms(100);        //Wait for the display to power up

    LCD_CLEAR();                      //Clear the display
    
    //Set display settings
    LCD_SEND_CMD(0b00000110);         //Set cursor to inc, display shift off
    //0b 000001 ID S. ID 1 = inc address (cursor goes right), ID 0 = dec address (cursor goes left). S 1 = shift, 0 = no shift

    LCD_SEND_CMD(0b00111000);         //Set display type to 8 wire connection, dual line mode, 5x8 dots
    //0b 0 0 1 DL N F x x.   DL 1 = 8 wires, 0 = 4 wires. N 1 = 2 line display. 0 = 1 line display. F 1 = 5x10 dots, 0 = 5x8 dots

    LCD_SEND_CMD(0b00001100);         //Turn on display, turn off cursor, turn off blink
    //0b00001 D C B. D = Display, C = Cursor, B = Blink. 1= ON 0 = OFF
}

void LCD_SEND_STRING(const char *var)
{
    while(*var)         //While *var =/= 0 send *var and inc to next char
    {
        LCD_SEND_DATA(*var++);
    }
}

void LCD_SEND_NUM(unsigned char val)
{
    char num[4];                //Create a 4 long array of chars to store the 3 digit values + null terminator
    sprintf(num, "%d",val);     //Print val in decimal format to string called num
    LCD_SEND_STRING(num);       //Send string to LCD
}

void LCD_NEW_CHAR(unsigned char address, unsigned char line0, unsigned char line1, unsigned char line2, unsigned char line3, unsigned char line4, unsigned char line5, unsigned char line6, unsigned char line7)
{

    LCD_SEND_CMD(0x40 + address);       //Set address to CGRAM. CHAR0 is at 0x40, CHAR1 is at 0x48, CHAR2 is at 0x56, etc. 8 CHARS can be stored
    LCD_SEND_DATA(line0);               //Send line one of char 0bXXX11111. 3MSBs are ignored
    LCD_SEND_DATA(line1);               //Send line two of char 0bXXX11111. 3MSBs are ignored
    LCD_SEND_DATA(line2);               //etc
    LCD_SEND_DATA(line3);
    LCD_SEND_DATA(line4);
    LCD_SEND_DATA(line5);
    LCD_SEND_DATA(line6);
    LCD_SEND_DATA(line7);
    LCD_SEND_CMD(0b10000000);           //Set address back to DRAM, location 1,1

}

void LCD_SET_CURSOR(unsigned char row, unsigned char column)
{

    if (row == 1)        //If row 1
    {
        LCD_SEND_CMD(0b10000000 + (column-1));      //set DRAM address 0b1xxxxxxx = row 1, 0b10000000 = Row 1 column 1, 0b10000001 = row 1, column 2, etc
    }
    else if (row==2)    //If row 2
    {
        LCD_SEND_CMD(0b11000000 + (column-1));      ////set DRAM address 0b11xxxxxx = row 2
    }
}

void LCD_HOME(void)
{
    LCD_SEND_CMD(0b00000010);       //Sets DRAM to address 0, and returns display from being shifted
}

void LCD_CLEAR(void)
{
    LCD_SEND_CMD(0b00000001);       //Clears all DRAM, sets DRAM address to 0
}

void LCD_CURSOR_SHIFT(unsigned char direction)
{
    LCD_SEND_CMD(0b00010000 | direction);   //Sends command to shift cursor
}                                           //Bit 2 = 0 = Shift right. //Bit 2 = 1 = Shift left

void LCD_SCREEN_SHIFT(unsigned char direction)
{
    LCD_SEND_CMD(0b00011000 | direction);    //Sends command to shift display
}                                            //Bit 2 = 0 = Shift right. //Bit 2 = 1 = Shift left
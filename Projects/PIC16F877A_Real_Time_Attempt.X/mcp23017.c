#include "i2c.h"

void mcp_init()
{
    I2C_Master_Init(400000);      //Initialize I2C Master with 100KHz clock

    //MCP23017 IOCON
    I2C_Master_Start();
    I2C_Master_Write(0b01000000); //OPCODE WRITE
    I2C_Master_Write(0x0A); //Register Address IOCON
    I2C_Master_Write(0b11101000); 
    I2C_Master_Stop();
    
    
}

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
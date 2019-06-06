#include <xc.h>
#include "system.h"
#include "M24C04.h"
#include "i2c.h"

void romWrite(unsigned short addr, unsigned char data)
{
    unsigned char addrLSB = 0;
    unsigned char opcode;
    
    if(addr >= 256 && addr <= 511)
    {
        opcode = 0b10100010; //Write A8 = 1
        addrLSB = (addr - 256);
    }
    else if(addr <= 255 && addr >= 0)
    {
        opcode = 0b10100000; //Write A8 = 0
        addrLSB = addr;
    }
    
    I2C_Master_Start();         //Start condition
    I2C_Master_Write(opcode);    //WRITE opcode
    I2C_Master_Write(addrLSB); //address
    I2C_Master_Write(data); //WRITE data
    I2C_Master_Stop();
    __delay_ms(3);
}

unsigned short romRead(unsigned short addr)
{
    unsigned char addrLSB = 0;
    unsigned char opcode;
    unsigned char opcodeRead;
    unsigned char temp;
    
    if(addr >= 256 && addr <= 511)
    {
        opcode = 0b10100010; //Write A8 = 1
        opcodeRead = 0b10100011; //Read A8 = 1
        addrLSB = (addr - 256);
    }
    else if(addr <= 255 && addr >= 0)
    {
        opcode = 0b10100000; //Write A8 = 0
        opcodeRead = 0b10100001; //Read A8 = 0
        addrLSB = addr;
    }
    
    I2C_Master_Start();         //Start condition
    I2C_Master_Write(opcode);    //WRITE opcode
    I2C_Master_Write(addrLSB); //address
    I2C_Master_Stop();
    
    I2C_Master_Start();         //read from address
    I2C_Master_Write(opcodeRead);    //READ Opcode    
    temp = I2C_Master_Read(0); // 0 = ACK
    I2C_Master_Stop();
    return temp;
}


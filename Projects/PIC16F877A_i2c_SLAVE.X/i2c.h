/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef _i2c_H
#define	_i2c_H

extern void I2C_Master_Init(const unsigned long c);

extern void I2C_Slave_Init(short address); 

extern void I2C_Master_Wait();

extern void I2C_Master_Start();

extern void I2C_Master_RepeatedStart();

extern void I2C_Master_Stop();

extern void I2C_Master_Write(unsigned d);

extern unsigned short I2C_Master_Read(unsigned short a);

#endif	/* XC_HEADER_TEMPLATE_H */


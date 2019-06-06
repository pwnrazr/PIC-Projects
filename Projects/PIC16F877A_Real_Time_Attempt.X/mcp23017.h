
// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef _mcp23017_H
#define	_mcp23017_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include "i2c.h"

extern void mcp_init();


extern void extGPIOAdir(unsigned short a);

extern void extGPIOA(unsigned short a);

#endif	/* XC_HEADER_TEMPLATE_H */


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

unsigned int addr = 0;

void interrupt isr(void)
{
   
if(SSPIF == 1)
  {
    if(SSPSTATbits.R_nW)                // Master read (R_nW = 1)
        { 
            if(!SSPSTATbits.D_nA)         // last byte was an address (D_nA = 0)
            {
                junk = SSPBUF;                  // dummy read to clear BF bit
                switch(addr)
                {
                    case 1:
                        SSPBUF = 69;   //Return 3 to master
                        access++;
                        break;
                    case 2:
                        SSPBUF = temperature;  //return rising number to master
                        access++;
                        break;
                }
                
                if(SSPCONbits.SSPOV)		// Did a read collision occur?
				{
                    SSPCONbits.SSPOV = 0;       // clear SSPOV bit
                    junk = SSPBUF;              // clear SSPBUF
				}
                SSPCONbits.CKP = 1;        // release CLK
            } 
        }
    
    if(!SSPSTATbits.R_nW)			// master write (R_nW = 0)
        {
            if(!SSPSTATbits.D_nA)        // last byte was an address (D_nA = 0)
            {
                junk = SSPBUF;			// read buffer to clear BF
				SSPCONbits.CKP = 1;            // release CLK
            }
            if(SSPSTATbits.D_nA)                // last byte was data (D_nA = 1)
            {
            	switch(SSPBUF)
                {
                    case 1:
                        addr = 1; //fixed number 69
                        break;
                    case 2:
                        addr = 2;  //Rising number
                        break;
                    case 0xFF: //toggle LED
                        RC7=!RC7;
                        access++;
                        break;
                    //default:
                        //junk = SSPBUF;
                        //access++;
                        //break;
                }
                
				if(SSPCONbits.WCOL)		// Did a write collision occur?
				{
                    SSPCONbits.WCOL = 0;       // clear WCOL bit
                    junk = SSPBUF;              // clear SSPBUF
				}
				SSPCONbits.CKP = 1;    		// release CLK
            }
    	}
    SSPIF = 0;
  }

}



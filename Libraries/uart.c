/*******************************************************************************
* This file provides the functions for the UART module 
*
* Cytron Technologies Sdn. Bhd.
*******************************************************************************/



#include <htc.h>
#include "system.h"
#include "uart.h"



/*******************************************************************************
* PUBLIC FUNCTION: uart_initialize
*
* PARAMETERS:
* ~ void
*
* RETURN:
* ~ void
*
* DESCRIPTIONS:
* Initialize the UART module.
*
*******************************************************************************/
char uart_init(const long int baudrate)
{
  unsigned int x;
  x = (_XTAL_FREQ - baudrate*64)/(baudrate*64);   //SPBRG for Low Baud Rate
  if(x>255)                                       //If High Baud Rage Required
  {
    x = (_XTAL_FREQ - baudrate*16)/(baudrate*16); //SPBRG for High Baud Rate
    BRGH = 1;                                     //Setting High Baud Rate
  }
  if(x<256)
  {
	RCIE = 1;                                     //Enable receive interrupt
	//TXIE = 1;                                     //Enable transmit interrupt   
    SPBRG = x;                                    //Writing SPBRG Register
    SYNC = 0;                                     //Setting Asynchronous Mode, ie UART
    SPEN = 1;                                     //Enables Serial Port
    TRISC7 = 1;                                   //As Prescribed in Datasheet
    TRISC6 = 1;                                   //As Prescribed in Datasheet
    CREN = 1;                                     //Enables Continuous Reception
    TXEN = 1;                                     //Enables Transmission
    return 1;                                     //Returns 1 to indicate Successful Completion
  }
  return 0;                                       //Returns 0 to indicate UART initialization failed
}


/*******************************************************************************
* PUBLIC FUNCTION: uart_transmit
*
* PARAMETERS:
* ~ uc_data		- The data that we want to transmit.
*
* RETURN:
* ~ void
*
* DESCRIPTIONS:
* This function will transmit one byte of data using UART. This is a blocking
* function, if the transmit buffer is full, we will wait until the
* data in the buffer has been sent out before we move in the new data.
*
*******************************************************************************/
void uart_send(unsigned char uc_data)
{
	// Wait until the transmit buffer is ready for new data.
	while (!TXIF);
	
	// Transmit the data.
	TXREG = uc_data;
}



/*******************************************************************************
* PUBLIC FUNCTION: uc_uart_receive
*
* PARAMETERS:
* ~ void
*
* RETURN:
* ~ The data received from the UART.
*
* DESCRIPTIONS:
* This function will receive one byte of data using UART. This is a blocking
* function because if the receive buffer is empty, we will wait until the
* data is received.
*
*******************************************************************************/
unsigned char uart_read(void)
{
	// If there is overrun error...
	if (OERR == 1) {
		// Clear the flag by disable and enable back the reception.
		CREN = 0;
		CREN = 1;
	}	
	
	// Wait until there is data available in the receive buffer.
	while(!RCIF);
	
	// Return the received data.
	return RCREG;
}



/*******************************************************************************
* PUBLIC FUNCTION: uart_putstr
*
* PARAMETERS:
* ~ csz_string	- The null terminated string to transmit.
*
* RETURN:
* ~ void
*
* DESCRIPTIONS:
* Transmit a string using the UART.
*
*******************************************************************************/

void uart_putstr(char* st_pt)
{
    while(*st_pt) //if there is a char
        uart_send(*st_pt++); //process it as a byte data
}
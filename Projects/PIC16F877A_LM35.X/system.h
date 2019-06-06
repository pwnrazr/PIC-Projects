/******************************************************************************/
/* System Level #define Macros                                                */
/******************************************************************************/

/* TODO Define system operating frequency */

/* Microcontroller MIPs (FCY) */
#define SYS_FREQ        20000000L
#define FCY             SYS_FREQ/4
#define _XTAL_FREQ 20000000

/******************************************************************************/
/* System Function Prototypes                                                 */
/******************************************************************************/

/* Custom oscillator configuration funtions, reset source evaluation
functions, and other non-peripheral microcontroller initialization functions
go here. */

// I/O Connections.
// Parallel 2x16 Character LCD
#define LCD_E			RB5		// E clock pin is connected to RA3	
#define LCD_RS			RB4		// RS pin is used for LCD to differentiate data is command or character, RA2

#define	LCD_DATA		PORTD	// Data port of LCD is connected to PORTD, 8 bit mode
								// DB7(LCD) = RD7(PIC)
								// DB6(LCD) = RD6(PIC)
								// DB5(LCD) = RD5(PIC)
								// DB4(LCD) = RD4(PIC)
								// DB3(LCD) = RD3(PIC)
								// DB2(LCD) = RD2(PIC)
								// DB1(LCD) = RD1(PIC)
								// DB0(LCD) = RD0(PIC)

void ConfigureOscillator(void); /* Handles clock switching/osc initialization */

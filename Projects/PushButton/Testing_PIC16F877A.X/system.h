/******************************************************************************/
/* System Level #define Macros                                                */
/******************************************************************************/

/* Microcontroller MIPs (FCY) */
#define SYS_FREQ        20000000L
#define FCY             SYS_FREQ/4
#define	_XTAL_FREQ	20000000

#define LCD_E			RB5		// E clock pin is connected to RA3	
#define LCD_RS			RB4		// RS pin is used for LCD to differentiate data is command or character, RA2

#define	LCD_DATA		PORTD
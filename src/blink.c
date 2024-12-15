//#define __MSP430FR2355__
#include <msp430.h>

void main(void)
{
	WDTCTL = WDTPW | WDTHOLD; //stop watchdo timer
	P1DIR |= 0x01;		//configure P1.0 as output
	
	volatile unsigned long int i;		//volatile to prevent optimization

	// Disable the GPIO power-on default high-impedance mode
    	// to activate previously configured port settings
	PM5CTL0 &= ~LOCKLPM5;	
	
	while(1)
	{
		P1OUT ^= 0x01;		//toggle P1.0
		for(i=10000; i>0; i--);			//delay
	}
}

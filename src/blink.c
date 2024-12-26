//#define __MSP430FR2355__
#include <msp430.h>
#include <stdint.h>
#include <stdbool.h>

void main(void)
{
	WDTCTL = WDTPW | WDTHOLD; //stop watchdo timer
	P1DIR |= 0x01;		//configure P1.0 as output
	P6DIR |= 0x40;		//configure P6.6 as output
	bool switch1_pushed;
	// uint8_t switch1_pushed;
	volatile unsigned long int i;		//volatile to prevent optimization

	// Disable the GPIO power-on default high-impedance mode
    	// to activate previously configured port settings
	PM5CTL0 &= ~LOCKLPM5;	
		// S1 is connected to signal SW1, there is marking P4.1 on it
	// schematic confirms that signal SW1 is on P4.1
	// Need to Select GPIO on 4.1
		P4SEL0 &= ~0x02;
		P4SEL1 &= ~0x02;
		// Set P4.1 as input
		P4DIR &= ~0x02;
		// Enable resistor and Pull up on P4.1 because pin 3 on S1 is GND
		P4REN |= 0x02;
		P4OUT |= 0x02;

	while(1)
	{
		/*
		P1OUT ^= 0x01;		//toggle P1.0
		P6OUT ^= 0x40;		//toggle P6.6
		for(i=10000; i>0; i--);			//delay
	}
	// PxREN
	// PxDIR
	// PxOUT
	// PxSEL0 and PxSEL1
	// PxIN
	// Not required PxIE
	*/
		// Read P4.1 in P4IN.1
		switch1_pushed = ( (P4IN & 0x02) == 0x00);
	
		// If it is pushed then turn the LED ON
		if(switch1_pushed)
		{
			P6OUT |= 0x40;
		}
		else
		{
			P6OUT &= ~0x40;
		}

//		for(i=10000; i>0; i--);			//delay
	}
}

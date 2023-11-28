#include <msp430.h>
#include "leds_and_switches.h"
#include "../11-buzzer-change-tone/buzzer.h"
#include "../2-red-blink-quick/led.h"
#include "modules.h"
#include "events.h"

 char switch_update_interrupt_sense()
{
	char p2val = P2IN;

	P2IES |= (p2val & SWITCHES);
	P2IES &= (p2val | ~SWITCHES);
	return p2val;
}


void led_init(){
	P1DIR |= LEDS;
	P1OUT &= ~LEDS;
}

void switch_init(){	
 	P2REN |= SWITCHES;		/* enables resistors for switches */
  	P2IE |= SWITCHES;		/* enable interrupts from switches */
  	P2OUT |= SWITCHES;		/* pull-ups for switches */
  	P2DIR &= ~SWITCHES;		/* set switches' bits for input */
	switch_update_interrupt_sense();
}

void switch_interrupt_handler(){
	
	char p2val = switch_update_interrupt_sense();	/* switch is in P2 */
	events(p2val);	
}

#include <msp430.h>
#include "leds_and_switches.h"
#include "../11-buzzer-change-tone/buzzer.h"
#include "../2-red-blink-quick/led.h"
#include "modules.h"


static char switch_update_interrupt_sense()
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
	
	//if a switch associated with the corresponding bit is pressed
	 if(!(p2val & SW1)){ 	  //BIT0
		start_module11();
		start_module2();
	 }
	 else if(!(p2val & SW2)){ //BIT1
	 	start_module1();
	 }	 
	 else if(!(p2val & SW3)){ //BIT2
	 	start_module2();
		buttonSound();
	 }
	 else if(!(p2val & SW4)){ //BIT3
	 	start_module4();
		buzzer_set_period(0);// turn off buzzer with SW4
	 }
	 else if(p2val & SW3){	      //SW3 released
		buzzer_set_period(0); //turn off buttonSound()
		P1OUT |= LED_RED;     //turn on red led
		P1OUT &= ~LED_GREEN;
	 }
}

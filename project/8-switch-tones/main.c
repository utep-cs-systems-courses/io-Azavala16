
#include <msp430.h>
#include "../../demos/timerLib/libTimer.h"
#include "../11-buzzer-change-tone/buzzer.h"//changed

#define LED_RED BIT6               // P1.6
#define LED_GREEN BIT0             // P1.0
#define LEDS (BIT0 | BIT6)

#define SW1 BIT0		/* switch1 is p1.0 */
//#define SW2 BIT1		/* switch1 is p1.1 */
//#define SW3 BIT2		/* switch1 is p1.2 */
//#define SW4 BIT3		/* switch1 is p1.3 */

#define SWITCHES (BIT0) //| BIT1 | BIT2 | BIT3)		/* only 1 switch on this board */

void main(void) 
{  
 
  P1DIR |= LEDS;
  P1OUT &= ~LEDS;		/* leds initially off */
  
  P2REN |= SWITCHES;		/* enables resistors for switches */
  P2IE |= SWITCHES;		/* enable interrupts from switches */
  P2OUT |= SWITCHES;		/* pull-ups for switches */
  P2DIR &= ~SWITCHES;		/* set switches' bits for input */
  
  configureClocks();
  buzzer_init();
  enableWDTInterrupts();
  or_sr(0x18);  // CPU off, GIE on
} 

void
switch_interrupt_handler()
{
  char p2val = P2IN;		/* switch is in P1 */

/* update switch interrupt sense to detect changes from current buttons */
  P2IES |= (p2val & SWITCHES);	/* if switch up, sense down */
  P2IES &= (p2val | ~SWITCHES);	/* if switch down, sense up */

/* up=red, down=green */
  if (p2val & SW1) { //button not pressed
//	  buzzer_init();
//buzzer_set_period(3000);
   P1OUT |= LED_RED;
   P1OUT &= ~LED_GREEN;
  } else {	     //pressed
	  buzzer_set_period(1000);
   P1OUT |= LED_GREEN;// changed
   P1OUT &= ~LED_RED;// changed
  }
}

void
__interrupt_vec(PORT2_VECTOR) Port_2(){
	if(P2IFG & SWITCHES){
		P2IFG &= ~SWITCHES;
		switch_interrupt_handler();
	}
}



// Description: This file implements the initialization of an external
// switch.
//----------------------------------------------------------------------//

#include "switch.h"
#include <avr/io.h>

/*
 * Initializes pull-up resistor on PB3 and sets it into input mode
 */
void initSwitchPB3(){
    //Set direction for the input
    DDRB &= ~(1 << DDB3);

    // enable the pullup resistor for stable input
    PORTB |= (1 << PORTB3);

    // Enable Interupts for switch
    PCICR |= (1 << PCIE0); // enabling PCINT 0-7

    PCMSK0 |= (1 << PCINT3); // enabling PCINT3

    
}
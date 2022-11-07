// Description: This file implements the initialization of an external
// switch.
//----------------------------------------------------------------------//

#include "switch.h"
#include <avr/io.h>

/*
 * Initializes pull-up resistor on PB3 and sets it into input mode
 */
void initSwitchPD0(){
    //Set direction for the input
    DDRD &= ~(1 << DDD0);

    // enable the pullup resistor for stable input
    PORTD |= (1 << PORTD0);

    // Enable Interupts for switch
    PCICR |= (1 << PCIE0); // enabling INT0
    
    PCMSK0 |= (1 << PCINT3); // enabling PCINT3
}

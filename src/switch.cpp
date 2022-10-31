// Author: Alan Manuel Loreto Cornídez
// Net ID: aloretocornidez
// Date: October 3rd, 2022
// Assignment: Lab 3
//
// Description: This file implements the initialization of an external
// switch.
//----------------------------------------------------------------------//

#include "switch.h"
#include <avr/io.h>

/*
 * Initializes pull-up resistor on PB3 and sets it into input mode
 */
void initSwitchPB3()
{

    // Pin PB3 is Digital pin 50 on the microcontroller.
    // Setting PORTx to logical 1 configures the pin as an input pin.
    PORTB |= (1 << PORTB3);

    //Setting DDRx to a logical 0 configures the Pxn as an input pin.
    DDRB &= ~(1 << DDB3);

    //enable the group pin change interrupts PCINTs 0 through 7
    PCICR |= (1 << PCIE0);

    // Enable PCINT for digital pin 50
    PCMSK0 |= (1 << PCINT3);

}

// Author: Jason Freeman
// Net ID: japareman
// Date: 11/7/2022
// Assignment:     Lab 4
//
// Description: This file contains a programmatic overall description of the
// program. It should never contain assignments to special function registers
// for the exception key one-line code such as checking the state of the pin.
//
// Requirements:
//----------------------------------------------------------------------//




#include <avr/interrupt.h>
#include <avr/io.h>
#include "switch.h"
#include "timer.h"

// defines
#define DEBOUNCE_DELAY 5




ISR(INT0_vect){
  // check for if switch is pressed
  // if (switchState == wait_press){
  //   switchState = debounce_press;
  // }
  // else if(switchState == wait_release) {
  //   switchState = debounce_release;
  //   if(ledDelay == LONG_DELAY){
  //     ledDelay = SHORT_DELAY;
  //     moveCursor(1,0);
  //     writeString("Fast");
  //   }
  //   else{
  //     ledDelay = LONG_DELAY;
  //     moveCursor(1,0);
  //     writeString("Slow");
  //   }
  // }
}
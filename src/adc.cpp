// Author: Jason Freeman
// Net ID: japareman
// Date: 11/7/2022
// Assignment: Lab 4
//----------------------------------------------------------------------//

#include "timer.h"
#include <avr/io.h>

// initializing the ADC using pin A0 as input
void initADC(){
    DDRA &= ~(1 << DDA0);
}
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
    // set reference voltage set to AVCC = 5V output.  (we really want to measure 5V output from the 
  // development board to determine what the reference value is for precise calculations)
  ADMUX |= (1 << REFS0);
  ADMUX &= ~(1 << REFS1);

  // determine left or right justified (ADLAR = 0 RIGHT JUSTIFIED)
  ADMUX &= ~(1 << ADLAR);

  // Specify ADC input channel and mode
  //Set ADC7 as single-ended input with MUX[5:0] = 0b000111
  ADMUX |= (1 << MUX2) | (1 << MUX1) | (1 << MUX0);
  ADMUX &= ~((1 << MUX4) | (1 << MUX3));
  ADCSRB &= ~(1 << MUX5);

  // set Auto Trigger Source Selection
  // Use free-running mode ADTS[2:0] = 0b000
  // 
  ADCSRB &= ~((1 << ADTS2) | (1 << ADTS1) | (1 << ADTS0));

  // enable ADC and enable auto-triggering
  ADCSRA|= (1 << ADEN) | (1 << ADATE);


  // set the ADC clock frequemcy.  Use a pre-scaler of 128
  // ADC clock frequency is 16 Mhz divided by pre-scaler = 125KHz
  // Sampling rate is 1/ ((1/125K Hz )*(13 clock cycles)) = 9615 KHz
ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
  // disable ADC0 pin digital input - pin A0 on board
  DIDR0 |= (1 << ADC7D);

  // start the first ADC conversion
  ADCSRA |= ( 1 << ADSC);

}

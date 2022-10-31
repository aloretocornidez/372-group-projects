// Author: Jason Freeman        
// Net ID: japareman         
// Date: 11/7/2022          
// Assignment:     Lab 4
//----------------------------------------------------------------------//

#ifndef TIMER_H
#define TIMER_H

#include <avr/io.h>

void initTimer1();
void delayS(unsigned int delay);
void initTimer0();
void delayMs(unsigned int delay); 

#endif

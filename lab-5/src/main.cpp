// Author: Alan Manuel Loreto Cornidez, Jeremy Sharp, Jason Freeman
// Net ID:
// Date:
// Assignment:     Lab 3
//
// Description: This file contains a programmatic overall description of the
// program. It should never contain assignments to special function registers
// for the exception key one-line code such as checking the state of the pin.
//
// Requirements:
//----------------------------------------------------------------------//

#include <Arduino.h>

#include <avr/io.h>
#include "7seg.h"
#include "timer.h"
#include "switch.h"
#include <avr/interrupt.h>

#define wt_press 0
#define db_press 1
#define wt_release 2
#define db_release 3
int btncase = 0;
int motorState = 0;
#define on 1
#define off 0
// defines

int num = 0;
int cds = 0;
/*
 * Define a set of states that can be used in the state machine using an enum.
 */
// typedef enum .......

// Initialize states.  Remember to use volatile

void countDown()
{
  int cdt = 9;
  while (cdt >= 0)
  {
    turnOn7SegWithNum(cdt);
    delayS(1);
    cdt--;
  }
  turnOn7SegWithNum(-1);
}

int main()
{
  Serial.begin(9600);
  init7Seg();
  initTimer0();
  initTimer1();
  initSwitchPD0();
  sei();

  while (1)
  {
    if (num > 9)
    {
      num = 0;
    }
    if (cds == on)
    {
      countDown();
      cds = off;
    }

    switch (btncase)
    { // debounce button
    case wt_press:
      break;
    case db_press:
      delayMs(1);
      btncase = wt_release;
      break;
    case wt_release:
      break;
    case db_release:
      delayMs(1);
      btncase = wt_press;
      break;
    }
  }
}

ISR(INT0_vect)
{ // ISR
  if (btncase == wt_press)
  { // move through state machine based on button
    btncase = db_press;
  }
  else if (btncase == wt_release)
  {
    Serial.println("rel");
    if (motorState == off)
    { // change motor power state
      motorState = on;
      Serial.println("motor on");
    }
    else
    {
      motorState = off; // change motor power state
      Serial.println("motor off");
      cds = on;
    }
    btncase = db_release;
  }
}

// Author: Alan Manuel Loreto Cornídez
// Net ID: aloretocornidez
// Date: October 3rd, 2022
// Assignment: Lab 3
//
// Description: This file contains a programmatic overall description of the
// program. It should never contain assignments to special function registers
// for the exception key one-line code such as checking the state of the pin.
//
// Requirements:
//----------------------------------------------------------------------//

#include <avr/io.h>
#include <avr/interrupt.h>
#include "led.h"
#include "switch.h"
#include "timer.h"
#include "lcd.h"

// defines
#define SHORT_DELAY 200
#define LONG_DELAY 100

/*
 * Define a set of states that can be used in the state machine using an enum.
 */
typedef enum stateType_enum
{
        wait_press,
        debounce_press,
        wait_release,
        debounce_release
} stateType;

volatile stateType state = wait_press;

// A boolean variable to keep track of the LED speed.
bool fastLedSpeed = true;

int main()
{
        // Initialize a char variable to keep track of the count on the LEDs.
        unsigned char count = '0';

        // Seting up exterinal interrupts.
        // Initialize all of the components.
        // Turns on the LED pins for correct output.
        // Initializes the switch.
        // Initializes the Timer0.
        initTimer1();
        initTimer0();
        initLCD();
        initSwitchPB3();
        initLED();
        sei();


        // TODO: SET UP THESE FUNCTIONS
        moveCursor(0, 0); // moves the cursor to 0,0 position
        writeString("Current Mode:");
        moveCursor(1, 0); // moves the cursor to 1,0 position
        writeString("Slow");


        // // Seting up exterinal interrupts.
        // sei();
        // // Initialize all of the components.
        // // Turns on the LED pins for correct output.
        // initLED();
        // // Initializes the switch.
        // initSwitchPB3();
        // // Initializes the Timer0.
        // initTimer0();


        // // TODO: SET UP THESE FUNCTIONS
        // initTimer1();
        // initLCD();
        // moveCursor(0, 0); // moves the cursor to 0,0 position
        // writeString("Current mode: ");
        // moveCursor(1, 0); // moves the cursor to 1,0 position

        // while loop
        while (1)
        {

                // Delay the system by a certain amount of time
                if (fastLedSpeed)
                {
                        delayMs(SHORT_DELAY);
                        // Change the LEDs by the count.
                        turnOnLEDWithChar(count);
                }
                else
                {
                        delayMs(LONG_DELAY);
                        // Change the LEDs by the count.
                        turnOnLEDWithChar(count);
                }

                switch (state)
                {
                case wait_press:
                        break;

                case debounce_press:
                        delayMs(1);
                        state = wait_release;
                        break;

                case wait_release:
                        break;

                case debounce_release:
                        delayMs(1);
                        state = wait_press;
                        break;
                }

                // increment the counter
                count++;
                // modulo the counter
                count %= 16;
        }
        return 0;
}

/* Implement an Pin Change Interrupt which handles the switch being
 * pressed and released. When the switch is pressed and released, the LEDs
 * change at twice the original rate. If the LEDs are already changing at twice
 * the original rate, it goes back to the original rate.
 */
ISR(PCINT0_vect)
{
        // This function is hit when the button is presssed
        if (state == wait_press)
        {
                state = debounce_press;
        }
        else if (state == wait_release)
        {
                // Do nothing while waiting
                if (fastLedSpeed == true)
                { // if the led_speed is fast then change it to slow
                        fastLedSpeed = false;
                        moveCursor(1, 0);
                        writeString("Fast");
                }
                else
                {
                        moveCursor(1, 0);
                        writeString("Slow");
                        fastLedSpeed = true; // else led_speed was slow so change it to fast
                }
                state = debounce_release;
        }

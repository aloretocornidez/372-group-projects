// Author: Alan, Jason, Jeremy
// Net ID:
// Date: 11/28/2022
// Assignment:     Lab 5
//
// Description: This file contains a programmatic overall description of the
// program. It should never contain assignments to special function registers
// for the exception key one-line code such as checking the state of the pin.
//
// Requirements:
//----------------------------------------------------------------------//

#include <Arduino.h>

#include <avr/io.h>
#include <avr/interrupt.h>

#include "i2c.h"
#include "timer.h"
#include "switch.h"
#include "pwm.h"
#include "spi.h"

#define SLA 0x68 // MPU_6050 address with PIN AD0 grounded
#define PWR_MGMT 0x6B
#define WAKEUP 0x00
#define SL_MEMA_XAX_HIGH 0x3B
#define SL_MEMA_XAX_LOW 0x3C
#define SL_MEMA_YAX_HIGH 0x3D
#define SL_MEMA_YAX_LOW 0x3E
#define SL_MEMA_ZAX_HIGH 0x3F
#define SL_MEMA_ZAX_LOW 0x40
#define SL_TEMP_HIGH 0x41
#define SL_TEMP_LOW 0x42

typedef enum accelerometerState
{
    initialState,
    trippedState
} acceleroMeterState;

typedef enum stateType_enum
{
    wait_press,
    debounce_press,
    wait_release,
    debounce_release
} buttonState;

volatile buttonState state = wait_press;
volatile acceleroMeterState accelState = initialState;

// Variables to keep track of the state of the face and the buzzer.
bool buzzerOn = false;
bool faceState = true; // True: Happy, False: sad

int main()
{

    Serial.begin(9600); // using serial port to print values from I2C bus

    sei();
    init_SPI(); // Initialize SPI protocol for the LED Matrix (that shows the smiley face)
    initSwitchPB3();
    initTimer1();
    initPWMTimer3(true);

    // Gyroscope Initialization

    initI2C(); // initialize I2C and set bit rate
    StartI2C_Trans(SLA);
    write(PWR_MGMT); // address on SLA for Power Management
    write(WAKEUP);   // send data to Wake up from sleep mode

    StopI2C_Trans();
    // Finish Gyroscope Initialization

    float xAxis = 0;
    float yAxis = 0;
    float zAxis = 0;

    while (1)
    {

        // Read the data from the gyroscope
        readAllAxes(&xAxis, &yAxis, &zAxis);
        StopI2C_Trans();
        printAxes(&xAxis, &yAxis, &zAxis);

        switch (accelState)
        {
        // Happy state of the accelerometer.
        case initialState:

            // Accelerometer is tripped when this case is reached.
            if (zAxis > 10000 || yAxis > 10000 || zAxis < -10000 || yAxis < -10000)
            {

                // Buzzer is turned on.
                buzzerOn = true;

                // Face is now sad
                faceState = false;

                // Accelerometer is send to normal state.
                accelState = trippedState;
            }

        // Tripped state of the acceleromter.
        case trippedState:

            // When the accelerometer is tripped, if the thresholds return to normal.
            if (zAxis < 10000 && yAxis < 10000 && zAxis > -10000 && yAxis > -10000)
            {

                faceState = true;
                buzzerOn = false;
                accelState = initialState;
            }
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


        // The buzzer turns off whenever the switch is pressed or if the accelerometer returns to neutral.
        if (buzzerOn) turnOn();
        else turnOff();

        face(faceState);
    }

    return 0;
}

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
        if (buzzerOn == true)
        { // if the led_speed is fast then change it to slow
            buzzerOn = false;
        }
        else
        {
            buzzerOn = true; // else led_speed was slow so change it to fast
        }
        state = debounce_release;
    }
}

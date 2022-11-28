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
#include "i2c.h"
#include "timer.h"
#include "switch.h"
#include "pwm.h"
#include "spi.h"
#include <avr/interrupt.h>

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

#define wt_press 0
#define db_press 1
#define wt_release 2
#define db_release 3
int btncase = 0;
#define on 1
#define off 0

#define sad false

typedef enum accelerometerState
{
    initialState,
    trippedState
} acceleroMeterState;

volatile acceleroMeterState accelState = initialState;

signed int readSensor(unsigned char sensorHigh, unsigned char sensorLow);

void turnOn()
{
    // prescaler 1
    TCCR4B |= (1 << CS40);
    TCCR4B &= ~((1 << CS41) | (1 << CS42));

    // output
    DDRE |= (1 << DDE3);
}
void turnOff()
{
    // prescaler no clock
    TCCR4B &= ~((1 << CS41) | (1 << CS42) | (1 << CS40));

    // low
    DDRE &= ~(1 << DDE3);
}

bool buzzerOn = false;
bool happy = true;

int main()
{

    Serial.begin(9600); // using serial port to print values from I2C bus

    sei();
    init_SPI(); // Initialize SPI protocol for the LED Matrix (that shows the smiley face)
    initSwitchPB3();

    //
    // Gyroscope Initialization
    //
    initI2C(); // initialize I2C and set bit rate
    float xAxis = 0;
    float yAxis = 0;
    float zAxis = 0;
    StartI2C_Trans(SLA);
    write(PWR_MGMT); // address on SLA for Power Management
    write(WAKEUP);   // send data to Wake up from sleep mode

    StopI2C_Trans();
    //
    // Finish Gyrozope Initialization
    //

    // Variables to keep track of the state of the face and the buzzer.
    initPWMTimer3(true);

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

            // if the acceleromter is tripped turn make face sad and turn on buzzer
            if (zAxis > 10000 || yAxis > 10000 || zAxis < -10000 || yAxis < -10000)
            {

                // Buzzer is turned on.
                buzzerOn = true;
                // Face is happy
                happy = false;
                // Accelerometer is send to normal state.
                accelState = trippedState;
            }

        // Tripped state of the acceleromter.
        case trippedState:

            // When the accelerometer is tripped, if the thresholds return to normal.
            if (zAxis < 10000 && yAxis < 10000 && zAxis > -10000 && yAxis > -10000)
            {

                happy = true;
                buzzerOn = false;
                accelState = initialState;
            }
        }

        // The buzzer turns off whenever the switch is pressed or if the accelerometer returns to neutral.

        if (buzzerOn)
            turnOn();
        else
            turnOff();

        if (happy)
            face(happy);
        else
            face(sad);
    }

    return 0;
}

ISR(PCINT0_vect)
{ // ISR
    if (btncase == wt_press)
    { // move through state machine based on button
        btncase = db_press;
    }
    else if (btncase == wt_release)
    {
        Serial.println("in wt_release");
        if(buzzerOn == true)
        {
            buzzerOn = false;
        }
        else if(buzzerOn == false)
        {
            buzzerOn = true;
        }
    }
    else
    {
        Serial.println("in");
    }
    btncase = db_release;
}

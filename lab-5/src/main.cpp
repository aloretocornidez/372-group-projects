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

signed int readSensor(unsigned char sensorHigh, unsigned char sensorLow);



int main()
{

    Serial.begin(9600); // using serial port to print values from I2C bus
    sei();
    init_SPI(); // Initialize SPI protocol for the LED Matrix (that shows the smiley face)


    /*
     * Gyroscope Initialization
     */
    initI2C(); // initialize I2C and set bit rate
    float xAxis = 0;
    float yAxis = 0;
    float zAxis = 0;
    StartI2C_Trans(SLA);
    write(PWR_MGMT); // address on SLA for Power Management
    write(WAKEUP);   // send data to Wake up from sleep mode

    StopI2C_Trans();
    /*
     * Finish Gyrozope Initialization
     */

    while (1)
    {

        //_delay_ms(500);
        readAllAxes(&xAxis, &yAxis, &zAxis);
        //printAxes(&xAxis, &yAxis, &zAxis);
        StopI2C_Trans();



        // Call this function for to display the face.
        face(true);

        // Arduino Time Delay.
        _delay_ms(1000); // delay for 1 s to display "HI"


        face(false);
    }

    return 0;
}





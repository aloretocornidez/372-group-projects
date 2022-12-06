// Author: Alan, Jason, Jeremy
// Net ID:
// Date: 11/29/2022
// Assignment:     Final Project
#include <Arduino.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdfix.h>

#include "spi.h"
#include "fft.h"
#include "adc.h"
#include "parameters.h"

static uint8_t channel = 0;

fix fr[NUM_SAMPLES]; // array of real part of samples (WINDOWED)
fix fi[NUM_SAMPLES]; // array of imaginary part of samples (WINDOWED)

int main()
{

    // Initialize an array that shall hold the input signal
    float inputSignal[FFT_SIZE];

    // This array holds the power in each of the 8 frequency bins.
    float powerArray[8];

    /* Initialize Analog to Digital Conversion with an anolog input. */
    initADC(channel); // Initialize ADC.

    /* Initialize 8x8 Matrix */
    init_SPI();

    /* Initialize FFT parameters to prepare for the fast fourier transform. */
    initFFTparams(); // Initialialize FFT parameters (like butterfly values).

    // Initialize i2c communication with a baud rate of 9600.
    Serial.begin(9600); // using serial port to print values from I2C bus

    while (true)
    {

        // Sample the data and write the data into a matrix (the matrix length should be a power of 2.
        populateInputBuffer(inputSignal);

        // Conduct a foucrier transform on the data and ouptut a matrix.
        FFT(inputSignal, fr, fi);

        // Take the fourier transform matrix and calculate the power within specified frequency bins.
        powerCalculation(fr, powerArray);

        // Normalize the values that are gathered in each bin to values parsable by the display api.
        normalizePower(powerArray);

        // Take the power matrix and  print out the bins on the 8x8 matrix.
        testDisplay(powerArray);

    }

    return 0;
}

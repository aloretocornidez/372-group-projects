#include <avr/io.h>
#include "adc.h"
#include "parameters.h"

void initADC(uint8_t channel)
{

    // 16MHz/128 = 125kHz the ADC reference clock
    ADCSRA |= ((1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0));
    ADMUX |= (1 << REFS0); // Set Voltage reference to Avcc (5v)
    ADCSRA |= (1 << ADEN); // Turn on ADC
    ADCSRA |= (1 << ADSC);

    ADMUX &= 0xE0;               // Clear bits MUX0-4
    ADMUX |= channel & 0x07;     // Defines the new ADC channel to be read by setting bits MUX0-2
    ADCSRB = channel & (1 << 3); // Set MUX5
}

uint16_t readADC()
{

    ADCSRA |= (1 << ADSC); // Starts a new conversion
    while (ADCSRA & (1 << ADSC))
        ; // Wait until the conversion is done
    return ADCW;
}

float sampleVoltage()
{

    uint16_t value = readADC();
    float voltage = normalizeValue(value);

    // Returns a normalized voltage to the caller. after the value has been sampled.
    return voltage;
}

// Converts the unsigned value retrieved from the adc conversion into a signed number.
float normalizeValue(int value)
{

    return ((((float)value - 396.0) / 139.0));
}

void populateInputBuffer(float *array)
{

    // Samples the voltage to fill the 
    for (int i = 0; i < FFT_SIZE; i++)
    {
        array[i] = sampleVoltage();
    }
}

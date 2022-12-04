#ifndef ADC_H
#define ADC_H




// Initializes analog conversion.
void initADC();

// Reads a value from a specified channel.
uint16_t readADC(uint8_t channel);

// Normalizes a sample that is retrieved from the ADC conversion.
float normalizeValue(int value);

// Samples the voltage on the channel that is specified. Converts a 10bit number into a value between 5.0 V - 0.0 V
float sampleVoltage(uint8_t channel);




#endif
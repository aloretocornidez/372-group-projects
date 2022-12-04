#ifndef ADC_H
#define ADC_H




// Initializes analog conversion.
// Reads a value from a specified channel.
void initADC(uint8_t channel);

// Reads the register after the ADC has taken place.
uint16_t readADC();

// Samples the voltage on the channel that is specified. Converts a 10bit number into a value between 5.0 V - 0.0 V
float sampleVoltage();

// Normalizes a sample that is retrieved from the ADC conversion.
float normalizeValue(int value);

void populateInputBuffer(float* array);


#endif
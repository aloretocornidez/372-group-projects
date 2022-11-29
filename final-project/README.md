# Final Project

## Group Members:
- Alan Manuel
- Jason Freeman
- Jerey Sharp

## Member Tasks
### Jason Freeman
- Analog to digital converison of an input signal, in other words, he must sample the data.
- The sample rate must be at least 44kHz
- Output of his data must be an array of length L = {2, 4, 8, 16}

### Alan Manuel
- Fast fourier transform of the sampled data.
- Create a power analysis of 8 frequency bins.
- Output will be an array with 8 indexes, each index will be the power in each frequency bin.

### Jeremy Sharp
- Create a function that will print the frequency response of the signal in each frequency bin.
- The function will look at each index of the power of the array and will light up LEDs in each column of the matrix proportionately to the power in the frequency bin.
- Thresholds will be set in order to have a maximum power light up all 8 leds in a column and minimum power that must be met in order to light up the column. 

// Header File for the SPI communication with the 8x8 matrix
#ifndef SPI_H
#define SPI_H

void SPI_MASTER_Init();
void write_execute(unsigned char CMD, unsigned char data);
void init_SPI();

void display(byte input[]);
void displayArray(float *array);
void disp_spectrum(int inputlevels[7]);
#endif

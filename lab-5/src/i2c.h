#ifndef I2C_H
#define I2C_H




void initI2C();
void StartI2C_Trans(unsigned char SLA);
void StopI2C_Trans();
void write(unsigned char data);
void Read_from(unsigned char SLA, unsigned char MEMADDRESS);
unsigned char Read_data();


void printAxes(float *x, float *y, float *z);
void readAllAxes(float *x, float *y, float *z);
signed int readSensor(unsigned char, unsigned char);
// signed int readSensor(unsigned char sensorHigh, unsigned char sensorLow);



// Custom Function to read data

void fullGyroInit();
#endif

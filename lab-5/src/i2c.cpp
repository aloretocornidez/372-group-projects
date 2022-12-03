#include "i2c.h"
#include <avr/io.h>
#include "Arduino.h"

#define wait_for_completion      \
  while (!(TWCR & (1 << TWINT))) \
    ;
#define SLA 0x68 // MPU_6050 address with PIN AD0 grounded
#define SL_MEMA_XAX_HIGH 0x3B
#define SL_MEMA_XAX_LOW 0x3C
#define SL_MEMA_YAX_HIGH 0x3D
#define SL_MEMA_YAX_LOW 0x3E
#define SL_MEMA_ZAX_HIGH 0x3F
#define SL_MEMA_ZAX_LOW 0x40




void initI2C()
{

  PRR0 &= ~(1 << PRTWI); // wake up I2C module on AT2560 power management register
  TWSR |= (1 << TWPS0);  // prescaler power = 1
  TWSR &= ~(1 << TWPS1); // prescaler power = 1

  //𝑇𝑊𝐵𝑅=((𝐶𝑃𝑈 𝐶𝑙𝑜𝑐𝑘 𝑓𝑟𝑒𝑞𝑢𝑒𝑛𝑐𝑦)/(𝑆𝐶𝐿 𝑓𝑟𝑒𝑞𝑢𝑒𝑛𝑐𝑦)−16)/(2∗〖(4)〗^𝑇𝑊𝑃𝑆 )
  TWBR = 0xC6; // bit rate generator = 10k  (TWBR = 198)

  TWCR |= (1 << TWINT) | (1 << TWEN); // enable two wire interface
}

void StartI2C_Trans(unsigned char sla)
{
  // this function initiates a start condition and calls slave device with SLA
  TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN); // clear TWINT, intiate a start condition and enable
  wait_for_completion;
  TWDR = (sla << 1);                 // slave address + write bit '0'
  TWCR = (1 << TWINT) | (1 << TWEN); // trigger action:clear flag and enable TWI
  wait_for_completion;
}

void StopI2C_Trans()
{
  // this function sends a stop condition to stop I2C transmission

  TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO); // trigger action:  send stop condition
}
void write(unsigned char data)
{
  // this function loads the data passed into the I2C data register and transmits
  TWDR = data;                       // load data into TWDR register
  TWCR = (1 << TWINT) | (1 << TWEN); // trigger action:  clear flag and enable TWI
  wait_for_completion;
}
void Read_from(unsigned char sla, unsigned char memaddress)
{
  // this function sets up reading from SLA at the SLA MEMADDRESS

  StartI2C_Trans(SLA);

  write(memaddress);

  TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN); // restart to switch to read mode
  wait_for_completion;
  TWDR = (SLA << 1) | 0x01;                        // 7 bit address for slave plus read bit
  TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA); // trigger with master sending ack
  wait_for_completion;
  TWCR = (1 << TWINT) | (1 << TWEN); // master can send a nack now
  wait_for_completion;
  TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO); // Stop condition
  // after this function is executed the TWDR register has the data from SLA that Master wants to read
}

unsigned char Read_data() // Returns the last byte  from the data register
{

  return TWDR;
}

void printAxes(float *xAxis, float *yAxis, float *zAxis)
{
  Serial.print("(");
  Serial.print(*xAxis);
  Serial.print(", ");
  Serial.print(*yAxis);
  Serial.print((", "));
  Serial.print(*zAxis);
  Serial.println(")");
}

void readAllAxes(float *xAxis, float *yAxis, float *zAxis)
{
  *zAxis = readSensor(SL_MEMA_ZAX_HIGH, SL_MEMA_ZAX_LOW);
  *yAxis = readSensor(SL_MEMA_YAX_HIGH, SL_MEMA_YAX_LOW);
  *xAxis = readSensor(SL_MEMA_XAX_HIGH, SL_MEMA_XAX_LOW);
}


signed int readSensor(unsigned char sensorHigh, unsigned char sensorLow)
{
    signed int T_val;

    Read_from(SLA, sensorHigh);

    // status = TWSR & 0xF8;

    T_val = Read_data(); // read upper value

    Read_from(SLA, sensorLow);
    T_val = (T_val << 8) | Read_data(); // append lower value

    return T_val;
}
#ifndef _MAX31865_H_
#define _MAX31865_H_
#include "globals.h"

#define MAX_CS1     PIN_C2
#define MAX_CS2     PIN_C1

#define RTD_CONFIGURATION           0x00;      /**< Configuration Register */
#define RTD_RTD_MSB                 0x01;      /**< RTD Data MSB Register*/
#define RTD_RTD_LSB                 0x02;      /**< RTD Data LSB Register*/
#define RTD_HI_FLT_THRHLD_MSB       0x03;      /**< High Fault Threshold MSB register */
#define RTD_HI_FLT_THRHLD_LSB       0x04;      /**< High Fault Threshold LSB register */
#define RTD_LO_FLT_THRHLD_MSB       0x05;      /**< Low Fault Threshold MSB register */
#define RTD_LO_FLT_THRHLD_LSB       0x06;      /**< Low Fault Threshold LSB register */
#define RTD_FLT_STATUS              0x07;      /**< Fault Status Register */
#define RREF                        430         // Reference resistor
#define FACTOR                      32768        // 2^15 used for data to resistance conversion
#define ALPHA                       0.003851    // PT-100 temperature coefficient

unsigned int16 RTD_REF_RESISTANCE_430 = 430;       /**< Value of referent resistor in Ohms */

void max_spiWrite(unsigned int8 *pBuf, unsigned int16 nBytes);
void max_spiRead(unsigned int8 *pBuf, unsigned int16 nBytes);
void max_spiTransfer(unsigned int8 *pIn, unsigned int8 *pOut, unsigned int16 nBytes);

void max_writeRegister1(unsigned int8 regAddress, unsigned int8 writeData);
void max_writeRegister2(unsigned int8 regAddress, unsigned int8 writeData);

unsigned int8 max_readRegister1(unsigned int8 regAddress);
unsigned int8 max_readRegister2(unsigned int8 regAddress);

unsigned int16 max_readTemperature1();
unsigned int16 max_readTemperature2();

float max_convertTemperature(unsigned int16 inputData, unsigned int16 referentResistance);
void max31865_init();

/*-------------------- Begin Max31865 --------------------*/
//SPI write n bytes
void max_spiWrite(unsigned int8 *pBuf, unsigned int16 nBytes) {
    unsigned int8 *ptr = pBuf;
    while( nBytes-- )
        spi_write( *( ptr++ ) );
}

//SPI read n bytes
void max_spiRead(unsigned int8 *pBuf, unsigned int16 nBytes) {
    unsigned int8 *ptr = pBuf;
    while( nBytes-- )
        *( ptr++ ) = spi_read(0x00);
}

void max_spiTransfer(unsigned int8 *pIn, unsigned int8 *pOut, unsigned int16 nBytes) {
    unsigned int8 *in = pIn;
    unsigned int8 *out = pOut;
    while( nBytes-- )
        *( out++ ) = spi_read( *( in++ ) );
}

//Write data to Max_1
void max_writeRegister1(unsigned int8 regAddress, unsigned int8 writeData) {
    unsigned int8 tmp[2];
    regAddress |= 0x80;
    tmp[0] = regAddress;
    tmp[1] = writeData;
    output_low(MAX_CS1);
    max_spiWrite(tmp, 2);
    output_high(MAX_CS1);
}

//Write data to Max_2
void max_writeRegister2(unsigned int8 regAddress, unsigned int8 writeData) {
    unsigned int8 tmp[2];
    regAddress |= 0x80;
    tmp[0] = regAddress;
    tmp[1] = writeData;
    output_low(MAX_CS2);
    max_spiWrite(tmp, 2);
    output_high(MAX_CS2);
}

//Read data from register Max_1
unsigned int8 max_readRegister1(unsigned int8 regAddress) {
    unsigned int8 tmp;
    output_low(MAX_CS1);
    max_spiWrite(&regAddress, 1);
    max_spiRead(&tmp, 1);
    output_high(MAX_CS1);
    return tmp;
}

//Read data from register Max_2
unsigned int8 max_readRegister2(unsigned int8 regAddress) {
    unsigned int8 tmp;
    output_low(MAX_CS2);
    max_spiWrite(&regAddress, 1);
    max_spiRead(&tmp, 1);
    output_high(MAX_CS2);
    return tmp;
}

//Read Temperature from Max_1
unsigned int16 max_readTemperature1() {
     unsigned int16 returnValue = 0;
     unsigned int8 buff[2];
    buff[0] = max_readRegister1(0x01);
    buff[1] = max_readRegister1(0x02);
    returnValue = buff[0] << 8;
    returnValue |= buff[1];
    returnValue >>= 1;
    return returnValue;
}

//Read Temperature from Max_2
unsigned int16 max_readTemperature2() {
     unsigned int16 returnValue = 0;
     unsigned int8 buff[2];
    buff[0] = max_readRegister2(0x01);
    buff[1] = max_readRegister2(0x02);
    returnValue = buff[0] << 8;
    returnValue |= buff[1];
    returnValue >>= 1;
    return returnValue;
}

//Convert Temperature to degree C
float max_convertTemperature(unsigned int16 inputData, unsigned int16 referentResistance) {
    float floatValue;
    /*float coefficient;
    coefficient = (referentResistance/400.0);
    floatValue = (float)inputData * coefficient;
    floatValue /= 32;
    floatValue -= 256;*/
    // Calculate the actual resistance of the sensor
    float resistance = ((float) inputData * RREF) / FACTOR;
    // Calculate the temperature from the measured resistance
    floatValue = ((resistance / 100) - 1) / ALPHA;
    return floatValue;
}

//Init max31865 mode 3 wires
void max31865_init() {
     max_writeRegister1(0x00, 0xD0);
     delay_us(10);
     max_writeRegister2(0x00, 0xD0);
     delay_us(10);
}

#endif

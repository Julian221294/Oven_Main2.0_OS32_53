#ifndef _AFE90100_H_
#define _AFE90100_H_

/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
! NOTE: The document of LMP90100 has error in describing reading registers. The
code for INST1 need to be 0x10 for both writing and reading, not 0x90 as stated!
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
#include "globals.h"

#include "TI_LMP90100.h"

unsigned char URA = 0;


void AFE90100_init(void)
{
   /*** Note the CCS compiler has error in the setup_spi,where the SPI_L_TO_H
      or SPI_H_TO_L does not work, use a constant such as 0x4010, ref from link:
      "http://www.ccsinfo.com/forum/viewtopic.php?t=20611"
   ***/
   //my_spi_init();
}

void AFE90100_WriteReg(unsigned char addr, unsigned char value)
{
   unsigned char new_URA, inst;
   output_low(PIN_A0);                          //Enable the AFE90100
   new_URA = (addr & LMP90100_URA_MASK)>>4;
   if (new_URA != URA)
   {
      inst = LMP90100_INSTRUCTION_BYTE1_WRITE;                                 // Transaction-1
      spi_write(inst);
      URA = new_URA;
      spi_write(URA);
   }
   inst = LMP90100_WRITE_BIT | LMP90100_SIZE_1B |(addr & LMP90100_LRA_MASK);    // lower register address
   spi_write(inst);                                                            // Send lower register address
   spi_write(value);                                                           // Send data value  
   output_high(PIN_A0);                          //Disable the AFE90100
}

unsigned char AFE90100_ReadReg(unsigned char addr)
{
   unsigned char new_URA, inst, value;
   output_low(PIN_A0);                          //Enable the AFE90100
   new_URA = (addr & LMP90100_URA_MASK)>>4;
   if (new_URA != URA)
   {
      inst = LMP90100_INSTRUCTION_BYTE1_WRITE;                                 // Transaction-1
      spi_write(inst);
      URA = new_URA;
      spi_write(URA);
   }
   inst = LMP90100_READ_BIT | LMP90100_SIZE_1B |(addr & LMP90100_LRA_MASK);    // lower register address
   spi_write(inst);                                                            // Send lower register address
   value = spi_read(0x00);                                                           // Send data value  
   output_high(PIN_A0);                          //Disable the AFE90100
   return value;
}

void  AFE90100_SetPGA(unsigned char ch, unsigned char pga)
{
   AFE90100_WriteReg(ch, pga);
}

signed int32 AFE90100_ReadADC(void)
{
  ADC_DATA_TYPE adc_data;
  adc_data.bytes[3] = AFE90100_ReadReg(TI_LMP90100_ADC_DOUT2_REG);
  adc_data.bytes[2] = AFE90100_ReadReg(TI_LMP90100_ADC_DOUT1_REG);
  adc_data.bytes[1] = AFE90100_ReadReg(TI_LMP90100_ADC_DOUT0_REG);
  adc_data.bytes[0] = 0;
  return adc_data.whole;
}

#endif //#define _AFE90100_H_

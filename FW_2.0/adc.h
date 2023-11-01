#ifndef _ADC_H_
#define _ADC_H_

#include "AFE90100.h"

#inline
void adc_init(void)
{
   //Set scan mode to "Continuous scan", from CH0 to CH1; 10001000
   AFE90100_WriteReg(TI_LMP90100_CH_SCAN_REG, 0x88);
   //Set CH0 to measure thermocouple (IN4-IN3); REF = REFP1-REFN1;00100011
   AFE90100_WriteReg(TI_LMP90100_CH0_INPUTCN_REG, 0x23);
   //Set CH0 sample rate to 13SPS and CH0 gain to X128. 
   AFE90100_WriteReg(TI_LMP90100_CH0_CONFIG_REG, LMP90100_ODR_13SPS|LMP90100_PGA_128);
   //Set CH1 to measure lm335 (IN5-IN3); REF = REFP1-REFN1; 00101011
   AFE90100_WriteReg(TI_LMP90100_CH1_INPUTCN_REG, 0x2B);
   //Set CH1 sample rate to 13SPS and CH1 gain to X1. 00110000
   AFE90100_WriteReg(TI_LMP90100_CH1_CONFIG_REG, LMP90100_ODR_13SPS|LMP90100_PGA_1);
   adc_data = 0;
   adc_integ_data = 0;
   adc_integ_count = ADC_FILTER_COUNT;
   float_temp = 0.0;
   k_b = 0.80;
   k_a = 1.0-k_b;
}
/*
T = ADC_OUT/X;
120 degree --> RTD = 146.07 ohm
12000(T) --> 46.07/400 * 2^31
X = 41223
ADC_DOUT = 46.07/(4*100)*2^N = 
T = R/0.3839
ADC_OUT * 100 = (T*0.3839)*2^29;
T = ADC_OUT/(0.3839*2^27);
*/

int8 adc_ch = 0;
#inline
void adc_scan(void)
{
   int8 adc_done = 0;
   adc_done = AFE90100_ReadReg(0x18); //ADC_DONE register's address is 0x18.
   if(adc_done != 0xFF){
      adc_ch = 0x07 & AFE90100_ReadReg(0x19);//SAMPLED_CH is 3 LSB of SENDIAG_FLAG (address 0x19)
      if(adc_ch == 0) {//channel 0
         adc_value_ch0 = AFE90100_ReadADC();
      } else { //channel 1
         adc_value_ch1 = AFE90100_ReadADC();
      }
   }
}

/*
   LM335: 10mV / degree
*/
/*
   Type K: PGA = 128.
   V_K = 19.5mV --> ADC_Out = 0x3FFFFFFF
   V_K = 19.494 --> T = 473 deg;
   t = ADC_Out * 47300 / 0x7FFFFFFF ~ ADC_Out / 22701
   V_K = 4.096mV --> T = 100 deg; 
   V_K = 4.096mV --> ADC_Out = 225540847.
   t = ADC_Out * 10000 / 225540847 ~ ADC_Out / 22554
*/

#define THERMO_COEFF (22701)

void get_temp(void)
{
   thermo_temp = adc_value_ch0/THERMO_COEFF;
   env_temp = adc_value_ch1/42950 - 2300;
   adc_data_buff = thermo_temp + env_temp;
   //adc_data_buff = thermo_temp + env_temp + temp_offset;
}

void read_lm335(void)
{
   //Set CH0 to measure lm335 (IN5-IN7); REF = REFP1-REFN1; 00101111
   AFE90100_WriteReg(TI_LMP90100_CH0_INPUTCN_REG, 0x2F);
   //Set CH0 sample rate to 13SPS and CH0 gain to X1. 
   AFE90100_WriteReg(TI_LMP90100_CH0_CONFIG_REG, LMP90100_ODR_13SPS|LMP90100_PGA_1);
   delay_ms(100);
   //10mV/deg; 2.98V @ 25 deg
   env_temp = AFE90100_ReadADC()/85899 - 27300;
}

void read_thermocouple(void)
{
   //Set CH0 to measure thermocouple (IN3-IN4); REF = REFP1-REFN1;00100011
   AFE90100_WriteReg(TI_LMP90100_CH0_INPUTCN_REG, 0x23);
   //Set CH0 sample rate to 13SPS and CH0 gain to X128. 
   AFE90100_WriteReg(TI_LMP90100_CH0_CONFIG_REG, LMP90100_ODR_13SPS|LMP90100_PGA_128);
   delay_ms(100);
   //39uV/deg; X128 --> 5mV/deg 2.98V @ 25 degree
   thermo_temp = AFE90100_ReadADC()/THERMO_COEFF;
}

#endif //_ADC_H_

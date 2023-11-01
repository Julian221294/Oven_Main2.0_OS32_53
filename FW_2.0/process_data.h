#ifndef _PROCESS_DATA_H_
#define _PROCESS_DATA_H_

#include "pid.h"
#include "max31865.h"
void Get_Data(void)
{
   if (temp_accum_count == 0) {
      temp_accum_count = ADC_FILTER_COUNT;
      // unsigned int16 readValue1, readValue2;
      // float RTD_Temp1 = 0, RTD_Temp2 = 0;
      GLb_nCountAvrTemp++;
      get_temp();
       t1 = t2; t2 = t3; t3 = t4; t4 = t5; t5 = t6;
       t6 = t7; t7 = t8; t8 = t9; t9 = t10; t10 = adc_data_buff;
       if(10 == GLb_nCountAvrTemp) {
          float_temp = ((float)(t1/10 + t2/10 + t3/10 + t4/10 + t5/10 + t6/10 + t7/10 + t8/10 + t9/10 + t10/10)*10 / 10) + temp_offset;
          realTemp = float_temp;
          GLb_nCountAvrTemp = 0;
       }
      //old version
      //realTemp = adc_data_buff;
      //float_temp = realTemp;

      /*      PT100         */
      //readValue1 = max_readTemperature1();
      // readValue2 = max_readTemperature2();
      //RTD_Temp1 = max_convertTemperature(readValue1, RTD_REF_RESISTANCE_430);
      // RTD_Temp2 = max_convertTemperature(readValue2, RTD_REF_RESISTANCE_430);
      //RTD_realTemp1 = (signed int16)(RTD_Temp1 * 100);
      // RTD_realTemp2 = (unsigned int16)(RTD_Temp2 * 100);
      // realTemp = RTD_realTemp2;
      // float_temp = realTemp;
   }
}

void Process_Data(void)
{  
   //static unsigned int16 index_time_hour, index_time_day;
   if (pid_countdown == 0) { //Update every 2 seconds (~100 cycles of 50Hz power)
      pid_countdown = 1; 
      //printf("tick!");
      
      //PID
      //tmp_int16 = process_pid(float_temp);
      //Adaptive
      tmp_int16 = process_adaptive(float_temp);
      disable_interrupts(GLOBAL);
      triac_on_time_new1 = tmp_int16;
      enable_interrupts(GLOBAL);
      //clock display
      min = read_ds1307(1);   // min
      if (min != last_min) {
         last_min = min;
         //hour = read_ds1307(2);
         if (remain_time != 0) {
            if ((g_state == ST_RUN_WAITING_TIME) || (g_state == ST_RUN_HOLDING_TIME) || (g_state == ST_RUN_HEATING_TIME)) {
               remain_time -= 1;
            }
         }
         /*if (day_remain_time != 0 || hour_remain_time != 0) {
            if (g_state == ST_RUN_HOLDING_TIME) {
               index_time_hour += 1;
               if(index_time_hour > 59) {
                  index_time_hour = 0;
                  //index_time_day += 1;
                  hour_remain_time -= 1;
               }
               if(hour_remain_time == 0 && day_remain_time != 0) {
                  day_remain_time -= 1;
                  hour_remain_time = 23;
               }
            }
         } 
         else {
            index_time_hour = 0;
            index_time_day = 0;
         }*/
      }
   }
}

#endif // #define _PROCESS_DATA_H_

#ifndef _RTCC_H_
#define _RTCC_H_

#include "globals.h"

#int_RTCC
void  RTCC_isr(void) 
{
   if (spk_on_count > 0) {
      spk_on_count--;
      SpeakerOn();
   } else {
      SpeakerOff();
   }
   if (fan_rol_count > 0)
   {
      fan_rol_count--;
   }
   if (temp_accum_count > 0){
      temp_accum_count--;
   }
   if (timed_count_ms > 0) {
      timed_count_ms--;
      if(125 == timed_count_ms) {
         led7[0][1] |= 0x20;
         if (g_state != ST_COMPLETED)
            led7[2][1] |= 0x20;
      }
   } else {
      timed_count_ms = 250;
      if (pid_countdown > 0){
         pid_countdown--;
      }
      led7[0][1] &= 0xDF;
      led7[2][1] &= 0xDF;
   }
   
   key_scan();
   adc_scan();
   triac_scan();
   Led_Scan();

}

void RTCC_init(void)
{
   setup_wdt(WDT_OFF);
   //setup_timer_0(RTCC_INTERNAL|RTCC_DIV_32|RTCC_8_bit); //2.7 ms cycle
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_64|RTCC_8_bit); //5.4 ms cycle
   setup_timer_1(T1_DISABLED);
   //setup_timer_1(T1_INTERNAL|T1_DIV_BY_1);
   setup_timer_2(T2_DISABLED,0,1);
   setup_timer_3(T3_DISABLED|T3_DIV_BY_1);
   setup_comparator(NC_NC_NC_NC);
   setup_vref(FALSE);
   setup_psp(PSP_DISABLED);
   enable_interrupts(INT_RTCC);
   enable_interrupts(GLOBAL);
}

#endif   //#define _RTCC_H_


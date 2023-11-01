#ifndef _TRIAC_H_
#define _TRIAC_H_

#inline
void HeaterOn(void)
{
   //output_high(PIN_C0);
   //output_high(PIN_C1);
   //output_high(PIN_C2);
   //output_high(PIN_A4);
   //output_high(PIN_A5);
   //output_high(PIN_D0);
   //output_high(PIN_E0);
   //output_high(PIN_E1);
   output_high(PIN_E2);
}

#inline
void HeaterOff(void)
{
   //output_low(PIN_C0);
   //output_low(PIN_C1);
   //output_low(PIN_C2);
   //output_low(PIN_A4);
   //output_low(PIN_A5);
   //output_low(PIN_D0);
   //output_low(PIN_E0);
   //output_low(PIN_E1);
   output_low(PIN_E2);
}

#inline
void Ctrl1On(void) {
   output_high(PIN_E0);
   led1[0] &= 0xFE;
}

#inline
void Ctrl1Off(void) {
   output_low(PIN_E0);
   led1[0] |= 0x01;
}
#inline
void Ctrl2On(void) {
   output_high(PIN_E1);
   led1[0] &= 0xFD;
}

#inline
void Ctrl2Off(void) {
   output_low(PIN_E1);
   led1[0] |= 0x02;
}
#inline
void Ctrl3On(void) {
   output_high(PIN_E2);
   led1[0] &= 0xFB;
}

#inline
void Ctrl3Off(void) {
   output_low(PIN_E2);
   led1[0] |= 0x04;
}
#inline
void triac_init(void)
{
   set_tris_e(0x00); // PortE bit 0, 1, 2 as output
   Ctrl1Off();
   Ctrl2Off();
   Ctrl3Off();
}

#inline
void triac_scan(void)
{
   //Scanning the heating triac:
   if (triac_count1 < TRIAC_CYCLE) {
      triac_count1++;
   } else {
      triac_count1 = 0; 
      triac_on_time1 = triac_on_time_new1;
   }
   if ((triac_count1 < triac_on_time1) && ((g_state == ST_RUN_HEATING_TIME) || (g_state == ST_RUN_HOLDING_TIME ))) {
      Ctrl3On();
      //Ctrl1On();
   } else {
      Ctrl3Off();
      //Ctrl1Off();
   }
   //Scanning the fan triac:0
   if (triac_count2 < TRIAC_CYCLE) {
      triac_count2++;
   } else {
      triac_count2 = 0; 
      triac_on_time2 = (int16)(fan_speed*TRIAC_CYCLE/FAN_SPEED_MAX);
   }
   if(fan_speed == FAN_SPEED_MAX) {
      Ctrl2On();
   }
   else {
      if (triac_count2 < triac_on_time2) {
      Ctrl2On();
      } else {
         Ctrl2Off();
      }
   }
}

#endif // _TRIAC_H_

#ifndef _PROCESS_LEDS_H_
#define _PROCESS_LEDS_H_

#include "leds.h"
#include "keys.h"
//#include "adc.h"
//#include "triac.h"
#include "rtcc.h"
#include "cap1188.h"

void Process_Led(void)
{
   if ((timed_count_ms%151) == 0) {
      PutDateTime();
      switch (g_state) {
         case ST_SET_PROGRAM:
            LedSetTempOff();
            LedProtectTempOff();
            LedTimeDelayOff();
            LedTimeSterOff();
            switch (g_set){
               case SET_PROGRAM_USER:
                  led7[1][0] = 0x00;       
                  led7[1][1] = 0x00;       
                  led7[1][2] = 0xDC;       //'P'
                  led7[1][3] = 0x4F;       //'U'
                  break;
               case SET_TIME_REAL_TIME_CLOCK:
                  led7[1][0] = 0x00;       
                  led7[1][1] = Get7Seg(5);       
                  led7[1][2] = 0x80;             //'S'
                  led7[1][3] = Get7Seg(1);       //'1'
                  break;
               case SET_TIME_CLOCK:
                  led7[1][0] = 0x00;       
                  led7[1][1] = Get7Seg(5);       
                  led7[1][2] = 0x80;             //'S'
                  led7[1][3] = Get7Seg(2);       //'2'
                  break;
               default:
                  break;
            }
            Led_Dot_Off();
            led7[2][0] = 0x00;       
            led7[2][1] = 0x00;       
            led7[2][2] = 0x00;
            led7[2][3] = 0x00;
            break;
         case ST_SET_PASS:
         case ST_SAVE_PASS:
            led7[1][0] = 0xDC;
            led7[1][1] = 0xDD;
            led7[1][2] = Get7Seg(5);
            led7[1][3] = Get7Seg(5);
            
            led7[2][0] = Get7Seg(password / 1000);
            led7[2][1] = Get7Seg((password%1000) / 100);
            led7[2][2] = Get7Seg((password%100)/10);
            led7[2][3] = Get7Seg(password%10) ;
            break;
         case ST_SET_TIME_STER_DRY:
            LedSetTempOff();
            LedProtectTempOff();
            LedTimeDelayOff();
            LedTimeSterOff();
            Led_Prog_Off();
            led7[1][0] = 0x00;
            led7[1][1] = Get7Seg(5);
            led7[1][2] = 0xD6;       
            led7[1][3] = 0x54;

            PutSign(2,SIGN_BLANK);
            break;
         case ST_SET_SETPOINT:
            LedSetTempOn();
            LedProtectTempOff();
            LedTimeDelayOff();
            LedTimeSterOn();
            PutTempSign(1, setpoint);
            PutTime_One(2, ster_time);
            break;
         case ST_SET_PROTECT:
            LedSetTempOff();
            LedProtectTempOn();
            LedTimeDelayOff();
            LedTimeSterOn();
            PutTempSign(1, protect);
            PutTime_One(2, ster_time);
            break;
         case ST_SET_TIME_DELAY:
         case ST_SET_WAIT_TIME:
         case ST_RUN_WAITING_TIME:
            LedSetTempOff();
            LedProtectTempOff();
            LedTimeDelayOn();
            LedTimeSterOff();
            switch (wait_day) {                                                                                                                                                                                                                                                                                                                                                                                                     
                  case 1:
                  PutSign(1,SIGN_CN);
                  break;
                  case 2:
                  PutSign(1,SIGN_T2);
                  break;
                  case 3:
                  PutSign(1,SIGN_T3);
                  break;
                  case 4:
                  PutSign(1,SIGN_T4);
                  break;
                  case 5:
                  PutSign(1,SIGN_T5);
                  break;
                  case 6:
                  PutSign(1,SIGN_T6);
                  break;
                  case 7:
                  PutSign(1,SIGN_T7);
                  break;
                  case 0:
                  PutSign(1,SIGN_ALL);
                  break;
            }
            PutTime_One(2, delay_time);
            break;
         case ST_SET_HOLD_TIME:
            LedSetTempOff();
            LedProtectTempOn();
            LedTimeDelayOff();
            LedTimeSterOn();
            PutTempSign(1, protect);
            PutTime_One(2, ster_time);
            break;
         /*case ST_DIS_TIME_DAY_HOUR:
            LedSetTempOff();
            LedProtectTempOn();
            LedTimeDelayOff();
            LedTimeSterOn();
            PutTempSign(1, protect);

            led7[2][0] = 0x8F; //d
            led7[2][1] = 0x8F;
            led7[2][2] = 0xCD; //h
            led7[2][3] = 0xCD;
            break;
         case ST_DIS_TIME_HOUR_MIN:
            LedSetTempOff();
            LedProtectTempOn();
            LedTimeDelayOff();
            LedTimeSterOn();
            PutTempSign(1, protect);

            led7[2][0] = 0xCD; //h
            led7[2][1] = 0xCD;
            led7[2][2] = 0xDC; //p
            led7[2][3] = 0xDC;
            break;
         case ST_SET_TIME_DAY_HOUR:
            LedSetTempOff();
            LedProtectTempOn();
            LedTimeDelayOff();
            LedTimeSterOn();
            PutTempSign(1, protect);
            PutTime_DayHour(2,user_day_ster_time,user_hour_ster_time);
            break;
         case ST_SET_TIME_HOUR_MIN:
            LedSetTempOff();
            LedProtectTempOn();
            LedTimeDelayOff();
            LedTimeSterOn();
            PutTempSign(1, protect);
            PutTime_One(2, ster_time);
            break;*/
         case ST_SET_SERI:
            Led_Prog_Off();
            led7[1][0] = 0x00;
            led7[1][1] = 0x00;
            led7[1][2] = 0x44;
            led7[1][3] = 0x8F;
            
            led7[2][0] = Get7Seg(seri / 1000);
            led7[2][1] = Get7Seg((seri%1000) / 100);
            led7[2][2] = Get7Seg((seri%100)/10);
            led7[2][3] = Get7Seg(seri%10);
            break;
         case ST_RUN_HEATING_TIME:
            LedSetTempOn();
            LedProtectTempOff();
            LedTimeDelayOff();
            LedTimeSterOn();
            PutTempSign(1,realTemp);
            /*if(flag_day_hour == 0 && g_mode == USER_MODE) {
               PutTime_DayHour(2,user_day_ster_time,user_hour_ster_time);
            }
            else PutTime_One(2,user_ster_time);*/
            PutTime_One(2, ster_time);
            if (realTemp >= protect) {
               Beep(500);
               g_state = ST_ERR;
               old_state = g_state;
               if (realTemp >= MAX_TEMP_RANGE) {
                  PutSign(1, SIGN_SENSOR_BROKEN);
               } else {
                  PutSign(1, SIGN_TEMP_OVERLOAD);
                  LedProtectTempOn();
               }
            } else {
               LedProtectTempOff();
            }
            break;
         case ST_RUN_HOLDING_TIME:
            LedSetTempOn();
            LedProtectTempOff();
            LedTimeDelayOff();
            LedTimeSterOn();
            PutTempSign(1,realTemp);
            /*if(flag_day_hour == 0 && g_mode == USER_MODE) {
               PutTime_DayHour(2,day_remain_time,hour_remain_time);
            }
            else PutTime_One(2, remain_time);*/
            PutTime_One(2, remain_time);
            if (realTemp >= protect) {
               Beep(500);
               g_state = ST_ERR;
               old_state = g_state;
               if (realTemp >= MAX_TEMP_RANGE) {
                  PutSign(1, SIGN_SENSOR_BROKEN);
               } else {
                  PutSign(1, SIGN_TEMP_OVERLOAD);
                  LedProtectTempOn();
               }
            } else {
               LedProtectTempOff();
            }
            break;
         case ST_RUN_COOLING_TIME:
            LedSetTempOn();
            LedProtectTempOff();
            LedTimeDelayOff();
            LedTimeSterOff();
            PutTempSign(1,realTemp);
            PutTime_One(2, 0);
            if (realTemp >= protect) {
               Beep(500);
               g_state = ST_ERR;
               old_state = g_state;
               if (realTemp >= MAX_TEMP_RANGE) {
                  PutSign(1, SIGN_SENSOR_BROKEN);
               } else {
                  PutSign(1, SIGN_TEMP_OVERLOAD);
                  LedProtectTempOn();
               }
            } else {
               LedProtectTempOff();
            }
            break;
            break;
         case ST_SET_PID_KP:
            Led_F_On();
            PutPid(1,pid_Kp);
            break;
         case ST_SET_PID_KI:
            Led_E_On();
            PutPid(1,pid_Ki);
            break;
         case ST_SET_PID_KD:
            Led_D_On();
            PutPid(1,pid_Kd);
            break;
         case ST_COMPLETED:
            LedSetTempOn();
            LedProtectTempOff();
            LedTimeDelayOff();
            LedTimeSterOff();
            PutTempSign(1,realTemp);
            PutSign(2, SIGN_PROCESS_END);
            break;
         case ST_IDLE:
            LedSetTempOn();
            LedProtectTempOff();
            LedTimeDelayOff();
            LedTimeSterOn();
            PutTempSign(1, setpoint);
            PutTime_One(2, ster_time);
            /*if(flag_day_hour == 0 && g_mode == USER_MODE) {
               PutTime_DayHour(2,user_day_ster_time,user_hour_ster_time);
            }
            else PutTime_One(2,user_ster_time);*/
            Led_Prog_Off();
            switch (g_mode)
            {
               case PROGRAM1:
                  Led_0_On();
                  break;
               case PROGRAM2:
                  Led_1_On();
                  break;
               case PROGRAM3:
                  Led_2_On();
                  break;
               case PROGRAM4:
                  Led_3_On();
                  break;
               case PROGRAM5:
                  Led_4_On();
                  break;
               case PROGRAM6:
                  Led_5_On();
                  break;
               case PROGRAM7:
                  Led_6_On();
                  break;
               case PROGRAM8:
                  Led_7_On();
                  break;
               case PROGRAM9:
                  Led_8_On();
                  break;
               case PROGRAM10:
                  Led_A_On();
                  break;
               case USER_MODE:
                  Led_D_On();
                  break;
            }
            break;
      }
   } else {
      if (40 == timed_count_ms) {
         switch (g_state) {
            case ST_SET_DAY_OF_WEEK:
               led1[2] |= 0xFE;
               break;
            case ST_SET_HOUR:
               led7[0][0] = 0;
               led7[0][1] = 0;
               break;
            case ST_SET_MINUTE:
               led7[0][2] = 0;
               led7[0][3] = 0;
               break;
            case ST_SET_SETPOINT:
               led1[1] |= 0x01;
               break;
            case ST_SET_PROTECT:
               led1[1] |= 0x02;
               break;
            case ST_SET_TIME_DELAY:
               led1[1] |= 0x04;
               PutSign(1,SIGN_BLANK);
               break;
            case ST_SET_PROGRAM:
               PutSign(1,SIGN_BLANK);
               break;
            case ST_SET_WAIT_TIME:
               led1[1] |= 0x04;
               PutSign(2,SIGN_BLANK);
               break;
            case ST_SET_HOLD_TIME:
               led1[1] |= 0x08;
               break;
            case ST_SET_PID_KP:
            case ST_SET_PID_KI:
            case ST_SET_PID_KD:
               Led_Prog_Off();
               break;
         }
      }
   }   
}

#endif // #define _PROCESS_LEDS_H_

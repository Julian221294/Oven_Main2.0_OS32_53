#ifndef _PROCESS_LIFECYCLE_H_
#define _PROCESS_LIFECYCLE_H_

#define TEMP_GAP 0
#define TEMP_ENV 10000
#define TIME_PRE_HOLD   5
void process_lifecycle(void)
{
   switch(g_state) {
      case ST_RUN_WAITING_TIME:
         if(((BCD2Dec(hour) == wait_hour) && (BCD2Dec(min) == wait_min) || (0 == user_delay_time)) && ((BCD2Dec(day) == wait_day) || (0 == wait_day))) {
            g_state = ST_RUN_HEATING_TIME;
            flag_Pre_Hold = 0;
            /*if(flag_day_hour == 0 && g_mode == USER_MODE) remain_time = user_hold_time;
            else remain_time = user_ster_time;*/
            LedHeaterOn();
         }
         break;
      case ST_RUN_HEATING_TIME:
         if (realTemp >= (setpoint - TEMP_GAP) && flag_Pre_Hold == 0) {
            remain_time = TIME_PRE_HOLD;
            flag_Pre_Hold = 1;
            //remain_time = ster_time;
            //g_state = ST_RUN_HOLDING_TIME;
         }
         if (realTemp >= (setpoint - TEMP_GAP ) && flag_Pre_Hold == 1 && remain_time == 0) {
            g_state = ST_RUN_HOLDING_TIME;
            remain_time = ster_time;
            flag_Pre_Hold = 0;
         }
         break;
      case ST_RUN_HOLDING_TIME:
         if(remain_time == 0) {
            g_state = ST_RUN_COOLING_TIME;
            LedHeaterOff();
         }
         break;
      case ST_RUN_COOLING_TIME:
         if (realTemp < TEMP_ENV) {
            g_state = ST_COMPLETED;
            old_state = g_state;
            Beep(3000);
         }
   }
}

#endif // define _PROCESS_LIFECYCLE_H_


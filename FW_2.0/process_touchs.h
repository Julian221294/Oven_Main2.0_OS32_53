#ifndef _PROCESS_KEYS_H_
#define _PROCESS_KEYS_H_

#include "leds.h"
#include "keys.h"
//#include "adc.h"
//#include "triac.h"
#include "rtcc.h"
#include "cap1188.h"
//unsigned char setpoint_H, setpoint_L, protect_H, protect_L;
//int8 a,b,e,f,g,h,k;
static char n = 0;

void Process_Touch(void);

void Process_Touch_0(void);
void Process_Touch_1(void);
void Process_Touch_2(void);
void Process_Touch_3(void);
void Process_Touch_4(void);
void Process_Touch_5(void);
void Process_Touch_6(void);
void Process_Touch_7(void);
void Process_Touch_8(void);
void Process_Touch_9(void);
void Process_Touch_A(void);
void Process_Touch_B(void);
void Process_Touch_C(void);
void Process_Touch_D(void);
void Process_Touch_E(void);
void Process_Touch_F(void);
void Process_Touch_Down(void);
void Process_Touch_Up(void);
void Process_Touch_a_Small(void);
void Process_Touch_b_Small(void);
//void Process_Touch_c_Small(void);
void Process_Touch_d_Small(void);
void Process_Touch_e_Small(void);
void Process_Touch_f_Small(void);
void Process_Touch_h_Small(void);

void Process_Setup(void);

void Process_Touch(void)
{
   if(key_flag) {
      beep(BEEP_TIME);
      switch(key_code)
      {
         case '0':
            Process_Touch_0();
            Process_Setup();
            break;
         case '1':
            Process_Touch_1();
            Process_Setup();
            break;
         case '2':
            Process_Touch_2();
            Process_Setup();
            break;
         case '3':
            Process_Touch_3();
            Process_Setup();
            break;
         case '4':
            Process_Touch_4();
            Process_Setup();
            break;
         case '5':
            Process_Touch_5();
            Process_Setup();
            break;
         case '6':
            Process_Touch_6();
            Process_Setup();
            break;
         case '7':
            Process_Touch_7();
            Process_Setup();
            break;
         case '8':
            Process_Touch_8();
            Process_Setup();
            break;
         case '9':
            Process_Touch_9();
            break;
         case 'A':
            Process_Touch_A();
            Process_Setup();
            break;
         case 'B':
            Process_Touch_B();
            break;
         case 'C':
            Process_Touch_C();
            break;
         case 'D':
            Process_Touch_D();
            break;
         case 'E':
            Process_Touch_Down();
            break;
         case 'F':
            Process_Touch_Up();
            break;
         case 'a':
            Process_Touch_a_Small();
            break;
         case 'b':
            Process_Touch_b_Small();
            break;
         /*case 'c':
            Process_Touch_c_Small();
            break;*/
         case 'd':
            Process_Touch_d_Small();
            break;
         case 'e':
            Process_Touch_e_Small();
            break;
         case 'f':
            Process_Touch_f_Small();
            break;
         case 'h':
            Process_Touch_h_Small();
            break;
      }
      key_flag = 0;
   }
   if ((24 > wait_hour) && (wait_min < 60)) {
            user_delay_time = (int16)wait_hour * 60 + wait_min;
      }
      else {
            user_delay_time = 0;
            wait_hour = 0;
            wait_min = 0;
      }
            delay_time = user_delay_time;
}

void Process_Touch_0(void)
{
   i  = 1;
   switch (g_state) {
      case ST_IDLE:
      case ST_SET_TIME_STER_DRY:
         Led_Prog_Off();
         Led_0_On();
         g_mode = PROGRAM1;
         /*g_active_mode = read_eeprom(0x50);
         if (g_active_mode != MODE_SET_1) {
            g_active_mode = MODE_STAND;
         }*/
         Load_Data_Program_EEPROM();
         setpoint = user_setpoint;
         protect = user_protect;
         ster_time = user_ster_time;
         /*if (g_state == ST_SET_TIME_STER_DRY) {
            g_state = ST_SET_SETPOINT;
            g_active_mode = MODE_SET_1;
         }*/
         break;
   }
}
void Process_Touch_1(void)
{
   i  = 2;
   switch (g_state) {
      case ST_IDLE:
      case ST_SET_TIME_STER_DRY:
         Led_Prog_Off();
         Led_1_On();
         g_mode = PROGRAM2;
         /*g_active_mode = read_eeprom(0x51);
         if (g_active_mode != MODE_SET_2) {
            g_active_mode = MODE_STAND;
         }*/
         Load_Data_Program_EEPROM();
         setpoint = user_setpoint;
         protect = user_protect;
         ster_time = user_ster_time;
         /*if (g_state == ST_SET_TIME_STER_DRY) {
            g_state = ST_SET_SETPOINT;
            g_active_mode = MODE_SET_2;
         }*/
         break;
   }
}
void Process_Touch_2(void)
{
   i  = 3;
   switch (g_state) {
      case ST_IDLE:
      case ST_SET_TIME_STER_DRY:
         Led_Prog_Off();
         Led_2_On();
         g_mode = PROGRAM3;
         /*g_active_mode = read_eeprom(0x52);
         if (g_active_mode != MODE_SET_3) {
            g_active_mode = MODE_STAND;
         }*/
         Load_Data_Program_EEPROM();
         setpoint = user_setpoint;
         protect = user_protect;
         ster_time = user_ster_time;
         /*if (g_state == ST_SET_TIME_STER_DRY) {
            g_state = ST_SET_SETPOINT;
            g_active_mode = MODE_SET_3;
         }*/
         break;
   }
}
void Process_Touch_3(void)
{
   i  = 4;
   switch (g_state) {
      case ST_IDLE:
      case ST_SET_TIME_STER_DRY:
         Led_Prog_Off();
         Led_3_On();
         g_mode = PROGRAM4;
         /*g_active_mode = read_eeprom(0x53);
         if (g_active_mode != MODE_SET_4) {
            g_active_mode = MODE_STAND;
         }*/
         Load_Data_Program_EEPROM();
         setpoint = user_setpoint;
         protect = user_protect;
         ster_time = user_ster_time;
         /*if (g_state == ST_SET_TIME_STER_DRY) {
            g_state = ST_SET_SETPOINT;
            g_active_mode = MODE_SET_4;
         }*/
         break;
   }
}
void Process_Touch_4(void)
{
   i  = 5;
   switch (g_state) {
      case ST_IDLE:
      case ST_SET_TIME_STER_DRY:
         Led_Prog_Off();
         Led_4_On();
         g_mode = PROGRAM5;
         /*g_active_mode = read_eeprom(0x54);
         if (g_active_mode != MODE_SET_5) {
            g_active_mode = MODE_STAND;
         }*/
         Load_Data_Program_EEPROM();
         setpoint = user_setpoint;
         protect = user_protect;
         ster_time = user_ster_time;
         /*if (g_state == ST_SET_TIME_STER_DRY) {
            g_state = ST_SET_SETPOINT;
            g_active_mode = MODE_SET_5;
         }*/
         break;
   }
}
void Process_Touch_5(void)
{
   i  = 6;
   switch (g_state) {
      case ST_IDLE:
      case ST_SET_TIME_STER_DRY:
         Led_Prog_Off();
         Led_5_On();
         g_mode = PROGRAM6;
         /*g_active_mode = read_eeprom(0x55);
         if (g_active_mode != MODE_SET_6) {
            g_active_mode = MODE_STAND;
         }*/
         Load_Data_Program_EEPROM();
         setpoint = user_setpoint;
         protect = user_protect;
         ster_time = user_ster_time;
         /*if (g_state == ST_SET_TIME_STER_DRY) {
            g_state = ST_SET_SETPOINT;
            g_active_mode = MODE_SET_6;
         }*/
         break;
   }
}
void Process_Touch_6(void)
{
   i  = 7;
   switch (g_state) {
      case ST_IDLE:
      case ST_SET_TIME_STER_DRY:
         Led_Prog_Off();
         Led_6_On();
         g_mode = PROGRAM7;
         /*g_active_mode = read_eeprom(0x56);
         if (g_active_mode != MODE_SET_7) {
            g_active_mode = MODE_STAND;
         }*/
         Load_Data_Program_EEPROM();
         setpoint = user_setpoint;
         protect = user_protect;
         ster_time = user_ster_time;
         /*if (g_state == ST_SET_TIME_STER_DRY) {
            g_state = ST_SET_SETPOINT;
            g_active_mode = MODE_SET_7;
         }*/
         break;
   }
}
void Process_Touch_7(void)
{
   i  = 8;
   switch (g_state) {
      case ST_IDLE:
      case ST_SET_TIME_STER_DRY:
         Led_Prog_Off();
         Led_7_On();
         g_mode = PROGRAM8;
         /*g_active_mode = read_eeprom(0x57);
         if (g_active_mode != MODE_SET_8) {
            g_active_mode = MODE_STAND;
         }*/
         Load_Data_Program_EEPROM();
         setpoint = user_setpoint;
         protect = user_protect;
         ster_time = user_ster_time;
         /*if (g_state == ST_SET_TIME_STER_DRY) {
            g_state = ST_SET_SETPOINT;
            g_active_mode = MODE_SET_8;
         }*/
         break;
   }
}
void Process_Touch_8(void)
{
   i  = 9;
   switch (g_state) {
      case ST_IDLE:
      case ST_SET_TIME_STER_DRY:
         Led_Prog_Off();
         Led_8_On();
         g_mode = PROGRAM9;
         /*g_active_mode = read_eeprom(0x58);
         if (g_active_mode != MODE_SET_9) {
            g_active_mode = MODE_STAND;
         }*/
         Load_Data_Program_EEPROM();
         setpoint = user_setpoint;
         protect = user_protect;
         ster_time = user_ster_time;
         /*if (g_state == ST_SET_TIME_STER_DRY) {
            g_state = ST_SET_SETPOINT;
            g_active_mode = MODE_SET_9;
         }*/
         break;
   }
}
void Process_Touch_A(void)
{
   i  = 0;
   switch (g_state) {
      case ST_IDLE:
      case ST_SET_TIME_STER_DRY:
         Led_Prog_Off();
         Led_A_On();
         g_mode = PROGRAM10;
         /*g_active_mode = read_eeprom(0x59);
         if (g_active_mode != MODE_SET_10) {
            g_active_mode = MODE_STAND;
         }*/
         Load_Data_Program_EEPROM();
         setpoint = user_setpoint;
         protect = user_protect;
         ster_time = user_ster_time;
         /*if (g_state == ST_SET_TIME_STER_DRY) {
            g_state = ST_SET_SETPOINT;
            g_active_mode = MODE_SET_10;
         }*/
         break;
   }
}
void Process_Touch_D(void) // Set
{
   if (g_state == ST_IDLE || (g_state == ST_SET_PROGRAM && g_set == SET_PROGRAM_USER)) {
      Load_Data_User();
      setpoint = user_setpoint;
      protect = user_protect;
      ster_time = user_ster_time;
   }
   switch (g_state) {
      case ST_IDLE:
         Led_Prog_Off();
         Led_D_On();
         g_mode = USER_MODE;
         break;
      case ST_SET_PROGRAM:
         switch(g_set) {
            case SET_PROGRAM_USER:
               g_mode = USER_MODE;
               Led_Prog_Off();
               Led_D_On();
               g_state = ST_SET_SETPOINT;
               break;
            case SET_TIME_REAL_TIME_CLOCK:
               g_state = ST_SET_DAY_OF_WEEK;
               break;
            case SET_TIME_CLOCK:
               g_state = ST_SET_TIME_DELAY;
               break;
         }
         break;
      case ST_SET_DAY_OF_WEEK:
         g_state = ST_SET_HOUR;
         break;
      case ST_SET_HOUR:
         g_state = ST_SET_MINUTE;
         break;
      case ST_SET_TIME_DELAY:
         g_state = ST_SET_WAIT_TIME;
         hour_min_flag = 1;
         Led_Dot_On();
         break;
      case ST_SET_MINUTE:
         Led_Dot_Off();
         g_state = ST_SET_PROGRAM;
         break;
      case ST_SET_WAIT_TIME:
         Store_WaitTime();
         g_state = ST_SET_PROGRAM;
         break;
         case ST_SET_HOLD_TIME:
            hold_hour = user_ster_time/60;
            hold_min = user_ster_time%60;
            g_state = ST_SET_PROGRAM;
            Check_Data_Previous();
            Store_Setpoint();
            Store_Protect();
            Store_HoldTime();
            break;
      /*case ST_DIS_TIME_DAY_HOUR:
         g_state = ST_SET_TIME_DAY_HOUR;
         flag_day_hour = 0;
         user_ster_time = ster_time = 0;
         break;
      case ST_DIS_TIME_HOUR_MIN:
         g_state = ST_SET_TIME_HOUR_MIN;
         flag_day_hour = 1;
         user_day_ster_time = day_ster_time = 0;
         user_hour_ster_time = hour_ster_time = 0;
         break;
      case ST_SET_TIME_DAY_HOUR:
      case ST_SET_TIME_HOUR_MIN:
         g_state = ST_SET_PROGRAM;
         Check_Data_Previous();
         Store_Setpoint();
         Store_Protect();
         Store_DayTime();
         Store_HourTime();
         Store_HoldTime();
         write_eeprom(0x50, flag_day_hour);
         user_hold_time = user_day_ster_time*24*60 + user_hour_ster_time*60;
         break;*/
      case ST_SET_PASS:
      case ST_SAVE_PASS:
         if (password == check_password) {
            //g_state = ST_SET_TIME_STER_DRY;
            g_state = ST_SET_SERI;
            password = 0;
         }
         else password = 0;
         break;
      case ST_SET_SERI:
         Store_SERI();
         //flag_ID = 0;
         g_state = ST_IDLE;
         break;
   }
}
void Process_Touch_9(void) // .
{
   switch (g_state) {
      case ST_SET_WAIT_TIME:
      case ST_SET_HOLD_TIME:
      case ST_SET_TIME_DAY_HOUR:
      case ST_SET_TIME_HOUR_MIN:
         if(0 == hour_min_flag) {
            hour_min_flag = 1;
            Led_Dot_On();
         } else {
            hour_min_flag = 0;
            if(ster_time == 0) {
               n = 1;
            }
            Led_Dot_Off();
         }
         break;
   }
}
void Process_Touch_B(void) //Clear
{
   switch (g_state) {
      case ST_SET_SETPOINT:
         setpoint = 0;
         user_setpoint = setpoint;
         break;
      case ST_SET_PROTECT:
         protect = 0;
         user_protect = protect;
         break;
      case ST_SET_WAIT_TIME:
         delay_time = 0;
         wait_hour = 0;
         wait_min = 0;
         user_delay_time = delay_time;
         hour_min_flag = 1;
         Led_Dot_On();
         break;
      case ST_SET_HOLD_TIME:
      //case ST_SET_TIME_DAY_HOUR:
      //case ST_SET_TIME_HOUR_MIN:
         ster_time = 0;
         user_ster_time = ster_time;
         /*day_ster_time = 0;
         user_day_ster_time = day_ster_time;
         day_remain_time = user_day_ster_time;
         hour_ster_time = 0;
         user_hour_ster_time = hour_ster_time;
         hour_remain_time = user_hour_ster_time;*/
         hour_min_flag = 1;
         n = 0;
         Led_Dot_On();
         break;
      case ST_SET_PASS:
         password = 0;
         break;
      case ST_SET_SERI:
         seri = 0;
         break;
   }
}
void Process_Touch_C(void) //Start/Stop
{
   if (g_state <= ST_SET_OFFSET) {
      g_state = ST_RUN_WAITING_TIME;
      old_state = g_state;
      Led_C_On();
      Store_Mode();
      Load_PID();
      remain_time = delay_time;
      last_min = read_ds1307(1);
      flag_Rs232 = 1;
      flag_Rs232_Ster = 1;
      flag_Rs232_Complete = 1;
      flag_Rs232_Err = 1;
      flag_Pre_Hold = 0;
      /*switch (g_mode) {
         case PROGRAM1:
            write_eeprom(0x50, g_active_mode);
         break;
         case PROGRAM2:
            write_eeprom(0x51, g_active_mode);
         break;
         case PROGRAM3:
            write_eeprom(0x52, g_active_mode);
         break;
         case PROGRAM4:
            write_eeprom(0x53, g_active_mode);
         break;
         case PROGRAM5:
            write_eeprom(0x54, g_active_mode);
         break;
         case PROGRAM6:
            write_eeprom(0x55, g_active_mode);
         break;
         case PROGRAM7:
            write_eeprom(0x56, g_active_mode);
         break;
         case PROGRAM8:
            write_eeprom(0x57, g_active_mode);
         break;
         case PROGRAM9:
            write_eeprom(0x58, g_active_mode);
         break;
         case PROGRAM10:
            write_eeprom(0x59, g_active_mode);
         break;
      }*/
   } else {
      g_state = ST_IDLE;
      Led_C_Off();
      g_mode = read_DS1307(0x08);
      flag_Rs232 = 0;
      flag_Rs232_Ster = 0;
      flag_Rs232_Complete = 0;
      flag_Rs232_Err = 0;
      flag_Pre_Hold = 0;
      if(old_state != ST_IDLE && old_state != ST_COMPLETED && old_state != ST_ERR) {
         flag_Rs232_IDLE = 1;
         old_state = ST_IDLE;
      }
      switch(g_mode) {
         case PROGRAM1:
            Process_Touch_0();
            break;
         case PROGRAM2:
            Process_Touch_1();
            break;
         case PROGRAM3:
            Process_Touch_2();
            break;
         case PROGRAM4:
            Process_Touch_3();
            break;
         case PROGRAM5:
            Process_Touch_4();
            break;
         case PROGRAM6:
            Process_Touch_5();
            break;
         case PROGRAM7:
            Process_Touch_6();
            break;
         case PROGRAM8:
            Process_Touch_7();
            break;
         case PROGRAM9:
            Process_Touch_8();
            break;
         case PROGRAM10:
            Process_Touch_A();
            break;
         default:
            Led_D_On();
            delay_time = user_delay_time;
            ster_time = user_ster_time;
            /*if(flag_day_hour == 0) {
               user_hold_time = (user_day_ster_time)*24*60 + user_hour_ster_time*60;
               day_remain_time = user_day_ster_time;
               hour_remain_time = user_hour_ster_time;
            }
            if(flag_day_hour == 1) {
               user_hold_time = (unsigned int16)(user_ster_time);
            }*/
            setpoint = user_setpoint;
            protect = user_protect;
            break;
      }
   }
}

void Process_Touch_Down(void) //Down
{
   int8 d1, d0;
   switch(g_state) {
      case ST_SET_PROGRAM:
         switch (g_set) {
            case SET_TIME_CLOCK:
               g_set = SET_TIME_REAL_TIME_CLOCK;
               break;
            case SET_TIME_REAL_TIME_CLOCK:
               g_set = SET_PROGRAM_USER;
               break;
         }
         break;
      case ST_SET_SETPOINT:
         g_state = ST_SET_PROTECT;
         break;
      case ST_SET_PROTECT:
         g_state = ST_SET_HOLD_TIME;
         //g_state = ST_DIS_TIME_DAY_HOUR;
         hour_min_flag = 1;
         Led_Dot_On();
         break;
      /*case ST_DIS_TIME_DAY_HOUR:
         g_state = ST_DIS_TIME_HOUR_MIN;
         break;*/
      /*case ST_SET_HOLD_TIME:
         switch (g_mode) {
            case USER_MODE:
               Store_WaitTime();
               Store_HoldTime();
               Store_Setpoint();
               Store_Protect();
               break;
            /*case PROGRAM1:
               a = 0x09;
               b = 0x0A;
               e = 0x0D;
               f = 0x0E;
               g = 0x12;
               h = 0x13;
               k = 0x50;
               break;
            case PROGRAM2:
               a = 0x16;
               b = 0x17;
               e = 0x1A;
               f = 0x1F;
               g = 0x22;
               h = 0x23;
               k = 0x51;
               break;
            case PROGRAM3:
               a = 0x07;
               b = 0x08;
               e = 0x30;
               f = 0x31;
               g = 0x32;
               h = 0x33;
               k = 0x52;
               break;
            case PROGRAM4:
               a = 0x0B;
               b = 0x0C;
               e = 0x34;
               f = 0x35;
               g = 0x36;
               h = 0x37; 
               k = 0x53;
               break;
            case PROGRAM5:
               a = 0x10;
               b = 0x11;
               e = 0x38;
               f = 0x39;
               g = 0x3A;
               h = 0x3B;
               k = 0x54;
               break;
            case PROGRAM6:
               a = 0x14;
               b = 0x15;
               e = 0x3C;
               f = 0x3D;
               g = 0x3E;
               h = 0x3F; 
               k = 0x55;
               break;
            case PROGRAM7:
               a = 0x18;
               b = 0x19;
               e = 0x40;
               f = 0x41;
               g = 0x42;
               h = 0x43; 
               k = 0x56;
               break;
            case PROGRAM8:
               a = 0x20;
               b = 0x21;
               e = 0x44;
               f = 0x45;
               g = 0x46;
               h = 0x47; 
               k = 0x57;
               break;
            case PROGRAM9:
               a = 0x24;
               b = 0x25;
               e = 0x48;
               f = 0x49;
               g = 0x4A;
               h = 0x4B; 
               k = 0x58;
               break;
            case PROGRAM10:
               a = 0x28;
               b = 0x29;
               e = 0x4C;
               f = 0x4D;
               g = 0x4E;
               h = 0x4F; 
               k = 0x59;
               break;
         }
         if (g_mode >= PROGRAM1 && g_mode <= PROGRAM10) {
            write_eeprom(a, hold_hour);
            write_eeprom(b, hold_min);
            write_eeprom(e, setpoint_H);
            write_eeprom(f, setpoint_L);
            write_eeprom(g, protect_H);
            write_eeprom(h, protect_L);
            write_eeprom(k, g_active_mode);
         }
         if (g_mode == USER_MODE) {
            g_state = ST_SET_PROGRAM;
         }
         //else g_state = ST_SET_TIME_STER_DRY;
         setpoint = user_setpoint;
         protect = user_protect;
         ster_time = user_ster_time;
         break;*/
      case ST_SET_PID_KP:
         if (pid_kp > 0) {
            pid_kp -= 1;
            PutPid(1, pid_kp);
            Store_Kp();
         }
         break;
      case ST_SET_PID_KI:
         if (pid_ki > 0) {
            pid_ki -= 1;
            PutPid(1, pid_ki);
            Store_Ki();
         }
         break;
      case ST_SET_PID_KD:
         if (pid_kd > 0) {
            pid_kd -= 1;
            PutPid(1, pid_kd);
            Store_Kd();
         }
         break;
      case ST_SET_OFFSET:
         if (temp_offset > -OFFSET_TEMP_RANGE) {
            temp_offset -= 10;
            PutOffset(1, temp_offset);
            Store_Offset();
         }
         break;
      case ST_SET_DAY_OF_WEEK:
         if(day > SUNDAY)
            day -= 1;
         else
            day = SATURDAY;
         write_ds1307(3, day);
         break;
      case ST_SET_HOUR:
         d1 = hour / 16;
         d0 = hour & 0x0F;
         if (d0 > 0)
            d0 -= 1;
         else {
            if (d1 > 0) {
                  d0 = 9;
                  d1 -= 1;
            }   
            else {
                  d0 = 0;
                  d1 = 0;
            }
         }
         hour = d1 * 16 + d0;
         write_ds1307(2, hour);
         break;
      case ST_SET_MINUTE:
         d1 = min / 16;
         d0 = min & 0x0F;
         if (d0 > 0)
            d0 -= 1;
         else {
            d0 = 9;
            if (d1 > 0)
               d1 -= 1;
            else
               d1 = 5;
         }
         min = d1 * 16 + d0;
         write_ds1307(1, min);
         break;
      case ST_SET_TIME_DELAY:
         if(wait_day > 0)
            wait_day -= 1;
         else {
            wait_day = 0;
         }
         write_DS1307(0x1D,wait_day);
         break;
      default:
      if(g_set == SET_NONE)
      {
         if (fan_speed >= (FAN_SPEED_MIN+1)) {
            fan_speed -= 1;
            Store_FanSpeed();
         }
      }
         break;
    }
}
void Process_Touch_Up(void) //Up
{
   int8 d1, d0;
   switch(g_state){
      case ST_SET_PROGRAM:
         switch (g_set) {
            case SET_PROGRAM_USER:
               g_set = SET_TIME_REAL_TIME_CLOCK;
               break;
            case SET_TIME_REAL_TIME_CLOCK:
               g_set = SET_TIME_CLOCK;
               break;
         }
         break;
      /*case ST_SET_SETPOINT:
         hold_hour = user_ster_time/60;
         hold_min = user_ster_time%60;

         setpoint_H = user_setpoint >> 8;
         setpoint_L = user_setpoint & 0xFF;
         protect_H = user_protect >> 8;
         protect_L = user_protect & 0xFF;

         Check_Data_Previous();
         switch (g_mode) {
            case USER_MODE:
               Store_WaitTime();
               Store_HoldTime();
               Store_Setpoint();
               Store_Protect();
               break;
            /*case PROGRAM1:
               a = 0x09;
               b = 0x0A;
               e = 0x0D;
               f = 0x0E;
               g = 0x12;
               h = 0x13;
               k = 0x50;
               break;
            case PROGRAM2:
               a = 0x16;
               b = 0x17;
               e = 0x1A;
               f = 0x1F;
               g = 0x22;
               h = 0x23;
               k = 0x51;
               break;
            case PROGRAM3:
               a = 0x07;
               b = 0x08;
               e = 0x30;
               f = 0x31;
               g = 0x32;
               h = 0x33;
               k = 0x52;
               break;
            case PROGRAM4:
               a = 0x0B;
               b = 0x0C;
               e = 0x34;
               f = 0x35;
               g = 0x36;
               h = 0x37; 
               k = 0x53;
               break;
            case PROGRAM5:
               a = 0x10;
               b = 0x11;
               e = 0x38;
               f = 0x39;
               g = 0x3A;
               h = 0x3B;
               k = 0x54;
               break;
            case PROGRAM6:
               a = 0x14;
               b = 0x15;
               e = 0x3C;
               f = 0x3D;
               g = 0x3E;
               h = 0x3F; 
               k = 0x55;
               break;
            case PROGRAM7:
               a = 0x18;
               b = 0x19;
               e = 0x40;
               f = 0x41;
               g = 0x42;
               h = 0x43; 
               k = 0x56;
               break;
            case PROGRAM8:
               a = 0x20;
               b = 0x21;
               e = 0x44;
               f = 0x45;
               g = 0x46;
               h = 0x47; 
               k = 0x58;
               break;
            case PROGRAM9:
               a = 0x24;
               b = 0x25;
               e = 0x48;
               f = 0x49;
               g = 0x4A;
               h = 0x4B; 
               k = 0x58;
               break;
            case PROGRAM10:
               a = 0x28;
               b = 0x29;
               e = 0x4C;
               f = 0x4D;
               g = 0x4E;
               h = 0x4F; 
               k = 0x59;
               break;
         }
         /*if (g_mode >= PROGRAM1 && g_mode <= PROGRAM10) {
            write_eeprom(a, hold_hour);
            write_eeprom(b, hold_min);
            write_eeprom(e, setpoint_H);
            write_eeprom(f, setpoint_L);
            write_eeprom(g, protect_H);
            write_eeprom(h, protect_L);
            write_eeprom(k, g_active_mode);
         }
         if (g_mode == USER_MODE) {
            g_state = ST_SET_PROGRAM;
         }
         //else g_state = ST_SET_TIME_STER_DRY;
         setpoint = user_setpoint;
         protect = user_protect;
         ster_time = user_ster_time;
         break;*/
      case ST_SET_PROTECT:
         g_state = ST_SET_SETPOINT;
         break;
      /*case ST_DIS_TIME_DAY_HOUR:
         g_state = ST_DIS_TIME_HOUR_MIN;
         Led_Dot_Off();
         break;
      case ST_DIS_TIME_HOUR_MIN:
         g_state = ST_DIS_TIME_DAY_HOUR;
         break;*/
      case ST_SET_HOLD_TIME:
         g_state = ST_SET_PROTECT;
         Led_Dot_Off();
         break;
      case ST_SET_PID_KP:
         if (pid_kp < (100)) {
            pid_kp += 1;
            PutPid(1, pid_kp);
            Store_Kp();
         }
         break;
      case ST_SET_PID_KI:
         if (pid_ki < (100)) {
            pid_ki += 1;
            PutPid(1, pid_ki);
            Store_Ki();
         }
         break;
      case ST_SET_PID_KD:
         if (pid_kd < (100)) {
            pid_kd += 1;
            PutPid(1, pid_kd);
            Store_Kd();
         }
         break;
      case ST_SET_OFFSET:
         if (temp_offset < OFFSET_TEMP_RANGE) {
            temp_offset += 10;
            PutOffset(1, temp_offset);
            Store_Offset();
         }
         break;
      case ST_SET_DAY_OF_WEEK:
         if(day < SATURDAY)
            day += 1;
         else
            day = SUNDAY;
         write_ds1307(3, day);
         break;
      case ST_SET_HOUR:
         d1 = hour / 16;
         d0 = hour & 0x0F;
         if((d1*10+d0) < 24) {
            d0 += 1;
            d1 += d0/10;
            d0 %= 10;
            hour = d1*16 + d0;
         } else {
            hour = 0;
         }
         write_ds1307(2, hour);
         break;
      case ST_SET_MINUTE:
         d1 = min / 16;
         d0 = min & 0x0F;
         if((d1*10+d0) < 59) {
            d0 += 1;
            d1 += d0/10;
            d0 %= 10;
            min = d1*16 + d0;
         } else {
            min = 0;
         }
         write_ds1307(1, min);
         break;
      case ST_SET_TIME_DELAY:
         if(wait_day < 7)
            wait_day += 1;
         else {
               wait_day = 0;
         }
         write_DS1307(0x1D,wait_day);
         break;
      default:
      if(g_set == SET_NONE)
      {
         if (fan_speed <= (FAN_SPEED_MAX-1)) {
            fan_speed += 1;
            Store_FanSpeed();
         }
      }
         break;
   }
}

//-------------------------------------------------------------------------------------------------------------
void Process_Touch_d_small()
{
   switch(g_state) {
      case ST_IDLE:
         g_state = ST_SET_PROGRAM;
         g_set = SET_PROGRAM_USER;
         break;
      case ST_SET_PROGRAM:
         g_state = ST_IDLE;
         g_set = SET_NONE;
         break;
      case ST_SET_PASS:
         check_password = password;
         Store_Password();
         password = 0;
         break;
   }
}

void Process_Touch_a_small()
{
   if (g_state == ST_IDLE) {
      beep(BEEP_TIME);
      g_state = ST_SET_OFFSET;
      PutOffset(1, temp_offset);
   } else if (g_state == ST_SET_OFFSET){
      beep(BEEP_TIME);
      g_state = ST_IDLE;
   }
}

void Process_Touch_b_small() //Key 1
{
   if (g_state == ST_IDLE) {
      Load_PID();
      beep(BEEP_TIME);
      g_state = ST_SET_PID_KD;
      PutPid(1, pid_kd);
   } else if (g_state == ST_SET_PID_KD){
      beep(BEEP_TIME);
      g_state = ST_IDLE;
   }
}

void Process_Touch_e_small() //Key 2
{
   if (g_state == ST_IDLE) {
      beep(BEEP_TIME);
      Load_PID();
      g_state = ST_SET_PID_KI;
      PutPid(1, pid_ki);
   } else if (g_state == ST_SET_PID_KI){
      beep(BEEP_TIME);
      g_state = ST_IDLE;
   }
}

void Process_Touch_f_small() {  //Key 3
   if (g_state == ST_IDLE) {
      Load_PID();
      g_state = ST_SET_PID_KP;
      PutPid(1, pid_kp);
   } else if (g_state == ST_SET_PID_KP) {
      g_state = ST_IDLE;
   }
}

void Process_Touch_h_Small() {
   beep(BEEP_TIME);
   switch (g_state) {
      case ST_IDLE:
         Led_Prog_Off();
         g_state = ST_SET_PASS;
         break;
      case ST_SET_PASS:
      case ST_SAVE_PASS:
      case ST_SET_SERI:
      //case ST_SET_TIME_STER_DRY:
         password = 0;
         g_state = ST_IDLE;
         break;
   }
}
// Setup for programs
void Process_Setup(void) {
   switch (g_state) {
      case ST_SET_SETPOINT:
         if (setpoint <= 2500)
         setpoint = setpoint*10+100*i;
         user_setpoint = setpoint;
         break;
      case ST_SET_PROTECT:
         if (protect <= 3100)
            protect = protect*10+100*i;
            user_protect = protect;
         break;
      case ST_SET_WAIT_TIME:
         if(1 == hour_min_flag) {
            if(wait_hour < 24)
               wait_hour = wait_hour*10 + i;
         } else {
            if(wait_min < 60)
               wait_min = wait_min*10 + i;
         }
         user_delay_time = (int16)wait_hour * 60 + wait_min;
         break;
      /*case ST_SET_TIME_DAY_HOUR:
         if(0 == hour_min_flag) {
            if(hour_ster_time < 24) {
                  hour_ster_time = hour_ster_time * 10 + i;
               }
            if(hour_ster_time >= 24) {
               user_hour_ster_time = hour_ster_time = 0;
            }
            else user_hour_ster_time = hour_ster_time;
            hour_remain_time = user_hour_ster_time;
         }
         if(1 == hour_min_flag) {
            if(day_ster_time < 100) {
               day_ster_time = day_ster_time * 10 + i;
            }
            if(day_ster_time >= 100) {
               user_day_ster_time = day_ster_time = 0;
            }
            else user_day_ster_time = day_ster_time;
            day_remain_time = user_day_ster_time;
         }
         break;
      case ST_SET_TIME_HOUR_MIN:
         if (1 == n) {
            if (0 == hour_min_flag && ster_time < 60) {
               if((ster_time%60) < 100) {
                  ster_time = (ster_time/60)*60 + (ster_time%60)*10+i;
               }
            }
            else {
               ster_time = ster_time*10 + i;
            }
            if (ster_time < 6000) {
               user_ster_time = ster_time;
            }
            else user_ster_time = ster_time = 0;
         }
         else {
            if(1 == hour_min_flag) {
               if(ster_time < 600)
                  ster_time = (ster_time/60)*600+60*i;
            } else {
               if((ster_time%60) < 10)
                  ster_time = (ster_time/60)*60 + (ster_time%60)*10 + i;
            }
            if (ster_time < 6000) {
               user_ster_time = ster_time;
            }
            else user_ster_time = ster_time = 0;
         }
         break;*/
      case ST_SET_HOLD_TIME:
         if (1 == n) {
            if (0 == hour_min_flag && ster_time < 60) {
               if((ster_time%60) < 100) {
                  ster_time = (ster_time/60)*60 + (ster_time%60)*10+i;
               }
            }
            else {
               ster_time = ster_time*10 + i;
            }
            if (ster_time < 6000) {
               user_ster_time = ster_time;
            }
            else user_ster_time = ster_time = 0;
         }
         else {
            if(1 == hour_min_flag) {
               if(ster_time < 600)
                  ster_time = (ster_time/60)*600+60*i;
            } else {
               if((ster_time%60) < 10)
                  ster_time = (ster_time/60)*60 + (ster_time%60)*10 + i;
            }
            if (ster_time < 6000) {
               user_ster_time = ster_time;
            }
            else user_ster_time = ster_time = 0;
         }
         break;
      case ST_SET_PASS:
         if (password <= 9999) {
            password = password*10 + i;
         }
         if (password > 9999) {
            password = 0;
         }
         break;
      case ST_SET_SERI:
         if (seri <= 9999) {
            seri = seri*10 + i;
         }
         if (seri > 9999) {
            seri = 0;
         }
         break;
   }
}

#endif // #define _PROCESS_KEYS_H_

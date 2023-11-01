#ifndef _DS1307_H_
#define _DS1307_H_

#include "globals.h"

#use i2c(Master,Slow,sda=PIN_A5,scl=PIN_A4)

void write_DS1307(byte address, BYTE data)
{
   short int status;
   disable_interrupts(GLOBAL);
   i2c_start();
   i2c_write(0xd0);
   i2c_write(address);
   i2c_write(data);
   i2c_stop();
   i2c_start();
   status=i2c_write(0xd0);
   while(status==1)
   {
      i2c_start();
      status=i2c_write(0xd0);
   }
   enable_interrupts(GLOBAL);
}

BYTE read_DS1307(byte address)
{
   BYTE data;
   disable_interrupts(GLOBAL);
   i2c_start();
   i2c_write(0xd0);
   i2c_write(address);
   i2c_start();
   i2c_write(0xd1);
   data=i2c_read(0);
   i2c_stop();
   enable_interrupts(GLOBAL);
   return(data);
}

void Stop_DS1307(void)
{
   write_ds1307(0,sec | 0x80);
}

void Start_DS1307(void)
{
   write_ds1307(0,sec & 0x7F);
}

unsigned int BCD2Dec(unsigned int BCD) {
   unsigned int L, H;
   L=BCD & 0x0F;
   H=(BCD>>4)*10;
   return (H+L);
}

void Store_Kp(void)
{
   unsigned char tmp_H, tmp_L;
   tmp_H = pid_kp >> 8;
   tmp_L = pid_kp & 0xFF;
   // write_DS1307(0x10, tmp_H);
   // write_DS1307(0x11, tmp_L);
   if(setpoint < 20000) {
      write_eeprom(0x30, tmp_H);
      write_eeprom(0x31, tmp_L);
   }
   else {
      write_eeprom(0x40, tmp_H);
      write_eeprom(0x41, tmp_L);
   }
   
}

void Store_Ki(void)
{
   unsigned char tmp_H, tmp_L;
   tmp_H = pid_ki >> 8;
   tmp_L = pid_ki & 0xFF;
   // write_DS1307(0x12, tmp_H);
   // write_DS1307(0x13, tmp_L);
   if(setpoint < 20000) {
      write_eeprom(0x32, tmp_H);
      write_eeprom(0x33, tmp_L);
   }
   else {
      write_eeprom(0x42, tmp_H);
      write_eeprom(0x43, tmp_L);
   }
   //write_eeprom(0x32, tmp_H);
   //write_eeprom(0x33, tmp_L);
}

void Store_Kd(void)
{
   unsigned char tmp_H, tmp_L;
   tmp_H = pid_kd >> 8;
   tmp_L = pid_kd & 0xFF;
   // write_DS1307(0x14, tmp_H);
   // write_DS1307(0x15, tmp_L);
   if(setpoint < 20000) {
      write_eeprom(0x34, tmp_H);
      write_eeprom(0x35, tmp_L);
   }
   else {
      write_eeprom(0x44, tmp_H);
      write_eeprom(0x45, tmp_L);
   }
   //write_eeprom(0x34, tmp_H);
   //write_eeprom(0x35, tmp_L);
}

void Store_Offset(void)
{
   unsigned char tmp_H, tmp_L;
   tmp_H = temp_offset >> 8;
   tmp_L = temp_offset & 0xFF;
   /*write_DS1307(0x1B, tmp_H);
   write_DS1307(0x1C, tmp_L);
   With Air Jet Temp and Offset, we store in EEPROM*/
   write_eeprom(0x1B, tmp_H);
   write_eeprom(0x1C, tmp_L);
}

void Store_Mode(void)
{
   write_DS1307(0x08, g_mode);
}

void Store_WaitTime(void)
{
   wait_hour = user_delay_time/60;
   wait_min = user_delay_time%60;
   write_DS1307(0x0A, wait_hour);
   write_DS1307(0x0B, wait_min);
}

void Store_HoldTime(void)
{
   hold_hour = user_ster_time/60;
   hold_min = user_ster_time%60;
   write_eeprom(0x55, hold_hour);
   write_eeprom(0x56, hold_min);
}

/*void Store_DayTime(void) {
   write_eeprom(0x51, user_day_ster_time/10);
   write_eeprom(0x52, user_day_ster_time%10);
}

void Store_HourTime(void) {
   write_eeprom(0x53, user_hour_ster_time/10);
   write_eeprom(0x54, user_hour_ster_time%10);
}*/

void Store_Setpoint(void)
{
   unsigned char tmp_H, tmp_L;
   tmp_H = user_setpoint >> 8;
   tmp_L = user_setpoint & 0xFF;
   //write_DS1307(0x16, tmp_H);
   //write_DS1307(0x17, tmp_L);
   write_eeprom(0x51, tmp_H);
   write_eeprom(0x52, tmp_L);
}

void Store_Protect(void)
{
   unsigned char tmp_H, tmp_L;
   tmp_H = user_protect >> 8;
   tmp_L = user_protect & 0xFF;
   //write_DS1307(0x18, tmp_H);
   //write_DS1307(0x19, tmp_L);
   write_eeprom(0x53, tmp_H);
   write_eeprom(0x54, tmp_L);
}

void Store_Password(void) {
   unsigned char tmp_H, tmp_L;
   tmp_H = check_password >> 8;
   tmp_L = check_password & 0xFF;
   write_eeprom(0x2C, tmp_H);
   write_eeprom(0x2D, tmp_L);
}
void Store_SERI(void) {
   unsigned char tmp_H, tmp_L;
   tmp_H = seri >> 8;
   tmp_L = seri & 0xFF;
   write_eeprom(0x07, tmp_H);
   write_eeprom(0x08, tmp_L);
}

void Store_FanSpeed(void)
{
   // write_DS1307(0x1A, fan_speed);
   write_eeprom(0x36, fan_speed);
}

void Check_Data_Previous(void) {
     if (SETPOINT_MIN > user_setpoint || SETPOINT_MAX < user_setpoint) {
           user_setpoint = SETPOINT_DEF;
     }
     if (PROTECT_MIN > user_protect || PROTECT_MAX < user_protect) {
           user_protect = PROTECT_MAX;
     }
}

void Load_Data_Program_EEPROM(void) {
   switch (g_mode) {
      case PROGRAM1:
         user_setpoint = PROG1_SETPOINT;
         user_protect = PROG1_PROTECT;
         user_ster_time = PROG1_STER_TIME;
      break;
      case PROGRAM2:
         user_setpoint = PROG2_SETPOINT;
         user_protect = PROG2_PROTECT;
         user_ster_time = PROG2_STER_TIME;
      break;
      case PROGRAM3:
         user_setpoint = PROG3_SETPOINT;
         user_protect = PROG3_PROTECT;
         user_ster_time = PROG3_STER_TIME;
      break;
      case PROGRAM4:
         user_setpoint = PROG4_SETPOINT;
         user_protect = PROG4_PROTECT;
         user_ster_time = PROG4_STER_TIME;
      break;
      case PROGRAM5:
         user_setpoint = PROG5_SETPOINT;
         user_protect = PROG5_PROTECT;
         user_ster_time = PROG5_STER_TIME;
      break;
      case PROGRAM6:
         user_setpoint = PROG6_SETPOINT;
         user_protect = PROG6_PROTECT;
         user_ster_time = PROG6_STER_TIME;
      break;
      case PROGRAM7:
         user_setpoint = PROG7_SETPOINT;
         user_protect = PROG7_PROTECT;
         user_ster_time = PROG7_STER_TIME;
      break;
      case PROGRAM8:
         user_setpoint = PROG8_SETPOINT;
         user_protect = PROG8_PROTECT;
         user_ster_time = PROG8_STER_TIME;
      break;
      case PROGRAM9:
         user_setpoint = PROG9_SETPOINT;
         user_protect = PROG9_PROTECT;
         user_ster_time = PROG9_STER_TIME;
      break;
      case PROGRAM10:
         user_setpoint = PROG10_SETPOINT;
         user_protect = PROG10_PROTECT;
         user_ster_time = PROG10_STER_TIME;
      break;
   }
   /*unsigned char tmp_H,tmp_L;
   int8 a,b,e,f,g,h,k;
   switch(g_mode) {
      case PROGRAM1:
         a = 0x09;
         b = 0x0A;
         e = 0x0D;
         f = 0x0E;
         g = 0x12;
         h = 0x13;
         //k = 0x50;
         break;
      case PROGRAM2:
         a = 0x16;
         b = 0x17;
         e = 0x1A;
         f = 0x1F;
         g = 0x22;
         h = 0x23;
         //k = 0x51;
         break;
      case PROGRAM3:
         a = 0x07;
         b = 0x08;
         e = 0x30;
         f = 0x31;
         g = 0x32;
         h = 0x33;
         //k = 0x52;
         break;
      case PROGRAM4:
         a = 0x0B;
         b = 0x0C;
         e = 0x34;
         f = 0x35;
         g = 0x36;
         h = 0x37;
         //k = 0x53;
         break;
      case PROGRAM5:
         a = 0x10;
         b = 0x11;
         e = 0x38;
         f = 0x39;
         g = 0x3A;
         h = 0x3B;
         //k = 0x54;
         break;
      case PROGRAM6:
         a = 0x14;
         b = 0x15;
         e = 0x3C;
         f = 0x3D;
         g = 0x3E;
         h = 0x3F; 
         //k = 0x55;
         break;
      case PROGRAM7:
         a = 0x18;
         b = 0x19;
         e = 0x40;
         f = 0x41;
         g = 0x42;
         h = 0x43; 
         //k = 0x56; 
         break;
      case PROGRAM8:
         a = 0x20;
         b = 0x21;
         e = 0x44;
         f = 0x45;
         g = 0x46;
         h = 0x47;  
         //k = 0x57;
         break;
      case PROGRAM9:
         a = 0x24;
         b = 0x25;
         e = 0x48;
         f = 0x49;
         g = 0x4A;
         h = 0x4B; 
         //k = 0x58; 
         break;
      case PROGRAM10:
         a = 0x28;
         b = 0x29;
         e = 0x4C;
         f = 0x4D;
         g = 0x4E;
         h = 0x4F; 
         //k = 0x59;
         break;
   }
   if (g_active_mode != MODE_STAND) {
      hold_hour = read_eeprom(a);
      hold_min = read_eeprom(b);
      user_ster_time = (int16)hold_hour*60 + hold_min;
      tmp_H = read_eeprom(e);
      tmp_L = read_eeprom(f);
      user_setpoint = (unsigned int16)(tmp_H)*0x100 + tmp_L;
      tmp_H = read_eeprom(g);
      tmp_L = read_eeprom(h);
      user_protect = (unsigned int16)(tmp_H)*0x100 + tmp_L;
   }
   else {
      switch (g_mode) {
         case PROGRAM1:
            user_setpoint = PROG1_SETPOINT;
            user_protect = PROG1_PROTECT;
            user_ster_time = PROG1_STER_TIME;
         break;
         case PROGRAM2:
            user_setpoint = PROG2_SETPOINT;
            user_protect = PROG2_PROTECT;
            user_ster_time = PROG2_STER_TIME;
         break;
         case PROGRAM3:
            user_setpoint = PROG3_SETPOINT;
            user_protect = PROG3_PROTECT;
            user_ster_time = PROG3_STER_TIME;
         break;
         case PROGRAM4:
            user_setpoint = PROG4_SETPOINT;
            user_protect = PROG4_PROTECT;
            user_ster_time = PROG4_STER_TIME;
         break;
         case PROGRAM5:
            user_setpoint = PROG5_SETPOINT;
            user_protect = PROG5_PROTECT;
            user_ster_time = PROG5_STER_TIME;
         break;
         case PROGRAM6:
            user_setpoint = PROG6_SETPOINT;
            user_protect = PROG6_PROTECT;
            user_ster_time = PROG6_STER_TIME;
         break;
         case PROGRAM7:
            user_setpoint = PROG7_SETPOINT;
            user_protect = PROG7_PROTECT;
            user_ster_time = PROG7_STER_TIME;
         break;
         case PROGRAM8:
            user_setpoint = PROG8_SETPOINT;
            user_protect = PROG8_PROTECT;
            user_ster_time = PROG8_STER_TIME;
         break;
         case PROGRAM9:
            user_setpoint = PROG9_SETPOINT;
            user_protect = PROG9_PROTECT;
            user_ster_time = PROG9_STER_TIME;
         break;
         case PROGRAM10:
            user_setpoint = PROG10_SETPOINT;
            user_protect = PROG10_PROTECT;
            user_ster_time = PROG10_STER_TIME;
         break;
      }
   }
   Check_Data_Previous();*/
}

void Load_Data_User(void) {
   unsigned char tmp_H, tmp_L;
   /*if(flag_day_hour == 1) {
      hold_hour = read_eeprom(0x55);
      hold_min = read_eeprom(0x56);
      user_ster_time = (unsigned int16)hold_hour*60 + hold_min;
   }
   if(flag_day_hour == 0) {
      user_day_ster_time = read_eeprom(0x51) * 10 + read_eeprom(0x52);
      user_hour_ster_time = read_eeprom(0x53) * 10 + read_eeprom(0x54);
      day_remain_time = user_day_ster_time;
      hour_remain_time = user_hour_ster_time;
      user_hold_time = user_day_ster_time*24*60 + user_hour_ster_time*60;
   }*/
   // hold_hour = read_DS1307(0x55);
   // hold_min = read_DS1307(0x56);
   // user_ster_time = (unsigned int16)hold_hour*60 + hold_min;
   // tmp_H = read_DS1307(0x16);
   // tmp_L = read_DS1307(0x17);
   // user_setpoint = (unsigned int16)(tmp_H) * 0x100 + tmp_L;
   // if (user_setpoint > SETPOINT_MAX)
   //    user_setpoint = SETPOINT_DEF;
   // tmp_H = read_DS1307(0x18);
   // tmp_L = read_DS1307(0x19);
   // user_protect = (unsigned int16)(tmp_H) * 0x100 + tmp_L;
   // if (user_protect > PROTECT_MAX)
   //    user_protect = PROTECT_DEF;
   hold_hour = read_eeprom(0x55);
   hold_min = read_eeprom(0x56);
   user_ster_time = (unsigned int16)hold_hour*60 + hold_min;
   tmp_H = read_eeprom(0x51);
   tmp_L = read_eeprom(0x52);
   user_setpoint = (unsigned int16)(tmp_H) * 0x100 + tmp_L;
   if (user_setpoint > SETPOINT_MAX)
      user_setpoint = SETPOINT_DEF;
   tmp_H = read_eeprom(0x53);
   tmp_L = read_eeprom(0x54);
   user_protect = (unsigned int16)(tmp_H) * 0x100 + tmp_L;
   if (user_protect > PROTECT_MAX)
      user_protect = PROTECT_DEF;
}

void Load_PID(void)
{
   unsigned char  tmp_H, tmp_L;
   if(setpoint < 20000) {
      tmp_H = read_eeprom(0x30);
      tmp_L = read_eeprom(0x31);
   }
   else {
      tmp_H = read_eeprom(0x40);
      tmp_L = read_eeprom(0x41);
   }
   pid_kp = (unsigned int16)(tmp_H) * 0x100 + tmp_L;
   if (pid_kp > PID_KP_MAX) {
      if(setpoint < 20000) {
         pid_kp = PID_KP_DEF; 
      }
      else pid_kp = PID_KP_DEF1; 
   }
   // tmp_H = read_DS1307(0x12);
   // tmp_L = read_DS1307(0x13);
   
   if(setpoint < 20000) {
      tmp_H = read_eeprom(0x32);
      tmp_L = read_eeprom(0x33);
   }
   else {
      tmp_H = read_eeprom(0x42);
      tmp_L = read_eeprom(0x43);
   }
   pid_ki = (unsigned int16)(tmp_H) * 0x100 + tmp_L;
   if (pid_ki > PID_KI_MAX) {
      if(setpoint < 20000) {
         pid_ki = PID_KI_DEF; 
      }
      else pid_ki = PID_KI_DEF1; 
   }
   // tmp_H = read_DS1307(0x14);
   // tmp_L = read_DS1307(0x15);
   
   if(setpoint < 20000) {
      tmp_H = read_eeprom(0x34);
      tmp_L = read_eeprom(0x35);
   }
   else {
      tmp_H = read_eeprom(0x44);
      tmp_L = read_eeprom(0x45);
   }
   pid_kd = (unsigned int16)(tmp_H) * 0x100 + tmp_L;
   if (pid_kd > PID_KD_MAX) {
      if(setpoint < 20000) {
         pid_kd = PID_KD_DEF; 
      }
      else pid_kd = PID_KD_DEF1; 
   }
      
      
}
void Load_Data(void)
{
   unsigned char  tmp_H, tmp_L;
   g_mode = read_DS1307(0x08);
   wait_day = read_DS1307(0x1D);
   if (wait_day > 7) {
         wait_day = 0;
   }

   wait_hour = read_DS1307(0x0A);
   wait_min = read_DS1307(0x0B);
   if ((24 > wait_hour) && (wait_min < 59)) {
      user_delay_time = (int16)wait_hour * 60 + wait_min;
      }
   else user_delay_time = 0;

   // tmp_H = read_DS1307(0x10);
   // tmp_L = read_DS1307(0x11);
   
   // fan_speed = read_DS1307(0x1A);
   fan_speed = read_eeprom(0x36);
   if (fan_speed > FAN_SPEED_MAX || fan_speed < FAN_SPEED_MIN)
      fan_speed = FAN_SPEED_MAX;

   tmp_H = read_eeprom(0x07);
   tmp_L = read_eeprom(0x08);
   seri = (unsigned int16)(tmp_H)*0x100 + tmp_L;
   if (seri > 10000) {
      seri = 0;
   }

   tmp_H = read_eeprom(0x1B);
   tmp_L = read_eeprom(0x1C);
   temp_offset = (unsigned int16)(tmp_H) * 0x100 + tmp_L;
   if ((temp_offset > OFFSET_TEMP_RANGE)||(temp_offset < -OFFSET_TEMP_RANGE))
      temp_offset = 0;
   
   flag_day_hour = read_eeprom(0x50);
   if(flag_day_hour != 0 && flag_day_hour != 1) flag_day_hour = 0;
}

#endif   // #define _DS1307_H_

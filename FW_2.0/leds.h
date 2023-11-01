#ifndef _LEDS_H_
#define _LEDS_H_

#use fast_io(ALL)

#include "globals.h"
#include "ds1307.h"
#include "cap1188.h"

/*
      4                 7 6 5 4 3 2 1 0
    -----               0 1 0 1 1 1 1 1   0x5F --> 0
   |     |              0 0 0 0 1 0 0 1   0x09 --> 1
 6 |  7  |3             1 0 0 1 1 1 1 0   0x9E --> 2
    -----               1 0 0 1 1 0 1 1   0x9B --> 3
   |     |              1 1 0 0 1 0 0 1   0xC9 --> 4
 2 |     |0             1 1 0 1 0 0 1 1   0xD3 --> 5
    ----- o 5           1 1 0 1 0 1 1 1   0xD7 --> 6
      1                 0 0 0 1 1 0 0 1   0x19 --> 7
                        1 1 0 1 1 1 1 1   0xDF --> 8
                        1 1 0 1 1 0 1 1   0xDB --> 9
                        1 1 0 1 0 1 1 0   0xD6 --> E
                        1 1 0 1 1 1 0 0   0xDC --> P
                        0 1 0 0 0 1 0 0   0x44 --> I
                        1 0 0 0 1 1 1 1   0x8F --> d
                        1 0 0 0 0 1 0 1   0x85 --> n
                        1 1 0 0 1 1 0 1   
*/

static unsigned char index;

unsigned char Get7Seg(unsigned char key) {
   switch (key) {
      case 0:
         return 0x5F;
      case 1:
         return 0x09;
      case 2:
         return 0x9E;
      case 3:
         return 0x9B;
      case 4:
         return 0xC9;
      case 5:
         return 0xD3;
      case 6:
         return 0xD7;
      case 7:
         return 0x19;
      case 8:
         return 0xDF;
      case 9:
         return 0xDB;
      default:
         return 0x00;   //blank;
   }
}

unsigned char AddPoint(unsigned char key) {
   return key | 0x20;
}

void led_init(void) {
   //Led7[0][0] = Get7Seg(0); Led7[0][1] = Get7Seg(1); Led7[0][2] = Get7Seg(2); Led7[0][3] = Get7Seg(3);
   //Led7[1][0] = Get7Seg(3); Led7[1][1] = Get7Seg(4); Led7[1][2] = Get7Seg(5); Led7[1][3] = Get7Seg(6);
   //Led7[2][0] = Get7Seg(6); Led7[2][1] = Get7Seg(7); Led7[2][2] = Get7Seg(8); Led7[2][3] = Get7Seg(9);
   //Led1[0] = 0xA5; Led1[1] = 0xA5; Led1[2] = 0xA5;
   // Setup realtime clock:
   hour = read_ds1307(2);
   sec = read_ds1307(0);
   if (sec & 0x80) {   // If clock is disabled
      hour = read_ds1307(2);
      hour &= 0xBF;     // Turn on 24 hour mode
      write_ds1307(2, hour);
      write_ds1307(0,sec & 0x7F); // enable oscillator(bit 7 =0)
   }
}

void sclk_out(void) {
   output_low(PIN_A3);
   #asm
//   NOP
   #endasm
   output_high(PIN_A3);
}

void strb_out1(void) {
   output_low(PIN_D1);
   #asm
//   NOP
   #endasm
   output_high(PIN_D1);
}

void strb_out2(void) {
   output_low(PIN_D3);
   #asm
//   NOP
   #endasm
   output_high(PIN_D3);
}

void Byte_Out_All(int8 data1, int8 data2) {
   char i;
   for(i=0; i<8; i++){
      output_bit(PIN_D0,shift_left(&data1,1,0));
      output_bit(PIN_D2,shift_left(&data2,1,0));
      sclk_out();
   }
}

void Led_Scan(void){
   led1[0] &= 0x87;
   switch(index) {
      case 0:
         index = 1;
         led1[0] |= 0x20;
         Byte_Out_All(led7[2][1], led1[0]);
         Byte_Out_All(led7[1][1], led1[1]);
         Byte_Out_All(led7[0][1], led1[2]);
         break;
      case 1:
         index = 2;
         led1[0] |= 0x10;
         Byte_Out_All(led7[2][2], led1[0]);
         Byte_Out_All(led7[1][2], 0xFF);
         Byte_Out_All(led7[0][2], 0xFF);
         break;
      case 2:
         index = 3;
         led1[0] |= 0x08;
         Byte_Out_All(led7[2][3], led1[0]);
         Byte_Out_All(led7[1][3], 0xFF);
         Byte_Out_All(led7[0][3], 0xFF);
         break;
      case 3:
         index = 4;
         led1[0] |= 0x40;
         Byte_Out_All(led7[2][0], led1[0]);
         Byte_Out_All(led7[1][0], 0xFF);
         Byte_Out_All(led7[0][0], 0xFF);
         break;
      case 4:
         index = 5;
         Byte_Out_All(led7[2][0], led1[0]);
         Byte_Out_All(led7[1][0], 0xFF);
         Byte_Out_All(led7[0][0], 0xFF);
         break;
      case 5:
         index = 6;
         Byte_Out_All(led7[2][0], led1[0]);
         Byte_Out_All(led7[1][0], 0xFF);
         Byte_Out_All(led7[0][0], 0xFF);
         break;
      case 6:
         index = 7;
         Byte_Out_All(led7[2][0], led1[0]);
         Byte_Out_All(led7[1][0], 0xFF);
         Byte_Out_All(led7[0][0], 0xFF);
         break;
      default:
         index = 0;
         Byte_Out_All(led7[2][0], led1[0]);
         Byte_Out_All(led7[1][0], 0xFF);
         Byte_Out_All(led7[0][0], 0xFF);
         //led1[0] |= 0x40;
         break;
   }
   strb_out1();
   strb_out2();
}

void SpeakerOn(void) {
   Led1[0] &= 0x7F;
}

void SpeakerOff(void) {
   spk_on_count = 0;
   Led1[0] |= 0x80;
}

void LedClockOn(void)
{
   led1[2] &= 0xFE;
}

void LedClockOff(void) {
   Led1[2] |= 0x01;
}

void LedSetTempOn(void)
{
   led1[1] &= 0xFE;
}

void LedSetTempOff(void) {
   Led1[1] |= 0x01;
}

void LedProtectTempOn(void)
{
   led1[1] &= 0xFD;
}

void LedProtectTempOff(void) {
   Led1[1] |= 0x02;
}

void LedTimeDelayOn(void)
{
   led1[1] &= 0xFB;
}

void LedTimeDelayOff(void) {
   Led1[1] |= 0x04;
}

void LedTimeSterOn(void)
{
   led1[1] &= 0xF7;
}

void LedTimeSterOff(void) {
   Led1[1] |= 0x08;
}

//==============================================================================

void LedTimeOn(void)
{
   led1[4] &= 0x7F;
}

void LedTimeOff(void)
{
   led1[4] |= 0x80;
}

void LedHeaterOn(void)
{
   led1[3] &= 0xDF;
}

void LedHeaterOff(void)
{
   led1[3] |= 0x20;
}

void LedAlarmOn(void)
{
   led1[2] &= 0xFE;
}

void LedAlarmOff(void)
{
   led1[2] |= 0x01;
}

void LedIconOn(void)
{
   led1[2] &= 0xFD;
}

void LedMaxOn(void)
{
   led1[2] &= 0xFB;
}
void LedMaxOff(void)
{
   led1[2] |= 0x04;
}

void LedTempOn(void)
{
   led1[3] &= 0xBF;
}

void LedTempOff(void)
{
   led1[3] |= 0x40;
}

/*
================================================================================
*/
/*void Led_1CDEF8_Off(void) {
   //Led1 Off:
   int8 tmp = cap1188_read_data1(0x74);
   tmp &= 0xFD;
   cap1188_write_data1(0x74, tmp);
   //LedCDEF8 off:
   tmp = cap1188_read_data2(0x74);
   tmp &= 0x0E;
   cap1188_write_data2(0x74, tmp);
}*/
void Led_Prog_Off(void) {
   //Led 1,2,3,4,5,6,7,8 Off:
   int8 tmp = cap1188_read_data1(0x74);
   tmp &= 0x00;
   cap1188_write_data1(0x74, tmp);
   //Led 9,10 off:
   tmp = cap1188_read_data2(0x74);
   tmp &= 0xC8;
   cap1188_write_data2(0x74, tmp);
}

void Led_0_On(void)
{
   int8 tmp = cap1188_read_data1(0x74);
   tmp |= 0x01;
   cap1188_write_data1(0x74, tmp);
}
void Led_0_Off(void)
{
   int8 tmp = cap1188_read_data1(0x74);
   tmp &= 0xFE;
   cap1188_write_data1(0x74, tmp);
}
void Led_1_On(void)
{
   int8 tmp = cap1188_read_data1(0x74);
   tmp |= 0x02;
   cap1188_write_data1(0x74, tmp);
}

void Led_1_Off(void)
{
   int8 tmp = cap1188_read_data1(0x74);
   tmp &= 0xFD;
   cap1188_write_data1(0x74, tmp);
}
void Led_2_On(void)
{
   int8 tmp = cap1188_read_data1(0x74);
   tmp |= 0x04;
   cap1188_write_data1(0x74, tmp);
}
void Led_2_Off(void)
{
   int8 tmp = cap1188_read_data1(0x74);
   tmp &= 0xFB;
   cap1188_write_data1(0x74, tmp);
}
void Led_3_On(void)
{
   int8 tmp = cap1188_read_data1(0x74);
   tmp |= 0x08;
   cap1188_write_data1(0x74, tmp);
}
void Led_3_Off(void)
{
   int8 tmp = cap1188_read_data1(0x74);
   tmp &= 0xF7;
   cap1188_write_data1(0x74, tmp);
}
void Led_4_On(void)
{
   int8 tmp = cap1188_read_data1(0x74);
   tmp |= 0x10;
   cap1188_write_data1(0x74, tmp);
}
void Led_4_Off(void)
{
   int8 tmp = cap1188_read_data1(0x74);
   tmp &= 0xEF;
   cap1188_write_data1(0x74, tmp);
}
void Led_5_On(void)
{
   int8 tmp = cap1188_read_data1(0x74);
   tmp |= 0x20;
   cap1188_write_data1(0x74, tmp);
}
void Led_5_Off(void)
{
   int8 tmp = cap1188_read_data1(0x74);
   tmp &= 0xDF;
   cap1188_write_data1(0x74, tmp);
}
void Led_6_On(void)
{
   int8 tmp = cap1188_read_data1(0x74);
   tmp |= 0x40;
   cap1188_write_data1(0x74, tmp);
}
void Led_6_Off(void)
{
   int8 tmp = cap1188_read_data1(0x74);
   tmp &= 0xBF;
   cap1188_write_data1(0x74, tmp);
}
void Led_7_On(void)
{
   int8 tmp = cap1188_read_data1(0x74);
   tmp |= 0x80;
   cap1188_write_data1(0x74, tmp);
}
void Led_7_Off(void)
{
   int8 tmp = cap1188_read_data1(0x74);
   tmp &= 0x7F;
   cap1188_write_data1(0x74, tmp);
}
void Led_8_On(void)
{
   int8 tmp = cap1188_read_data2(0x74);
   tmp |= 0x01;
   cap1188_write_data2(0x74, tmp);
}
void Led_8_Off(void)
{
   int8 tmp = cap1188_read_data2(0x74);
   tmp &= 0xFE;
   cap1188_write_data2(0x74, tmp);
}
void Led_Dot_On(void)   //void Led_9_On(void)
{
   int8 tmp = cap1188_read_data2(0x74);
   tmp |= 0x02;
   cap1188_write_data2(0x74, tmp);
}
void Led_Dot_Off(void)  //void Led_9_Off(void)
{
   int8 tmp = cap1188_read_data2(0x74);
   tmp &= 0xFD;
   cap1188_write_data2(0x74, tmp);
}
void Led_A_On(void)
{
   int8 tmp = cap1188_read_data2(0x74);
   tmp |= 0x04;
   cap1188_write_data2(0x74, tmp);
}
void Led_A_Off(void)
{
   int8 tmp = cap1188_read_data2(0x74);
   tmp &= 0xFB;
   cap1188_write_data2(0x74, tmp);
}
void Led_B_On(void)
{
   int8 tmp = cap1188_read_data2(0x74);
   tmp |= 0x08;
   cap1188_write_data2(0x74, tmp);
}
void Led_B_Off(void)
{
   int8 tmp = cap1188_read_data2(0x74);
   tmp &= 0xF7;
   cap1188_write_data2(0x74, tmp);
}
void Led_C_On(void)
{
   int8 tmp = cap1188_read_data2(0x74);
   tmp |= 0x10;
   cap1188_write_data2(0x74, tmp);
}
void Led_C_Off(void)
{
   int8 tmp = cap1188_read_data2(0x74);
   tmp &= 0xEF;
   cap1188_write_data2(0x74, tmp);
}
void Led_D_On(void)
{
   int8 tmp = cap1188_read_data2(0x74);
   tmp |= 0x20;
   cap1188_write_data2(0x74, tmp);
}
void Led_D_Off(void)
{
   int8 tmp = cap1188_read_data2(0x74);
   tmp &= 0xDF;
   cap1188_write_data2(0x74, tmp);
}
void Led_E_On(void)
{
   int8 tmp = cap1188_read_data2(0x74);
   tmp |= 0x40;
   cap1188_write_data2(0x74, tmp);
}
void Led_E_Off(void)
{
   int8 tmp = cap1188_read_data2(0x74);
   tmp &= 0xBF;
   cap1188_write_data2(0x74, tmp);
}
void Led_F_On(void)
{
   int8 tmp = cap1188_read_data2(0x74);
   tmp |= 0x80;
   cap1188_write_data2(0x74, tmp);
}
void Led_F_Off(void)
{
   int8 tmp = cap1188_read_data2(0x74);
   tmp &= 0x7F;
   cap1188_write_data2(0x74, tmp);
}

/*
================================================================================
*/

void Beep(unsigned int16 duration)
{
   spk_on_count = duration;
}
/*
void ClrLed7(unsigned char mon)
{
   Led7[mon][0] = 0x00;  //clear led
   Led7[mon][1] = 0x00;
   Led7[mon][2] = 0x00;
   Led7[mon][3] = 0x00;
}
*/
void SetDate(WEEKDAY date) {
   unsigned char tmp;
   tmp = led1[2];
   if ((SUNDAY <= date)&&(date <= SATURDAY)) {
      tmp |= 0xFE;  // Turn off all leds for date indicator
      switch(date)
      {
         case SUNDAY:
            tmp &= 0xFD;
            break;
         case MONDAY:
            tmp &= 0xFB;
            break;
         case TUESDAY:
            tmp &= 0xF7;
            break;
         case WEDNESDAY:
            tmp &= 0xEF;
            break;
         case THURSDAY:
            tmp &= 0xDF;
            break;
         case FRIDAY:
            tmp &= 0xBF;
            break;
         case SATURDAY:
            tmp &= 0x7F;
            break;
      }
      led1[2] = tmp;
   } else {
      led1[2] |= 0xFE;
   }
}
/*
void PutDay(void)
{
   day = read_ds1307(3)&0x07;
   SetDate((WEEKDAY)(day));
}
*/
void PutDateTime(void)
{
   day = read_ds1307(3)&0x07;
   SetDate((WEEKDAY)(day));
   hour = read_ds1307(2);   // hour
   led7[0][0] = Get7Seg(hour/0x10);
   led7[0][1] = Get7Seg(hour&0x0F);
   min = read_ds1307(1);   // min
   led7[0][2] = Get7Seg(min/0x10);
   led7[0][3] = Get7Seg(min&0x0F);
}
/*
void PutTime(unsigned char mon, unsigned char hour, unsigned char min)
{
   led7[mon][0] = Get7Seg(hour/0x10);
   led7[mon][1] = AddPoint(Get7Seg(hour&0x0F));
   led7[mon][2] = Get7Seg(min/0x10);
   led7[mon][3] = Get7Seg(min&0x0F);
}
*/
void PutTime_DayHour(unsigned char mon, unsigned int16 time1, unsigned int16 time2)
{
   //if((g_mode != PROGRAM1)&&(g_mode != PROGRAM2)) {
      led7[mon][0] = Get7Seg(time1/10);
      led7[mon][1] = AddPoint(Get7Seg(time1%10));
      led7[mon][2] = Get7Seg(time2/10);
      led7[mon][3] = AddPoint(Get7Seg(time2%10));
}

void PutTime_One(unsigned char mon, int16 time)
{
   int8 hour, min;
   hour = time / 60;
   min = time % 60;
   //if((g_mode != PROGRAM1)&&(g_mode != PROGRAM2)) {
      led7[mon][0] = Get7Seg(hour/10);
      led7[mon][1] = AddPoint(Get7Seg(hour%10));
      led7[mon][2] = Get7Seg(min/10);
      led7[mon][3] = Get7Seg(min%10);
}
/*
void PutTime_One_Blank(unsigned char mon)
{
   led7[mon][0] = 0x00;
   led7[mon][1] = 0x00;
   led7[mon][2] = 0x00;
   led7[mon][3] = 0x00;
}
*/
/*
void PutTemp(unsigned char mon, unsigned int16 temp)
{
   if (temp >= 10000) {
      led7[mon][0] = Get7Seg(temp / 10000);
      led7[mon][1] = Get7Seg((temp%10000) / 1000);
      led7[mon][2] = AddPoint(Get7Seg((temp%1000) / 100));
      led7[mon][3] = Get7Seg((temp%100) / 10);
   } else {
      led7[mon][0] = Get7Seg(temp / 1000);
      led7[mon][1] = AddPoint(Get7Seg((temp%1000) / 100));
      led7[mon][2] = Get7Seg((temp%100) / 10);
      led7[mon][3] = Get7Seg(temp % 10);   
   }
}
*/
void PutTempSign(unsigned char mon, signed int16 temp)
{
   if (temp >= 0) {
      if (temp >= 10000) {
         led7[mon][0] = Get7Seg(temp / 10000);
         led7[mon][1] = Get7Seg((temp%10000) / 1000);
         led7[mon][2] = AddPoint(Get7Seg((temp%1000) / 100));
         led7[mon][3] = Get7Seg((temp%100) / 10);
      } else {
         led7[mon][0] = Get7Seg(temp / 1000);
         led7[mon][1] = AddPoint(Get7Seg((temp%1000) / 100));
         led7[mon][2] = Get7Seg((temp%100) / 10);
         //led7[mon][3] = Get7Seg(temp % 10);  
         led7[mon][3] = Get7Seg(0);   
      }
   } else {
      led7[mon][0] = 0x80;
      led7[mon][1] = Get7Seg(-temp / 1000);
      led7[mon][2] = AddPoint(Get7Seg((-temp%1000) / 100));
      led7[mon][3] = Get7Seg((-temp%100) / 10);
   }
}

void PutOffset(unsigned char mon, signed int16 offset)
{
   if (offset >= 0) {
      led7[mon][0] = Get7Seg(offset / 10000);
      led7[mon][1] = Get7Seg((offset%10000) / 1000);
      led7[mon][2] = AddPoint(Get7Seg((offset%1000) / 100));
      led7[mon][3] = Get7Seg((offset%100) / 10);
   } else {
      led7[mon][0] = 0x80;
      led7[mon][1] = Get7Seg(-offset / 1000);
      led7[mon][2] = AddPoint(Get7Seg((-offset%1000) / 100));
      led7[mon][3] = Get7Seg((-offset%100) / 10);
   }
}

void PutPid(unsigned char mon, unsigned int16 temp)
{
   tmp %= 10000;
   led7[mon][0] = Get7Seg(0);
   led7[mon][1] = Get7Seg(temp / 100);
   led7[mon][2] = Get7Seg((temp%100) / 10);
   led7[mon][3] = Get7Seg(temp % 10);   
}

void PutSign(unsigned char mon, Sign_CODE sign)
{
   switch (sign)
   {
      case SIGN_SENSOR_BROKEN:
         led7[mon][0] = 0xD6;
         led7[mon][2] = 0x00;
         led7[mon][3] = 0x00;
         led7[mon][1] = Get7Seg(1);
         g_err_code = 1;
         break;
      case SIGN_TEMP_OVERLOAD:
         led7[mon][0] = 0xD6;
         led7[mon][2] = 0x00;
         led7[mon][3] = 0x00;
         led7[mon][1] = Get7Seg(2);
         g_err_code = 2;
         break;
      case SIGN_SET_PID_KP:
         led7[mon][0] = 0xDC;
         led7[mon][2] = 0x00;
         led7[mon][3] = 0x00;
         led7[mon][1] = 0x00;
         break;
      case SIGN_SET_PID_KI:
         led7[mon][0] = 0x44;
         led7[mon][2] = 0x00;
         led7[mon][3] = 0x00;
         led7[mon][1] = 0x00;
         break;
      case SIGN_SET_PID_KD:
         led7[mon][0] = 0x8F;
         led7[mon][2] = 0x00;
         led7[mon][3] = 0x00;
         led7[mon][1] = 0x00;
         break;
      case SIGN_PROCESS_END:
         led7[mon][0] = 0xD6;
         led7[mon][2] = 0xAF;
         led7[mon][3] = 0x00;
         led7[mon][1] = 0x85;
         break;
      case SIGN_T2:
         led7[mon][0] = 0x00;       
         led7[mon][1] = 0x00;       
         led7[mon][2] = 0x54;       //'T'
         led7[mon][3] = Get7Seg(2); //'2'
         break;
       case SIGN_T3:
         led7[mon][0] = 0x00;      
         led7[mon][1] = 0x00;       
         led7[mon][2] = 0x54;       //'T'
         led7[mon][3] = Get7Seg(3); //'3'
         break;
       case SIGN_T4:
         led7[mon][0] = 0x00;       
         led7[mon][1] = 0x00;       
         led7[mon][2] = 0x54;       //'T'
         led7[mon][3] = Get7Seg(4); //'4'
         break;
       case SIGN_T5:
         led7[mon][0] = 0x00;       
         led7[mon][1] = 0x00;       
         led7[mon][2] = 0x54;       //'T'
         led7[mon][3] = Get7Seg(5); //'5'
         break;
      case SIGN_T6:
         led7[mon][0] = 0x00;       
         led7[mon][1] = 0x00;       
         led7[mon][2] = 0x54;       //'T'
         led7[mon][3] = Get7Seg(6); //'6'
         break;
       case SIGN_T7:
         led7[mon][0] = 0x00;       
         led7[mon][1] = 0x00;       
         led7[mon][2] = 0x54;       //'T'
         led7[mon][3] = Get7Seg(7); //'7'
         break;
       case SIGN_CN:
         led7[mon][0] = 0x00;       
         led7[mon][1] = 0x00;       
         led7[mon][2] = 0x56;      //'C'
         led7[mon][3] = 0x85;      //'N'
         break;
       case SIGN_ALL:
         led7[mon][0] = 0x00;      
         led7[mon][1] = 0xDD;     //'A'  
         led7[mon][2] = 0x46;     //'L'  
         led7[mon][3] = 0x46;     //'L'
         break;
      case SIGN_BLANK:
         led7[mon][0] = 0x00;
         led7[mon][1] = 0x00;
         led7[mon][2] = 0x00;
         led7[mon][3] = 0x00;
         break;
   }
   
}

void SetPhaseIndicator(PROCESS_PHASE phase)
{
   unsigned char tmp;
   tmp = led1[3];
   if ((WAITING_PHASE <= phase)&&(phase <= IDLE_PHASE)) {
      tmp |= 0x1F;  // Turn off all leds for phase indicator
      switch(phase)
      {
         case WAITING_PHASE:
            tmp &= 0xFE;
            break;
         case HEAT_RISING_PHASE:
            tmp &= 0xFD;
            break;
         case HEAT_HOLDING_PHASE:
            tmp &= 0xFB;
            break;
         case HEAT_FALLING_PHASE:
            tmp &= 0xF7;
            break;
         case IDLE_PHASE:
            tmp &= 0xEF;
            PutSign(1, SIGN_PROCESS_END);
            break;
      }
      led1[3] = tmp;
   }
}

void SetStateIndicator(STATE state)
{
   unsigned char tmp1;
   unsigned char tmp2;
   tmp1 = led1[0];
   tmp2 = led1[1];
   tmp1 |= 0x03;  // 
   tmp2 |= 0xE0;
   if ((ST_IDLE < state)&&(state < TOTAL_NUMBER_OF_STATE)) {
      switch(state)
      {
         case ST_SET_TIMER:
         case ST_SET_WAIT_TIME:
            tmp2 &= 0xBF;
            break;
         case ST_SET_PID_KP:
         case ST_SET_HOLD_TIME:
            tmp2 &= 0x7F;
            break;
         case ST_SET_PID_KI:
         case ST_SET_SETPOINT:
            tmp1 &= 0xFE;
            break;
         case ST_SET_PID_KD:
         case ST_SET_PROTECT:
            tmp1 &= 0xFD;
            break;
      }
      led1[0] = tmp1;
      led1[1] = tmp2;
   }
}

void LedFanOn1(void)
{
   led1[1] |= 0xF0;
   led1[1] &= 0xEF;
}
void LedFanOn2(void)
{
   led1[1] |= 0xF0;
   led1[1] &= 0xDF;
}
void LedFanOn3(void)
{
   led1[1] |= 0xF0;
   led1[1] &= 0xBF;
}
void LedFanOn4(void)
{
   led1[1] |= 0xF0;
   led1[1] &= 0x7F;
}

void LedFanLow(void)
{
   led1[1] |= 0xF0;
   led1[1] &= 0xEF;
}

void LedFanMedium(void)
{
   led1[1] |= 0xF0;
   led1[1] &= 0xCF;
}

void LedFanHigh(void)
{
   led1[1] |= 0xF0;
   led1[1] &= 0x8F;
}


void LedFanOnAll(void)
{
   led1[1] &= 0x0F;
}

void LedFanOffAll(void)
{
   led1[1] |= 0xF0;
}

void LedFan1(void)
{
   led1[1] |= 0xF0;
   led1[1] &= 0xEF;  //1110
}
void LedFan2(void)
{
   led1[1] |= 0xF0;
   led1[1] &= 0xCF;  //1100
}
void LedFan3(void)
{
   led1[1] |= 0xF0;
   led1[1] &= 0xDF;  //1101
}
void LedFan4(void)
{
   led1[1] |= 0xF0;
   led1[1] &= 0x9F;  //1001
}
void LedFan5(void)
{
   led1[1] |= 0xF0;
   led1[1] &= 0xBF;  //1011
}
void LedFan6(void)
{
   led1[1] |= 0xF0;
   led1[1] &= 0x3F;  //0011
}
void LedFan7(void)
{
   led1[1] |= 0xF0;
   led1[1] &= 0x7F;  //0111
}
void LedFan8(void)
{
   led1[1] |= 0xF0;
   led1[1] &= 0x6F;  //0110
}

void SetFanSimulator1(void)
{
   if (fan_rol_count == 0)
   {
      switch(fan_pos)
      {
         case 0:
            LedFan1();
            fan_pos = 1;
            break;
         case 1:
            LedFan2();
            fan_pos = 2;
            break;
         case 2:
            LedFan3();
            fan_pos = 3;
            break;
         case 3:
            LedFan4();
            fan_pos = 4;
            break;
         case 4:
            LedFan5();
            fan_pos = 5;
            break;
         case 5:
            LedFan6();
            fan_pos = 6;
            break;
         case 6:
            LedFan7();
            fan_pos = 7;
            break;
         default:
            LedFan8();
            fan_pos = 0;
            break;
      }
      fan_rol_count = 6-fan_speed;
   }
}

void SetFanSimulator(void)
{
   if (fan_rol_count == 0)
   {
      switch(fan_pos)
      {
         case 0:
            LedFanOn1();
            fan_pos = 1;
            break;
         case 1:
            LedFanOn2();
            fan_pos = 2;
            break;
         case 2:
            LedFanOn3();
            fan_pos = 3;
            break;
         default:
            LedFanOn4();
            fan_pos = 0;
            break;
      }
      fan_rol_count = 25-fan_speed*2;
   }
}

void SetFanIndicator(unsigned char level)
{
   unsigned char tmp1;
   unsigned char tmp2;
   tmp1 = led1[1] | 0x1F;
   tmp2 = led1[2] | 0xF8;
   if (level > 0) {
      tmp2 &= 0xF7;
      if (level > 1) {
         tmp2 &= 0xEF;
         if (level > 2) {
            tmp2 &= 0xDF;
            if (level > 3) {
               tmp2 &= 0xBF;
               if (level > 4) {
                  tmp2 &= 0x7F;
                  if (level > 5) {
                     tmp1 &= 0xFE;
                     if (level > 6) {
                        tmp1 &= 0xFD;
                        if (level > 7) {
                           tmp1 &= 0xFB;
                           if (level > 8) {
                              tmp1 &= 0xF7;
                              if (level > 9) {
                                 tmp1 &= 0xEF;
                              }  //9
                           }  //8
                        }  //7
                     }  //6
                  }  //5
               }  //4
            }  //3
         }  //2
      }  //1
   }  //0
   led1[1] = tmp1;
   led1[2] = tmp2;
}


#endif //#define _LEDS_H_

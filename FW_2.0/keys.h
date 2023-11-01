#ifndef _KEYS_H_
#define _KEYS_H_

#include "globals.h"
#include "cap1188.h"

unsigned char Get_Key_Code(void);
unsigned char kthit(void);

#inline
void key_init(void)
{
   cap1188_init();
   //Only press generate interrupt, release doesn't:
   //cap1188_write_data1(0x44, 0x41);
   //cap1188_write_data2(0x44, 0x41);
   //Press and hold does not generate key repeatedly; only the Up/Down keys are
   // configured for repeatable:
   //cap1188_write_data1(0x28, 0xF0);
   //cap1188_write_data2(0x28, 0x00);
   //Automatic Recalibration:
   cap1188_write_data1(0x20, 0x28);
   cap1188_write_data2(0x20, 0x28);
   //Automatic Recalibration after press and hold for 11200ms:
   //cap1188_write_data1(0x22, 0xF4);
   //cap1188_write_data2(0x22, 0xF4);
   //Touch is linked to LED for Touch 2,3,4,5,6,7
   //cap1188_write_data1(0x72, 0xFC);
   //cap1188_write_data2(0x72, 0x0E);
   //Touch is not linked to any LED
   //cap1188_write_data1(0x72, 0x00);
   //cap1188_write_data2(0x72, 0x00);
   //Touch is not linked to 'CLEAR'(B), 'DOWN'(E), 'UP'(F)
   cap1188_write_data1(0x72, 0x00);
   cap1188_write_data2(0x72, 0xC8);
   //Touch Led duty cycle reduced to 7%-0%
   cap1188_write_data1(0x93, 0x00);
   cap1188_write_data2(0x93, 0x00);
   //Set sensitivity to X64
   //cap1188_write_data1(0x1F, 0x1F);
   //cap1188_write_data2(0x1F, 0x1F);
   key_flag = 0;
   key_state = STATE_KEY_IDLE;
   key_hold_count = 0;
   key_repeat_count = 0;
   key_code = 0xFF;
   
}

#inline
void key_scan(void) {
   cap1188_write_data1(0, 0);
   cap1188_write_data2(0, 0);
   touch_state1 = cap1188_read_data1(3);
   touch_state2 = cap1188_read_data2(3);
   switch(key_state) {
      case STATE_KEY_IDLE:
         if (touch_state1 | touch_state2) {
            key_state = STATE_KEY_PRESSED;
            key_code = Get_Key_Code();
            key_hold_count = 0;
         }
         break;
      case STATE_KEY_PRESSED:
         if (touch_state1 | touch_state2) {
            key_hold_count += 1;
            if (key_hold_count > KEY_HOLD_THRESHOLD) {
               key_state = STATE_KEY_HOLD;
            }
         } else {
            key_flag = 1;
            key_state = STATE_KEY_IDLE;
            key_hold_count = 0;
            key_repeat_count = 0;
         }
         break;
      case STATE_KEY_HOLD:
         if (touch_state1 | touch_state2) {
            key_repeat_count += 1;
            if (key_repeat_count > KEY_REPEAT_TIME) {
               switch (key_code) {
                 /* case '7':
                  case '6':
                  case '5':
                  case '4':
                     key_flag = 1;
                     key_repeat_count = 0;
                     break;*/
                  //case '0':
                     //key_flag = 1;
                     //key_code = 'c';
                     //break;
                  case '0':
                     key_flag = 1;
                     key_code = 'b';
                     break;
                  case '1':
                     key_flag = 1;
                     key_code = 'e';
                     break;
                  case '2':
                     key_flag = 1;
                     key_code = 'f';
                     break;
                  case 'B':
                     key_flag = 1;
                     key_code = 'h';
                     //key_state = STATE_KEY_IDLE;
                     break;
                  case 'A':
                     key_flag = 1;
                     key_code = 'a';
                     //key_state = STATE_KEY_IDLE;
                     break;
                  case 'C':
                    // key_flag = 1;
                     //key_code = 'c';
                     //key_state = STATE_KEY_IDLE;
                     break;
                  case 'D':
                     key_flag = 1;
                     key_code = 'd';
                     //key_state = STATE_KEY_IDLE;
                     break;
                  case 'E':
                     //key_flag = 1;
                     //key_code = 'e';
                     //key_state = STATE_KEY_IDLE;
                     break;
                  case 'F':
                     //key_flag = 1;
                     //key_code = 'f';
                     //key_state = STATE_KEY_IDLE;
                     break;
               }
            }
         } else {
            //key_flag = 1;
            key_state = STATE_KEY_IDLE;
            key_hold_count = 0;
            key_repeat_count = 0;
         }
         break;
   }
}

unsigned char kthit(void)
{
   touch_state1 = 0x01 & cap1188_read_data1(0);
   if (touch_state1) {
      touch_state1 = cap1188_read_data1(3);
      key_code = Get_Key_Code();
      cap1188_write_data1(0, 0);
      return key_code;
   }
   touch_state2 = 0x01 & cap1188_read_data2(0);
   if (touch_state2) {
      touch_state2 = cap1188_read_data2(3);
      key_code = Get_Key_Code();
      cap1188_write_data2(0, 0);
      return key_code;
   }
   return 0;
}

unsigned char Get_Key_Code(void)
{
   if(touch_state1) {
      switch(touch_state1)
      {
         case 0x01:
            return '0';   // 0
         case 0x02:
            return '1';   // 1
         case 0x04:
            return '2';   // 2
         case 0x08:
            return '3';   // 3
         case 0x10:
            return '4';   // 4
         case 0x20:
            return '5';   // 5
         case 0x40:
            return '6';   // 6
         case 0x80:
            return '7';   // 7
         default:
            return 128;
      }
   } else {
      switch(touch_state2)
      {
         case 0x01:
            return '8';   // 8
         case 0x02:
            return '9';   // 9
         case 0x04:
            return 'A';   // A
         case 0x08:
            return 'B';   // B
         case 0x10:
            return 'C';   // C
         case 0x20:
            return 'D';   // D
         case 0x40:
            return 'E';   // E
         case 0x80:
            return 'F';   // F
         default:
            return 128;
      }
   }
}

#endif //#define _KEYS_H_


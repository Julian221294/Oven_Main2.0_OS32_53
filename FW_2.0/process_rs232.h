#ifndef _PROCESS_RS232_H_
#define _PROCESS_RS232_H_

#include "leds.h"
#include "keys.h"
//#include "adc.h"
//#include "triac.h"
#include "rtcc.h"
#include "cap1188.h"
float TempPrint = 0;
static unsigned char min_rs232, last_min_rs232;
//static unsigned char flag_Err = 0;
//static unsigned char flag_Recv = 0;
//static unsigned char flag_Completed = 0;
//static unsigned char flag_Rs232_Complete = 0;
//unsigned char ch;
//int s[1];
int8 code_program = 0;
void Process_Rs232(void) {
    TempPrint = (float)(realTemp / 100.00);
    min_rs232 = min;
    if (1 == flag_Rs232 && ((BCD2Dec(hour) == wait_hour) && (BCD2Dec(min) == wait_min) || (0 == user_delay_time)) && ((BCD2Dec(day) == wait_day) || (0 == wait_day))) {
        puts("    BAO CAO SO LIEU ME SAY\r\nNGAY/THANG/NAM:\r\nDON VI SU DUNG:\r\nDIA CHI:\r\nNGUOI VAN HANH:\r\nMODEL:NIHOPHAWA OS53");
        printf("SERI:\r\n");
        //printf("SERI:OS53102");
        //printf("%d%d%d%d\r\n",(int8)(seri/1000),(int8)(seri%1000)/100,(int8)(seri%100)/10,(int8)(seri%10));
        //printf("%d%d%d%d\r\n",1,(int8)(seri%1000)/100,(int8)(seri%100)/10,(int8)(seri%10));
        // if(seri < 10) {
        //     printf("000%d\r\n",(int8)(seri%10));
        // }
        // if(seri >= 10 && seri < 100) {
        //     printf("00%d%d\r\n",(int8)(seri/10),(int8)(seri%10));
        // }
        // if(seri >= 100 && seri < 1000) {
        //     printf("0%d%d\r\n",(int8)(seri/100),(int8)(seri%100));
        // }
        // if(seri >= 1000) {
        //     printf("%d%d\r\n",(int8)(seri/100),(int8)(seri%100));
        // }
        printf("CHUONG TRINH SU DUNG: ");
        if(g_mode != USER_MODE) {
            switch(g_mode) {
                case PROGRAM1:
                //s = "P1";
                code_program = 1;
                break;
                case PROGRAM2:
                //s = "P2";
                code_program = 2;
                break;
                case PROGRAM3:
                //s = "P3";
                code_program = 3;
                break;
                case PROGRAM4:
                //s = "P4";
                code_program = 4;
                break;
                case PROGRAM5:
                //s = "P5";
                code_program = 5;
                break;
                case PROGRAM6:
                //s = "P6";
                code_program = 6;
                break;
                case PROGRAM7:
                //s = "P7";
                code_program = 7;
                break;
                case PROGRAM8:
                //s = "P8";
                code_program = 8;
                break;
                case PROGRAM9:
                //s = "P9";
                code_program = 9;
                break;
                case PROGRAM10:
                //s = "P10";
                code_program = 10;
                break;
            }
            printf("P%d\r\n",code_program);
        }
        else printf("User\r\n");
        printf("THOI GIAN BAT DAU %d:%d:%d\r\n",BCD2Dec(hour), BCD2Dec(min), BCD2Dec(sec));
        flag_Rs232 = 0;
    }
    if (g_state == ST_RUN_HOLDING_TIME) {
        if(min_rs232 != last_min_rs232) {
            last_min_rs232 = min_rs232;
            if (1 == flag_Rs232_Ster) {
                flag_Rs232_Ster = 0;
                printf("NHIET DO(oC)      THOI GIAN\r\n");
            }
            if (TempPrint >= 100.00) printf(" %.1f",TempPrint);
            else printf(" %.2f", TempPrint);
            printf("             %d:%d:%d\r\n",BCD2Dec(hour), BCD2Dec(min), BCD2Dec(sec));
        }
    }
    if (((g_state == ST_COMPLETED)) && (flag_Rs232_Complete == 1)) {
        flag_Rs232_Complete = 0;
        printf("THOI GIAN KET THUC %d:%d:%d\r\n",BCD2Dec(hour), BCD2Dec(min), BCD2Dec(sec));
        printf("KET QUA ME SAY: DAT\r\n");
        printf("CHU KY NGUOI VAN HANH\r\n");
        puts("\r\n");
        printf("------------------------------\r\n");
        printf("       ME SAY HOAN THANH\r\n");
        puts("\r\n");
    }
    if(g_state == ST_ERR && flag_Rs232_Err == 1) {
        flag_Rs232_Err = 0;
        printf("ERROR CODE: E%d\r\n",g_err_code);
        printf("KET QUA ME SAY: KHONG DAT\r\n");
        printf("CHU KY NGUOI VAN HANH\r\n");
        puts("\r\n");
        printf("-------------------------------\r\n");
        printf("    ME SAY KHONG HOAN THANH\r\n");
        puts("\r\n");
    }
    if(1 == flag_Rs232_IDLE) {
        flag_Rs232_IDLE = 0;
        printf("THOI GIAN KET THUC %d:%d:%d\r\n",BCD2Dec(hour), BCD2Dec(min), BCD2Dec(sec));
        printf("KET QUA ME SAY: KHONG DAT\r\n");
        printf("CHU KY NGUOI VAN HANH\r\n");
        puts("\r\n");
        printf("-------------------------------\r\n");
        printf(" KET THUC BOI NGUOI VAN HANH\r\n");
        puts("\r\n");
    }
}

#endif // #define _PROCESS_RS232_H_
 

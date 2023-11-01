#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#use fast_io(ALL)

typedef union _ADC_DATA_TYPE
{
   signed int32 whole;
   unsigned char bytes[4];
}ADC_DATA_TYPE;

typedef enum {
   SIGN_SENSOR_BROKEN,
   SIGN_TEMP_OVERLOAD,
   SIGN_SET_PID_KP,
   SIGN_SET_PID_KI,
   SIGN_SET_PID_KD,
   SIGN_PROCESS_END,
   SIGN_CN,
   SIGN_T2,
   SIGN_T3,
   SIGN_T4,
   SIGN_T5,
   SIGN_T6,
   SIGN_T7,
   SIGN_ALL,
   SIGN_BLANK,
} SIGN_CODE;

typedef enum {
   STATE_KEY_IDLE,
   STATE_KEY_PRESSED,
   STATE_KEY_HOLD,
} KEY_STATE_;

typedef enum _STATE {
   ST_INVALID,
   ST_IDLE,
   ST_SET_PROGRAM,
   ST_SET_DAY_OF_WEEK,
   ST_SET_HOUR,
   ST_SET_MINUTE,
   ST_SET_TIME_STER_DRY,
   ST_SET_SETPOINT,
   ST_SET_PROTECT,
   ST_SET_TIME_DELAY,
   ST_SET_WAIT_TIME,
   ST_SET_HOLD_TIME,
   ST_DIS_TIME_DAY_HOUR,
   ST_DIS_TIME_HOUR_MIN,
   ST_SET_TIME_DAY_HOUR,
   ST_SET_TIME_HOUR_MIN,
   ST_SET_TIMER,
   ST_SET_PASS,
   ST_SAVE_PASS,
   ST_CHECK_PASS,
   ST_SET_SERI,
   ST_SET_PID_KP,
   ST_SET_PID_KI,
   ST_SET_PID_KD,
   ST_SET_OFFSET,
   ST_RUN_WAITING_TIME,
   ST_RUN_HEATING_TIME,
   ST_RUN_HOLDING_TIME,
   ST_RUN_COOLING_TIME,
   ST_COMPLETED,
   ST_ERR,
   TOTAL_NUMBER_OF_STATE,
} STATE;

typedef enum _SET {
   SET_NONE,
   SET_PROGRAM_USER,
   SET_TIME_REAL_TIME_CLOCK,
   SET_TIME_CLOCK,
   SET_DONE,
} SET;

typedef enum _SET_TIME {
   SET_TIME_DAY_HOUR,
   SET_TIME_HOUR_MIN,
   SET_TIME_DONE,

} SET_TIME;

typedef enum _WEEKDAY {
   NULLDAY,
   SUNDAY,
   MONDAY,
   TUESDAY,
   WEDNESDAY,
   THURSDAY,
   FRIDAY,
   SATURDAY,
   NONEDAY,
} WEEKDAY;

typedef enum _PROCESS_PHASE {
   WAITING_PHASE,
   HEAT_RISING_PHASE,
   HEAT_HOLDING_PHASE,
   HEAT_FALLING_PHASE,
   IDLE_PHASE,
} PROCESS_PHASE;

typedef enum _OVEN_MODE {
   NONE,
   PROGRAM1,
   PROGRAM2,
   PROGRAM3,
   PROGRAM4,
   PROGRAM5,
   PROGRAM6,
   PROGRAM7,
   PROGRAM8,
   PROGRAM9,
   PROGRAM10,
   USER_MODE,
} OVEN_MODE;

typedef enum _FLAG_MODE {
   MODE_STAND,
   MODE_SET_1,
   MODE_SET_2,
   MODE_SET_3,
   MODE_SET_4,
   MODE_SET_5,
   MODE_SET_6,
   MODE_SET_7,
   MODE_SET_8,
   MODE_SET_9,
   MODE_SET_10,
} FLAG_MODE;

#define TRIAC_CYCLE 555.0
#define TEMP_COEFF 0.652085      //
unsigned char led7[6][4];
unsigned char led1[5];
unsigned char temp_accum_count = 16;
STATE g_state;
STATE old_state;
OVEN_MODE g_mode = PROGRAM1;
SET g_set = SET_NONE;
//SET_TIME g_set_time;
//FLAG_MODE g_active_mode = MODE_STAND;

unsigned int16 timed_count_ms = 187;   //toggle every 1000 ms;
unsigned char pid_countdown = 0;
unsigned int16 spk_on_count;
int16    tmp_int16;
int8     key_state;
int8     key_flag = 0;
unsigned char key_code = 0;
unsigned char tmp = 0;
unsigned int8 touch_state1, touch_state2;
int16 key_hold_count, key_repeat_count;
#define KEY_HOLD_THRESHOLD (400)
#define KEY_REPEAT_TIME (10)

unsigned char sec, min, hour, day;
unsigned char last_min;

int16 user_setpoint = 15000;
int16 user_protect = 16000;
int16 user_delay_time = 15;
int16 user_ster_time = 90;
int16 i = 0;
      
unsigned char wait_hour, wait_min, wait_day;
unsigned char hold_hour, hold_min;

unsigned int16 password = 0, check_password = 0;
//unsigned int16 remain_time;      //unit is in minute!
unsigned int16 setpoint;
unsigned int16 protect;
unsigned int16 realTemp;
unsigned int16 t1 = 0, t2 = 0, t3 = 0, t4 = 0, t5 = 0;
unsigned int16 t6 = 0, t7 = 0, t8 = 0, t9 = 0, t10 = 0;
unsigned int16 delay_time;
unsigned int16 ster_time;
//unsigned int16 day_ster_time;
//unsigned int16 hour_ster_time;
//unsigned int16 user_day_ster_time;
//unsigned int16 user_hour_ster_time;
//unsigned int16 day_remain_time, hour_remain_time;
unsigned int16 pid_kp, pid_ki, pid_kd;
//unsigned int16 RTD_realTemp2;
//unsigned long long_ster_time, long_user_ster_time;
unsigned long remain_time;
//unsigned long user_hold_time;
//float TEMP_LOWER_FULLON_CORRECTION = 3000.0;

#define SETPOINT_MAX (25000)
#define SETPOINT_DEF (15000)
#define SETPOINT_MIN (1000)
#define PROTECT_MAX (31000)
#define PROTECT_DEF (31000)
#define PROTECT_MIN (1000)
#define FAN_SPEED_MAX (10)
#define FAN_SPEED_DEF (7)
#define FAN_SPEED_MIN (5)
#define DELAY_TIME_MAX (5999)
#define DELAY_TIME_DEF (0)
#define DELAY_TIME_MIN (0)
#define STER_TIME_MAX (5999)
#define STER_TIME_DEF (60)
#define STER_TIME_MIN (0)

#define PID_KP_MAX (100)
#define PID_KP_DEF (60)
#define PID_KP_MIN (0)
#define PID_KI_MAX (100)
#define PID_KI_DEF (55)
#define PID_KI_MIN (0)
#define PID_KD_MAX (100)
#define PID_KD_DEF (28)
#define PID_KD_MIN (0)

#define PID_KP_MAX1 (100)
#define PID_KP_DEF1 (65)
#define PID_KP_MIN1 (0)
#define PID_KI_MAX1 (100)
#define PID_KI_DEF1 (65)
#define PID_KI_MIN1 (0)
#define PID_KD_MAX1 (100)
#define PID_KD_DEF1 (38)
#define PID_KD_MIN1 (0)

#define PROG1_SETPOINT (12000)
#define PROG1_PROTECT (13000)
#define PROG1_DELAY_TIME (0)
#define PROG1_STER_TIME (90)
#define PROG2_SETPOINT (13000)
#define PROG2_PROTECT (14000)
#define PROG2_DELAY_TIME (0)
#define PROG2_STER_TIME (85)
#define PROG3_SETPOINT (14000)
#define PROG3_PROTECT (15000)
#define PROG3_DELAY_TIME (0)
#define PROG3_STER_TIME (80)
#define PROG4_SETPOINT (15000)
#define PROG4_PROTECT (16000)
#define PROG4_DELAY_TIME (0)
#define PROG4_STER_TIME (70)
#define PROG5_SETPOINT (16000)
#define PROG5_PROTECT (17000)
#define PROG5_DELAY_TIME (0)
#define PROG5_STER_TIME (60)
#define PROG6_SETPOINT (17000)
#define PROG6_PROTECT (18000)
#define PROG6_DELAY_TIME (0)
#define PROG6_STER_TIME (50)
#define PROG7_SETPOINT (18000)
#define PROG7_PROTECT (19000)
#define PROG7_DELAY_TIME (0)
#define PROG7_STER_TIME (45)
#define PROG8_SETPOINT (19000)
#define PROG8_PROTECT (20000)
#define PROG8_DELAY_TIME (0)
#define PROG8_STER_TIME (40)
#define PROG9_SETPOINT (20000)
#define PROG9_PROTECT (21000)
#define PROG9_DELAY_TIME (0)
#define PROG9_STER_TIME (35)
#define PROG10_SETPOINT (22000)
#define PROG10_PROTECT (23000)
#define PROG10_DELAY_TIME (0)
#define PROG10_STER_TIME (30)

#define BEEP_TIME (3)

#define OFFSET_TEMP_RANGE (3000)

#define MAX_TEMP_RANGE (32000)
//#define ADC_FILTER_COUNT (256)
#define ADC_FILTER_COUNT (16)

#define RTD_CONST (41876)

unsigned char  fan_speed = FAN_SPEED_MAX;
unsigned int16 triac_on_time1 = 0;
unsigned int16 triac_on_time_new1 = 0;
unsigned int16 triac_count1 = 0;
unsigned int16 triac_on_time2 = 0;
unsigned int16 triac_count2 = 0;

unsigned int16 seri = 0;
unsigned char adc_integ_count = 16;
signed int32 adc_integ_data;
signed int16 adc_data, adc_data_buff;
signed int16 env_temp;
signed int16 thermo_temp;
signed int16 temp_offset = 0;
signed int32 adc_value_ch0;
signed int32 adc_value_ch1;

float k_a, k_b, float_temp;

char fan_pos = 0;
char g_err_code = 0;
char fan_rol_count = 30;
char hour_min_flag = 1;
char flag_day_hour = 0;
char flag_Rs232 = 0;
char flag_Rs232_Ster = 0;
char flag_Rs232_Complete = 0;
char flag_Rs232_Err = 0;
char flag_Rs232_IDLE = 0;
char flag_Pre_Hold = 0;

unsigned char GLb_nCountAvrTemp = 0;

#endif // #define _GLOBALS_H_

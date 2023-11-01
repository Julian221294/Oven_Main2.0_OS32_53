#include "main.h"

#use fast_io(ALL)

#include "leds.h"
#include "keys.h"
#include "adc.h"
#include "triac.h"
#include "rtcc.h"
#include "cap1188.h"
#include "process_touchs.h"
#include "process_leds.h"
#include "process_rs232.h"
#include "process_lifecycle.h"
#include "process_data.h"
#include "AFE90100.h"
// #include "max31865.h"

void global_init(void)
{
   setup_oscillator(OSC_8MHZ | OSC_NORMAL | OSC_31250 | OSC_PLL_ON);
   set_tris_a(0x06);    // All port A (except A1, A2) as output
   set_tris_b(0x00);    // All port B as output
   set_tris_c(0x90);    // PIN_C7=RXD; PIN_C4=SPI-SDI as inputs, other pins as outputs
   set_tris_d(0x40);    // All port D (except D6) as output
   set_tris_e(0x00);    // PortE bit 0, 1, 2 as output
   output_high(PIN_A0); // Disable the AFE
   // output_high(MAX_CS1);//Disable the Max31865-IC1
   // output_high(MAX_CS2);//Disable the Max31865-IC2
   output_high(CAP_CS1);                                                  // Disable the CAP1188-IC1
   output_high(CAP_CS2);                                                  // Disable the CAP1188-IC2
   setup_spi(SPI_MASTER | SPI_L_TO_H | SPI_XMIT_L_TO_H | SPI_CLK_DIV_16); // LMP90100
   // setup_spi(SPI_MASTER|SPI_H_TO_L|SPI_XMIT_L_TO_H|SPI_CLK_DIV_16); //Max31865
   key_init();
   adc_init();
   triac_init();
   RTCC_init();
   Start_DS1307();
   // max31865_init();
   PutDateTime();
   LedClockOn();
   g_state = ST_IDLE;
   old_state = g_state;
   SpeakerOff();
   Load_Data();
   Load_PID();
   switch (g_mode)
   {
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
      Load_Data_User();
      g_mode = USER_MODE;
      ster_time = user_ster_time;
      setpoint = user_setpoint;
      protect = user_protect;
      break;
   }
}

void main()
{
   // delay_ms(5000);
   global_init();

   while (TRUE)
   {
      Process_Touch();
      Process_Led();
      Process_Rs232();
      Get_Data();
      if (fan_speed > 0)
      {
         SetFanSimulator();
         if (fan_speed == FAN_SPEED_MAX)
            Ctrl2On();
      }
      else
      {
         LedFanOffAll();
         Ctrl2Off();
      }
      if (g_state >= ST_RUN_WAITING_TIME)
      {
         Process_Data();
         Process_LifeCycle();
      }
   }
}

//
//==============================================================================
//

#ifndef _PID_H_
#define _PID_H_

//Heater all off when    above setpoint 0.5 Degree Celcius
//Heater full on when below setpoint 50.0 Degree Celcius
#define TEMP_UPPER_ALLOFF (-80.0)
#define TEMP_LOWER_FULLON (2000.0)
// 1 degree / second MAX
//#define TEMP_SPEED_MAX_CONST (100.0)
// 0.2 degree / second MAX
#define TEMP_SPEED_MAX_CONST (20.0)
//
#define TEMP_INTEG_MAX_CONST (60000.0)
/*
unsigned int16 process_pid(float temp)
{
   static float pre_err = 0;
   static float i_term = 0;
   float err, p_term, d_term;
   float power_term;
   //pid_kp = 1.0; pid_ki = 0.0; pid_kd = 0.0;
   err = 1.0*setpoint - temp;
   //printf("PID:\r\n");
   //lower and upper ranges:
   if (err < TEMP_UPPER_ALLOFF)
   {
      power_term = 0;
      return (unsigned int16)power_term;   //    turn off heater
   }
   //if (err > TEMP_LOWER_FULLON)
   if (err > TEMP_LOWER_FULLON_CORRECTION)
   {
      i_term = 0;
      power_term = TRIAC_CYCLE;
      return (unsigned int16)power_term;  // heater 100% on
   }
   
   //p_term = 100% at (setpoint - TEMP_LOWER_FULLON); p_term = 0% at (setpoint - TEMP_UPPER_ALLOFF)
   p_term = (err * TRIAC_CYCLE)/(TEMP_LOWER_FULLON_CORRECTION);
   d_term = ((err-pre_err) * TRIAC_CYCLE)/TEMP_SPEED_MAX_CONST;
   if (d_term <= (-1.0*TRIAC_CYCLE))
      d_term = -1.0*TRIAC_CYCLE;
   if (d_term > 1.0*TRIAC_CYCLE)
      d_term = 1.0*TRIAC_CYCLE;
   i_term += err*TRIAC_CYCLE/TEMP_INTEG_MAX_CONST;
   if (i_term >= TRIAC_CYCLE)
      i_term = TRIAC_CYCLE;
   if (i_term <= -TRIAC_CYCLE)
      i_term = -TRIAC_CYCLE;
   //printf("p_term = %f; i_term = %f; d_term = %f;\r\n", p_term, i_term, d_term);
   pre_err = err;
   power_term = (pid_kp*p_term + pid_ki*i_term + pid_kd*d_term)/100.0;
   //printf("Power_Term: %f\r\n", power_term);
   if (power_term <= 0.0)
   {
      return 0;
      //i_term = 0;
   }
   if (power_term >= (1.0*TRIAC_CYCLE))
   {
      //i_term = 0;
      return (unsigned int16)TRIAC_CYCLE;
   }
   return (unsigned int16)(power_term);
}
*/
unsigned int16 process_adaptive(float temp)
{
   static float pre_err = 0;
   static float power_term = 0;
   float err, p_term, d_term;
   float power_adjust_term;
   err = 1.0*setpoint - temp;
   //lower and upper ranges:
   if (err < TEMP_UPPER_ALLOFF)
   {
      power_term = 0;
      return (unsigned int16)power_term;   //    turn off heater
   }
   if (err > TEMP_LOWER_FULLON)
   {
      power_term = TRIAC_CYCLE;
      return (unsigned int16)power_term;  // heater 100% on
   }
   
   p_term = (pid_kp*err * TRIAC_CYCLE)/(TEMP_LOWER_FULLON*100.0);
   d_term = (pid_kd*(err-pre_err) * TRIAC_CYCLE)/(TEMP_SPEED_MAX_CONST*100.0);
   pre_err = err;
   power_adjust_term = (p_term + d_term);
   power_term += power_adjust_term;
   //printf("\n\r %f; %f; %f; %f; %f", err, p_term, d_term, power_adjust_term, power_term);
   if (power_term <= 0.0)
      power_term = 0.0;
   if (power_term >= (1.0*TRIAC_CYCLE))
      power_term = TRIAC_CYCLE;
   return (unsigned int16)((power_term*pid_ki)/100.0);
}

#endif   // define _PID_H_

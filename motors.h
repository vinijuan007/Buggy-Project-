#include "mbed.h"


class Motor{
protected:
   DigitalOut direction;
   PwmOut pwm;
   int period; // period in milli seconds of the pwm signal 
   float duty_cycle; // number between 0.0f - 1.0f
   
public:
   Motor(PinName d,PinName p) : direction(d), pwm(p){
       direction = 0 ;// depending on which wheel it will be 1 or 0 
       period = 100;
       pwm.period_ms(period);//setting the period 

   }
   void set_dt(float dc) {
   pwm.write(dc); // setting the duty cycle 
   }
   
};


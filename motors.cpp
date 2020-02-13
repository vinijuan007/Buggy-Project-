#include "motors.h"


   Motors::Motors(){
       PwmOut pwmA(D4);
       DigitalOut polar_modeA(D5);
       polar_modeA = 1;// Bipolar mode should be chossen 
       PwmOut pwmB(D4);
       DigitalOut polar_modeB(D5);
       polar_modeB = 1;// Bipolar mode should be chossen 
       
       period = 100;
       
       pwmA.period_ms(period);//setting the period 
       pwmB.period_ms(period);//setting the period 
   }

   void Motors::set_duty_cycleA(float dc) {
    pwmA.write(dc); // setting the duty cycle 
   }

   void Motors::set_duty_cycleB(float dc) {
    pwmB.write(dc); // setting the duty cycle 
   }
   

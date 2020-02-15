#include "motors.h"


   Motors::Motors():pwmA(D5), polar_modeA(D4), pwmB(D3),polar_modeB(D2){

       polar_modeA = 1;// Bipolar mode 
       polar_modeB = 1;// Bipolar mode  
       
       period = 50; // 20kHz
            
   }

   void Motors::set_duty_cycleA(float dcA) {
    
    
    pwmA.period_us(period);//setting the period of the pwm signal from motor A
    dcA = dcA - 1;
    pwmA.write(dcA); // dcA 
                     //goes foward  in 0.5 to 1.0
                     //and backward in 0.5 to 0.0 
   }

   void Motors::set_duty_cycleB(float dcB) {
       
    dcB = dcB - 1;
    pwmB.period_us(period);//setting the period of the pwm signal from motor B
    pwmB.write(dcB); 
                     //goes foward  in 0.5 to 1.0
                     //and backward in 0.5 to 0.0  
   }
   


#include "mbed.h"

class { 
protected:
   DigitalOut direction;// direction of rotation
   DigitalOut polar_mode;//Bipolar or Unipolar mode
   PwmOut pwm;
   int period; // period in milli seconds of the pwm signal 
   float duty_cycle; // number between 0.0f - 1.0f
   
public:
   Motor(PinName d,PinName pm, PinName p)
   : direction(d), polar_mode(pm), pwm(p){
       polar_mode = 1;// 1 for bipolar 0 for unipolar (check info)
       period = 100;
       pwm.period_ms(period);//setting the period 
   }

   void set_duty_cycle(float dc) {
   pwm.write(dc); // setting the duty cycle 
   }

   void set_direction(bool a) {
   direction = a; // directio the motor will turn 
   }
   
};

class Movement{
protected:
    Motor* RM;
    Motor* LM;

public:
    Movement(Motor* r,Motor* l) : RM(r), LM(l){}
    void Move_foward(float speed){
        RM->set_duty_cycle(speed);
        RM->set_direction(1);
        LM->set_duty_cycle(speed);
        LM->set_direction(0);
    }
    
};

int main(){
    Motor* Right_Motor = new Motor(D1,D2,D3);
    Motor* Left_Motor = new Motor(D4,D5),D6;
    Movement Move_Buggy(Right_Motor, Left_Motor);
     while (1) {};
      
} 


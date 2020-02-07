#include "mbed.h"


class Motor{
protected:
   DigitalOut direction;
   PwmOut pwm;
   int period; // period in milli seconds of the pwm signal 
   float duty_cycle; // number between 0.0f - 1.0f
   
public:
   Motor(PinName d,PinName p) : direction(d), pwm(p){
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
    Motor* Right_Motor = new Motor(D1,D2);
    Motor* Left_Motor = new Motor(D3,D4);
    Movement Move_Buggy(PL , CC, 0.0, 3.3, 1, 10);
     while (1) {};
      
} 


#include "mbed.h"
#include "QEI.h"
#include "C12832.h"

C12832 lcd(D11, D13, D12, D7, D10);

// This class just sets the duty cycle of a the input motor 
class Motor { 
protected:
   DigitalOut polar_mode;//Bipolar 
   PwmOut pwm;
   int period; // period in milli seconds of the pwm signal 
   float duty_cycle; // number between 0.0f - 1.0f
   
public:
   Motor( PinName pm, PinName p): polar_mode(pm), pwm(p){
       polar_mode = 1;// Bipolar mode should be chossen 
       period = 100;
       pwm.period_ms(period);//setting the period 
   }

   void set_duty_cycle(float dc) {
   pwm.write(dc); // setting the duty cycle 
   }
   
};


class Speed_Control{
protected:
Motor* RMotor;
Motor* LMotor;
QEI* REncoder;
QEI* LEncoder;
float speed_REncoder;
float speed_LEncoder;
float time; // amount of time between ticker update of speed 
float diameter; // diameter of wheel 
float duty_cycle; 
Ticker tkr;

public:
Speed_Control(QEI* r, QEI* l,Motor* rr,Motor* ll): REncoder(r), LEncoder(l), RMotor(rr), LMotor(ll){
    REncoder->reset();
    LEncoder->reset();
    diameter = 20;
    time = 2;
    duty_cycle = 0.8;
    RMotor->set_duty_cycle(duty_cycle);
    LMotor->set_duty_cycle(duty_cycle);
    tkr.attach(callback(this,&Speed_Control::Move_foward()), time);
}

void calculate_speed(void){
    float pulse_a,pulse_b;
    pulse_a = (float (REncoder->getPulses()))/time;
    pulse_b = (float (LEncoder->getPulses()))/time;
    speed_REncoder = pulse_a * 3.1416 * (diameter / 256);
    speed_LEncoder = pulse_b * 3.1416 * (diameter / 256);
    REncoder->reset();
    LEncoder->reset();
}

void printRM(void){
    lcd.locate(0,3);
    lcd.printf("Speed RM");
    lcd.locate(15,3);
    lcd.printf("%float ", speed_LEncoder);
}

void printLM(){
    lcd.locate(0,14);
    lcd.printf("Speed LM");
    lcd.locate(15,14);
    lcd.printf("%float ", speed_REncoder);
}

void control_speed(void){
    if(speed_REncoder > speed_LEncoder){
        RMotor->set_duty_cycle(duty_cycle + 0.01);
        LMotor->set_duty_cycle(duty_cycle - 0.01);
    }
    else if(speed_REncoder < speed_LEncoder){
        RMotor->set_duty_cycle(duty_cycle - 0.01);
        LMotor->set_duty_cycle(duty_cycle + 0.01);
    }

}

void Move_foward(void){
    calculate_speed();
    printLM();
    printRM();
    control_speed();
}

};


int main(){
    Motor* Right_Motor = new Motor(D2,D3);
    Motor* Left_Motor = new Motor(D5,D6);
    QEI* Right_Encoder = new QEI(D7,D8, D9, 20);
    QEI* Left_Encoder = new QEI(D7,D8, D9, 20);
    Speed_Control Speed_of_buggy(Right_Encoder, Left_Encoder,Right_Motor, Left_Motor);
     while (1) {};
      
} 


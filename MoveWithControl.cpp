
#include "mbed.h"
#include "QEI.h"
#include "C12832.h"
#include "motors.h"

C12832 lcd(D11, D13, D12, D7, D10);


class Speed_Control{
protected:
Motors Buggy_Motors;
QEI* REncoder;
QEI* LEncoder;
float speed_REncoder;
float speed_LEncoder;
float distanceA;
float distanceB;
float time; // amount of time between ticker update of speed 
float duty_cycleA; 
float duty_cycleB;
float sum_of_pulsesA;

Ticker tkr;

public:
Speed_Control(QEI* r, QEI* l): REncoder(r), LEncoder(l){
    sum_of_pulsesA = 0;
    REncoder->reset();
    LEncoder->reset();
    time = 0.5;
    duty_cycleA = 0.586;
    duty_cycleB = 0.6;
    Buggy_Motors.set_duty_cycleA(duty_cycleA);
    Buggy_Motors.set_duty_cycleB(duty_cycleB);
    tkr.attach(callback(this , &Speed_Control::Move_foward ), time);
}

void calculate_speed(void){
    float pulse_a,pulse_b;
    float diameter = 0.08; // diameter of the wheels 
    pulse_a = (float (REncoder->getPulses()))/time;// pulse rate of A
    pulse_b = (float (LEncoder->getPulses()))/time;// pulse rate of B
    speed_REncoder = abs(pulse_a) * 3.141 * diameter / 1024;
    speed_LEncoder = abs(pulse_b) * 3.141 * diameter / 1024;
    REncoder->reset();
    LEncoder->reset();
}

void calculate_distance(void){

    sum_of_pulsesA = sum_of_pulsesA + (float (REncoder->getPulses()));
    distanceA = sum_of_pulsesA * 3.141 * 0.08 / 1024;
    lcd.locate(0,20);
    lcd.printf("%.4f ",distanceA );
}

void printRM(void){
    lcd.locate(0,2);
    lcd.printf("A");
    lcd.locate(0,12);
    lcd.printf("%.4f ", speed_REncoder);
}

void printLM(){
    lcd.locate(60,2);
    lcd.printf("B");
    lcd.locate(60,12);
    lcd.printf("%.4f ", speed_LEncoder);
}

void control_speedR(void){
    float error;
    if(1.3 > speed_REncoder){
        error = (1.3 - speed_REncoder)*0.5/1.558;
        duty_cycleA = duty_cycleA + error;
        Buggy_Motors.set_duty_cycleA(duty_cycleA);
        lcd.locate(0,20);
        lcd.printf(">>%.4f ", duty_cycleA);
        if(duty_cycleA > 1){
            duty_cycleA = 1.0; 
            }
    }
    else if(1.3 < speed_REncoder){
        error = (1.3 - speed_REncoder)*0.5/1.558;
        duty_cycleA = duty_cycleA + error;
        Buggy_Motors.set_duty_cycleA(duty_cycleA);
        lcd.locate(0,20);
        lcd.printf("<<%.4f ", duty_cycleA);
        if(duty_cycleA > 1){
            duty_cycleA = 1.0; 
            }
    
    }
    else {
        Buggy_Motors.set_duty_cycleA(duty_cycleA);
    }
}

void Move_foward(void){
    calculate_distance();
    calculate_speed();
   // control_speedR();
    printLM();
    printRM();
    }




};


int main(){

    QEI* Right_Encoder = new QEI(PB_15,PB_14, NC, 1024, QEI::X4_ENCODING);
    QEI* Left_Encoder = new QEI(PC_8,PC_6, NC, 1024 , QEI::X4_ENCODING);
    Speed_Control Speed_of_buggy(Right_Encoder, Left_Encoder);
     while (1) {};
      
} 

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
int a;

Ticker tkr;

public:
Speed_Control(QEI* r, QEI* l): REncoder(r), LEncoder(l){
    a = 0; //initializing a ;
    REncoder->reset();
    LEncoder->reset();
    time = 0.4;
    duty_cycleA = 0.6;
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
    speed_REncoder = pulse_a * 3.141 * diameter / 256;
    speed_LEncoder = pulse_b * 3.141 * diameter / 256;
    REncoder->reset();
    LEncoder->reset();
}

/*void calculate_distance(void){
    distanceA = speed_REncoder*time;
    distanceB = speed_LEncoder*time;
}*/

void printRM(void){
    lcd.locate(0,3);
    lcd.printf("A");
    lcd.locate(15,3);
    lcd.printf("%float ", speed_LEncoder);
}

void printLM(){
    lcd.locate(0,14);
    lcd.printf("B");
    lcd.locate(15,14);
    lcd.printf("%float ", speed_REncoder);
}

void control_speed(void){
    if(speed_REncoder > speed_LEncoder){
        duty_cycleA = duty_cycleA - 0.01;
        duty_cycleB = duty_cycleB + 0.01;
        Buggy_Motors.set_duty_cycleA(duty_cycleA);
        Buggy_Motors.set_duty_cycleB(duty_cycleB);
    }
    else if(speed_REncoder < speed_LEncoder){
        duty_cycleA = duty_cycleA + 0.01;
        duty_cycleB = duty_cycleB - 0.01;
        Buggy_Motors.set_duty_cycleA(duty_cycleA);
        Buggy_Motors.set_duty_cycleB(duty_cycleB);
    }
    else {
        Buggy_Motors.set_duty_cycleA(duty_cycleA);
        Buggy_Motors.set_duty_cycleB(duty_cycleB);
    }
}

void Move_foward(void){
    calculate_speed();
    control_speed();
    a++;
    if(a == 3){
        a = 0;
        printLM();
        printRM();
    }

}


};


int main(){

    QEI* Right_Encoder = new QEI(PC_8,PC_6, NC, 1024, QEI::X4_ENCODING);
    QEI* Left_Encoder = new QEI(PB_15,PB_14, NC, 1024 , QEI::X4_ENCODING);
    Speed_Control Speed_of_buggy(Right_Encoder, Left_Encoder);
     while (1) {};
      
} 


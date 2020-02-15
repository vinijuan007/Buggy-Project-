#include "mbed.h"
#include "motors.h"

int main(){

    Motors Buggy_motors; 
    Buggy_motors.set_duty_cycleA(0.45);
    Buggy_motors.set_duty_cycleB(0.45);
     while(1){};

}
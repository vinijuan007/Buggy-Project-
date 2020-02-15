#ifndef MOTORS_H
#define MOTORS_H

/**
 * Includes
 */
#include "mbed.h"

class Motors {

public:
    Motors();
    void set_duty_cycleA(float dc);
    void set_duty_cycleB(float dc);

    
private: 
   DigitalOut polar_modeA;//Bipolar 
   PwmOut pwmA;

   DigitalOut polar_modeB;//Bipolar 
   PwmOut pwmB; 

   int period; // period in milli seconds of the pwm signal 
};

#endif 

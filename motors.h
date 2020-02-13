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

    

   DigitalOut polar_modeA;//Bipolar 
   PwmOut pwmA;
   float duty_cycleA; // number between 0.0f - 1.0f
   DigitalOut polar_modeB;//Bipolar 
   PwmOut pwmB; 
   float duty_cycleB; // number between 0.0f - 1.0f
   int period; // period in milli seconds of the pwm signal 
};

#endif 

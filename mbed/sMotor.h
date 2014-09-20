/*
############################################
##           sMotor v0.1 Library          ##
##          created by Samuel Matildes    ##
############################################
        ---- sam.naeec@gmail.com -----
This library was made for 4-Phase Stepper Motors
I don't take any resposability for the damage caused to your equipment.

*/
#ifndef MBED_SMOTOR_H
#define MBED_SMOTOR_H

#include "mbed.h"

class sMotor {
public:
    
    sMotor(PinName A0, PinName A1, PinName A2, PinName A3); //motor constructor

    int step(int num_steps, int direction, int speed,int* total_steps);
    int anticlockwise(int current_step,int* total_steps);
    int clockwise(int current_step,int* total_steps);
    int stop(int current_step);
    void delay(int delay_time);

private:

    DigitalOut _A0;
    DigitalOut _A1;
    DigitalOut _A2;
    DigitalOut _A3;

};

#endif

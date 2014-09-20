
#include "mbed.h"

int motorSpeed; // Steper speed
sMotor::sMotor(PinName A0, PinName A1, PinName A2, PinName A3) : _A0(A0), _A1(A1), _A2(A2), _A3(A3) { // Defenition of motor pins
    _A0=0;
    _A1=0;
    _A2=0;
    _A3=0;
}


int sMotor::anticlockwise(int current_step, int* total_steps) { // rotate the motor 1 step anticlockwise 
    if (*total_steps == 300) {return current_step;}
        current_step = (current_step+1)%8;
        (*total_steps)++;
        switch (current_step) { // activate the ports A0, A2, A3, A3 in a binary sequence for steps
            case 0: {
                _A0=0;
                _A1=0;
                _A2=0;
                _A3=1;
            }
            break;
            case 1: {
                _A0=0;
                _A1=0;
                _A2=1;
                _A3=1;
            }
            break;
            case 2: {
                _A0=0;
                _A1=0;
                _A2=1;
                _A3=0;
            }
            break;
            case 3: {
                _A0=0;
                _A1=1;
                _A2=1;
                _A3=0;
            }
            break;
            case 4: {
                _A0=0;
                _A1=1;
                _A2=0;
                _A3=0;
            }
            break;
            case 5: {
                _A0=1;
                _A1=1;
                _A2=0;
                _A3=0;
            }
            break;
            case 6: {
                _A0=1;
                _A1=0;
                _A2=0;
                _A3=0;
            }
            break;
            case 7: {
                _A0=1;
                _A1=0;
                _A2=0;
                _A3=1;
            }
            
            break;
        }
    wait_us(motorSpeed); // wait time defines the speed 
    return current_step;
}

int sMotor::clockwise(int current_step, int* total_steps) { // rotate the motor 1 step clockwise 
    if (*total_steps == -300) {return current_step;}
        current_step = (current_step+8-1)%8;
        (*total_steps)--;
        switch (current_step) {
            case 0: {
                _A0=0;
                _A1=0;
                _A2=0;
                _A3=1;
            }
            break;
            case 1: {
                _A0=0;
                _A1=0;
                _A2=1;
                _A3=1;
            }
            break;
            case 2: {
                _A0=0;
                _A1=0;
                _A2=1;
                _A3=0;
            }
            break;
            case 3: {
                _A0=0;
                _A1=1;
                _A2=1;
                _A3=0;
            }
            break;
            case 4: {
                _A0=0;
                _A1=1;
                _A2=0;
                _A3=0;
            }
            break;
            case 5: {
                _A0=1;
                _A1=1;
                _A2=0;
                _A3=0;
            }
            break;
            case 6: {
                _A0=1;
                _A1=0;
                _A2=0;
                _A3=0;
            }
            break;
            case 7: {
                _A0=1;
                _A1=0;
                _A2=0;
                _A3=1;
            }
            break;
        }
 
 
        wait_us(motorSpeed); // wait time defines the speed 
        return current_step;
}

int sMotor::step(int current_step, int direction, int speed, int* total_steps) {// steper function: number of steps, direction (0- right, 1- left), speed (default 1200)
    motorSpeed=speed; //set motor speed
    int next_step;
    //printf("hello");
    if (direction==0) // turn clockwise
         {
            next_step = clockwise(current_step,total_steps);
        } // turn number of steps applied 
    else if (direction==1)// turn anticlockwise
         {
            next_step = anticlockwise(current_step,total_steps);
        }// turn number of steps applied 
    else if (direction==3){next_step = current_step;};
    next_step = next_step % 8;
    return next_step;
}
    
void sMotor::delay(int delay_time){
    wait_us(delay_time);   
}

/*
############################################
##           sMotor v0.1 Test Program     ##
##          created by Samuel Matildes    ##
############################################
        ---- sam.naeec@gmail.com -----
This library was made for 4-Phase Stepper Motors
I don't take any resposability for the damage caused to your equipment.

*/

#include "mbed.h"
#include "sMotor.h"


Serial pc(USBTX, USBRX);
sMotor motor(p9, p10, p11, p12); // creates new stepper motor: IN1, IN2, IN3, IN4
DigitalOut myled1(LED1);
DigitalOut myled2(LED2);
DigitalOut myled3(LED3);
DigitalOut myled4(LED4);
AnalogOut signal(p18);
int step_speed = 1500 ; // set default motor speed
int numstep = 512 ; // defines full turn of 360 degree
int current_step=0;
int* total_steps = (int*) malloc(sizeof(int));
//you might want to calibrate this value according to your motor

int main()
{

    //Credits
    printf("4 Phase Stepper Motor v0.1 - Test Program\r\n");
    printf("developed by Samuel Matildes\r\n");
    printf("\n\r");


    // Screen Menu
    printf("Default Speed: %d\n\r",step_speed);
    printf("1-forward");
    printf("2-backward");
    printf("3-stop");
    printf("5- Change Speed\n\r");

        myled1=1;
        wait(0.2);
        myled1=0;
        wait(0.2);
        int temp;

    while (1) {
            signal = 1;
            if (pc.readable()) { // checks for serial
            printf("ask for input   ");
            }
        
            if (pc.getc()=='1'){
                for (int j=0;j<100;j++){
                    temp = current_step;
                current_step = motor.step(current_step,0,step_speed,total_steps); // number of steps, direction, speed
                if (current_step == temp){break;}
                myled1=1;myled2=0;myled3=0;myled4=0;
                }
                for (int j=0;j<5000;j++){
                    temp = current_step;
                current_step = motor.step((current_step%8) , 0 , (step_speed*0.75),total_steps);
                if (current_step == temp){break;}
                myled1=0;myled2=1;myled3=0;myled4=0;
                }
                myled1=1;myled2=1;myled3=1;myled4=1;
                
            }
            if (pc.getc()=='2'){
                temp = current_step;
                for (int j=0;j<200;j++){
                    temp = current_step;
                current_step = motor.step(current_step%8,1,step_speed,total_steps);
                if (current_step == temp){break;}
                myled1=0;myled2=1;myled3=0;myled4=0;
                }
                for (int j=0;j<5000;j++){
                    temp = current_step;
                current_step = motor.step(current_step%8,1,step_speed*0.75,total_steps);
                if (current_step == temp){break;}
                myled1=0;myled2=1;myled3=0;myled4=0;
                }
                myled1=1;myled2=1;myled3=1;myled4=1;
            }
            
            if (pc.getc()=='3'){
                //current_step = motor.step(current_step%8,3,step_speed);
                myled1=1;myled2=1;myled3=1;myled4=1;
                }
            
            if (0) {
                printf("Current Speed: %d\n\r", step_speed);
                printf("New speed: \n\r");
                pc.scanf("%d",&step_speed); // sets new speed
            }
        }
        
    
}

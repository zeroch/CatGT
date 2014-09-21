#include "mbed.h"
#include "EthernetInterface.h"
#include "MbedJSONValue.h"
#include "sMotor.h"


#define RETRIES_ALLOWED 5

Serial pc(USBTX, USBRX);
sMotor motor(p9, p10, p11, p12); // creates new stepper motor: IN1, IN2, IN3, IN4
DigitalOut myled1(LED1);
DigitalOut myled2(LED2);
DigitalOut myled3(LED3);
DigitalOut myled4(LED4);
int step_speed = 1200 ; // set default motor speed
int numstep = 512 ; // defines full turn of 360 degree
int* total_steps = (int*) malloc(sizeof(int));


const char* SERVER_ADDRESS = "198.74.55.55";
const int SERVER_PORT = 4321;
//Stepper Part

int stepper(int index,int current_step)
{
    if (pc.readable()) { // checks for serial
        printf("ask for input   ");
    }
    int temp;
    if (index==0) {
        for (int j=0; j<50; j++) {
            temp = current_step;
            current_step = motor.step(current_step,0,step_speed,total_steps); // number of steps, direction, speed
            if (current_step == temp) {
                break;
            }
            myled1=1;
            myled2=0;
            myled3=0;
            myled4=0;
        }
        for (int j=0; j<700; j++) {
            temp = current_step;
            current_step = motor.step((current_step%8) , 0 , (step_speed*0.75),total_steps);
            if (current_step == temp) {
                break;
            }
            myled1=0;
            myled2=1;
            myled3=0;
            myled4=0;
        }
        myled1=1;
        myled2=1;
        myled3=1;
        myled4=1;

    }
    if (index==1) {
        temp = current_step;
        for (int j=0; j<50; j++) {
            temp = current_step;
            current_step = motor.step(current_step%8,1,step_speed,total_steps);
            if (current_step == temp) {
                break;
            }
            myled1=0;
            myled2=1;
            myled3=0;
            myled4=0;
        }
        for (int j=0; j<700; j++) {
            temp = current_step;
            current_step = motor.step(current_step%8,1,step_speed*0.75,total_steps);
            if (current_step == temp) {
                break;
            }
            myled1=0;
            myled2=1;
            myled3=0;
            myled4=0;
        }
        myled1=1;
        myled2=1;
        myled3=1;
        myled4=1;
    }

    return current_step;
}



int main()
{

    MbedJSONValue demo;
    std::string s;

    printf("hello world!");
    printf("Initialising...\n");
    set_time(0);

    EthernetInterface eth;
    DigitalOut led1(LED1);

    // use DHCP
    eth.init();

    //Stepper Part
    AnalogOut LEDsignal(p18);
    int current_step=0;
    LEDsignal = 1;

    // attempt DHCP and if timing out then try again
    while (eth.connect()) {
        printf("DHCP timeout\n");
    };


    // successful DHCP
    printf("IP Address is %s\n", eth.getIPAddress());


    // bind socket connection.
    TCPSocketConnection socket;
    while(socket.connect(SERVER_ADDRESS, SERVER_PORT) < 0) {
        printf("Unable to connect to %s on part %d \n",  SERVER_ADDRESS, SERVER_PORT );
        wait(1);
        led1 = !led1;
    }


    char * buf = (char*)malloc(sizeof(char));

    int value;
    bool on = false;
                
    while(true) {
        int n = socket.receive(buf,1);

        if(n != -1) {

        printf("[Debug]: Total bytes received : %d\n", n);
        printf("[Debug]: Command %c ", buf[0]);

            switch(*buf){
                case 'A': 
                    value = 1;
                    break;
                case 'B':
                    value = 0;
                    break;
                case 'C':
                    on = true;
                    break;
                case 'D':
                    on = false;
                    break;
                default:
                    break;        
            }
            /***************
             This place the stepper motor action.
            ****************/
            //Stepper Part
            current_step = stepper(value, current_step);
            memset(buf,0,n);
        } else {
            printf("[DEBUG]: socket.receive %d\n", n);
        }

    }

    // close socket at end of send and receive
    socket.close();

}
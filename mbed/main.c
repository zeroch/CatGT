#include "mbed.h"
#include "EthernetInterface.h"
#include "MbedJSONValue.h"

#define RETRIES_ALLOWED 5

Serial pc2(USBTX, USBRX);

const char* SERVER_ADDRESS = "198.74.55.55";
const int SERVER_PORT = 10000;
int* total_steps = (int*) malloc(sizeof(int));

//Stepper Part

LEDsignal = 1;
int stepper(int index,int current_step){
    if (pc.readable()) { // checks for serial
        printf("ask for input   ");
    }

    if (index==1){
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
    if (index==2){
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
    
    return current_step;
}



int main()
{

    MbedJSONValue demo;
    std::string s;


    printf("hello world!");
    pc2.baud(115200);
    printf("Initialising...\n");
    set_time(0);

    EthernetInterface eth;
    DigitalOut led1(LED1);
    // use DHCP
    eth.init();
    
    //Stepper Part
    AnalogOut LEDsignal(p18);
    int step_speed = 1500 ; // set default motor speed
    int numstep = 512 ; // defines full turn of 360 degree
    int current_step=0;
    LEDsignal = 1

    // attempt DHCP and if timing out then try again
    while (eth.connect()) {
        printf("DHCP timeout\n");
    };

    
    // successful DHCP
    printf("IP Address is %s\n", eth.getIPAddress());
    
    TCPSocketConnection socket;
    while(socket.connect(SERVER_ADDRESS, SERVER_PORT) < 0){
        printf("Unable to connect to %s on part %d \n",  SERVER_ADDRESS, SERVER_PORT );
        wait(1);
        led1 = !led1;

    }


    char echo[] ="This is echo from cat alpha\n";
    socket.send_all(echo, sizeof(echo)-1);

    int index;
    while(true){

        char buf[35];
        
        int n = socket.receive(buf,35);
       if(n != -1) {

         buf[n] = '\0';
         printf("[DEBUG] %s\n", buf);           
           parse(demo, buf);
           index = demo["Value"].get<int>();
           printf("[DEBUG]: current Index is %d \n", index);

           /***************


            This place the stepper motor action. 

           ****************/
            //Stepper Part
            current_step = stepper(index, current_step);

       }else {
            printf("[DEBUG]: socket.receive %d\n", n);
       }
       wait(2);
        

    }
   
        // close socket at end of send and receive
        socket.close();
        
        // wait before repeating
        Thread::wait(1000);

    // }
}

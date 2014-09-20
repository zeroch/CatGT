#include "mbed.h"
#include "EthernetInterface.h"
#include "MbedJSONValue.h"

#define RETRIES_ALLOWED 5

Serial pc2(USBTX, USBRX);

const char* SERVER_ADDRESS = "198.74.55.55";
const int SERVER_PORT = 10000;



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
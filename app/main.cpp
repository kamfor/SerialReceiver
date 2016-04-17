#include <iostream>
#include "include/serial.h"
#include "include/interface.h"
#include "include/buffer.h"

using namespace std;

int main()
{    
    SerialPort* connection = new SerialPort("Baud9600", "NoParity", "OneStop", "Data8", "ttyACM0", "NoFlowControl");
    Buffer buffer(1024,'\n');
    Interface console;
    int i;

    /*console.setbaud(connection);

    console.clearscreen();

    console.setparity(connection);

    console.clearscreen();

    console.setstop(connection);

    console.clearscreen();

    console.setdata(connection);

    console.clearscreen();

    console.setport(connection);

    console.clearscreen();

    console.setflow(connection);

    console.clearscreen();*/

    console.showconnectionoptions(connection);

    connection->connect();

    connection->flush();

    while(1){

        i = connection->receive(buffer.data);
        if(i>0){
            buffer.show(i);
        }
        usleep(10000000);
    }

    connection->disconnect();

    return 0;
}

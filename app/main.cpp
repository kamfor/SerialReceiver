#include <iostream>
#include "include/serial.h"
#include "include/interface.h"
#include "include/buffer.h"

using namespace std;

int main()
{    
    SerialPort* connection = new SerialPort("Baud9600", "NoParity", "OneStop", "Data8", "ttyS0", "NoFlowControl");
    Buffer buffer(1024,'\n');
    Interface console;

    console.clearscreen();

    console.setbaud(connection);

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

    console.clearscreen();

    console.showconnectionoptions(connection);

    connection->connect();

    connection->receive(buffer.fill());

    return 0;
}

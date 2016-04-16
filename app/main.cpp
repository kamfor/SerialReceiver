#include <iostream>
#include "include/serial.h"

using namespace std;

int main()
{
    string i;

    SerialPort connection("Baud9600", "NoParity", "OneStop", "Data8", "ttyS0", "NoFlowControl");
    Buffer buffer(1024,'\n');

    cout<<"SerialReceiverConsole\n"<<endl;
    cout<<"Chose connection parameters\n"<<endl;

    cout<<"Type baudrate name from list below\n"<<endl;
    connection.baudrate.showoptions();
    do{
        cin>>i;
    } while(connection.baudrate.set(i));

    cout<<"Type parity type name from list below\n"<<endl;
    connection.parity.showoptions();
    do {
        cin>>i;
    }while(connection.parity.set(i));

    cout<<"Type stop bits name from list below\n"<<endl;
    connection.stopbits.showoptions();
    do{
        cin>>i;
    }while(connection.stopbits.set(i));

    cout<<"Type data bits name from list below\n"<<endl;
    connection.databits.showoptions();
    do{
        cin>>i;
    }while(connection.databits.set(i));

    cout<<"Type port name from list below\n"<<endl;
    connection.portname.showoptions();
    do{
        cin>>i;
    }while(connection.portname.set(i));

    cout<<"Type flow control type from list below\n"<<endl;
    connection.flowcontrol.showoptions();
    do{
        cin>>i;
    }while(connection.flowcontrol.set(i));



    connection.connect();

    //connection.receive(buffer.fill());

    return 0;
}

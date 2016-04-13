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
    cin>>i;
    connection.baudrate.set(i);

    cout<<"Type parity type name from list below\n"<<endl;
    connection.parity.showoptions();
    cin>>i;
    connection.parity.set(i);

    cout<<"Type stop bits name from list below\n"<<endl;
    connection.stopbits.showoptions();
    cin>>i;
    connection.stopbits.set(i);

    cout<<"Type data bits name from list below\n"<<endl;
    connection.databits.showoptions();
    cin>>i;
    connection.databits.set(i);

    cout<<"Type port name from list below\n"<<endl;
    connection.portname.showoptions();
    cin>>i;
    connection.portname.set(i);

    cout<<"Type flow control type from list below\n"<<endl;
    connection.flowcontrol.showoptions();
    cin>>i;
    connection.flowcontrol.set(i);



    //connection.connect();

    //connection.receive(buffer.fill());

    return 0;
}

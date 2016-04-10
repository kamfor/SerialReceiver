#include <iostream>
#include "include/serial.h"

using namespace std;

int main(int argc, char *argv[])
{
    SerialPort connection("Baud9600", "NoParity", "OneStop", "Data8", "ttyS0", "NoFlowControl");

    cout << "Hello World!" << endl;
    return 0;
}

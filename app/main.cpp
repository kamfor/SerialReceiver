#include <iostream>
#include "include/serial.h"

using namespace std;

int main(int argc, char *argv[])
{
    Status sample;

    sample.nic();

    cout << "Hello World!" << endl;
    return 0;
}

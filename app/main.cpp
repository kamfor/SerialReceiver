#include <iostream>
#include "include/serial.h"

using namespace std;

int main(int argc, char *argv[])
{
    Status pierwszy;

    pierwszy.set("dziala");

    int liczba = pierwszy.getint();

    cout<<liczba<<endl;

    cout << "Hello World!" << endl;
    return 0;
}

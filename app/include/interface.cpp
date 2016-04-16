#include<cstdio>
#include<iostream>
#include "interface.h"

using namespace std;

Interface::Interface()
{
    cout<<"SerialReceiverConsole\n"<<endl;
    cout<<"Chose connection parameters\n"<<endl;
}

void Interface::clearscreen(){
    printf("\033[2J");
    printf("\033[0;0f");
}

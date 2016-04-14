#include <iostream>
#include "../include/serial.h"
#include "../include/rs232.h"

using namespace std;


const string Element::getstring(){ 
	
	return current->first;
}

int Element::getint(){
	
	return current->second;
}

int Status::set(const string input){

    current = value.find(input);
    if(current == value.end())return 1;

    return 0;
}


int Parity::set(const string input){

    current = value.find(input);
    if(current == value.end())return 1;

    return 0;
}

void Parity::showoptions(){

    for(current =value.begin(); current!=value.end(); ++current){

        cout<<current->first<<": "<<current->second<<endl;
    }
    cout<<endl;
}

int BaudRate::set(const string input){

    current = value.find(input);
    if(current == value.end())return 1;

    return 0;

}

void BaudRate::showoptions(){

    for(current =value.begin(); current!=value.end(); ++current){

        cout<<current->first<<": "<<current->second<<endl;
    }
    cout<<endl;
}

int StopBits::set(const string input){
	
	 current = value.find(input);
     if(current == value.end())return 1;

     return 0;
}

void StopBits::showoptions(){

    for(current =value.begin(); current!=value.end(); ++current){

        cout<<current->first<<": "<<current->second<<endl;
    }
    cout<<endl;
}

int SerialError::set(const string input){

  current = value.find(input);

  return 0;

}

int DataBits::set(const string input){
	
	current = value.find(input);
    if(current == value.end())return 1;

    return 0;
}

void DataBits::showoptions(){

    for(current =value.begin(); current!=value.end(); ++current){

        cout<<current->first<<": "<<current->second<<endl;
    }
    cout<<endl;
}

int FlowControl::set(const string input){
    
    current = value.find(input);
    if(current == value.end())return 1;

    return 0;
}

void FlowControl::showoptions(){

    for(current =value.begin(); current!=value.end(); ++current){

        cout<<current->first<<": "<<current->second<<endl;
    }
    cout<<endl;
}

int PortName::set(const string input){
    
    current = value.find(input);
    if(current == value.end())return 1;

    return 0;
}

void PortName::showoptions(){

    for(current =value.begin(); current!=value.end(); ++current){

        cout<<current->first<<": "<<current->second<<endl;
    }
    cout<<endl;
}

Buffer::Buffer(int nofbytes, char ter){

    size = nofbytes;
    data = new unsigned char[nofbytes];
    terminator = ter;
}

Buffer::~Buffer(){

    free(data);
}

unsigned char* Buffer::fill(){

    return data;
}

void Buffer::flush(){

    data[0] = 0;// to change
}

void Buffer::show(){

    cout<<data[0]<<endl; // temp vector
}



SerialPort::SerialPort(const string baud, const string par, const string stop, const string data, const string port, const string flow){
	
    baudrate.set(baud);
    parity.set(par);
    stopbits.set(stop);
    databits.set(data);
    portname.set(port);
    flowcontrol.set(flow);

}

SerialPort::~SerialPort(){

    this->disconnect();
}

Status SerialPort::connect(){ //functions from rs232.c

    if(RS232_OpenComport(portname.getint(), baudrate.getint(), databits.getint(), parity.getint(), stopbits.getint(), flowcontrol.getint())){

        printf("Can not open comport\n");

        status.set("Error");
    }

    return status;
}

Status SerialPort::disconnect(){

    RS232_CloseComport(portname.getint());

    return status;
}

int SerialPort::receive(unsigned char * buffer){

    int n = RS232_PollComport(portname.getint(),buffer, 4095);

    return n;
}


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

void Status::set(const string input){

    current = value.find(input);
    if(current == value.end()){
       SerialError error;
       error.set("InvalidStatus");
       throw error;
    }
}


void Parity::set(const string input){

    current = value.find(input);
    if(current == value.end()){
        SerialError error;
        error.set("InvalidParity");
        throw error;
    }

}

void Parity::showoptions(){

    for(current =value.begin(); current!=value.end(); ++current){

        cout<<current->first<<": "<<current->second<<endl;
    }
    cout<<endl;
}

void BaudRate::set(const string input){

    current = value.find(input);
    if(current == value.end()){
        SerialError error;
        error.set("InvalidBaudRate");
        throw error;
    }

}

void BaudRate::showoptions(){

    for(current =value.begin(); current!=value.end(); ++current){

        cout<<current->first<<": "<<current->second<<endl;
    }
    cout<<endl;
}

void StopBits::set(const string input){
	
	 current = value.find(input);
	 if(current == value.end()){
		SerialError error;
		error.set("InvalidStopBits");
		throw error;
    }
}

void StopBits::showoptions(){

    for(current =value.begin(); current!=value.end(); ++current){

        cout<<current->first<<": "<<current->second<<endl;
    }
    cout<<endl;
}

void SerialError::set(const string input){

  current = value.find(input);

}

void DataBits::set(const string input){
	
	current = value.find(input);
    if(current == value.end()){
        SerialError error;
        error.set("InvalidDataBits");
        throw error;
    }
}

void DataBits::showoptions(){

    for(current =value.begin(); current!=value.end(); ++current){

        cout<<current->first<<": "<<current->second<<endl;
    }
    cout<<endl;
}

void FlowControl::set(const string input){
    
    current = value.find(input);
    if(current == value.end()){
        SerialError error;
        error.set("InvalidFlowControl");
        throw error;
    }
}

void FlowControl::showoptions(){

    for(current =value.begin(); current!=value.end(); ++current){

        cout<<current->first<<": "<<current->second<<endl;
    }
    cout<<endl;
}

void PortName::set(const string input){
    
    current = value.find(input);
    if(current == value.end()){
        SerialError error;
        error.set("InvalidPortName");
        throw error;
    }
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


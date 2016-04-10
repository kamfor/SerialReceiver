#include <iostream>
#include "../include/serial.h"

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

void BaudRate::set(const string input){

    current = value.find(input);
    if(current == value.end()){
        SerialError error;
        error.set("InvalidBaudRate");
        throw error;
    }

}

void StopBits::set(const string input){
	
	 current = value.find(input);
	 if(current == value.end()){
		SerialError error;
		error.set("InvalidStopBits");
		throw error;
    }
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

void FlowControl::set(const string input){
    
    current = value.find(input);
    if(current == value.end()){
        SerialError error;
        error.set("InvalidFlowControl");
        throw error;
    }
}

void PortName::set(const string input){
    
    current = value.find(input);
    if(current == value.end()){
        SerialError error;
        error.set("InvalidPortName");
        throw error;
    }
}

SerialPort::SerialPort(const string baud, const string par, const string stop, const string data, const string port, const string flow){
	
    baudrate.set(baud);
    parity.set(par);
    stopbits.set(stop);
    databits.set(data);
    portname.set(port);
    flowcontrol.set(flow);

    cout<<baudrate.getstring()<<endl;
    cout<<parity.getstring()<<endl;
    cout<<stopbits.getstring()<<endl;
    cout<<databits.getstring()<<endl;
    cout<<portname.getstring()<<endl;
    cout<<flowcontrol.getstring()<<endl;

}

SerialPort::~SerialPort(){
	this->disconnect();
}

Status SerialPort::connect(){

}

Status SerialPort::disconnect(){

}


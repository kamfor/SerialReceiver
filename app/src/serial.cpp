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

    //current = value.find(input);
    //if(current == value.end()){
     //   SerialError error;
     //   error.set("InvalidStatus");
     //   throw error;
    //}
    cout<<input<<endl;
}

void Parity::set(const string input){

    current = value.find(input);
    if(current == value.end()){
        SerialError error;
        error.set("InvalidParity");
        throw error;
    }

}

const string Parity::getstring(){

    return current->first;
}

int Parity::getint(){

    return current->second;

}

void BaudRate::set(const string input){

    current = value.find(input);
    if(current == value.end()){
        SerialError error;
        error.set("InvalidBaudRate");
        throw error;
    }

}

const string BaudRate::getstring(){

    return current->first;

}

int BaudRate::getint(){

    return current->second;
}

void StopBits::set(const string input){
	
	 current = value.find(input);
	 if(current == value.end()){
		SerialError error;
		error.set("InvalidStopBits");
		throw error;
    }
}

const string StopBits::getstring(){
	
	return current->first;
}

int StopBits::getint(){
	
	return current->second;
}

void SerialError::set(const string input){

  current = value.find(input);

}

const string SerialError::getstring(){

}

int SerialError::getint(){

}

void DataBits::set(const string input){
	
	current = value.find(input);
    if(current == value.end()){
        SerialError error;
        error.set("InvalidDataBits");
        throw error;
    }
}

const string DataBits::getstring(){

}

int DataBits::getint(){

}

void FlowControl::set(const string input){
    
    current = value.find(input);
    if(current == value.end()){
        SerialError error;
        error.set("InvalidFlowControl");
        throw error;
    }
}

const string FlowControl::getstring(){

}

int FlowControl::getint(){

}

void PortName::set(const string input){
    
    current = value.find(input);
    if(current == value.end()){
        SerialError error;
        error.set("InvalidPortName");
        throw error;
    }
}

const string PortName::getstring(){

}

int PortName::getint(){

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

Status SerialPort::connect(){

}

Status SerialPort::disconnect(){

}


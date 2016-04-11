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

}

SerialPort::~SerialPort(){
    //this->disconnect();
}

Status SerialPort::connect(){ //functions from rs232.c

    int i, n,
        cport_nr=0,        /* /dev/ttyS0 (COM1 on windows) */
        bdrate=9600;       /* 9600 baud */

    unsigned char buf[4096];

    char mode[]={'8','N','1',0};

    if(RS232_OpenComport(cport_nr, bdrate, mode)){

        printf("Can not open comport\n");

        status.set("Connected");
    }

    while(1){

        n = RS232_PollComport(cport_nr, buf, 4095);

        if(n > 0)
        {
            buf[n] = 0;   /* always put a "null" at the end of a string! */

            for(i=0; i < n; i++){

                if(buf[i] < 32)  /* replace unreadable control-codes by dots */
                {

                    buf[i] = '.';

                }
            }

          printf("received %i bytes: %s\n", n, (char *)buf);

        }

        usleep(100000);

    }

    return status;

}

Status SerialPort::disconnect(){

    return status;
}


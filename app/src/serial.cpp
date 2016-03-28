#include <iostream>
#include "../include/serial.h"
using namespace std;

void Status::set(const string input){

    current = value.find(input);
    if(current == value.end()){
        SerialError error;
        error.set("InvalidStatus");
        throw error;
    }
}

const string Status::getstring(){

    cout<<current->first<<endl;

}

int Status::getint(){

}

void Parity::set(const string){

}

const string Parity::getstring(){

}

int Parity::getint(){

}

void BaudRate::set(const string){

}

const string BaudRate::getstring(){

}

int BaudRate::getint(){

}

void StopBits::set(const string){

}

const string StopBits::getstring(){

}

int StopBits::getint(){

}

void SerialError::set(const string input){

  current = value.find(input);

}

const string SerialError::getstring(){

}

int SerialError::getint(){

}

void DataBits::set(const string){

}

const string DataBits::getstring(){

}

int DataBits::getint(){

}

void FlowControl::set(const string){

}

const string FlowControl::getstring(){

}

int FlowControl::getint(){

}

void PortName::set(const string){

}

const string PortName::getstring(){

}

int PortName::getint(){

}


SerialPort::SerialPort(const string baudrate, const string parity, const string stopbits, const string databits, const string portname, const string flowcontrol){


}

SerialPort::~SerialPort(){
    this->disconnect();
}

Status SerialPort::connect(){

}

Status SerialPort::disconnect(){

}


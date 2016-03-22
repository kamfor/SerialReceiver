#include <iostream>
#include "../include/serial.h"
using namespace std;

Status::value Status::get(){
    return v;
}

void Status::set(value status){
    v = status;
}

Parity::value Parity::get(){
    return v;
}

void Parity::set(value parity){
    v = parity;
}

BaudRate::value BaudRate::get(){
    return v;
}

void StopBits::set(value stopbits){
    v = stopbits;
}

StopBits::value StopBits::get(){
    return v;
}

void BaudRate::set(value baudrate){
    v = baudrate;
}

SerialError::value SerialError::get(){
    return v;
}

void SerialError::set(value serialerror){
    v = serialerror;
}

DataBits::value DataBits::get(){
    return v;
}

void DataBits::set(value databits){
    v = databits;
}

FlowControl::value FlowControl::get(){
    return v;
}

void FlowControl::set(value flowcontrol){
    v = flowcontrol;
}

PortName::value PortName::get(){
    return v;
}

void PortName::set(value portname){
    v = portname;
}


SerialPort::SerialPort(BaudRate baudrate, Parity parity, StopBits stopbits, DataBits databits, PortName portname, FlowControl flowcontrol){

}

SerialPort::~SerialPort(){

}

Status SerialPort::connect(){

}

Status SerialPort::disconnect(){

}


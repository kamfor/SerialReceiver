#ifndef _SERIAL_H
#define _SERIAL_H

#include<iostream>
#include<unordered_map>
#include<string>
#include "rs232.h"
#include "buffer.h"

using namespace std;

class Element{

public:

    unordered_map<string, const int>::const_iterator current;
    const string getstring();
    int getint();
};

class Status : public Element{

private:

    const unordered_map<string,const int> value = {
        {"Connected", 0},
        {"Disconnected" , 1},
        {"Error", 2}
    };

public:

    void set(const string);
    void showoptions();
};

class Parity : public Element{

private:

    const unordered_map<string,const int> value = {
        {"NoParity", 0},
        {"EvenParity", 1},
        {"OddParity", 2},
        {"UnknownParity", 3}
    };


public:

    void set(const string);
    void showoptions();
};

class BaudRate : public Element{

private:

    const unordered_map<string,const int> value = {
        {"Baud1200", 1200},
        {"Baud1800", 1800},
        {"Baud2400", 2400},
        {"Baud4800", 4800},
        {"Baud9600", 9600},
        {"Baud19200", 19200},
        {"Baud38400", 38400},
        {"Baud57600", 57600},
        {"Baud115200", 115200},
        {"Baud230400", 230400},
        {"Baud460800", 460800},
        {"Baud500000", 500000},
        {"Baud576000", 576000},
        {"Baud921600", 921600},
        {"Baud1000000", 1000000},
        {"Baud1152000", 1152000},
        {"Baud1500000", 1500000},
        {"Baud2000000", 2000000},
        {"Baud2500000", 2500000},
        {"Baud3000000", 3000000},
        {"Baud3500000", 3500000},
        {"Baud4000000", 4000000}
    };

public:

    void set(const string);
    void showoptions();
};

class StopBits : public Element{

private:

    const unordered_map<string,const int> value = {
        {"OneStop", 0},
        {"TwoStop", 1},
        {"UnknownStop", 2}
    };

public:

    void set(const string);
    void showoptions();
};

class SerialError :public Element{

private:

    const unordered_map<string,const int> value = {
        {"NoError", 0},
        {"DeviceNotFound", 1},
        {"PermissionError", 2},
        {"OpenError", 3},
        {"IllegalPortNumber", 4},
        {"InvalidBaudrate", 5},
        {"InvalidMode", 6},
        {"InvalidDataBits", 7},
        {"InvalidParity", 8},
        {"InvalidStopBits", 9},
        {"UnableToGetPortStatus", 10},
        {"InvalidStatus", 11}
    };

public:

    void set(const string);
    void showoptions();
};

class DataBits : public Element{

private:

   const unordered_map<string,const int> value = {
        {"Data5", 5},
        {"Data6", 6},
        {"Data7", 7},
        {"Data8", 8},
        {"UnknownDataBits", 0}
    };

public:

    void set(const string);
    void showoptions();
};

class FlowControl : public Element{

private:

    const unordered_map<string,const int> value = {
        {"NoFlowControl", 0},
        {"HardwareControl", 1},
        {"SoftwareControl", 2},
        {"UnknownFlowControl", 3}
    };

public:

    void set(const string);
    void showoptions();
};

class PortName : public Element{

private:

    #if defined(__linux__) || defined(__FreeBSD__)
    const unordered_map<string,const int> value= {
        {"ttyS0", 0},
        {"ttyS1", 1},
        {"ttyS2", 2},
        {"ttyS3", 3},
        {"ttyS4", 4},
        {"ttyS5", 5},
        {"ttyS6", 6},
        {"ttyS7", 7},
        {"ttyS8", 8},
        {"ttyS9", 9},
        {"ttyS10", 10},
        {"ttyS11", 11},
        {"ttyS12", 12},
        {"ttyS13", 13},
        {"ttyS14", 14},
        {"ttyS15", 15},
        {"ttyUSB0", 16},
        {"ttyUSB1", 17},
        {"ttyUSB", 18},
        {"ttyUSB3", 20},
        {"ttyUSB4", 21},
        {"ttyUSB5", 22},
        {"ttyAMA0", 23},
        {"ttyAMA1", 24},
        {"ttyACM0", 25},
        {"ttyACM1", 26},
        {"rfcomm0", 27},
        {"rfcomm1", 28},
        {"ircomm0", 29},
        {"ircomm1", 30},
        {"cuau0", 31},
        {"cuau1", 32},
        {"cuau2", 33},
        {"cuau3", 34},
        {"cuaU0", 35},
        {"cuaU1", 36},
        {"cuaU2", 37},
        {"cuaU3", 38}
    };

    #else

    const unordered_map<string,const int> value= {,
        {"COM1", 39},
        {"COM2", 40},
        {"COM3", 41},
        {"COM4", 42},
        {"COM5", 43},
        {"COM6", 44},
        {"COM7", 45},
        {"COM8", 46},
        {"COM9", 47},
        {"COM10", 48},
        {"COM11", 49},
        {"COM12", 50},
        {"COM13", 51},
        {"COM14", 52}
    };

    #endif

public:

    void set(const string);
    void showoptions();
};

class Buffer{

private:

    unsigned char * data;
    char terminator;
    int size;

public:

    Buffer(int, char);
    ~Buffer();
    unsigned char* fill();
    void flush();
    void show();
};

class SerialPort{

public:

    Status status;
    Parity parity;
    BaudRate baudrate;
    StopBits stopbits;
    PortName portname;
    DataBits databits;
    FlowControl flowcontrol;

    SerialPort(const string, const string, const string, const string, const string, const string);
    ~SerialPort();
    Status connect();
    Status disconnect();
    int receive(unsigned char *);
};

#endif //_SERIAL_H

#ifndef _SERIAL_H
#define _SERIAL_H


#include "elements.h"
#include "buffer.h"

class Status : public Element{

private:

    enum value{
        Connected,
        Disconnected,
        Error
    }v;

};

class Parity : public Element{

private:

    enum value{
        NoParity,
        EvenParity,
        OddParity,
        SpaceParity,
        MarkParity,
        UnknownParity
    }v;
};

class BaudRate : public Element{

private:

    enum value{
        Baud1200 = 1200,
        Baud1800 = 1800,
        Baud2400 = 2400,
        Baud4800 = 4800,
        Baud9600 = 9600,
        Baud19200 = 19200,
        Baud38400 = 38400,
        Baud57600 = 57600,
        Baud115200 = 115200,
        Baud230400 = 230400,
        Baud460800 = 460800,
        Baud500000 = 500000,
        Baud576000 = 576000,
        Baud921600 = 921600,
        Baud1000000 = 1000000,
        Baud1152000 = 1152000,
        Baud1500000 = 1500000,
        Baud2000000 = 2000000,
        Baud2500000 = 2500000,
        Baud3000000 = 3000000,
        Baud3500000 = 3500000,
        Baud4000000 = 4000000
    }v;
};

class StopBits : public Element{

private:

    enum value{
        OneStop,
        OneAndHalfStop,
        TwoStop,
        UnknownStop
    }v;
};

class SerialError : public Element{

private:

    enum value{
        NoError,
        DeviceNotFound,
        PermissionError,
        OpenError,
        IllegalPortNumber,
        InvalidBaudrate,
        InvalidMode,
        InvalidDataBits,
        InvalidParity,
        InvalidStopBits,
        UnableToGetPortStatus
    }v;
};

class DataBits : public Element{

private:

    enum value{
        Data5,
        Data6,
        Data7,
        Data8,
        UnknownDataBits
    }v;
};

class FlowControl : public Element{

private:

    enum value{
        NoFlowControl,
        HardwareControl,
        SoftwareControl,
        UnknownFlowControl
    }v;
};

class PortName : public Element{

private:

    enum value{
        //linux
        ttyS0,
        ttyS1,
        ttyS2,
        ttyS3,
        ttyS4,
        ttyS5,
        ttyS6,
        ttyS7,
        ttyS8,
        ttyS9,
        ttyS10,
        ttyS11,
        ttyS12,
        ttyS13,
        ttyS14,
        ttyS15,
        ttyUSB0,
        ttyUSB1,
        ttyUSB,
        ttyUSB3,
        ttyUSB4,
        ttyUSB5,
        ttyAMA0,
        ttyAMA1,
        ttyACM0,
        ttyACM1,
        rfcomm0,
        rfcomm1,
        ircomm0,
        ircomm1,
        cuau0,
        cuau1,
        cuau2,
        cuau3,
        cuaU0,
        cuaU1,
        cuaU2,
        cuaU3
        //windows
        COM1,
        COM2,
        COM3,
        COM4,
        COM5,
        COM6,
        COM7,
        COM8,
        COM9,
        COM10,
        COM11,
        COM12,
        COM13,
        COM14
    }v;
};

class SerialPort{

private:

    Status status;
    Parity parity;
    BaudRate baudrate;
    StopBits stopbits;
    PortName portname;
    DataBits databits;
    //Buffer buffer;

public:

    SerialPort(BaudRate, Parity, StopBits, DataBits, PortName, FlowControl);
    ~SerialPort();
    Status connect();
    Status disconnect();
};

#endif //_SERIAL_H

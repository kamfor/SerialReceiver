#ifndef BUFFER_H
#define BUFFER_H

#include <iostream>
using namespace std;


class Buffer{

public:

    unsigned char * data;
    char terminator;
    int size;
    Buffer(int, char);
    ~Buffer();
    unsigned char* fill();
    void flush();
    string show(int);
};

#endif // BUFFER_H

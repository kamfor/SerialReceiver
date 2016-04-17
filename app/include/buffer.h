#ifndef BUFFER_H
#define BUFFER_H


class Buffer{

public:

    unsigned char * data;
    char terminator;
    int size;
    Buffer(int, char);
    ~Buffer();
    unsigned char* fill();
    void flush();
    void show(int);
};

#endif // BUFFER_H

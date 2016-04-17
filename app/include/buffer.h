#ifndef BUFFER_H
#define BUFFER_H


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

#endif // BUFFER_H

#include <iostream>
#include "./include/buffer.h"

using namespace std;

Buffer::Buffer(int nofbytes, char ter){

    size = nofbytes;
    data = new unsigned char[nofbytes];
    terminator = ter;
}

Buffer::~Buffer(){

    free(data);
}

unsigned char* Buffer::fill(){

    return data;
}

void Buffer::flush(){

    data[0] = 0;// to change
}

void Buffer::show(){

    for(unsigned int i=0; i<sizeof(data); i++){
      cout<<data[i]<<endl; // temp vector
    }

}

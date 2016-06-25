#ifndef READTHREAD_H
#define READTHREAD_H


class readThread : public QThread
{
public:
    readThread();
    void run();
};


#endif // READTHREAD_H

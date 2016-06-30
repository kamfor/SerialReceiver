#include "../include/readthread.h"
#include <QtCore>

ReadThread::ReadThread(QObject *parent) :
    QThread(parent)
{
    this->start();

}

void ReadThread::run(){
    //put data to console here

    emit DataReceived();
}

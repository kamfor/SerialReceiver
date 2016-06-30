#ifndef READTHREAD_H
#define READTHREAD_H

#include <QObject>

class ReadThread : public QThread
{
        Q_OBJECT
public:
    explicit ReadThread(QObject *parent =0);
    void run();
    bool Stop;

signals:
    void DataReceived();


public slots:
};

#endif // READTHREAD_H

#ifndef THREADCPU_H
#define THREADCPU_H

#include <QThread>
#include "cpuNode.h"
#include "memory.h"

class ThreadCPU : public QThread
{
    Q_OBJECT
public:
    explicit ThreadCPU(QObject *parent = nullptr);
    CPUNode *cpu;
    Memory *memory;
    BusCache *busCache;
    BusRAM busRam;

signals:
    void output(string,string);
protected:
    void run();
};
//Hacer el bus un puntero de una variable que se llame busDatos y otra busSnoop

#endif // THREADCPU_H
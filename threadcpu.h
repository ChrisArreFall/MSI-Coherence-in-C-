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
    //Bus de la ram es especifico para cada procesador
    BusRAM busRam;
    bool *state;
    QMutex *mutex;
//If i want to access memory or cache bus and someone else has the access, then i stall the instruction until i have access
signals:
    void output(string,string);
protected:
    void run();
};
//Hacer el bus un puntero de una variable que se llame busDatos y otra busSnoop

#endif // THREADCPU_H

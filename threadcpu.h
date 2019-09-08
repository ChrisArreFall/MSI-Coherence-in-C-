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
    bool state;
    QMutex *mutex;

    int mean, variance;
    bool *clk;
signals:
   void signalGUI(QString);

public slots:
    void setMean(const int &value);
    void setVar(const int &value);
    void setState();
protected:
    void run();
};

#endif // THREADCPU_H

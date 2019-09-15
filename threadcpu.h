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
    BusCacheMessage *busCache;
    //Bus de la ram es especifico para cada procesador
    BusRAM busRam;
    bool state;
    QMutex *mutex;



    int mean, variance;
    bool clk;

    void accessMemory();
    void executeInstruction(int iter,string type, string data, string tag);
signals:
   void signalGUI(QString);
   void signalWriteToBus(BusCacheMessage);

public slots:
    //Slot para recibir la media desde el GUI
    void setMean(const int &value);
    //Slot para recibir la varianza desde el GUI
    void setVar(const int &value);
    void setState();
    //Slot para recibir el CLK desde el thread CLK
    void setCLK(bool clk);
    //Slot para recibir notificacion de cambio en el bus de cache
    void hearBusCache(BusCacheMessage message);
protected:
    void run();
};

#endif // THREADCPU_H

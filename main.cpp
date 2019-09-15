#include "mainwindow.h"
#include <QApplication>

#include "cpuNode.h"
#include "memory.h"
#include <thread>
#include <list>
#include <algorithm>
#include <mutex>
#include <chrono>
#include "threadclk.h"
#include "threadcpu.h"
#include "instruction.h"
#include "threadbuscache.h"
#include <iostream>
#include "cachecontroller.h"



int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    CPUNode cpu0,cpu1,cpu2,cpu3;
    Memory memory;
    //Bus de la cache es uno para todos los nodes

    ThreadCPU *threadCPU0,*threadCPU1,*threadCPU2,*threadCPU3;
    ThreadCLK *threadCLK;
    ThreadBusCache *threadBusCache;

    qRegisterMetaType<BusCacheMessage>("BusCacheMessage");

    QMutex mutex;

    //Init all processors
    cpu0.init(0);
    cpu1.init(1);
    cpu2.init(2);
    cpu3.init(3);
    //Init all threads
    threadCPU0 = new ThreadCPU();
    threadCPU1 = new ThreadCPU();
    threadCPU2 = new ThreadCPU();
    threadCPU3 = new ThreadCPU();
    threadCLK = new ThreadCLK();
    threadBusCache = new ThreadBusCache();
    //Assign a processor to each thread
    threadCPU0->cpu=&cpu0;
    threadCPU1->cpu=&cpu1;
    threadCPU2->cpu=&cpu2;
    threadCPU3->cpu=&cpu3;
    //Reference main memory to CPUs
    threadCPU0->memory=&memory;
    threadCPU1->memory=&memory;
    threadCPU2->memory=&memory;
    threadCPU3->memory=&memory;
    //Reference mutex
    threadCPU0->mutex=&mutex;
    threadCPU1->mutex=&mutex;
    threadCPU2->mutex=&mutex;
    threadCPU3->mutex=&mutex;
    threadCLK->mutex = &mutex;
    //processor mutex
    threadCPU0->mutex=&mutex;
    threadCPU1->mutex=&mutex;
    threadCPU2->mutex=&mutex;
    threadCPU3->mutex=&mutex;
    //start processors
    threadCLK->start();
    threadBusCache->start();
    threadCPU0->start();
    threadCPU1->start();
    threadCPU2->start();
    threadCPU3->start();

    QObject::connect(threadCPU0,SIGNAL(signalGUI(const QString&)),&w,SLOT(setText(const QString&)));
    QObject::connect(threadCPU1,SIGNAL(signalGUI(const QString&)),&w,SLOT(setText(const QString&)));
    QObject::connect(threadCPU2,SIGNAL(signalGUI(const QString&)),&w,SLOT(setText(const QString&)));
    QObject::connect(threadCPU3,SIGNAL(signalGUI(const QString&)),&w,SLOT(setText(const QString&)));

    QObject::connect(&w,SIGNAL(signalMean(const int&)),threadCPU0,SLOT(setMean(const int&)));
    QObject::connect(&w,SIGNAL(signalMean(const int&)),threadCPU1,SLOT(setMean(const int&)));
    QObject::connect(&w,SIGNAL(signalMean(const int&)),threadCPU2,SLOT(setMean(const int&)));
    QObject::connect(&w,SIGNAL(signalMean(const int&)),threadCPU3,SLOT(setMean(const int&)));

    QObject::connect(&w,SIGNAL(signalVar(const int&)),threadCPU0,SLOT(setVar(const int&)));
    QObject::connect(&w,SIGNAL(signalVar(const int&)),threadCPU1,SLOT(setVar(const int&)));
    QObject::connect(&w,SIGNAL(signalVar(const int&)),threadCPU2,SLOT(setVar(const int&)));
    QObject::connect(&w,SIGNAL(signalVar(const int&)),threadCPU3,SLOT(setVar(const int&)));

    QObject::connect(threadCLK,SIGNAL(signalCLK(bool)),threadCPU0,SLOT(setCLK(bool)));
    QObject::connect(threadCLK,SIGNAL(signalCLK(bool)),threadCPU1,SLOT(setCLK(bool)));
    QObject::connect(threadCLK,SIGNAL(signalCLK(bool)),threadCPU2,SLOT(setCLK(bool)));
    QObject::connect(threadCLK,SIGNAL(signalCLK(bool)),threadCPU3,SLOT(setCLK(bool)));

    QObject::connect(&w,SIGNAL(setState()),threadCLK,SLOT(setState()));

    QObject::connect(threadCPU0,SIGNAL(signalWriteToBus(BusCacheMessage)),threadBusCache,SLOT(setBusCacheChange(BusCacheMessage)));
    QObject::connect(threadCPU1,SIGNAL(signalWriteToBus(BusCacheMessage)),threadBusCache,SLOT(setBusCacheChange(BusCacheMessage)));
    QObject::connect(threadCPU2,SIGNAL(signalWriteToBus(BusCacheMessage)),threadBusCache,SLOT(setBusCacheChange(BusCacheMessage)));
    QObject::connect(threadCPU3,SIGNAL(signalWriteToBus(BusCacheMessage)),threadBusCache,SLOT(setBusCacheChange(BusCacheMessage)));

    QObject::connect(threadBusCache,SIGNAL(signalBusCacheChange(BusCacheMessage)),threadCPU0,SLOT(hearBusCache(BusCacheMessage)));
    QObject::connect(threadBusCache,SIGNAL(signalBusCacheChange(BusCacheMessage)),threadCPU1,SLOT(hearBusCache(BusCacheMessage)));
    QObject::connect(threadBusCache,SIGNAL(signalBusCacheChange(BusCacheMessage)),threadCPU2,SLOT(hearBusCache(BusCacheMessage)));
    QObject::connect(threadBusCache,SIGNAL(signalBusCacheChange(BusCacheMessage)),threadCPU3,SLOT(hearBusCache(BusCacheMessage)));

    return a.exec();

}

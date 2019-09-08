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
#include <iostream>



int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    CPUNode cpu0,cpu1,cpu2,cpu3;
    Memory memory;
    //Bus de la cache es uno para todos los nodes
    BusCache busCache;

    ThreadCPU *threadCPU0,*threadCPU1,*threadCPU2,*threadCPU3;
    ThreadCLK *threadCLK;


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
    //Reference cache bus to CPUs
    threadCPU0->busCache=&busCache;
    threadCPU1->busCache=&busCache;
    threadCPU2->busCache=&busCache;
    threadCPU3->busCache=&busCache;
    //processor mutex
    threadCPU0->mutex=&mutex;
    threadCPU1->mutex=&mutex;
    threadCPU2->mutex=&mutex;
    threadCPU3->mutex=&mutex;
    //processor clk
    threadCPU0->clk=&threadCLK->clk0;
    threadCPU1->clk=&threadCLK->clk1;
    threadCPU2->clk=&threadCLK->clk2;
    threadCPU3->clk=&threadCLK->clk3;
    //start processors
    threadCLK->start();
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

    QObject::connect(&w,SIGNAL(signalStatus()),threadCPU0,SLOT(setState()));
    QObject::connect(&w,SIGNAL(signalStatus()),threadCPU1,SLOT(setState()));
    QObject::connect(&w,SIGNAL(signalStatus()),threadCPU2,SLOT(setState()));
    QObject::connect(&w,SIGNAL(signalStatus()),threadCPU3,SLOT(setState()));

    return a.exec();

}

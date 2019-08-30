#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "cpuNode.h"
#include "memory.h"
#include <thread>
#include <list>
#include <algorithm>
#include <mutex>
#include <chrono>
#include "threadcpu.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Ui::MainWindow *ui;

private:
    CPUNode cpu0,cpu1,cpu2,cpu3;
    Memory memory;
    //Bus de la cache es uno para todos los nodes
    BusCache busCache;

    ThreadCPU *threadCPU0,*threadCPU1,*threadCPU2,*threadCPU3;
};

#endif // MAINWINDOW_H

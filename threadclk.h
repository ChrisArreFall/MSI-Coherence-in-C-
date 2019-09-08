#ifndef THREADCLK_H
#define THREADCLK_H

#include <QObject>
#include <iostream>
#include <QThread>

class ThreadCLK : public QThread
{
    Q_OBJECT
public:
    explicit ThreadCLK(QObject *parent = nullptr);
    ulong frequency;
    bool clk;
    bool clk0,clk1,clk2,clk3;
    QMutex *mutex;
protected:
    void run();
};

#endif // THREADCLK_H

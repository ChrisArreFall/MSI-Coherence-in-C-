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
    bool state = true;
    QMutex *mutex;
protected:
    void run();
signals:
   void signalCLK(bool);
public slots:
   void setState();

};

#endif // THREADCLK_H

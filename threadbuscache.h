#ifndef THREADBUSCACHE_H
#define THREADBUSCACHE_H

#include <QObject>
#include <QThread>
#include "cachecontroller.h"

class ThreadBusCache : public QThread
{
    Q_OBJECT
public:
    explicit ThreadBusCache(QObject *parent = nullptr);
    BusCacheMessage currentMessage;
protected:
    void run();

signals:
    void signalBusCacheChange(BusCacheMessage);
public slots:
    void setBusCacheChange(BusCacheMessage message);
};

#endif // THREADBUSCACHE_H

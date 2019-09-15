#include "threadbuscache.h"

ThreadBusCache::ThreadBusCache(QObject *parent) : QThread(parent)
{

}

void ThreadBusCache::run()
{

}

void ThreadBusCache::setBusCacheChange(BusCacheMessage message)
{
    cout << "RECIVED BUS SIGNAL!..." << endl;
    emit signalBusCacheChange(message);
}

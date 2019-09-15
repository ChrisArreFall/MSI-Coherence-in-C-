#ifndef CACHECONTROLLER_H
#define CACHECONTROLLER_H
#include "cache.h"
#include "instruction.h"
#include "memory.h"
#include <QMutex>
#include <unistd.h>
#include <QThread>


struct BusRAM
{
    BusRAM() : tag("XXXX"), data("000000"),action("null"), enabled(false){}
    string tag;
    string data;
    string action; //write, read
    bool enabled;
};

struct BusCacheMessage
{
    BusCacheMessage() : id(100), tag("XXXX"), status("null") {}
    int id;
    string tag;
    string status;
};

class CacheController
{
public:
    CacheController();

    string cacheWrite(string tag, int id);
    string cacheRead(string tag,int id);
    string hearCacheBus(BusCacheMessage busCacheMessage);
    Cache *getCache() const;
    void setCache(Cache *value);


    BusRAM *getBusRAM() const;
    void setBusRAM(BusRAM *value);

    string printCache();

    std::default_random_engine generator;

    QMutex *mutex;

    Memory *memory;

    BusCacheMessage busCacheMessage;

    bool sendMessage;

    void messageSent();

private:
    Cache *cache;

    BusRAM *busRAM;
};

#endif // CACHECONTROLLER_H

#ifndef CACHECONTROLLER_H
#define CACHECONTROLLER_H
#include "cache.h"
#include "instruction.h"
#include "memory.h"
#include <QMutex>


struct BusRAM
{
    BusRAM() : tag("XXXX"), data("000000"),action("null"), enabled(false){}
    string tag;
    string data;
    string action; //write, read
    bool enabled;
};

struct BusCache
{
    BusCache() : tag("XXXX"), status("null"), cpuId(-1) {}
    string tag;
    string status;
    int cpuId;
};

class CacheController
{
public:
    CacheController();

    string cacheWrite(string tag, string data);
    string cacheRead(string tag);
    string hearCacheBus(BusCache *busCache);
    Cache *getCache() const;
    void setCache(Cache *value);

    BusCache *getBusCache() const;
    void setBusCache(BusCache *value);

    BusRAM *getBusRAM() const;
    void setBusRAM(BusRAM *value);

    string printCache();

    std::default_random_engine generator;

    QMutex *mutex;

    Memory *memory;


private:
    Cache *cache;
    BusCache *busCache;
    BusRAM *busRAM;
};

#endif // CACHECONTROLLER_H

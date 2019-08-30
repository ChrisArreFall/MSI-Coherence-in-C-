#ifndef CACHECONTROLLER_H
#define CACHECONTROLLER_H
#include "cache.h"


struct BusRAM
{
    string tag;
    string action; //write, read
    string status;
    string data;
    bool enabled=false;
};

struct BusCache
{
    string tag;
    string status;
};

class CacheController
{
public:
    CacheController();

    void cacheWrite(string tag, string data);
    string cacheRead(string tag);
    void changeStatus(string tag,string status);
private:
    Cache *cache;
    BusCache *busCache;
    BusRAM *busRAM;
};

#endif // CACHECONTROLLER_H

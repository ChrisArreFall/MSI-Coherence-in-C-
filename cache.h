#ifndef CACHE_H
#define CACHE_H
#include <iostream>
#include <string>
#define CACHE_SIZE 8
using namespace std;
struct CacheBlock
{
   CacheBlock() : tag("XXXX"), data("00000"), state("invalid"){}
   string tag;     //identificador del bloque
   string data;    //datos del bloque
   string state;   //invalid, shared, modified
};
class Cache
{
public:
    Cache();
    int cpuId;

    CacheBlock memory[CACHE_SIZE];
private:

};

#endif // CACHE_H

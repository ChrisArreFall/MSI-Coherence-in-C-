#include "cache.h"

Cache::Cache()
{

}

CacheBlock Cache::getBlock(int pos)
{
    return memory[pos];
}

void Cache::setBlock(int pos,string tag, string data,string state)
{
    memory[pos].tag = tag;
    memory[pos].data = data;
    memory[pos].state = state;
}

string Cache::getStatusBlock(int pos)
{
    return memory[pos].state;
}

void Cache::setStatusBlock(int pos, string state)
{
    memory[pos].state = state;
}

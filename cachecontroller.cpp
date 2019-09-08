#include "cachecontroller.h"

CacheController::CacheController()
{
}

string CacheController::cacheWrite(string tag, string data)
{
    //Here we do care about the case where the tag is not in the cache
    //std::cout << "Started write..." << std::endl;
    //First we check if the tag is in our cache
    for(int i = 0;i<CACHE_SIZE;i++){
        //std::cout << "Comparing..." << this->cache->getBlock(i).tag << std::endl;
        if(this->cache->memory[i].tag==tag){
            //std::cout << "Found match..." << std::endl;
            if(this->cache->memory[i].state=="modified"){
                //std::cout << "Modified..." << std::endl;
                //If it is in the modified state, we can be sure no other processor has the tag in their cache
                //that means we dont have to tell any other processors and we dont have to do anything.
                return "foundModified";
            }
            else if (this->cache->memory[i].state=="invalid") {
                //std::cout << "Invalid..." << std::endl;
                //If the block is in the invalid state we change it to modified state and put a
                //write request in the cache bus to invalidate everyone else
                this->cache->memory[i].state="modified";
                this->cache->memory[i].data=data;
                //We also put a write request in the cache bus
                //we have to take in consideration that is another processor has the
                //data in an modified state then we have to first write back its data before we proceed.
                this->busCache->tag = tag;
                this->busCache->status = "write";
                this->busCache->cpuId = this->cache->cpuId;
                return "foundInvalid";
            }
            else if (this->cache->memory[i].state=="shared") {
                //std::cout << "Shared..." << std::endl;
                //If the block is in the shared state we change it to modified state and put a
                //write request in the cache bus to invalidate everyone else
                this->cache->memory[i].state="modified";
                this->cache->memory[i].data=data;
                //We also put a write request in the cache bus
                //we have to take in consideration that if another processor has the
                //data in an modified or shared state then we have to make sure they know.
                this->busCache->tag = tag;
                this->busCache->status = "write";
                this->busCache->cpuId = this->cache->cpuId;
                return "foundShared";
            }
        }
    }
    //If the block is not in the cache we have to put a
    //write request in the cache bus to invalidate everyone else
    //std::cout << "Not in cache..." << std::endl;
    this->busCache->tag = tag;
    this->busCache->status = "write";
    this->busCache->cpuId = this->cache->cpuId;


    //we put the tag in the cache in a random place
    int pos = rand()%8;
    std::cout << "Putting in cache in pos: "<< pos << std::endl;
    this->cache->memory[pos].state="modified";
    this->cache->memory[pos].data=data;
    this->cache->memory[pos].tag=tag;

    return "notFound";
}

string CacheController::cacheRead(string tag)
{
    for(int i = 0;i<CACHE_SIZE;i++){
        if(this->cache->memory[i].tag==tag){
            //If we want to do a local read in a shared or modified state we dont have to tell anyone
            if(this->cache->memory[i].state=="shared" || this->cache->memory[i].state=="modified"){
                //we get the data from cache
                return this->cache->memory[i].data;
            }
            //If we want to do a local read and the block is in the invalid state
            else if(this->cache->memory[i].state=="invalid"){
                //first we put a read request on the cache bus
                this->busCache->tag = tag;
                this->busCache->status = "read";
                this->busCache->cpuId = cache->cpuId;
                //then we fetch the data from the memory
                //we have to first make sure every other CPU knows
                this->busRAM->enabled = true;
                this->busRAM->tag = tag;
                this->busRAM->action = "read";
                this->cache->memory[i].state = "shared";
                return "foundInvalid";
            }
        }
    }
    //If we did no find it in cache, that means we
    //first put a read request on the cache bus
    this->busCache->tag = tag;
    this->busCache->status = "read";
    this->busCache->cpuId = cache->cpuId;
    //then we fetch the data from the memory
    //we have to first make sure every other CPU knows
    this->busRAM->enabled = true;
    this->busRAM->tag = tag;
    this->busRAM->action = "read";
    //we put the tag in the cache in a random place
    std::normal_distribution<double> distributionTag(8,8);
    int pos = (int)abs(distributionTag(generator));
    while(pos>=8){
        pos = (int)abs(distributionTag(generator));
        std::cout << "Stuck here!" << std::endl;
    }
    if(cache->memory[pos].state=="modified"){
        //Emergency case
        this->memory->writeBlock(cache->memory[pos].tag,cache->memory[pos].data);
        std::cout << "Pos in modified state! : "<<pos << std::endl;
    }
    this->cache->memory[pos].tag = tag;
    this->cache->memory[pos].state = "shared";

    return "notFound";
}

string CacheController::hearCacheBus(BusCache *busCache)
{
    //Here we dont care about the case where the tag is not in the cache because
    //if its not in our cache it means we dont need it or we havent used it.

    //We still have to solve the problem that is nobody writes to cache we have to disable the cache bus after everybody read it

    //If in the cache bus, we hear that another cpuNode put a write in the bus
    //then we have to see if we have that tag in our cache
    if(busCache->status=="write" && busCache->cpuId!=this->cache->cpuId){
        for(int i = 0;i<CACHE_SIZE;i++){
            //if we do have that tag in our cache
            if(this->cache->memory[i].tag==busCache->tag){
                //and if we have the block in the modified state
                if(this->cache->memory[i].state=="modified"){
                    //we put the block in the invalid state
                    this->cache->memory[i].state="invalid";
                    //and we write to memory because its the most recent value of the data
                    this->busRAM->tag=this->cache->memory[i].tag;
                    this->busRAM->data=this->cache->memory[i].data;
                    this->busRAM->action="write";
                    this->busRAM->enabled = true;
                    //we have to access the memory and let it know to write that data
                    return "There was a WB, we had that tag in our cache, it was in modified state.";
                }
                else if (this->cache->memory[i].state=="shared") {
                    //we put the block in the invalid state and thats it
                    this->cache->memory[i].state="invalid";
                    return "There was a WB, we had that tag in our cache, it was in shared state.";
                }
                else if (this->cache->memory[i].state=="invalid") {
                    //If we are in the invalid state we dont do anything we just stay in
                    //the invalid state
                    return "There was a WB, we had that tag in our cache, it was in invalid state.";
                }

            }
        }
        return "There was a WB, we did not have the tag in our cache.";
    }
    else if(busCache->status=="read" && busCache->cpuId!=this->cache->cpuId){
        for(int i = 0;i<CACHE_SIZE;i++){
            //if we do have that tag in our cache
            if(this->cache->memory[i].tag==busCache->tag){
                //and if we have the block in the modified state
                if(this->cache->memory[i].state=="modified"){
                    //we put the block in the shared state
                    this->cache->memory[i].state="shared";
                    //and we write to memory because its the most recent value of the data
                    this->busRAM->tag=this->cache->memory[i].tag;
                    this->busRAM->data=this->cache->memory[i].data;
                    this->busRAM->action="read";
                    this->busRAM->enabled = true;
                    //we have to access the memory and let it know to write that data
                    return "There was a READ, we had that tag in our cache, it was in modified state.";
                }
                else if (this->cache->memory[i].state=="shared") {
                    //we do nothing
                    return "There was a READ, we had that tag in our cache, it was in shared state.";
                }
                else if (this->cache->memory[i].state=="invalid") {
                    //If we are in the invalid state we dont do anything we just stay in
                    //the invalid state
                    return "There was a READ, we had that tag in our cache, it was in invalid state.";
                }
            }
        }
        return "There was a READ, we did not have the tag in our cache.";
    }
    else {
        return "It was me!.";
    }
}

Cache *CacheController::getCache() const
{
    return cache;
}

void CacheController::setCache(Cache *value)
{
    cache = value;
}

BusCache *CacheController::getBusCache() const
{
    return busCache;
}

void CacheController::setBusCache(BusCache *value)
{
    busCache = value;
}

BusRAM *CacheController::getBusRAM() const
{
    return busRAM;
}

void CacheController::setBusRAM(BusRAM *value)
{
    busRAM = value;
}

string CacheController::printCache()
{
    string output;
    for(int i = 0;i<CACHE_SIZE;i++){
        output.append("Tag: "+ this->cache->memory[i].tag + ", Data: " + this->cache->memory[i].data + ", State: " + this->cache->memory[i].state + "\n");
    }
    return output;
}

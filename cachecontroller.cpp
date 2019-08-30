#include "cachecontroller.h"

CacheController::CacheController()
{

}

void CacheController::cacheWrite(string tag, string data)
{
    for(int i = 0;i<CACHE_SIZE;i++){
        if(this->cache->getBlock(i).tag==tag){
            if(this->cache->getBlock(i).state=="modified"){
                //If it is in the modified state, we can be sure no other processor has the tag in their catch
                //that means we dont have to tell any other processors
                this->cacheWrite(tag,data);
            }
            else if (this->cache->getBlock(i).state=="invalid") {
                //If the block is in the invalid state we have to get the data from the main memory
                //and put the blck in the modified state
                this->busRAM->tag = tag;
                this->busRAM->action = "write";
                this->busRAM->status = "modified";
                //We also put a write request in the cache bus
                //we have to take in consideration that is another processor has the
                //data in an modified state then we have to first write back its data before we proceed.
                this->busCache->tag = tag;
                this->busCache->status = "write";
            }
        }
    }
}

string CacheController::cacheRead(string tag)
{
    for(int i = 0;i<CACHE_SIZE;i++){
        if(this->cache->getBlock(i).tag==tag){
            //If we want to do a local read in a shared or modified state we dont have to tell anyone
            if(this->cache->getBlock(i).state=="shared" || this->cache->getBlock(i).state=="modified"){
                //
                return this->cache->getBlock(i).data;
            }
            //If we want to do a local read and the block is in the invalid state
            //
            else if(this->cache->getBlock(i).state=="invalid"){
                //first we put a read request on the cache bus
                this->busCache->tag = tag;
                this->busCache->status = "write";
                //then we fetch the data from the memory
                //we have to first make sure every other CPU knows
                this->busRAM->enabled = true;
                this->busRAM->tag = tag;
                this->busRAM->action = "read";
                this->busRAM->status = "shared";
                return "foundInvalid";
            }
        }
    }
    this->busRAM->tag = tag;
    this->busRAM->status = "shared";
    return "notFound";
}

void CacheController::changeStatus(string tag, string status)
{
    for(int i = 0;i<CACHE_SIZE;i++){
        if(this->cache->getBlock(i).tag==tag){
            //If another processor snoops a write in the bus then we have to put the
            //block in the invalid state
            //we also have to do a write back because we have the most recent data
            //so we have to first write the data and then let the other processor write
            if(status=="write"){
                cache->getBlock(i).state="invalid";
                this->busRAM->tag = tag;
                this->busRAM->status = "invalid";
            }

            else if(status=="read"){
                cache->getBlock(i).state="shared";
                this->busRAM->tag = tag;
                this->busRAM->status = "shared";
            }
        }
    }
}

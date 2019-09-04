#include "threadcpu.h"

ThreadCPU::ThreadCPU(QObject *parent) : QThread(parent)
{
}

void ThreadCPU::run()
{
    cpu->setBusCache(busCache);
    cpu->setBusRAM(&busRam);
    int i = 5;
    while(i!=0){
        i--;
        //First we hear the cache Bus in case we need to access memory
        mutex->lock();
        std::cout << "CPUID: " << cpu->getId() << ", Iteration: "<<i<< std::endl;
        if(this->busCache->status!="null"){
            string hearCacheBusOutput = this->cpu->getCacheController().hearCacheBus(this->busCache);
            std::cout << "hearCacheBus Output: " << hearCacheBusOutput << std::endl;
        }
        mutex->unlock();


        //Then, in case we do need to access memory, we read or write what we need to do from memory
        if(this->busRam.enabled==true){
            //if we need to write, we proceed to do that
            if(busRam.action=="write"){
                mutex->lock();
                this->memory->getBlock(busRam.tag)=busRam.data;
                mutex->unlock();
            }
            //if we need to read, we proceed to do that
            else if (busRam.action=="read") {
                //we look for that tag in our cache and rewrite the data with one in memory
                for(int i =0; i<CACHE_SIZE;i++){
                    if(this->cpu->getCache().memory[i].tag==busRam.tag){
                        mutex->lock();
                        this->cpu->getCache().memory[i].data=memory->getBlock(busRam.tag);
                        mutex->unlock();
                    }
                }
            }
            this->busRam.enabled=false;
        }


        //finally we process our next instruction
        int id = this->cpu->getId();

        string type = cpu->getCurrentInstruction().getType();
        string data = cpu->getCurrentInstruction().getData();
        string tag = cpu->getCurrentInstruction().getAddress();



        string outputInstruction = "";

        if(type=="write"){
            mutex->lock();
            outputInstruction=cpu->write(data,tag);
            mutex->unlock();
            msleep(1000);
        }


        else if(type=="read"){
            mutex->lock();
            outputInstruction=cpu->read(tag);
            mutex->lock();
            msleep(1000);
        }
        else{
            cpu->process();
            msleep(2000);
        }

        string outputCPU = "pid:"+to_string(id)+", type:"+type+"\n";
        string outputCache = this->cpu->getCacheController().printCache();


        mutex->lock();
        std::cout << "CPU output: \n" << outputCPU << "Cache output: \n" << outputCache << std::endl;
        mutex->unlock();
        //emit output(outputCPU,outputCache);

    }
}



#include "threadcpu.h"

ThreadCPU::ThreadCPU(QObject *parent) : QThread(parent)
{

}

void ThreadCPU::run()
{

    for(int i = 0; i < 100;i++){
        if(cpu->cacheController.busRAM->enabled==true){

        }
        int id = this->cpu->getId();
        string type = cpu->getCurrentInstruction().getType();
        string data = cpu->getCurrentInstruction().getData();
        string tag = cpu->getCurrentInstruction().getAddress();
        if(type=="write"){
            cpu->write(data,tag);
        }
        else if(type=="read"){
            cpu->read(tag);
        }
        else{
            cpu->process();
        }
        string outputCPU = "pid:"+to_string(id)+", type:"+type;
        string outputCache;
        for(int i = 0;i<CACHE_SIZE;i++){
            outputCache.append("tag:"+ cpu->getCache().getBlock(i).tag + ", data:" + cpu->getCache().getBlock(i).data + ", State:" + cpu->getCache().getBlock(i).state);
        }
        emit output(outputCPU,outputCache);
        msleep(1000);
    }
}

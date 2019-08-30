#include "cpuNode.h"

CPUNode::CPUNode()
{
    this->id = 100;
}

int CPUNode::getId() const
{
    return id;
}

void CPUNode::init(int id)
{
    this->id=id;

}
//--------------Seccion Instrucciones----------------
void CPUNode::write(string data, string tag)
{
    //if(this->cache.getBlock(address))
}
string CPUNode::read(string tag)
{
    if(cacheController.cacheRead(tag)=="foundInvalid"){

    }
    else{
        return cacheController.cacheRead(tag);
    }
}
void CPUNode::process()
{
}

//------------------Seccion Cache--------------------
Cache CPUNode::getCache() const
{
    return cache;
}

void CPUNode::setCache(const Cache &value)
{
    cache = value;
}
//--------------Seccion Manejo bus RAM----------------
BusRAM CPUNode::getBusRAM() const
{
    return *busRAM;
}

void CPUNode::setBusRAM(BusRAM *value)
{
    this->busRAM = value;
}
//--------------Seccion Manejo bus Cache----------------
BusCache CPUNode::getBusCache() const
{
    return *busCache;
}

void CPUNode::setBusCache(const string &value)
{
    busCache = value;
}

Instruction CPUNode::getCurrentInstruction()
{
    return this->instruction;
}



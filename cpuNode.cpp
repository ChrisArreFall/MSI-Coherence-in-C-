#include "cpuNode.h"

CPUNode::CPUNode()
{
    this->id = 100;
    cacheController.setCache(&cache);
    cacheController.setBusRAM(busRAM);
    cacheController.setBusCache(busCache);
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
string CPUNode::write(string data, string tag)
{
    std::cout << "Write Data: "<< data <<",Tag: "<<tag  << std::endl;
    string result = cacheController.cacheWrite(tag,data);
    std::cout << "Result: " << result << std::endl;
    if(result=="foundInvalid" || result=="notFound"){
        return "Miss";
    }
    else{
        return "Hit";
    }
}
string CPUNode::read(string tag)
{
    if(cacheController.cacheRead(tag)=="foundInvalid" || cacheController.cacheRead(tag)=="notFound"){
        return "Miss";
    }
    else{
        return "Hit";
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
    cacheController.setBusRAM(busRAM);
}
//--------------Seccion Manejo bus Cache----------------
BusCache CPUNode::getBusCache() const
{
    return *busCache;
}

void CPUNode::setBusCache(BusCache *value)
{
    this->busCache = value;
    cacheController.setBusCache(busCache);
}





#include "cpuNode.h"

CPUNode::CPUNode()
{
    this->id = 100;
    cacheController.setCache(&cache);
    cacheController.setBusRAM(busRAM);
    //cacheController.setBusCacheMessage(busCacheMessage);
}

int CPUNode::getId() const
{
    return id;
}

void CPUNode::init(int id)
{
    this->id=id;
    this->cache.cpuId=id;

}
//--------------Seccion Instrucciones----------------
string CPUNode::write(int data, string tag)
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
string CPUNode::read(int data,string tag)
{
    string status = cacheController.cacheRead(tag,data);
    cout <<"STATUS: "<< status << endl;
    if(status=="foundInvalid" || status=="notFound"){
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




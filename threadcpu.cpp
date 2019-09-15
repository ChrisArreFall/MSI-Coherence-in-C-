#include "threadcpu.h"

ThreadCPU::ThreadCPU(QObject *parent) : QThread(parent)
{
    mean = 50;
    variance = 100;
    state = true;
}

void ThreadCPU::accessMemory(){
    if(this->busRam.enabled==true){
        //if we need to write, we proceed to do that
        if(busRam.action=="write"){
            this->memory->writeBlock(busRam.tag,busRam.data);
            //std::cout << "Writting to memory..." << std::endl;
        }
        //if we need to read, we proceed to do that
        else if (busRam.action=="read") {
            //we look for that tag in our cache and rewrite the data with one in memory
            for(int i =0; i<CACHE_SIZE;i++){
                std::cout << "Reading from memory..." << std::endl;
                if(this->cpu->getCache().memory[i].tag==busRam.tag){
                    this->cpu->cache.memory[i].data=memory->getData(busRam.tag);
                    std::cout << "Obtained data: "<< memory->getData(busRam.tag)<< std::endl;
                }
            }
        }
        this->busRam.enabled=false;
    }
}

void ThreadCPU::executeInstruction(int iter,string type, string data, string tag){
    //finally we process our next instruction
    // instance of class std::normal_distribution with specific mean and stddev
    string outputInstruction = "";
    string stat = "";
    string outputCPU = "";
    int id = this->cpu->id;
    if(type=="write"){
        stat=outputInstruction=cpu->write(id,tag);
        outputCPU =  to_string(id) + "1" + to_string(iter)+ " T:" + type + ", Data: " + data + ", Tag: " + tag + " S: " + stat + "\n";
        //msleep(2000);
    }


    else if(type=="read"){
        stat=outputInstruction=cpu->read(id,tag);
        outputCPU =  to_string(id) + "1" + to_string(iter)+ " T:" + type +", " + tag + " S: " + stat + "\n";
        //msleep(2000);
    }
    else{
        cpu->process();
        outputCPU =  to_string(id) + "1" + to_string(iter)+ " T:" + type + "\n";
        //msleep(3000);
    }

    string outputCache = to_string(id)+"0"+this->cpu->cacheController.printCache();

    emit signalGUI(QString::fromStdString(outputCPU));
    string outputMEM = this->memory->printMemory();
    //std::cout <<"Cache output: \n" << outputCache<< "Mem output: \n"<<outputMEM << std::endl;
    emit signalGUI(QString::fromStdString(outputCache));
    emit signalGUI(QString::fromStdString(memory->printMemory()));


}

void ThreadCPU::run()
{
    cpu->setBusRAM(&busRam);
    cpu->mutex = this->mutex;
    cpu->cacheController.mutex = this->mutex;
    cpu->cacheController.memory = this->memory;
    Instruction *instruction = new Instruction();
    int id = this->cpu->getId();

    std::random_device rd;

    std::default_random_engine gen(rd());

    int iter = 0;
    while(1){
        if(clk){
            mutex->lock();
            cout  << " ---------------------- "<< id<<" ------------------------"<< endl;
            accessMemory();
            std::normal_distribution<double> d(mean, variance);
            int randValue = (int)d(gen)%100;
            std::normal_distribution<double> d2(8, 8);
            int randTag = (int)d2(gen)%16;
            instruction->generateType(randValue,abs(randTag));
            string type = instruction->getType();
            string data = to_string(id);
            string tag = instruction->getAddress();
            executeInstruction(iter,type,data,tag);
            if(cpu->cacheController.sendMessage){
                cpu->cacheController.messageSent();
                cpu->cacheController.busCacheMessage.id = id;
                cout << "Change in cache bus: " << cpu->cacheController.busCacheMessage.tag <<", " << cpu->cacheController.busCacheMessage.status << endl;
                emit signalWriteToBus(cpu->cacheController.busCacheMessage);
            }
            cout  << " -------------------------------------------------"<< endl;
            mutex->unlock();
            iter++;
            clk=false;
        }
    }
}
// direccion modulo 8

void ThreadCPU::setMean(const int &value){
    mean = value;
}
void ThreadCPU::setVar(const int &value){
    variance = value;
}
void ThreadCPU::setState(){
    this->state = !this->state;

}
void ThreadCPU::setCLK(bool clk){
    this->clk = clk;
}



void ThreadCPU::hearBusCache(BusCacheMessage message)
{
    if(message.id!=this->cpu->id){
        string hearCacheBusOutput = this->cpu->cacheController.hearCacheBus(message);
        std::cout << "hearCacheBus Output: " << hearCacheBusOutput << std::endl;
        string outputCache = to_string(this->cpu->id)+"0"+this->cpu->cacheController.printCache();
        emit signalGUI(QString::fromStdString(outputCache));
        emit signalGUI(QString::fromStdString(memory->printMemory()));
    }
    else{
        std::cout << "It was my own message..." << std::endl;
    }


}






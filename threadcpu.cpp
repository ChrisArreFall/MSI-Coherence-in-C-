#include "threadcpu.h"

ThreadCPU::ThreadCPU(QObject *parent) : QThread(parent)
{
    mean = 50;
    variance = 100;
    state = true;
}

void ThreadCPU::run()
{
    cpu->setBusCache(busCache);
    cpu->setBusRAM(&busRam);
    cpu->mutex = this->mutex;
    cpu->cacheController.mutex = this->mutex;
    cpu->cacheController.memory = this->memory;
    Instruction *instruction = new Instruction();
    int id = this->cpu->getId();

    // random device class instance, source of 'true' randomness for initializing random seed
    std::random_device rd;

    // Mersenne twister PRNG, initialized with seed from previous random device instance
    std::default_random_engine gen(rd());



    int iter = 0;
    while(true){
        while(state){
            mutex->lock();
            if(*this->clk){
                *this->clk = false;
                mutex->unlock();





                //First we hear the cache Bus in case we need to access memory
                mutex->lock();
                if(this->busCache->status!="null"){
                    string hearCacheBusOutput = this->cpu->cacheController.hearCacheBus(this->busCache);
                    std::cout << "hearCacheBus Output: " << hearCacheBusOutput << std::endl;
                }
                mutex->unlock();


                //Then, in case we do need to access memory, we read or write what we need to do from memory
                if(this->busRam.enabled==true){
                    //if we need to write, we proceed to do that
                    if(busRam.action=="write"){
                        mutex->lock();
                        this->memory->writeBlock(busRam.tag,busRam.data);
                        mutex->unlock();
                        std::cout << "Writting to memory..." << std::endl;
                    }
                    //if we need to read, we proceed to do that
                    else if (busRam.action=="read") {
                        //we look for that tag in our cache and rewrite the data with one in memory
                        for(int i =0; i<CACHE_SIZE;i++){
                            if(this->cpu->getCache().memory[i].tag==busRam.tag){
                                mutex->lock();
                                this->cpu->getCache().memory[i].data=memory->getData(busRam.tag);
                                mutex->unlock();
                                std::cout << "Reading from memory..." << std::endl;
                            }
                        }
                    }
                    this->busRam.enabled=false;
                }


                //finally we process our next instruction
                // instance of class std::normal_distribution with specific mean and stddev
                std::normal_distribution<double> d(mean, variance);
                int randValue = d(gen);
                std::normal_distribution<double> d2(8, 8);
                int randTag = d2(gen);


                instruction->generateType(randValue,abs(randTag));
                string type = instruction->getType();
                string data = instruction->getData();
                string tag = instruction->getAddress();
                std::cout << "CPU: "<<id<< ", type: " << type << ", data: "<<data<<", tag: " <<tag<<std::endl;


                string outputInstruction = "";
                string stat = "";
                string outputCPU = "";

                if(type=="write"){
                    mutex->lock();
                    stat=outputInstruction=cpu->write(data,tag);
                    mutex->unlock();
                    outputCPU =  to_string(id) + "1" + to_string(iter)+ " T:" + type + ", Data: " + data + ", Tag: " + tag + " S: " + stat + "\n";
                    msleep(2000);
                }


                else if(type=="read"){
                    mutex->lock();
                    stat=outputInstruction=cpu->read(tag);
                    mutex->unlock();
                    outputCPU =  to_string(id) + "1" + to_string(iter)+ " T:" + type +", " + tag + " S: " + stat + "\n";
                    msleep(2000);
                }
                else{
                    cpu->process();
                    outputCPU =  to_string(id) + "1" + to_string(iter)+ " T:" + type + "\n";
                    msleep(3000);
                }

                string outputCache = to_string(id)+"0"+this->cpu->cacheController.printCache();

                mutex->lock();
                emit signalGUI(QString::fromStdString(outputCPU));
                string outputMEM = this->memory->printMemory();
                std::cout <<"Cache output: \n" << outputCache<< "Mem output: \n"<<outputMEM << std::endl;
                emit signalGUI(QString::fromStdString(outputCache));
                emit signalGUI(QString::fromStdString(memory->printMemory()));
                mutex->unlock();

                iter++;

            }
            else{
                mutex->unlock();
            }
        }
    }
}

void ThreadCPU::setMean(const int &value){
    mean = value;
}
void ThreadCPU::setVar(const int &value){
    variance = value;
}
void ThreadCPU::setState(){
    this->state = !this->state;

}




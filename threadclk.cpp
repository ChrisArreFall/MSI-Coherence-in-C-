#include "threadclk.h"

ThreadCLK::ThreadCLK(QObject *parent) : QThread(parent)
{
    this->frequency = 1000;
    this->clk = false;
}


void ThreadCLK::run()
{
    while(1){
        clk = !clk;
        std::cout << "CLK: " << clk << std::endl;
        if(clk){
            mutex->lock();
            this->clk0 = this->clk1 = this->clk2 = this->clk3 = true;
            mutex->unlock();
        }
        msleep(frequency);
    }
}

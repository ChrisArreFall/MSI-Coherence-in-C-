#include "threadclk.h"

ThreadCLK::ThreadCLK(QObject *parent) : QThread(parent)
{
    this->frequency = 4000;
    this->clk = false;
}


void ThreadCLK::run()
{
    while(1){
        if(state){
            clk=!clk;
            std::cout <<"CLK: "<< clk << std::endl;
            emit signalCLK(clk);
        }
        else{
            clk=false;
            std::cout <<"CLK: "<< clk << std::endl;
            emit signalCLK(clk);
        }

        msleep(frequency);
    }
}

void ThreadCLK::setState()
{
    this->state = !state;
}

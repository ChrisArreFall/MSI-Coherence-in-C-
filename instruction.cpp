#include "instruction.h"

Instruction::Instruction()
{
    int write=0,read=0,process=0;
    generateType(write,read,process);
}

string Instruction::getType() const
{
    return type;
}

void Instruction::setType(const string &value)
{
    type = value;
}

string Instruction::getData() const
{
    return data;
}

void Instruction::setData(string value)
{
    data = value;
}

string Instruction::getAddress() const
{
    return tag;
}

void Instruction::setAddress(string value)
{
    tag = value;
}

void Instruction::generateType(int write, int read, int process)
{
    int seed = std::chrono::steady_clock::now().time_since_epoch().count();
    srand(seed);
    int value = rand() % 60;
    if(value <=30){
        this->type = "write";
    }
    else if(value <=50){
        this->type = "read";
    }
    else{
        this->type = "process";
    }
    int tag = rand() % 16;
    string binTag;
    while(tag!=0) {
        binTag=(tag%2==0 ?"0":"1")+binTag;
        tag/=2;
    }
    this->tag = binTag;
    this->data = to_string(value);
}

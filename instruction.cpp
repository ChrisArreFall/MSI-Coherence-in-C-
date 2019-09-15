#include "instruction.h"



Instruction::Instruction()
{

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




void Instruction::generateType(int value, int tag)
{

    if(value <=34){
        this->type = "write";
    }
    else if(value <=67){
        this->type = "read";
    }
    else{
        this->type = "process";
    }


    string binTag="";
    if(tag==0){
        binTag = "0000";
    }
    else{
        while(binTag.length()<4) {
            binTag=(tag%2==0 ?"0":"1")+binTag;
            tag/=2;
        }
    }
    this->tag = binTag;
}

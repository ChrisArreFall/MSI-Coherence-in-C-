#include "memory.h"

Memory::Memory()
{
    for(int i = 0; i<MEM_SIZE;i++){
        string binTag="";
        if(i==0){
            binTag = "0000";
        }
        else{
            int num = i;
            while(num!=0||binTag.length()<4) {
                binTag=(num%2==0 ?"0":"1")+binTag;
                num/=2;
            }
        }
        memory[i].tag=binTag;
    }

}

int Memory::bitsToInt(string bits)
{
    int number = 0;
        int size = int(bits.size());
        for(int i = 0;i <= size;i++){
            if(bits[size-1-i]=='1'){
                number+=pow(2,i);
            }
        }
    return number;
}

string Memory::printMemory()
{
    string output;
    for(int i = 0;i<MEM_SIZE;i++){
        output.append("Address: "+ this->memory[i].tag + ", Data: " + this->memory[i].data + "\n");
    }
    return output;

}

string Memory::getData(string tag)
{
    int pos = bitsToInt(tag);
    return this->memory[pos].data;
}

void Memory::writeBlock(string tag, string data)
{
    int pos = bitsToInt(tag);
    memory[pos].data = data;
}

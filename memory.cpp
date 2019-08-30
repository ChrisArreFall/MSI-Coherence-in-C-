#include "memory.h"

Memory::Memory()
{

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

string Memory::getBlock(string tag)
{
    int pos = bitsToInt(tag);
    return this->memory[pos].data;
}

void Memory::writeBlock(string tag, string data)
{
    int pos = bitsToInt(tag);
    memory[pos].data = data;
}

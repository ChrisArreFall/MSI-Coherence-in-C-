#ifndef MEMORY_H
#define MEMORY_H
#include <iostream>
#include <string>
#include <math.h>
#define MEM_SIZE 16
using namespace std;

struct RAMBlock
{
   RAMBlock() : tag("XXXX"), data("00000"){}
   string tag;     //identificador del bloque
   string data;    //datos del bloque
};
class Memory
{
public:
    Memory();
    string getData(string tag);
    void writeBlock(string tag,string data);
    int bitsToInt(string bits);
    string printMemory();
private:
    RAMBlock memory[MEM_SIZE];
};

#endif // MEMORY_H

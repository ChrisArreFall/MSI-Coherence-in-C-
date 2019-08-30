#ifndef MEMORY_H
#define MEMORY_H
#include <iostream>
#include <string>
#include <math.h>
using namespace std;

struct RAMBlock
{
    string tag;
    string data;
};
class Memory
{
public:
    Memory();
    string getBlock(string tag);
    void writeBlock(string tag,string data);
    int bitsToInt(string bits);
private:
    RAMBlock memory[16];
};

#endif // MEMORY_H

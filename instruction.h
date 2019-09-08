#ifndef INSTRUCTION_H
#define INSTRUCTION_H
#include <iostream>
#include <string>
#include <chrono>
#include <random>
using namespace std;
class Instruction
{
public:
    Instruction();


    string getType() const;
    void setType(const string &value);

    string getData() const;
    void setData(string value);

    string getAddress() const;
    void setAddress(string value);

    void generateType(int value, int tag);



    int instructionType;
    int tagValue;

private:
    string type;// write, read, process
    string data;   // 6 digit binary number
    string tag;    // 4 digit binary number
};

#endif // INSTRUCTION_H

#ifndef CACHE_H
#define CACHE_H
#include <iostream>
#include <string>
#define CACHE_SIZE 8
using namespace std;
//Este cache es full associative
struct CacheBlock
{
    string tag = "0000";         //identificador del bloque
    string data = "00000";      //datos del bloque
    string state = "invalid";   //invalid, shared, modified
};
class Cache
{
public:
    Cache();
    //Manejo de los bloques (obtener setear)
    CacheBlock getBlock(int pos);
    void setBlock(int pos,string tag,string data, string state);
    //Funciones para revisar el status de el bloque (invalid, shared, modified) y modificarlo
    string getStatusBlock(int pos);
    void setStatusBlock(int pos,string state);
private:
    CacheBlock memory[CACHE_SIZE];
};

#endif // CACHE_H

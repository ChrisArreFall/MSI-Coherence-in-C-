#ifndef CPU_H
#define CPU_H
#include "cache.h"
#include "instruction.h"
#include "cache.h"
#include "cachecontroller.h"




class CPUNode
{
public:
    //Constructor
    CPUNode();
    //Manejo del identificador
    int getId() const;
    //Inicia el procesador, dandole un id
    void init(int id);

    //Los tres tipos de instruccion
    void write(string data,string tag);
    string read(string tag);
    void process();

    //Obtiene el cache (entero)
    Cache getCache() const;
    //Se inicializa un cache (entero)
    void setCache(const Cache &value);

    //Obtiene el status del bus que conecta con la RAM de la instancia del procesador
    BusRAM getBusRAM() const;
    //Se le da un valor al bus de la RAM
    void setBusRAM(const BusRAM &value);

    //Obtiene el status del bus del Cache de la instancia del procesador
    BusCache getBusCache() const;
    //Se le da un valor al bus de el Cache
    void setBusCache(const BusCache &value);

    Instruction getCurrentInstruction();


private:
    int id;
    Cache cache;
    CacheController cacheController;
    Instruction instruction;
    BusCache *busCache;
    BusRAM *busRAM;
    bool writeBack = false;
    bool invalidation = false;
    bool readBack = false;
};

#endif // CPU_H

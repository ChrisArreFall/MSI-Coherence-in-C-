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
    string write(int data,string tag);
    string read(int data,string tag);
    void process();

    //Obtiene el cache (entero)
    Cache getCache() const;
    //Se inicializa un cache (entero)
    void setCache(const Cache &value);

    //Obtiene el status del bus que conecta con la RAM de la instancia del procesador
    BusRAM getBusRAM() const;
    //Se le da un valor al bus de la RAM
    void setBusRAM(BusRAM *value);





    CacheController cacheController;

    QMutex *mutex;


    int id;
    Cache cache;

    Instruction instruction;
    BusCacheMessage *busCache;
    BusRAM *busRAM;


};

#endif // CPU_H

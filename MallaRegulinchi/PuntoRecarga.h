//
// Created by lucia on 02/12/2024.
//

#ifndef PUNTORECARGA_H
#define PUNTORECARGA_H


#include "UTM.h"
#include "Coche.h"
#include <map>

class Coche;

class PuntoRecarga {
    int id, max, n_coches;
    UTM pos;
    std::multimap<int,Coche*> chargepoint;
public:
    PuntoRecarga():max(50),n_coches(0),id(0) {};
    PuntoRecarga (int id1,float latitude1,float longitude1,int max_cars1);
    Coche* getMaxBateria();
    bool addCoche(Coche* c);
    void deleteCoche(Coche* c);

    PuntoRecarga &operator=(PuntoRecarga p){
        id=p.id;
        max=p.max;
        n_coches=p.n_coches;
        pos=p.pos;
        max = p.max;
        return  *this;
    }

    int getNumCoches(){
        return n_coches;
    }

    void setPos(const UTM &pos);

    int getId();

    int getMax() {
        return max;
    }

    UTM getPos()  {
        return pos;
    }

    std::multimap<int,Coche*> *getChargepoint() ;
};



#endif //PUNTORECARGA_H

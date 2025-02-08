//
// Created by Usuario on 27/10/2024.
//

#ifndef PR3_EEDD_PUNTORECARGA_H
#define PR3_EEDD_PUNTORECARGA_H

#include "UTM.h"
#include "Coche.h"
#include <queue>

class Coche;

class PuntoRecarga {
    int id, max, n_coches;
    UTM pos;
    std::priority_queue<Coche*> chargepoint;
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

    int getId();

    int getMax() {
        return max;
    }

     UTM getPos()  {
        return pos;
    }

    std::priority_queue<Coche*> *getChargepoint() ;
};

#endif //PR3_EEDD_PUNTORECARGA_H

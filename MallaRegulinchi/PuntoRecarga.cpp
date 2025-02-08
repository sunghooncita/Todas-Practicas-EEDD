//
// Created by lucia on 02/12/2024.
//

#include "PuntoRecarga.h"

#include <iostream>

PuntoRecarga:: PuntoRecarga(int id1,float latitude1,float longitude1,int max_cars1):id(id1),max(max_cars1){
    UTM pos1(latitude1,longitude1);
    pos=pos1;
};


Coche *PuntoRecarga::getMaxBateria(){
    auto it = chargepoint.rbegin();
    return it->second;
};

bool PuntoRecarga::addCoche(Coche* c){
    if(chargepoint.size() < max) {
        chargepoint.insert(std::pair<int,Coche*>(c->getBateria(),c));
        n_coches++;
        return true;
    }
    return false;
};

void PuntoRecarga::deleteCoche(Coche* c){
    auto it = chargepoint.equal_range(c->getBateria());

    auto it2 = it.first;

    while (it2 != chargepoint.end()) {
        if(it2->second->getId_matricula() == c->getId_matricula()) {
            chargepoint.erase(it2);
            n_coches--;
        }
        it2++;
    }
}

int PuntoRecarga::getId() {
    return id;
}

std::multimap<int,Coche*> *PuntoRecarga::getChargepoint()  {
    return &chargepoint;
}

void PuntoRecarga::setPos(const UTM &pos) {
    PuntoRecarga::pos = pos;
}


/*VDinamico<Coche *> &PuntoRecarga::getCoches() {
    return coches;
}*/

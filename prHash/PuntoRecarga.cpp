

#include "PuntoRecarga.h"

#include <iostream>

PuntoRecarga:: PuntoRecarga(int id1,float latitude1,float longitude1,int max_cars1):id(id1),max(max_cars1){
    UTM pos1(latitude1,longitude1);
    pos=pos1;
};


Coche *PuntoRecarga::getMaxBateria(){

    Coche* c=chargepoint.top();
    return c;
};

bool PuntoRecarga::addCoche(Coche* c){
    if(chargepoint.size() < max) {
        chargepoint.push(c);
        n_coches++;
        return true;
    }
    return false;
};

void PuntoRecarga::deleteCoche(Coche* c){
    std::priority_queue<Coche*> temp;
    while (!chargepoint.empty()) {
        if (chargepoint.top()->getId_matricula() != c->getId_matricula()) {
            temp.push(chargepoint.top());
        }
        chargepoint.pop();
    }
//@todo ns si esto esta bn
    chargepoint = temp;
}

int PuntoRecarga::getId() {
    return id;
}

 std::priority_queue<Coche*> *PuntoRecarga::getChargepoint()  {
    return &chargepoint;
}


/*VDinamico<Coche *> &PuntoRecarga::getCoches() {
    return coches;
}*/

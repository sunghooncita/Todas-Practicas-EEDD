

#include "PuntoRecarga.h"

#include <iostream>

Coche *PuntoRecarga::getMaxBateria(){
    Coche *maxC=coches[0];
    for (int i = 1; i < 28; ++i) {
        if(coches[i]!=nullptr) {
            if (maxC->getBateria()<coches[i]->getBateria()){
                maxC=coches[i];
            }
        }
    }
    return maxC;
};

bool PuntoRecarga::addCoche(Coche* c){
    if(n_coches+1<max) {
        coches.insertar(c);
        n_coches++;
        return true;
    }else {return false;}
};

void PuntoRecarga::deleteCoche(Coche* c){
    coches.ordenar();
    coches.borrar(coches.busquedaBin(c));
    n_coches--;
}


VDinamico<Coche *> &PuntoRecarga::getCoches() {
    return coches;
}

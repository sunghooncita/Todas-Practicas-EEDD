//
// Created by Usuario on 27/10/2024.
//

#ifndef PR3_EEDD_PUNTORECARGA_H
#define PR3_EEDD_PUNTORECARGA_H

#include "UTM.h"
#include "Coche.h"
#include "VDinamico.h"

class Coche;

class PuntoRecarga {
    int id, max, n_coches;
    UTM pos;
    VDinamico<Coche*> coches;
public:
    PuntoRecarga():max(50),n_coches(0),id(0) {};
    Coche* getMaxBateria();
    bool addCoche(Coche* c);
    void deleteCoche(Coche* c);

    VDinamico<Coche *> &getCoches();

};

#endif //PR3_EEDD_PUNTORECARGA_H

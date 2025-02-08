//
// Created by lucia on 06/10/2024.
//

#ifndef REANELCAR_H
#define REANELCAR_H

#include <string>

#include "VDinamico.h"
#include "ListaDEnlazada.h"
#include "Coche.h"
#include "Usuario.h"


class ReanelCar {
private:
    VDinamico<Coche> cars;
    ListaDEnlazada<Usuario> users;

public:
    ReanelCar();

    Usuario *buscarUsrNif(std::string nif);

    ListaDEnlazada<Usuario*> buscarUsrNomb(std::string nom);

    ListaDEnlazada<Usuario*> buscarUsrNombBinario(std::string nom);

    Coche * buscarCochMat(std::string mat);

    VDinamico<Coche*> buscarCochModelo(std::string mod);

    VDinamico<Coche*> buscarCochModeloBinaria(std::string mod);

	bool alquilar(Usuario *usr, Coche *c);

    bool borrar(Usuario* u);

};



#endif //REANELCAR_H

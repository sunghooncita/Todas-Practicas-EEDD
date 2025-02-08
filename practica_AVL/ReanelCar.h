//
// Created by Usuario on 27/10/2024.
//

#ifndef PR3_EEDD_REANELCAR_H
#define PR3_EEDD_REANELCAR_H


#include <string>

#include "AVL.h"
#include "VDinamico.h"
#include "ListaDEnlazada.h"
#include "Coche.h"
#include "PuntoRecarga.h"
#include "Usuario.h"

class Usuario;

class ReanelCar {

public:

    AVL<Coche> cars;
    ListaDEnlazada<Usuario> users;
    PuntoRecarga *sities = new PuntoRecarga();


    ReanelCar();

    Usuario *buscarUsrNif(std::string nif);

    ListaDEnlazada<Usuario*> buscarUsrNomb(std::string nom);

    ListaDEnlazada<Usuario*> buscarUsrNombBinario(std::string nom);

    Coche * buscarCochMat(std::string mat);

    AVL<Coche*> buscarCochModelo(std::string mod);

    AVL<Coche*> buscarCochModeloBinaria(std::string mod);

    Coche *alquilar(Usuario *usr);

    void colocarCochePR(Coche *c);

    bool borrar(Usuario* u);

};


#endif //PR3_EEDD_REANELCAR_H

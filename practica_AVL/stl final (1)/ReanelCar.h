//
// Created by Usuario on 27/10/2024.
//

#ifndef PR3_EEDD_REANELCAR_H
#define PR3_EEDD_REANELCAR_H

#include <string>
#include <list>
#include <map>
#include <vector>


#include "Coche.h"
#include "PuntoRecarga.h"
#include "Usuario.h"
#include "Fecha.h"
#include "Trayecto.h"
#include <atomic>


class Usuario;

class ReanelCar {
private:
    std::atomic<int> idTrayecto = 0;
    std::map <std::string, Coche> cars;
    std::list <Usuario> users;
    std::vector<PuntoRecarga> sities;

    PuntoRecarga *buscarPunto(int id);

public:


    ReanelCar();

    Usuario *buscarUsrNif(std::string nif);

    std::list<Usuario*> buscarUsrNomb(std::string nom);

    Coche * buscarCochMat(std::string mat);

    std::map<std::string,Coche*> buscarCochModelo(std::string mod);


    Coche *alquilar(Usuario *u,int idPROrigen, int idPRDestino, Fecha *ini, Fecha *final);

    void colocarCochePR(Coche *c, PuntoRecarga *p);

    bool borrar(Usuario* u);

    PuntoRecarga *obtenerPRmenosCoches();

    std::vector<std::pair<Usuario*,Trayecto*>> trayectosEnFecha(Fecha f);

     std::map<std::string, Coche> getCars() {
        return cars;
    }

     std::list<Usuario> getUsers() {
        return users;
    }

     std::vector<PuntoRecarga> getSities() {
        return sities;
    }

    void Ejercicio1();

     void Ejercicio2(std::list<Usuario*> lusu);

    void Ejercicio3(std::list<Usuario*> lusuWa);

    void Ejercicio4(std::list<Usuario*> lusuWa);





};


#endif //PR3_EEDD_REANELCAR_H

//
// Created by Usuario on 27/10/2024.
//

#ifndef PR3_EEDD_USUARIO_H
#define PR3_EEDD_USUARIO_H

#include <string>
#include <vector>
#include "Coche.h"
#include "Trayecto.h"
#include <map>
#include <atomic>

class ReanelCar;
class Trayecto;

class Usuario {
private:
    std::string nif;
    std::string clave;
    std::string nombre;
    std::string direccion;
    Coche *coche;
    ReanelCar *linkReanel;
    std::multimap<Fecha, Trayecto> route;
    std::atomic<int> id;

public:

    Usuario(const std::string &nif=" ", const std::string &clave=" ", const std::string &nombre=" ", const std::string &direccion= " ", Coche *_coche=nullptr, std::atomic<int> id=0);
    Usuario(const Usuario &other);
    std::string getNif() const ;
    void setNif(const std::string &nif);
    std::string getClave() const;
    void setClave(const std::string &clave) ;
    std::string getNombre() const;
    void setNombre(const std::string &nombre) ;
    std::string getDireccion() const;
    void setDireccion(const std::string &direccion) ;
    Coche *getCoche();
    void setCoche(Coche *coche);
    bool operator==(Usuario usuario);
    Usuario &operator=(const Usuario &usu);
    void setLinkReanel(ReanelCar *_linkReanel);

    ReanelCar *getLinkReanel() const;

    std::multimap<Fecha, Trayecto> *getRoute() ;


    Trayecto* crearTrayecto(PuntoRecarga *ori, PuntoRecarga *des,Fecha *ini, Fecha*fin);

    Coche *iniciaTrayecto(int idPuntoInicio, int idPuntoFinal,Fecha *ini, Fecha*fin);

    void aparcaCoche(Coche *c, PuntoRecarga *pr);

    std::vector<Trayecto*> getTrayectosFecha (Fecha *f);

    Usuario* getUsu(){
        return this;
    }
};

#endif //PR3_EEDD_USUARIO_H

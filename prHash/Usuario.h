
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
    int puntos=100;
    Coche *coche;
    ReanelCar *linkReanel;
    std::multimap<Fecha, Trayecto> route;
    std::atomic<int> id;


public:

    unsigned long djb2(unsigned char *str) {
        unsigned long hash = 5381;
        int c;
        while (c = *str++) hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
        return hash;
    }
    Usuario(const std::string &nif=" ", const std::string &clave=" ", const std::string &nombre=" ", const std::string &direccion= " ", Coche *_coche=nullptr, std::atomic<int> id=0, int pn=100);
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

    int getPuntos() ;

    bool operator==(Usuario usuario);
    Usuario &operator=(const Usuario &usu);
    void setLinkReanel(ReanelCar *_linkReanel);

    ReanelCar *getLinkReanel() const;

    std::multimap<Fecha, Trayecto> *getRoute() ;


    Trayecto* crearTrayecto(PuntoRecarga *ori, PuntoRecarga *des,Fecha *ini, Fecha*fin);

    Coche *iniciaTrayecto(int idPuntoInicio, int idPuntoFinal,Fecha *ini, Fecha*fin);

    void aparcaCoche(Coche *c, PuntoRecarga *pr, int retraso);

    std::vector<Trayecto*> getTrayectosFecha (Fecha *f);

    Usuario* getUsu(){
        return this;
    }

    void eliminarTrayectos();
    void decrementarPuntos(int retraso);



};

#endif //PR3_EEDD_USUARIO_H

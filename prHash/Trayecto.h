
#ifndef STL_TRAYECTO_H
#define STL_TRAYECTO_H
#include "Fecha.h"
#include "Coche.h"
#include "PuntoRecarga.h"
#include <atomic>

class Trayecto {
private:
    Fecha fechaInicio;
    Fecha fechaFinal;
    Coche *inthecar;
    PuntoRecarga *origin;
    PuntoRecarga *destination;
    int idTrayecto=0;
public:

    Trayecto();

    Trayecto(Fecha fechaInicio, Fecha fechaFinal, Coche *inthecar,
             PuntoRecarga *origin, PuntoRecarga *destination,int id);

    void setCoche(Coche *c);

    void setFechaInicio(const Fecha &fechaInicio);

    void setFechaFinal(const Fecha &fechaFinal);

    void set_origin(PuntoRecarga *origin) {
        this->origin = origin;
    }

    void set_destination(PuntoRecarga *destination) {
        this->destination = destination;
    }

     PuntoRecarga* getOrigin() ;

     PuntoRecarga* getDestination() ;

     Fecha getFechaInicio() ;

     Fecha getFechaFinal() ;

     Coche *getInthecar() ;

     Trayecto &operator=(Trayecto t);


};


#endif //STL_TRAYECTO_H



#include "Trayecto.h"

void Trayecto::setCoche(Coche *c){
    inthecar=c;
}

Trayecto::Trayecto() {
    idTrayecto++;
}

void Trayecto::setFechaInicio(const Fecha &fechaInicio) {
    Trayecto::fechaInicio = fechaInicio;
}

void Trayecto::setFechaFinal(const Fecha &fechaFinal) {
    Trayecto::fechaFinal = fechaFinal;
}

 PuntoRecarga* Trayecto::getOrigin()  {
    return origin;
}

 PuntoRecarga* Trayecto::getDestination()  {
return destination;
}

 Fecha Trayecto::getFechaInicio()  {
    return fechaInicio;
}

 Fecha Trayecto::getFechaFinal()  {
    return fechaFinal;
}

Coche *Trayecto::getInthecar()  {
    return inthecar;
}

Trayecto &Trayecto::operator=(Trayecto t){
    this->origin=t.origin;
    this->inthecar=t.inthecar;
    this->fechaFinal=t.fechaFinal;
    this->fechaInicio=t.fechaInicio;
    this->destination=t.destination;
    //this->idTrayecto=t.idTrayecto;
    return *this;
}

Trayecto::Trayecto(Fecha fechaInicio, Fecha fechaFinal, Coche *inthecar, PuntoRecarga *origin,
                   PuntoRecarga *destination,int id) : fechaInicio(fechaInicio), fechaFinal(fechaFinal), inthecar(inthecar), origin(origin), destination(
        destination),idTrayecto(id) {
};


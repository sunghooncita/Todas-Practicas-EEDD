//
// Created by lucia on 02/12/2024.
//

#include "Usuario.h"
#include <cmath>

#include "ReanelCar.h"


Usuario::Usuario(const std::string &nif, const std::string &clave, const std::string &nombre, const std::string &direccion, Coche *_coche,std::atomic<int> id, int pn)
        : nif(nif),
          clave(clave),
          nombre(nombre),
          direccion(direccion),
          coche(_coche),
          puntos(pn)
          {
            id.store(id);
          }

Usuario::Usuario(const Usuario &other):nif(other.nif),
                                       clave(other.clave),
                                       nombre(other.nombre),
                                       direccion(other.direccion),
                                       puntos(other.puntos)
{
}

std::string Usuario::getNif() const {
    return nif;
}

void Usuario::setNif(const std::string &nif) {
    this->nif = nif;
}

std::string Usuario::getClave() const {
    return clave;
}

void Usuario::setClave(const std::string &clave) {
    this->clave = clave;
}

std::string Usuario::getNombre() const {
    return nombre;
}

void Usuario::setNombre(const std::string &nombre) {
    this->nombre = nombre;
}

std::string Usuario::getDireccion() const {
    return direccion;
}

void Usuario::setDireccion(const std::string &direccion) {
    this->direccion = direccion;
}

Coche *Usuario::getCoche(){
    return coche;
}


void Usuario::setCoche(Coche *coche) {
    this->coche = coche;
}

bool Usuario::operator==(Usuario usuario) {
    if(nif==usuario.nif)
        return true;
    return false;
}

Usuario &Usuario::operator=(const Usuario &usu) {
    nif = usu.nif;
    clave = usu.clave;
    nombre = usu.nombre;
    direccion = usu.direccion;
    coche = usu.coche;

    return *this;
}

void Usuario::setLinkReanel(ReanelCar *_linkReanel) {
    linkReanel = _linkReanel;
}


Trayecto* Usuario::crearTrayecto(PuntoRecarga *ori, PuntoRecarga *des,Fecha *ini, Fecha*fin) {
    Trayecto nuevoT(*ini,*fin,coche,ori,des,id.load());
    Fecha fecha;
    fecha = *ini;
    std::pair<Fecha,Trayecto> juan;
    juan.first = fecha;
    juan.second = nuevoT;
    route.insert(juan);
    Trayecto* puntNuevo=&nuevoT;
    return puntNuevo;
}

Coche *Usuario::iniciaTrayecto(int idPuntoInicio, int idPuntoFinal,Fecha *ini, Fecha*fin) {
    Coche *c=linkReanel->alquilar(this, idPuntoInicio, idPuntoFinal, ini,fin);
    Trayecto* tr=crearTrayecto(c->getPuntoR(),c->getPuntoD(),ini,fin);
    tr->setCoche(c);
    return c;
}

void Usuario::aparcaCoche(Coche *c, PuntoRecarga *pr) {
    linkReanel->colocarCochePR(c,pr);
    float kilom=0, diflat=0, diflong=0, r=6371,a=0,c1=0;
    if(this->coche->getPuntoD()!=pr){
        diflat=(pr->getPos().getLatitud())-(coche->getPuntoD()->getPos().getLatitud());
        diflong=(pr->getPos().getLongitud())-(coche->getPuntoD()->getPos().getLongitud());
        a=std::pow(std::sin(diflat/2), 2)+(std::cos(coche->getPuntoD()->getPos().getLatitud())*std::cos(pr->getPos().getLatitud())*std::pow(std::sin(diflong/2), 2));
        c1 = 2 * std::atan2(std::sqrt(a), std::sqrt(1 - a));
        kilom=r*c1;
        decrementarPuntos(static_cast<int>(kilom));
    }
    this->coche= nullptr;

}

std::vector<Trayecto*> Usuario::getTrayectosFecha (Fecha *f) {
    std::vector<Trayecto*> alberto;
    auto i = route.equal_range(*f);
    for (auto j = i.first ;j != route.end(); j++) {
            alberto.push_back(&j->second);
    }
    return alberto;
}

std::multimap<Fecha, Trayecto>* Usuario::getRoute()  {
    return &route;
}

ReanelCar *Usuario::getLinkReanel() const {
    return linkReanel;
}

void Usuario::eliminarTrayectos() {
    route.clear();
}

void Usuario::decrementarPuntos(int kilometro) {
    puntos=puntos-(kilometro*2);
}

int Usuario::getPuntos()  {
    return puntos;
}

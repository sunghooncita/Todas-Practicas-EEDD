
#include "Usuario.h"

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
    return &nuevoT;
   //@TODO NS SI EST BN
}

Coche *Usuario::iniciaTrayecto(int idPuntoInicio, int idPuntoFinal,Fecha *ini, Fecha*fin) {
    Coche *c=linkReanel->alquilar(this, idPuntoInicio, idPuntoFinal, ini,fin);
    Trayecto* tr=crearTrayecto(c->getPuntoR(),c->getPuntoD(),ini,fin);
    tr->setCoche(c);
    return c;
}

void Usuario::aparcaCoche(Coche *c, PuntoRecarga *pr, int retraso) {
    linkReanel->colocarCochePR(c,pr);
    this->coche= nullptr;
    decrementarPuntos(retraso);
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

void Usuario::decrementarPuntos(int retraso) {
    puntos=puntos-(retraso*2);
}

int Usuario::getPuntos()  {
    return puntos;
}

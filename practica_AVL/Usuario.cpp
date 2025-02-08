//
// Created by Usuario on 27/10/2024.
//

#include "Usuario.h"

Coche *Usuario::cogeCoche(){
    Coche *ch = linkReanel->alquilar(this);
    setCoche(ch);
    return ch;
};


Usuario::Usuario(const std::string &nif, const std::string &clave, const std::string &nombre, const std::string &direccion, Coche *_coche)
        : nif(nif),
          clave(clave),
          nombre(nombre),
          direccion(direccion),
          coche(_coche){}

Usuario::Usuario(const Usuario &other):nif(other.nif),
                                       clave(other.clave),
                                       nombre(other.nombre),
                                       direccion(other.direccion){
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
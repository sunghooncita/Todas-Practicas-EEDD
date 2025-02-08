//
// Created by lucia on 06/10/2024.
//

#ifndef USUARIO_H
#define USUARIO_H

#include <string>
#include "Coche.h"
#include "ListaDEnlazada.h"

class Usuario {
private:
    std::string nif;
    std::string clave;
    std::string nombre;
    std::string direccion;

    Coche *coche;

public:

    Usuario(const std::string &nif=" ", const std::string &clave=" ", const std::string &nombre=" ", const std::string &direccion= " ", Coche *_coche=nullptr);

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


};



#endif //USUARIO_H

//
// Created by lucia on 07/10/2024.
//

#include "Coche.h"

#include <iostream>
#include <sstream>

Coche::Coche():id_matricula(""),marca(""),modelo("") {}


Coche::Coche(std::string id_matricula,  std::string marca,  std::string modelo)
        : id_matricula(id_matricula),
          marca(marca),
          modelo(modelo) {
}

Coche::Coche(const Coche &other): id_matricula(other.id_matricula),
          marca(other.marca),
          modelo(other.modelo) {
}

std::string Coche::getId_matricula() const {
    return id_matricula;
}

void Coche::setId_matricula(const std::string &id_matricula) {
    this->id_matricula = id_matricula;
}

std::string Coche::getMarca() const {
    return marca;
}

void Coche::setMarca(const std::string &marca) {
    this->marca = marca;
}

std::string Coche::getModelo() const {
    return modelo;
}

void Coche::setModelo(const std::string &modelo) {
    this->modelo = modelo;
}

bool Coche::operator<(const Coche &car){
    return modelo < car.modelo;
   /* std::string data = id_matricula;
    std::string data2 = car.getId_matricula();
    std::istringstream iss(data);
    std::istringstream iss2(data2);
    int numero;
    int numero1;
    std::string texto;
    std::string texto1;

    iss >> numero >> texto;
    iss2 >> numero1 >> texto1;

    if(texto < texto1)
        return true;
    if (texto1 == texto)
        if(numero < numero1)
            return true;
    return false;*/

}

bool Coche::operator==(Coche car) {
    if(id_matricula==car.id_matricula)
        return true;
    return false;
}

bool Coche::operator!=(Coche origen)  {
    return !(origen == *this);
}



Coche &Coche::operator=(const Coche &car) {
    id_matricula = car.id_matricula;
    modelo = car.modelo;
    marca = car.marca;


    return *this;
}

bool Coche:: operator<=(const Coche &car) {
    if(id_matricula==car.id_matricula)
        return true;
    std::string data = id_matricula;
    std::string data2 = car.getId_matricula();
    std::istringstream iss(data);
    std::istringstream iss2(data2);
    int numero;
    int numero1;
    std::string texto;
    std::string texto1;

    iss >> numero >> texto;
    iss2 >> numero1 >> texto1;

    if(texto < texto1)
        return true;
    if (texto1 == texto)
        if(numero < numero1)
            return true;
    return false;
};








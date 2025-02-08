//
// Created by lucia on 30/09/2024.
//

#include "Coche.h"

#include <iostream>
#include <sstream>


/**
 * @brief Constructor parametrizado
 * @param id_matricula matricula que inicializamos
 * @param marca marca que inicializamos
 * @param modelo modelo que inicializamos
 */
Coche::Coche(std::string id_matricula,  std::string marca,  std::string modelo)
        : id_matricula(id_matricula),
          marca(marca),
          modelo(modelo) {
}

/**
 * @brief Constructor copia
 * @param other el tipo coche que vamos a copiar
 */
Coche::Coche(const Coche &other): id_matricula(other.id_matricula),
          marca(other.marca),
          modelo(other.modelo) {
}

/**
 * @brief getter de la matricula
 * @return el valor dentro de la matricula
 */
std::string Coche::getId_matricula() const {
    return id_matricula;
}

/**
 * @brief setter de matricula
 * @param id_matricula el valor para la matricula
 */
void Coche::setId_matricula(const std::string &id_matricula) {
    this->id_matricula = id_matricula;
}

/**
 * @brief getter de la marca
 * @return el valor dentro de marca
 */
std::string Coche::getMarca() const {
    return marca;
}

/**
 * @brief setter de matricula
 * @param marca el valor para la marca
 */
void Coche::setMarca(const std::string &marca) {
    this->marca = marca;
}

/**
 * @brief getter del modelo
 * @return el valor dentro de modelo
 */
std::string Coche::getModelo() const {
    return modelo;
}

/**
 * @brief setter de matricula
 * @param modelo el valor para el modelo
 */
void Coche::setModelo(const std::string &modelo) {
    this->modelo = modelo;
}

/**
 * @brief Operador menor que
 * @param car objeto con el que vamos a comparar
 * @return bool de si es menor o no
 */
bool Coche::operator<(const Coche &car){
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

}

/**
 * @brief Operador igual igual
 * @param car objeto con el que vamos a comparar
 * @return bool de si es igual la matricula o no
 */
bool Coche::operator==(const Coche &car) {
    if(id_matricula==car.id_matricula)
        return true;
    return false;
}

/**
 * @brief Operador igual
 * @param car objeto con el que vamos a comparar
 * @return bool de si es igual o no
 */
Coche &Coche::operator=(const Coche &car) {
    id_matricula = car.id_matricula;
    modelo = car.modelo;
    marca = car.marca;

    return *this;
}

/**
 * @brief Operador menor igual que
 * @param car objeto con el que vamos a comparar
 * @return bool de si es menor, igual o no
 */
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








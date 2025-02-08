//
// Created by lucia on 02/12/2024.
//

#ifndef CASILLA_H
#define CASILLA_H
#include <list>
#include "MallaRegular.h"

template<typename T> class MallaRegular;

template<typename T>
class Casilla{
    std::list<T> puntos;
public:
    friend class MallaRegular<T>;
    Casilla(){};
    void insertar( T dato) { puntos.push_back(dato); }
    T *buscar( T dato);
    bool borrar( T dato);
};


template<typename T>
T *Casilla<T>::buscar( T dato){
    typename std::list<T>::iterator it;
    it = puntos.begin();
    for (;it != puntos.end(); ++it){
        if (*it == dato)
            return &(*it);
    }
    return 0;
}

template<typename T>
bool Casilla<T>::borrar( T dato){
    typename std::list<T>::iterator it;
    it = puntos.begin();
    for (;it != puntos.end(); ++it){
        if (*it == dato) {
            puntos.erase(it);
            return true;
        }
    }
    return false;
}
#endif //CASILLA_H

//
// Created by lucia on 02/12/2024.
//

#ifndef MALLAREGULAR_H
#define MALLAREGULAR_H
#include <vector>
#include <list>
#include <cmath>
#include "Casilla.h"
#include "stdexcept"

template <typename T>
class MallaRegular{

    float xMin, yMin, xMax, yMax; // Tamaño real global
    float tamaCasillaX, tamaCasillaY; // Tamaño real de cada casilla
    float radioMax;
    std::vector<std::vector<Casilla<T> > > mr; // Vector 2D de casillas
    Casilla<T> *obtenerCasilla(float x, float y);
    float PI = 3.141516;
    float R = 6378.0;

public:
    MallaRegular(float aXMin=0, float aYMin=0, float aXMax=0, float aYMax=0, int nDiv=0);
    void insertar(float x, float y,T dato);
    T *buscar (float x, float y,  T dato);
    bool borrar(float x, float y,  T dato);
    float calcularDistancia(float lat1,float lat2,float lon1,float lon2);

    std::vector<T> buscarRadio(float xcentro, float ycentro, float radio);
    unsigned maxElementosPorCelda();
    float promedioElementosPorCelda();
};

/**
 * @brief Devuelve una casilla de la malla dados dos coordenadas
 * @tparam T tipo de dato qu está compuesto la malla
 * @param x primera coordenada
 * @param y segunda coordenada
 * @return la casilla con esas coordenadas
 */
template<typename T>
Casilla<T> *MallaRegular<T>::obtenerCasilla(float x, float y) {
    int i = (x - xMin) / tamaCasillaX;
    int j = (y - yMin) / tamaCasillaY;
    return &mr[i][j];
}


//Constructor
template<typename T>
MallaRegular<T>::MallaRegular(float aXMin, float aYMin, float aXMax, float aYMax, int aNDiv) :
        xMin(aXMin), yMin(-5), xMax(aXMax), yMax(aYMax){
    tamaCasillaX = (xMax - xMin)/aNDiv;
    tamaCasillaY = (yMax - yMin)/aNDiv;
    mr.insert(mr.begin(), aNDiv, std::vector<Casilla<T>>(aNDiv));
}


/**
 * @brief inserta un dato en una posición de la malla
 * @tparam T tipo de dato que está compuesta la malla
 * @param x primera coordenada
 * @param y segunda coordenada
 * @param dato dato que se va a introducir en la malla
 */
template<typename T>
void MallaRegular<T>::insertar(float x, float y,T dato){
    Casilla<T> *c = obtenerCasilla(x,y);
    c->insertar(dato);
}


/**
 * @brief busca un dato dentro de unas coordenadas dadas y lo devuelve
 * @tparam T tipo de dato que está compuesta la malla
 * @param x primera coordenada
 * @param y segunda coordenada
 * @param dato dato que vamos a buscar
 * @return devuelve el dato si lo ha encontrado
 */
template<typename T>
T *MallaRegular<T>::buscar(float x, float y,  T dato) {
    if(x<xMin || y<yMin || x>xMax || y>yMax){
        throw std::out_of_range ("Rango fuera de la malla");
    }
    Casilla<T> c = obtenerCasilla(x,y);
    return c.buscar(dato);
}


/**
 * @brief borra un dato de la malla dadas unas coordenadas
 * @tparam T tipo de dato que está compuesta la malla
 * @param x primera coordenada
 * @param y segunda coordenada
 * @param dato dato que se va a borrar
 * @return true si el borrado ha sido exitoso, false si no ha conseguido borrarlo
 */
template<typename T>
bool MallaRegular<T>::borrar(float x, float y,  T dato){
    Casilla<T> *c = obtenerCasilla(x,y);
    return c->borrar(dato);
}


template<typename T>
float MallaRegular<T>::calcularDistancia(float lat1, float lat2, float lon1, float lon2) {
    double incrLat = (lat2 - lat1) * (PI / 180.0);
    double incrLon = (lon2 - lon1) * (PI / 180.0);

    double a = sin(incrLat / 2.0) * sin(incrLat / 2.0) +
               cos(lat1 * (PI / 180.0)) * cos(lat2 * (PI / 180.0)) *
               sin(incrLon / 2.0) * sin(incrLon / 2.0);

    double c = 2.0 * atan2(sqrt(a), sqrt(1.0 - a));

    double d = R * c;

    return d;
}


/**
 * @brief Devuelve todos los datos que se encuentre en un rango dado
 * @tparam T tipo de dato compuesto de la malla
 * @param rXMin posicion minima de la x
 * @param rYMin posicion minima de la y
 * @param rXMax posicion maxima de la x
 * @param rYMax posicion maxima de la y
 * @return vector con todos los datos del rango
 */
template<typename T>
std::vector<T> MallaRegular<T>::buscarRadio(float xcentro, float ycentro, float radio) {

    if(xcentro > xMax || xcentro < xMin || ycentro < yMin || ycentro > yMax){
        throw std::out_of_range ("Ese rango se encuentra fuera de la malla");
    }
    std::vector<T> caja;
    float x_aux=xcentro-radio;  // esquina inf derecha
    float y_aux=ycentro-radio;


    while(x_aux<xcentro+radio){ //esquina sup derecha
        float y_aux=ycentro-radio;

        while (y_aux<ycentro+radio){ //esquina sup izquierda
            Casilla<T> *c=obtenerCasilla(x_aux,y_aux);
            for (auto itrecorre = c->puntos.begin();itrecorre != c->puntos.end(); ++itrecorre){
                float d = calcularDistancia(xcentro,(itrecorre).operator*()->getUTM().getLatitud(),ycentro,(itrecorre).operator*()->getUTM().getLongitud());
                if(d < radio) {
                    caja.push_back(*itrecorre);
                }
            }
            y_aux+=tamaCasillaY;
        }
        x_aux+=tamaCasillaX;
    }
    return caja;
}


/**
 * @brief calcula cual es el maximo de elementos que hay en una sola casilla
 * @tparam T tipo de dato que está compuesto la malla
 * @return el maximo de elementos encontrado
 */
template<typename T>
unsigned int MallaRegular<T>::maxElementosPorCelda() {
    float x_aux=xMin;
    float y_aux=yMin;
    int contadorpuntos=0;
    int maxpuntos=0;
    while(x_aux<xMax){
        y_aux=yMin;
        while (y_aux<yMax){
            contadorpuntos=0;
            Casilla<T> *c=obtenerCasilla(x_aux,y_aux);
            typename std::list<T>::iterator itrecorre=c->puntos.begin();
            for (;itrecorre != c->puntos.end(); ++itrecorre){
                ++contadorpuntos;
            }
            if(contadorpuntos>maxpuntos){
                maxpuntos=contadorpuntos;
            }
            y_aux+=tamaCasillaY;
        }
        x_aux+=tamaCasillaX;
    }
    return (maxpuntos);
}

/**
 * @brief calcula el promedio de elementos por celda que hay en la malla
 * @tparam T tipo de dato que está compuesta la malla
 * @return el promedio de elementos
 */
template<typename T>
float MallaRegular<T>::promedioElementosPorCelda() {
    float x_aux=xMin;
    float y_aux=yMin;
    int contadorpuntos=0;
    int contadorceldasvacias=0;
    int contadorceldas=0;
    while(x_aux<xMax){
        y_aux=yMin;
        while (y_aux<yMax){
            Casilla<T> *c=obtenerCasilla(x_aux,y_aux);
            typename std::list<T>::iterator itrecorre=c->puntos.begin();
            if(itrecorre == c->puntos.end()) { ///vemos si esa celda no este vacía
                ++contadorceldasvacias;
            }else{
                for (;itrecorre != c->puntos.end(); ++itrecorre){
                    ++contadorpuntos;
                }
            }
            ++contadorceldas;
            y_aux+=tamaCasillaY;
        }
        x_aux+=tamaCasillaX;
    }
    return (contadorpuntos/(contadorceldas/*-contadorceldasvacias*/));
}
#endif //MALLAREGULAR_H

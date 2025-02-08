//
// Created by chissu on 22/09/2024.
//

#ifndef PRACICA_1_EEDD_VDINAMICO_H
#define PRACICA_1_EEDD_VDINAMICO_H

#include <algorithm>

template<class T>

class VDinamico {

private:
    T *mem; //Vector de tipo T
    long int n_datos; //Tamaño del vector

public:

    VDinamico<T>(unsigned int n); //Constructor por defecto que crea espacio para n datos

    VDinamico<T>(const VDinamico<T> &origen); //Constructor copia

    VDinamico<T>(const VDinamico<T> &origen, unsigned int posicionInicial,
                 unsigned int numElementos); //Constructor copia parcial
    //el vector que se genera debe tener un tamaño máximo de numElementos.

    T &operator=(VDinamico &arr); //Operador =

    T &operator[](unsigned int posicion); //Operador [] para acceder a un dato en la posicion indicada

    void ordenar(); //Ordena de menor a mayor el vector mediante sort de la libreria algorithm

    void ordenaBurbuja(); //Ordena el vector pero mediante el metodo burbuja

    virtual ~VDinamico(); //Destructor

};


/**
 * @brief Constructor por defecto que lo crea espacio para n datos
 * @tparam T El tipo de los elementos almacenados en el vector dinámico.
 * @param n Es el tamaño del vector
 */
template<class T>
VDinamico<T>::VDinamico(unsigned int n) {
    mem = new T[n_datos = n];
};


/**
 * @brief Constructor copia
 * @tparam T El tipo de los elementos almacenados en el vector dinámico que rellenaremos con los datos del origen
 * @param origen El vector que queremos copiar
 */
template<class T>
VDinamico<T>::VDinamico(const VDinamico<T> &origen) {
    n_datos = origen.n_datos;
    mem = new T[n_datos];
    for (int i = 0; i < n_datos; i++) {
        mem[i] = origen.mem[i];
    }
};

/**
 * @brief Constructor copia parcial
 * @tparam T El tipo de los elementos almacenados en el vector dinámico que rellenaremos con los datos del origen.
 * @param origen El vector que queremos copiar
 * @param posicionInicial La posicion en la que iniciaremos la copia
 * @param numElementos El vector que se genera debe tener un tamaño máximo de numElementos.
 */
template<class T>
VDinamico<T>::VDinamico(const VDinamico<T> &origen, unsigned int posicionInicial, unsigned int numElementos) {
    n_datos = numElementos;
    mem = new T[n_datos];
    for (int i = 0; i < n_datos; i++) {
        mem[i] = origen.mem[i + posicionInicial];
    }
};

/**
 * @brief Operador =. Realiza una copia de los datos
 * @tparam T El tipo de los elementos almacenados en el vector dinámico.
 * @param v2 Referencia al objeto `VDinamico` a copiar.
 * @return T& Retorna una referencia al objeto actual después de realizar la asignación.
 */
template<class T>
T &VDinamico<T>::operator=(VDinamico &v2) {
    if (&v2 != this) {
        delete[] mem;
        n_datos = v2.tam;
        mem = new T[n_datos];
        for (int c = 0; c < n_datos; c++) {
            mem[c] = v2.mem[c];
        }
        return *this;
    }
};

/**
 * @brief Operador []. Permite acceder a los elementos del vector dinámico mediante el uso de índices
 * @tparam T El tipo de los elementos almacenados en el vector dinámico.
 * @param posicion La posición del elemento al que se desea acceder.
 * @return  T& Retorna una referencia al elemento en la posición solicitada.
 */
template<class T>
T &VDinamico<T>::operator[](unsigned int posicion) {
    if (posicion > n_datos) {
        throw std::out_of_range("La posicion introducida excede del rango");
    }
    return mem[posicion];
};

/**
 * @brief Utiliza el algoritmo estándar `std::sort` de la STL para ordenar los elementos en el vector de menor a mayor.
 * @tparam T El tipo de los elementos almacenados en el vector dinámico.
 */
template<class T>
void VDinamico<T>::ordenar() {
    std::sort(mem, mem + n_datos);
};

/**
 * Implementa el algoritmo de ordenación burbuja para ordenar los elementos de menor a mayor.
 * @tparam T  T El tipo de los elementos almacenados en el vector dinámico.
 */
template<class T>
void VDinamico<T>::ordenaBurbuja() {
    for (int i = 0; i < n_datos-1; ++i) {
        for (int j = 1; j < n_datos-i-1; ++j) {
            if (mem[j] > mem[j + 1]) {
                int aux = mem[j];
                mem[j] = mem[j + 1];
                mem[j + 1] = aux;
            }
        }
    }
};

/**
 * @brief Libera la memoria dinámica asignada para almacenar los elementos del vector
 * @tparam T El tipo de los elementos almacenados en el vector dinámico.
 */
template<class T>
VDinamico<T>::~VDinamico() {
    delete[] mem;
    mem = nullptr;
}

#endif //PRACICA_1_EEDD_VDINAMICO_H
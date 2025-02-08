//
// Created by lucia on 30/09/2024.
//

#ifndef VDINAMICO_H
#define VDINAMICO_H


#include <algorithm>
#include <cmath>

template<class T>

class VDinamico {

private:
    T *mem; //Vector de tipo T
   // long int n_datos; //Tamaño del vector
    long int tamFisico;
    long int tamLogico;

public:

    VDinamico(); //Constructor por defecto

    VDinamico(unsigned int tamlog); //constructor que inicia temlog

    VDinamico(const VDinamico<T> &origen); //Constructor copia

    VDinamico(const VDinamico<T> &origen, unsigned int posicionInicial,
                 unsigned int numElementos); //Constructor copia parcial
    //el vector que se genera debe tener un tamaño máximo de numElementos.

    long int getTamLogico() const {
        return tamLogico;
    }//getter tamaño logico

    T &operator=(VDinamico &arr); //Operador =

    T &operator[](unsigned int posicion); //Operador [] para acceder a un dato en la posicion indicada

    void insertar(const T& dato, unsigned int pos =UINT_MAX); //Inserta un dato en una posición dada

    void ordenar(); //Ordena de menor a mayor el vector mediante sort de la libreria algorithm

    int busquedaBin(T& dato);//Buscar un dato en el vector utilizando el metodo de búsqueda binaria o dicotómica

    void escribir(long int pos, const T &valor)
    { mem[pos] = valor; } //metodo escribir pata el main

    T borrar(unsigned int pos=UINT_MAX);

    virtual ~VDinamico(); //Destructor

};



/**
 * @brief Constructor por defecto que inicia el tamaño fisico a 1 y el logico a 0
 * @tparam T El tipo de los elementos almacenados en el vector dinámico.
 */
template<class T>
VDinamico<T>::VDinamico():tamFisico(1),tamLogico(0) {
    mem = new T[tamFisico];
}

/**
 * @brief Constructor parametrizado
 * @tparam T El tipo de los elementos almacenados en el vector dinámico.
 * @param tamlog tamaño logico inicial
 */
template <class T>
VDinamico<T>::VDinamico(unsigned int tamlog) : tamLogico(tamlog){
    int exponente=0;
    while(tamLogico>=pow(2,exponente)){
        ++exponente;
    }
    tamFisico=pow(2,exponente);
    mem=new T[tamFisico];
}

/**
 * @brief Constructor copia
 * @tparam T El tipo de los elementos almacenados en el vector dinámico que rellenaremos con los datos del origen
 * @param origen El vector que queremos copiar
 */
template<class T>
VDinamico<T>::VDinamico(const VDinamico<T> &origen) {
    tamFisico = origen.tamFisico;
    mem = new T[tamFisico];
    tamLogico=origen.tamLogico;
    for (int i = 0; i < tamLogico; i++) {
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
VDinamico<T>::VDinamico(const VDinamico<T>& origen, unsigned int posicionInicial, unsigned int numElementos) {
    tamLogico = numElementos;
    int exponente=0;
    while(tamLogico>=pow(2,exponente)){
        ++exponente;
    }
    tamFisico=pow(2,exponente);
    mem = new T[tamFisico];
    for (int i = 0; i < tamLogico; i++) {
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
        tamLogico = v2.tamLogico;
        tamFisico = v2.tamFisico;
        mem = new T[tamFisico];
        for (int c = 0; c < tamLogico; c++) {
            mem[c] = v2.mem[c];
        }
    }
    return *this;
};

/**
 * @brief Operador []. Permite acceder a los elementos del vector dinámico mediante el uso de índices
 * @tparam T El tipo de los elementos almacenados en el vector dinámico.
 * @param posicion La posición del elemento al que se desea acceder.
 * @return  T& Retorna una referencia al elemento en la posición solicitada.
 */
template<class T>
T &VDinamico<T>::operator[](unsigned int posicion) {
    if (posicion > tamLogico) {
        throw std::out_of_range("La posicion introducida excede del rango");
    }
    return mem[posicion];
};

//mal
template <class T>
void VDinamico<T>::insertar(const T& dato, unsigned int pos){
   /* if (posicion > tamLogico) {
        throw std::out_of_range("La posicion introducida excede del rango");
    }
    */
    if(tamLogico==tamFisico) {
        T *vaux;
        vaux= new T[tamFisico=tamFisico*2];
        for(int i=0;i<tamLogico;i++)
            vaux[i]=mem[i];
        delete[] mem;
        mem=vaux;
    }
    for(unsigned i=tamLogico;i>pos;i--){
        mem[i]=mem[i-1];
    }
    tamLogico++;
    mem[pos]=dato;
}

/**
 * @brief Elimina un dato de una posición intermedia
 * @tparam T  El tipo de los elementos almacenados en el vector dinámico.
 * @param pos posicion del dato que borramos
 * @return  T& Retorna una referencia al elemento en la posición borrada.
 */
template <class T>
T VDinamico<T>::borrar(unsigned int pos){
    T borrado=mem[pos];
    if(tamLogico*3<tamFisico) {
        tamFisico = tamFisico / 2;
        T *vaux = new T[tamFisico];
        for (unsigned i = 0; i < tamLogico; i++) {
            vaux[i] = mem[i];
        };
        delete[] mem;
        mem = vaux;
    }

    for(unsigned i=pos;i<tamLogico;i++){
        mem[i]=mem[i+1];
    };
    tamLogico--;
    return borrado;
}


/**
 * @brief Utiliza el algoritmo estándar `std::sort` de la STL para ordenar los elementos en el vector de menor a mayor.
 * @tparam T El tipo de los elementos almacenados en el vector dinámico.
 */
template<class T>
void VDinamico<T>::ordenar() {
    std::sort(mem, mem + tamLogico);
};


/**
 * @brief Busca un dato en el vector utilizando el método de búsqueda binaria o dicotómica
 * @tparam T El tipo de los elementos almacenados en el vector dinámico.
 * @param dato el dato que buscamos
 * @return la posicion del dato en el vector
 */
template<class T>
int VDinamico<T>::busquedaBin(T& dato){
    int inf = 0;
    int sup = tamLogico - 1;
    int curIn;
    while (inf <= sup) {
        curIn = (inf + sup) / 2;
        if (mem[curIn] == dato)
            return curIn;
        else if (mem[curIn] < dato) inf = curIn + 1;
        else sup = curIn - 1;
    }
    return -1;
}


/**
 * @brief Libera la memoria dinámica asignada para almacenar los elementos del vector
 * @tparam T El tipo de los elementos almacenados en el vector dinámico.
 */
template<class T>
VDinamico<T>::~VDinamico() {
    delete[] mem;
    mem = nullptr;
}



#endif //VDINAMICO_H

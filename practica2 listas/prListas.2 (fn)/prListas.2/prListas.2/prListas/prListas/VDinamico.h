//
// Created by lucia on 07/10/2024.
//

#ifndef VDINAMICO_H
#define VDINAMICO_H



#include <algorithm>
#include <cmath>
#include <stdexcept>

template<class T>

class VDinamico {

private:
    T *mem; //Vector de tipo T
   // long int n_datos; //Tamaño del vector
    long int tamFisico;
    long int tamLogico;

public:

    VDinamico();

    VDinamico(unsigned int tamlog);

    VDinamico(const VDinamico<T> &origen); //Constructor copia

    VDinamico(const VDinamico<T> &origen, unsigned int posicionInicial,
                 unsigned int numElementos); //Constructor copia parcial
    //el vector que se genera debe tener un tamaño máximo de numElementos.

    long int getTamLogico() const {
        return tamLogico;
    }

    T &operator=(VDinamico &arr); //Operador =

    T &operator[](unsigned int posicion); //Operador [] para acceder a un dato en la posicion indicada

    void insertar(const T& dato, unsigned int pos =UINT_MAX);

    void ordenar(); //Ordena de menor a mayor el vector mediante sort de la libreria algorithm

    int busquedaBin(T& dato);

    void escribir(long int pos, const T &valor)
    { mem[pos] = valor; }

    void Aumenta();
    void Decrementa();

    T borrar(unsigned int pos=UINT_MAX);
    T borrarModelo();
    virtual ~VDinamico(); //Destructor

};



/**
 * @brief Constructor por defecto que inicia el tamaño fisico a 1 y el logico a 0
 * @tparam T El tipo de los elementos almacenados en el vector dinámico.
 * @param n Es el tamaño del vector
 */
template<class T>
VDinamico<T>::VDinamico():tamFisico(1),tamLogico(0) {
    mem = new T[tamFisico];
}

/**
 * @brief Constructor parametrizado
 * @tparam T El tipo de los elementos almacenados en el vector dinámico.
 * @param n Es el tamaño del vector
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
VDinamico<T>::VDinamico(const VDinamico<T> &origen):tamFisico(origen.tamFisico), tamLogico(0) {
    mem = new T[tamFisico];
    for (int i = 0; i < tamFisico; i++) {
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
T &VDinamico<T>::   operator=(VDinamico &v2) {
    if (&v2 != this) {

        tamLogico = v2.tamLogico;
        tamFisico = v2.tamFisico;
        T* nuevoDat;
        nuevoDat = new T[tamFisico];
        for (int c = 0; c < tamLogico; c++) {
            nuevoDat[c] = v2.mem[c];
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


/**
 * @brief Inserta un numero en el vector y se incrementa el tam logico del vector.
 * @param dato lo que voy a agregar.
 * @param pos donde lo voy a agregar.
 */
template <class T>
void VDinamico<T>::insertar(const T &dato, unsigned int pos) {

    if(pos > tamFisico && pos != UINT_MAX){
        throw std::out_of_range ("VDinamico<T>::Insertar: La posicion no es valida.");
    }
    Aumenta();

    if(pos == UINT_MAX){
        mem[tamLogico] = dato;
        tamLogico++;
    }else{
        for(int i=tamLogico; i>pos; i--){
            mem[i] = mem[i-1];
        }
        tamLogico++;
        mem[pos] = dato;
    }

}

//metodo borrar

template <class T>
T VDinamico<T>::borrar(unsigned int pos){
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
    return mem[--tamLogico];
}


/**
 * @brief Utiliza el algoritmo estándar `std::sort` de la STL para ordenar los elementos en el vector de menor a mayor.
 * @tparam T El tipo de los elementos almacenados en el vector dinámico.
 */
template<class T>
void VDinamico<T>::ordenar() {
    std::sort(mem, mem + tamLogico);
};

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
 * @brief Aumenta el tamaño del vector, manteniendo el tamaño en potencia de 2.
 */
template <class T>
void VDinamico<T>:: Aumenta(){
    if(tamLogico == tamFisico){
        T *AuxV;
        tamFisico *= 2;          //sino tamf = tamf *2
        AuxV = new T[tamFisico];

        for(int i=0; i< tamLogico; i++){
            AuxV[i] = mem[i];
        }

        delete[] mem;
        mem = AuxV;

    }
}
/**
 * @brief Decrementa el tamaño fisico del vector en caso de que se ocupe menos de 1/3 del tamaño logico reservado, manteniendo pot de 2.
 */
template <class T>
void VDinamico<T>::Decrementa() {
    if(tamLogico*3 < tamFisico){    // es lo mismo que taml < tamf * 1/3
        tamFisico /= 2;        //la mitad del que tenia
        T *AuxV;
        AuxV = new T[tamFisico];

        for(int i=0; i< tamFisico; i++){
            AuxV[i] = mem[i];
        }

        delete[] mem;
        mem = AuxV;
    }
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

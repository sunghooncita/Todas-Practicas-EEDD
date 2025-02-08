//
// Created by Usuario on 27/10/2024.
//

#ifndef PR3_EEDD_LISTADENLAZADA_H
#define PR3_EEDD_LISTADENLAZADA_H
#include <stdexcept>


template <class T>
class Nodo {
public:
    T dato;
    Nodo *ant,*sig;
    Nodo(const T &aDato, Nodo *aAnt=0, Nodo *aSig=0):
            dato(aDato),ant(aAnt),sig(aSig) {
    }
};



template <class T>
class Iterador {
public:
    Nodo<T> *nodo;
    Iterador(Nodo<T> *aNodo): nodo(aNodo){}
    T iterador();
    bool hayAnterior(){ return nodo!=0; }
    bool haySiguiente(){ return nodo!=0; }
    void anterior() {nodo = nodo->ant; }
    void siguiente() {nodo = nodo->sig; }

    Nodo<T> * getnodo() const {
        return nodo;
    }

    T &dato() {return nodo->dato; }
};



template<class T>
class ListaDEnlazada {
private:
    Nodo <T> *cabecera, *cola;
    int tama;
public:
    ListaDEnlazada();
    ListaDEnlazada (const ListaDEnlazada<T> &lista);
    T &operator=(ListaDEnlazada &lista);
    T& inicio();
    T& fin();
    Iterador<T> iterador();
    void insertaInicio(const T &dato);
    void insertaFin(const T &dato);
    void inserta(Iterador<T> &i, T &dato);
    void borraInicio();
    void borraFinal();
    void borra(Iterador<T> &i);
    Iterador<T> final() { return Iterador<T>(cola); }
    int tam();
    ListaDEnlazada<T> concatena(const ListaDEnlazada<T> &l);
    ListaDEnlazada<T> operator+(const ListaDEnlazada<T> &l);
    T& leer(int n);
    ~ListaDEnlazada();
};


/**
 * @brief Constructor por defecto
 */
template<class T>
ListaDEnlazada<T>::ListaDEnlazada(): cabecera(0), cola(0),tama(0) {
}


/**
 * @brief Constructor de copia
 * @tparam T El tipo de los elementos almacenados en la lista doblemente enlazada.
 * @param origen la lista que copiamos
 */
template<class T>
ListaDEnlazada<T>::ListaDEnlazada(const ListaDEnlazada<T> &origen):tama(origen.tama) {
    if (origen.cola == nullptr) {
        throw std::out_of_range("La lista está vacia");
    }
    Nodo<T> *aux;
    aux= origen.cabecera;
    while (aux != nullptr) {
        insertaFin(aux->dato);
        aux = aux->sig;
    }
}


/**
 * @brief Operador =. Realiza una copia de los datos
 * @tparam T El tipo de los elementos almacenados en la lista doblemente enlazada.
 * @param lista Referencia al objeto `ListaDEnlazada` a copiar.
 * @return T& Retorna una referencia al objeto actual después de realizar la asignación.
 */
template<class T>
T &ListaDEnlazada<T>::operator=(ListaDEnlazada &lista) {
    if (lista.cola == nullptr) {
        throw std::out_of_range("La lista está vacia");
    }
    while (cola != nullptr) {
        borraFinal();
    }
    cabecera = cola = nullptr;
    Nodo<T> *aux;
    aux = lista.cabecera;
    while (aux != nullptr) {
        insertaFin(aux->dato);
        aux = aux->sig;
    }
    return *this;
}


/**
 * @brief Obtiene el elemento situado en el extremo inicial de la lista
 * @tparam T El tipo de los elementos almacenados en la lista doblemente enlazada.
 * @return Devuelve el dato inicial
 */
template<class T>
T& ListaDEnlazada<T>::inicio() {
    return cabecera->dato;
}


/**
 * @brief Obtiene el elemento situado en el extremo final de la lista
 * @tparam T El tipo de los elementos almacenados en la lista doblemente enlazada.
 * @return Devuelve el dato final
 */
template<class T>
T& ListaDEnlazada<T>::fin() {
    return cola->dato;
}


/**
 * @brief inicializamos el iterado???????????????????????????????
 * @tparam T El tipo de los elementos almacenados en la lista doblemente enlazada.
 * @return
 */
template<class T>
Iterador<T> ListaDEnlazada<T>::iterador() {
    return Iterador<T> (cabecera);
};


/**
 * @brief Inserta por el extremo inicial de la lista
 * @tparam T El tipo de los elementos almacenados en la lista doblemente enlazada.
 * @param dato Dato que instertamos en el inicio
 */
template<class T>
void ListaDEnlazada<T>::insertaInicio(const T &dato) {
    Nodo<T> *nuevo;
    nuevo = new Nodo<T>(dato,0,cabecera);
    if(cola==0)
        cola = nuevo;
    if (cabecera!=0)
        cabecera->ant = nuevo;
    cabecera = nuevo;
    tama++;
}


/**
 * @brief Inserta por el extremo final de la lista
 * @tparam T El tipo de los elementos almacenados en la lista doblemente enlazada.
 * @param dato Dato que instertamos en el final
 */
template <class T>
void ListaDEnlazada<T>::insertaFin(const T &dato) {

    Nodo<T> *nuevo;
    nuevo = new Nodo<T>(dato,cola,0);
    if (cabecera == 0) {
        cabecera = nuevo;
    }else
    if (cola !=0)
        cola->sig=nuevo;
    cola = nuevo;
    tama++;
}


/**
 * @brief Inserta un dato en la posición anterior apuntada por un iterador
 * @tparam T El tipo de los elementos almacenados en la lista doblemente enlazada.
 * @param i el iterador que apunta a la posicion
 * @param dato El dato que insertamos
 */
template <class T>
void ListaDEnlazada<T>::inserta(Iterador<T> &i, T &dato) {
    if (i.nodo == 0) {
        throw std::out_of_range("Iterador inexistente");
    }
    if (i.nodo==cabecera) {
        insertaInicio(dato);
    }else {
        Nodo<T> *nodo = new Nodo<T>(dato,i.nodo->ant,i.nodo);
        i.nodo->ant->sig = nodo;
        i.nodo->ant = nodo;
        tama++;
    }
}


/**
 * @brief Borra el elemento situado en el extremo inicial de la lista
 * @tparam T El tipo de los elementos almacenados en la lista doblemente enlazada.
 */
template <class T>
void ListaDEnlazada<T>::borraInicio() {
    Nodo <T> *borrado= cabecera;
    cabecera = cabecera->sig;
    delete borrado;
    if (cabecera == 0)
        cola = 0;
    else
        cabecera->ant=0;
}


/**
 * @brief Borra el elemento situado en el extremo final de la lista
 * @tparam T El tipo de los elementos almacenados en la lista doblemente enlazada.
 */
template <class T>
void ListaDEnlazada<T>::borraFinal() {
    Nodo <T> *borrado= cola;
    cola = cola->ant;
    delete borrado;
    tama--;
    if (cola == 0)
        cabecera = 0;
    else
        cola->sig=0;
}


/**
 * @brief Borra el elemento referenciado por un iterador
 * @tparam T El tipo de los elementos almacenados en la lista doblemente enlazada.
 * @param i el iterador que apunta a la posicion
 */
template <class T>
void ListaDEnlazada<T>::borra(Iterador<T> &i) {
    if (i.nodo==nullptr) {
        throw std::out_of_range("Iterador inexistente");
    }
    Nodo<T> *borrar = i.nodo;
    if(i.nodo==cabecera) {
        borraInicio();
    }
    if(i.nodo==cola) {
        borraFinal();
    }else {
        i.nodo->ant->sig = i.nodo->sig;
        i.nodo->sig->ant = i.nodo->ant;
        delete borrar;
        tama--;
    }
}


/**
 * @brief Devuelve el número de elementos de la lista
 * @tparam T El tipo de los elementos almacenados en la lista doblemente enlazada.
 * @return El tamaño de la lista
 */
template <class T>
int ListaDEnlazada<T>::tam() {
    return tama;
}






//lo hemos hecho igual al mas????????????????


/**
 * @brief Concatena la lista actual y la proporcionada por parámetro.
 * @tparam T El tipo de los elementos almacenados en la lista doblemente enlazada.
 * @param l la lista que concatenamos
 * @return Devuelve una nueva lista con la concatenación
 */
template <class T>
ListaDEnlazada<T> ListaDEnlazada<T>::concatena(const ListaDEnlazada<T> &l) {
    if(l.cola==nullptr) {
        throw std::out_of_range("Lista inexistente");
    }
    if(cola==nullptr) {
        throw std::out_of_range("Lista inexistente");
    }
    ListaDEnlazada<T> concatenada;
    Nodo<T> *aux;
    aux = cabecera;
    while (aux != nullptr) {
        concatenada.insertaFin(aux->dato);
        aux = aux->sig;
    }
    aux=l.cabecera;
    while (aux != nullptr) {
        concatenada.insertaFin(aux->dato);
        aux = aux->sig;
    }
    return concatenada;
}


/**
 * @brief Operador suma
 * @tparam T El tipo de los elementos almacenados en la lista doblemente enlazada.
 * @param l Lista que sumamos
 * @return Nueva lista con la suma realizada
 */
template <class T>
ListaDEnlazada<T> ListaDEnlazada<T>::operator+(const ListaDEnlazada<T> &l) {
    if(l.cola==nullptr) {
        throw std::out_of_range("Lista inexistente");
    }
    if(cola==nullptr) {
        throw std::out_of_range("Lista inexistente");
    }
    ListaDEnlazada<T> concatenada;
    Nodo<T> *aux;
    aux = cabecera;
    while (aux != nullptr) {
        concatenada.insertaFin(aux->dato);
        aux = aux->sig;
    }
    aux=l.cabecera;
    while (aux != nullptr) {
        concatenada.insertaFin(aux->dato);
        aux = aux->sig;
    }
    return concatenada;
}

template <class T>
T& ListaDEnlazada<T>:: leer(int n) {
    Nodo<T> *nodo = cabecera;
    while (n-- > 0 && nodo != 0) {
        nodo = nodo->sig;
    }
    if (nodo == 0)
        throw std::out_of_range("[listaEnlazada::leer] posición no válida");
    return nodo->dato;
}


/**
 * @brief Destructor
 * @tparam T El tipo de los elementos almacenados en la lista doblemente enlazada.
 */
template<class T>
ListaDEnlazada<T>::~ListaDEnlazada() {
    while (cola != nullptr) {
        borraFinal();
    }
}

#endif //PR3_EEDD_LISTADENLAZADA_H

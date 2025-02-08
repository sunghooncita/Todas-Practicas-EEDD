

#ifndef PR3_EEDD_AVL_H
#define PR3_EEDD_AVL_H
#include <iostream>
#include "VDinamico.h"
using namespace std;

template <typename T>
class NodoA {
public:
    NodoA<T> *izq, *der;
    T dato;
    char bal; // -1, 0 , 1 solo puede diferir en una unidad, balanceo= altura(izq(a)) - altura(der(a))
    NodoA(T &ele): izq(0), der(0), bal(0), dato(ele) {}

};

template <class T>
class AVL { //arbol avl es un arbol balanceado
    NodoA<T> *raiz;
    unsigned int numelementos;

    bool insertapriv(NodoA<T>* &c, T &dato);
    void rotDecha(NodoA<T>* &p);
    void rotIzqda(NodoA<T>* &p);
    T *buscaClave(T &dato, NodoA<T>* &p);
    void CopiaPreorden (NodoA<T> *p,  NodoA<T> *p2);
    void recorrePreorden (NodoA<T>* &p, VDinamico<T*> &vector);
    void recorreInorden (NodoA<T>* &p, VDinamico<T*> &vector);
    void BorrarPostorden (NodoA<T> *p);
    unsigned int altura(NodoA<T> *p);



public:
    AVL();
    AVL(AVL<T>& origen);
    T& operator=(AVL& dato);
    bool inserta(T &dato){
        if(insertapriv(raiz,dato)) {
            numelementos++;return true;
        }
        return false;
     }
    T* buscaRec(T &dato);
    T* buscaIt(T &dato);
    VDinamico<T*> recorrePreorden();
    VDinamico<T*> recorreInorden();
    unsigned int numElementos();
    unsigned int altura();
    ~AVL();
};


//PRIVATE:


/**
 * @brief Inserta un dato
 * @param c nuevo nodo que introduciermos
 * @param dato nuevo dato
 * @return devuelve entero para saber el balanceo
 */
template<typename T>
bool AVL<T>::insertapriv(NodoA<T>* &c, T &dato){
    NodoA<T> *p = c;
    int deltaH = 0;
    if (!p){
        p = new NodoA<T>(dato);
        c = p; deltaH=1;
    }
    else if ( p->dato < dato ){
        if (insertapriv(p->der, dato)){
            p->bal--;
            //numelementos++;
            if (p->bal == -1) deltaH=1;
            else if (p->bal == -2) {
                if (p->der->bal == 1) rotDecha(p->der);
                rotIzqda(c);
            } } }
    else if (dato < p->dato){
        if (insertapriv(p->izq, dato)){
            p->bal++;
            //numelementos++;
            if (p->bal==1) deltaH = 1;
            else if (p->bal == 2){
                if (p->izq->bal == -1) rotIzqda(p->izq);
                rotDecha(c);
            } } }
    return deltaH;
}


/**
 * @brief Rotación a la derecha en un nodo desequilibrado.
 * @param p Nodo en el que se hará la rotación.
 */
template<typename T>
void AVL<T>::rotDecha(NodoA<T>* &p){
    NodoA<T> *q = p, *l;
    p = l = q->izq;
    q->izq = l->der;
    l->der = q;
    q->bal--;
    if (l->bal > 0){
        q->bal -= l->bal;
    }
    l->bal--;
    if(q->bal < 0){
        l->bal -= -q->bal;
    }
};


/**
 * @brief Rotación a la izquierda en un nodo desequilibrado.
 * @param p Nodo en el que se hará la rotación.
 */
template<typename T>
void AVL<T>::rotIzqda(NodoA<T>* &p){
    NodoA<T> *q = p, *r;
    p = r = q->der;
    q->der = r->izq;
    r->izq = q;
    q->bal++;
    if (r->bal < 0) {
        q->bal += -r->bal;
    }
    r->bal++;
    if(q->bal > 0) {
        r->bal += q->bal;
    }
}


/**
 * @brief funcion recursiva para buscar un dato
 * @param dato dato que se buscara
 * @param p nodo que recorremos
 * @return devuelve un puntero al nodo que contiene el valor buscado, o nullptr
 */
template <typename T>
T *AVL<T>::buscaClave(T &dato, NodoA<T>* &p) {
    if (!p)
        return 0;
    else if (dato < p->dato)
        return buscaClave (dato, p->izq);
    else if (p-> dato < dato)
        return buscaClave (dato, p->der);
    else return &(p->dato);

}


/**
 * @brief Recorre el árbol en preorden y procesa cada nodo.
 * @param p Nodo actual.
 * @param nivel Nivel del nodo actual en el árbol.
 */
template <class T>
void AVL<T>::CopiaPreorden (NodoA<T> *p, NodoA<T> *p2){
    if(p2){
        p=new NodoA<T>(*p2);
        CopiaPreorden(p->izq, p2->izq);
        CopiaPreorden(p->der, p2->der);
    }

};


/**
 * @brief Recorre el árbol en preorden y procesa cada nodo.
 * @param p Nodo actual.
 * @param nivel Nivel del nodo actual en el árbol.
 */
template <class T>
void AVL<T>::recorrePreorden(NodoA<T>* &p, VDinamico<T*> &vector){
    if(p){
        vector.insertar(&(p->dato));
        recorrePreorden(p->izq, vector);
        recorrePreorden(p->der, vector);

    }
};


/**
 * @brief Recorre el árbol en inorden y procesa cada nodo.
 * @param p Nodo actual.
 * @param nivel Nivel del nodo actual en el árbol.
 */
template <class T>
void AVL<T>::recorreInorden(NodoA<T>* &p, VDinamico<T*> &vector){
    if(p){
        recorreInorden(p->izq, vector);
        vector.insertar(&(p->dato));
        recorreInorden(p->der, vector);
    }
};
/**
 * @brief Recorre el árbol en postorden y procesa cada nodo.
 * @param p Nodo actual.
 * @param nivel Nivel del nodo actual en el árbol.
 */
template <class T>
void AVL<T>::BorrarPostorden (NodoA<T> *p){
    if (p) {
        BorrarPostorden(p->izq);
        BorrarPostorden(p->der);
        delete p;
        p = nullptr;
    }
}


/**
 * @brief funcion que haya la altura
 * @param p nodo del arbol al que buscamos la altura
 * @return Altura del AVL
 */
template <class T>
unsigned int AVL<T>:: altura(NodoA<T> *p){
    if(!p){
        return 0;
    }
    unsigned int altizq=altura(p->izq);
    unsigned int altder=altura(p->der);
    if(altizq>altder){
        return (altizq + 1);
    }else{
        return (altder + 1);
    }
}


//PUBLIC:


/**
 * @brief Constructor por defecto
 */
template<class T>
AVL<T>::AVL(): raiz(0), numelementos(0) {
};


/**
 * @brief Constructor de copia.
 * @param origen Árbol AVL al que se le realizará la copia.
 */
template<class T>
AVL<T>::AVL( AVL<T> &origen) {
    CopiaPreorden(raiz, origen.raiz);
    numelementos=origen.numelementos;
}


/**
 * @brief Sobrecarga del operador de asignación.
 * @param dato Árbol que será asignado al actual.
 * @return Referencia al árbol AVL actual después de la asignación.
 */
template<class T>
T &AVL<T>::operator=(AVL &dato) {
    BorrarPostorden(raiz);
    CopiaPreorden(raiz, dato.raiz);
    numelementos=dato.numelementos;
};


/**
 * @brief funcion que busca un dato DE FORMA RECURSIVA
 * @param dato dato que buscamos
 * @return devuelve un puntero al nodo que contiene el valor buscado, o nullptr
 */
template<typename T>
T* AVL<T>::buscaRec(T &dato){
    return buscaClave(dato,raiz);
};


/**
 * @brief funcion que busca un dato DE FORMA ITERATIVA
 * @param dato dato que buscamos
 * @return devuelve un puntero al nodo que contiene el valor buscado, o nullptr
 */
template<typename T>
T* AVL<T>::buscaIt(T &dato){
    NodoA<T> *p=raiz;
    while(p!= nullptr){
        if(p->dato==dato)
            return (p->dato);
        else if(p->dato < dato)
            p = p->der;
        else
            p = p->izq;
    }
    return nullptr;
};


/**
 * @brief Recorrido en preorden
 * @return el vector dinamico recorrido
 */
template <typename T>
VDinamico<T*> AVL<T>::recorrePreorden() {
    VDinamico<T*> Vrecorrido;
    recorrePreorden(raiz,Vrecorrido);
    return Vrecorrido;
}


/**
 * @brief Recorrido en inorden
 * @return el vector dinamico recorrido
 */
template <typename T>
VDinamico<T*> AVL<T>::recorreInorden() {
    VDinamico<T*> Vrecorrido;
    recorreInorden(raiz,Vrecorrido);
    return Vrecorrido;
}


/**
 * @return Número de elementos del AVL
 */
template <class T>
unsigned int AVL<T>::numElementos(){
    return numelementos;
};


/**
 * @return Altura del AVL
 */
template <typename T>
unsigned int AVL<T>::altura() {
    if(raiz){
        return(altura(raiz)-1);
    }
    else{
        return 0;
    }
}

/**
 * @brief Destructor, libera todos los nodos del árbol.
 */
template <typename T>
AVL<T>::~AVL() {
    BorrarPostorden(raiz);
}


#endif //PR3_EEDD_AVL_H

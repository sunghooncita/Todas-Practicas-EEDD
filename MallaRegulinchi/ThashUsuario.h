//
// Created by lucia on 02/12/2024.
//

#ifndef THASHUSUARIO_H
#define THASHUSUARIO_H


#include "Usuario.h"
#include <list>
#include <string>

class Entrada {
public:
    unsigned long clave;
    bool estado_c1;         ///Si uno es True y el otro False la casilla estaba ocupada pero ahora esta libre
    bool estado_c2;         ///Si ambos son True la casilla estara libre, ambos Falses la casilla esta ocupada
    Usuario *dato;
    Entrada():estado_c1(true),estado_c2(true),clave(0) {dato = nullptr;}
    Entrada(long aClave, Usuario &aDato): clave(aClave) {dato = nullptr;}
};


class ThashUsuario {
private:
    std::vector<Entrada> table;

    unsigned long TAM_vector;
    unsigned int num_usuarios=0;          ///Numero de ususarios insertados
    unsigned int num_colisiones=0;        ///Veces total de colisiones
    unsigned long tamtotal;               ///Tamaño total de la tabla
    unsigned long MaxColisiones=0;        ///Cuantas veces colisiona el ultimo dato buscado
    unsigned long DatoMasColisiones=0;    ///Colisiones del dato que mas veces colisiona
    unsigned long numRedispersiones = 0;
    unsigned long numMas10=0;


    unsigned long hash(unsigned long clave,  int intento);
    unsigned long hash2(unsigned long clave,int intento);
    unsigned long hash3(unsigned long clave,int intento);
    unsigned long CalcularPrimoMen();
    unsigned long CalcularPrimoMay(unsigned long primMay);
    bool esPrimo(unsigned long numero);


public:
    ThashUsuario(int maxElementos, float lambda=0.65);
    ThashUsuario(ThashUsuario &thash);
    ThashUsuario operator=(ThashUsuario &thash);
    ~ThashUsuario();
    void redispersa(unsigned long tam);
    bool insertar(unsigned long clave, Usuario *usuario);
    Usuario* buscar(unsigned long clave, std::string &dato);
    bool borrar(unsigned long clave, std::string &dato);
    unsigned int numElementos();
    unsigned int maxColisiones();
    unsigned int numMax10();
    double promedioColisiones();
    float factorCarga();
    unsigned int tamTabla();
    unsigned long numColisiones();


};

#endif //THASHUSUARIO_H

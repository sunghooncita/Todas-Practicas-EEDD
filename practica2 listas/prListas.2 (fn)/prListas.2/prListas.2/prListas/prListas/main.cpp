#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Coche.h"
#include "ListaDEnlazada.h"
#include "VDinamico.h"
#include "Usuario.h"
#include "ReanelCar.h"

/**  @author Carlota Calderón Suárez ccs00064@red.ujaen.es
      @author Lucía Masats Aroza lma00072@red.ujaen.es */
int main(int argc, const char * argv[]) {

    //PROGRAMA DE PRUEBA 1

    //Crear una lista de enteros inicialmente vacía
    ListaDEnlazada<int> listaEnteros;

    //Insertar al final de la lista los valores crecientes desde 101 a 200
    for (int i = 100; i < 200; ++i) {
        listaEnteros.insertaFin(i);
    }

    //Insertar por el comienzo de la lista los valores decrecientes desde 98 a 1
    for (int i = 98; i >0; --i) {
        listaEnteros.insertaInicio(i);
    }

    //Insertar el dato 100 delante del 101
    int dato=100;
    Iterador<int> it = listaEnteros.iterador();
    while (it.haySiguiente()) {
        if (it.getnodo()->dato == 101) {
            listaEnteros.inserta(it, dato);
            break;
        }
        it.siguiente();
    }

    //Insertar el dato 99 detrás del 98
    dato=99;
    it = listaEnteros.iterador();
    while (it.haySiguiente()) {
        if (it.getnodo()->dato == 98) {
            it.siguiente();
            listaEnteros.inserta(it, dato);
            break;
        }
        it.siguiente();
    }

    //Mostrar la lista resultante por pantalla
    std::cout << "Lista resusltante: "<<std::endl;
    it = listaEnteros.iterador();
    while (it.haySiguiente()) {
        std::cout << it.getnodo()->dato << " ";
        it.siguiente();
    }

    //Borrar de la lista los 10 primeros y los 10 ultimos datos.
    for (int i = 0; i < 10; i++) {
         listaEnteros.borraFinal();
         listaEnteros.borraInicio();
    }
    std::cout <<std::endl<<std::endl<< "Lista resusltante tras borrar de la lista los 10 primeros y los 10 ultimos datos: "<<std::endl;
    it = listaEnteros.iterador();
    while (it.haySiguiente()) {
        std::cout << it.getnodo()->dato << " ";
        it.siguiente();
    }
    
    //Borrar de la lista todos los múltiplos de 10.
it = listaEnteros.iterador();
    do {
         if ((it.getnodo()->dato)%10 == 0) {
             listaEnteros.borra(it);
         }
         it.siguiente();
    }while(it.haySiguiente());
    std::cout <<std::endl<<std::endl<< "Lista resusltante tras borrar de la lista todos los multiplos de 10: "<<std::endl;
    it = listaEnteros.iterador();
    while (it.haySiguiente()) {
        std::cout << it.getnodo()->dato << " ";
        it.siguiente();
    }

    std::cout <<std::endl<<std::endl;


    //PROGRAMA DE PRUEBA 2

    //Instanciar las clases ReanelCar::Coche y Reanelcar::Usuario
    ReanelCar rean;

    //Alquilar a todos los usuarios cuyo nombre empiece por “W” un Ford Fiesta
    ListaDEnlazada<Usuario*> lisUsu(rean.buscarUsrNomb("W"));
    Iterador<Usuario*> iteUsu= lisUsu.iterador();
    VDinamico<Coche*> cochecito(rean.buscarCochModelo("Fiesta")) ;
    int cont = 0;
    while (iteUsu.haySiguiente()) {
        if(rean.alquilar(iteUsu.dato(),cochecito[cont])) {
            cont++;
        }
        iteUsu.siguiente();
    }


    //Eliminar de la lista Reanelcar::users a todos los usuarios que comienzan por “Wa”
    ListaDEnlazada<Usuario*> lisUsuBorrar(rean.buscarUsrNomb("Wa"));
    Iterador<Usuario*> iteUsuBorrar= lisUsuBorrar.iterador();
    Iterador<Usuario*> iteUsuBorrar2 = iteUsuBorrar;
    while (iteUsuBorrar.haySiguiente()) {
        iteUsuBorrar2 = iteUsuBorrar;
        rean.borrar(iteUsuBorrar2.dato());
        iteUsuBorrar.siguiente();
    }

    //Contar ahora cuántos usuarios quedan que comienzan con “W” y tengan un coche alquilado.
    cont = 0;
    ListaDEnlazada<Usuario*>lisUsuW(rean.buscarUsrNomb("W"));
    Iterador<Usuario*> iteUsuW = lisUsuW.iterador();
    while (iteUsuW.haySiguiente()) {
        if(iteUsuW.nodo->dato->getCoche()!= nullptr ){
            cont++;
        }
        iteUsuW.siguiente();
    }
    std::cout <<std::endl<< "Hay " << cont << " usuarios cuyo nombre empieza por W y tienen un coche alquilado." << std::endl;



    //Medir los tiempos de los dos métodos para encontrar todos los Ford “Fiesta”

    clock_t t_ini = clock();
    VDinamico<Coche*> c(rean.buscarCochModelo("Fiesta")) ;
    std::cout << std::endl<< "Tiempo de lectura del proceso de busqueda de la funcion Reanelcar::buscarCochModelo() : " << ((clock() - t_ini) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;


    clock_t t_ini1 = clock();
    VDinamico<Coche*> c2(rean.buscarCochModeloBinaria("Fiesta")) ;
    std::cout << std::endl<< "Tiempo de lectura del proceso de busqueda de la funcion Reanelcar::buscarCochModeloBinario() : " << ((clock() - t_ini1) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;

}
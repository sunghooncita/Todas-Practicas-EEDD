//
// Created by Usuario on 27/10/2024.
//


#include "ReanelCar.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stdexcept>


/**
 * @brief iniciamos Reanel Car junto con la lista de usuarios y el vector de coches rellenos
 */
ReanelCar::ReanelCar() {
    ///leo los ficheros y lo cargo



    std::ifstream is;
    std::stringstream  columnas;
    std::string fila;
    int contador=0;

    std::string id_matricula = "";
    std::string marca="";
    std::string modelo="";

    is.open("../coches.csv");

    if ( is.good() ) {

        clock_t t_ini = clock();
        int x=0;
        while ( getline(is, fila ) ) {

            //¿Se ha leído una nueva fila?
            if (fila!="") {

                columnas.str(fila);

                //formato de fila: id_matricula;marca;modelo;

                getline(columnas, id_matricula, ','); //leemos caracteres hasta encontrar y omitir ';'
                getline(columnas, marca,',');
                getline(columnas, modelo,' ');

                srand(static_cast<unsigned int>(time(0)));
                int numeroAleatorio = 20 + rand() % (100 - 20 + 1);

                Coche coche(id_matricula, marca, modelo, numeroAleatorio);
                if(cars.inserta(coche)) {
                    x++;
                }
                if(x==96) {
                    int j;
                }

                fila="";
                columnas.clear();
/*
                                std::cout << " Coche: ( Matricula=" << cars[contador].getId_matricula()
                                          << " Marca=" << v[contador].getMarca() << " Modelo=" << v[contador].getModelo()
                                          << ")" << std::endl;*/

                contador++;
            }
        }

        is.close();

        std::cout << "Tiempo lectura: " << ((clock() - t_ini) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;
    } else {
        std::cout << "Error de apertura en archivo" << std::endl;
    }



    std::ifstream iu;
    std::stringstream  columnas1;
    std::string fila1;
    int contador1=0;


    std::string nif= "";
    std::string clave= "";
    std::string nombre= "";
    std::string direccion= "";

    iu.open("../usuarios1.csv");//carpeta de proyecto
    if ( iu.good() ) {

        clock_t t_ini = clock();

        while ( getline(iu, fila1 ) ) {

            //¿Se ha leído una nueva fila?
            if (fila1!="") {

                columnas1.str(fila1);


                getline(columnas1, nif, ','); //leemos caracteres hasta encontrar y omitir ';'
                getline(columnas1, clave,',');
                getline(columnas1, nombre,',');
                getline(columnas1, direccion,' ');
                if(nif=="49496120X"){
                    int j=0;
                }
                Usuario usuario(nif, clave, nombre,direccion, nullptr);
                users.insertaFin(usuario);
                users.fin().setCoche(nullptr);
                users.fin().setLinkReanel(this);
                fila1="";
                columnas1.clear();
/*
                                std::cout << " Usuario: ( Nif=" <<users.leer(contador1).getNif()
                                          << " Clave=" << users.leer(contador1).getClave() << " Nombre=" << users.leer(contador1).getNombre()
                                          << " Direccion=" << users.leer(contador1).getDireccion() <<")" << std::endl;*/
            }

            contador1++;
        }

        is.close();

        std::cout << "Tiempo lectura: " << ((clock() - t_ini) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;
    } else {
        std::cout << "Error de apertura en archivo" << std::endl;
    }

}

/**
 * @brief Buscamos un usuario que coincida con el nif dado
 * @param nif
 * @return el usuario del vector que coincida
 */
Usuario *ReanelCar::buscarUsrNif(std::string nif) {
    Iterador<Usuario> iter = users.iterador();
    for (int i = 0; i < users.tam(); ++i) {
        if (nif == iter.getnodo()->dato.getNif()) {
            return &iter.getnodo()->dato;
        }
        iter.siguiente();
    }
}

/**
 * @brief Buscamos varios usuarios que coincida con el nombre dado
 * @param nom nombre
 * @return un vector con los usuarios del vector que coincida
 */
ListaDEnlazada<Usuario*> ReanelCar::buscarUsrNomb(std::string nom) {
    ListaDEnlazada<Usuario*> nuevo;
    Iterador<Usuario> iter = users.iterador();
    int longitud = nom.length();
    while (iter.haySiguiente()) {
        if (nom == iter.getnodo()->dato.getNombre().substr(0, longitud)) {
            Usuario *aniadir;
            aniadir = new Usuario(iter.getnodo()->dato.getNif(),iter.getnodo()->dato.getClave(),iter.getnodo()->dato.getNombre(),iter.getnodo()->dato.getDireccion(),nullptr);

            nuevo.insertaFin(aniadir);
        }
        iter.siguiente();
    }
    return nuevo;
}



/**
 * @brief Buscamos un coche que coincida con la matricula dado
 * @param mat matricula
 * @return el coche de la lista que coincida
 */
Coche * ReanelCar::buscarCochMat(std::string mat) {
    Coche *coch;
    Coche buscar;
    buscar.setId_matricula(mat);
    coch = cars.buscaRec(buscar);
    return coch;
}



/**
 * @brief Buscamos varrios coches que coincidan con el modelo dado
 * @param mod modelo
 * @return una lista con los coches de la lista que coincidan
 *//*
AVL<Coche *> ReanelCar::buscarCochModelo(std::string mod) {
    VDinamico<Coche *> nuevo;
    int cont=0;
    for (int i = 0; i < cars.getTamLogico(); ++i) {
        if (mod == cars[i].getModelo()) {
            nuevo.insertar(&cars[i],cont);
            cont++;
        }
    }
    return nuevo;
}*/

/**
 * @brief Buscamos varrios coches que coincidan con el modelo dado mediante una busqueda binaria
 * @param mod modelo
 * @return una lista con los coches de la lista que coincidan
 */
/*AVL<Coche *> ReanelCar::buscarCochModeloBinaria(std::string mod) {
    cars.ordenar();
    VDinamico<Coche *> nuevo;
    int cont = 0;
    int inf = 0;
    int sup = cars.getTamLogico() - 1;
    int curIn;
    while (inf <= sup) {
        curIn = (inf + sup) / 2;
        if (cars[curIn].getModelo() == mod) {
            nuevo.insertar(&cars[curIn]);
            // Busca hacia la izquierda
            int izquierda = curIn - 1;
            while (izquierda >= inf && cars[izquierda].getModelo() == mod) {
                nuevo.insertar(&cars[izquierda]);
                izquierda--;
            }
            // Busca hacia la derecha
            int derecha = curIn + 1;
            while (derecha <= sup && cars[derecha].getModelo() == mod) {
                nuevo.insertar(&cars[derecha]);
                derecha++;
            }
            return nuevo;
        } else if (cars[curIn].getModelo() < mod) {
            inf = curIn + 1;
        } else {
            sup = curIn - 1;
        }
    }
}*/


/**
 * @brief  enlaza al usuario y al coche que alquila.
 * @param usr usuario
 * @param c coche que enlazamos
 * @return un bool de si se ha podido hacer este enlace o no
 */
Coche* ReanelCar::alquilar(Usuario *usr){
    if (usr->getCoche() != nullptr) {
        throw std::out_of_range("Ya esta alquilando un coche");
    }
    return sities->getMaxBateria();
}


void ReanelCar::colocarCochePR(Coche *c){
    sities->addCoche(c);
};


/**
 * @brief borra el usuario que se indica de la lista
 * @param u usuario
 * @return un bool de si se ha podido eliminar o no
 */
bool ReanelCar::borrar(Usuario *u) {
    Iterador<Usuario> iter = users.iterador();
    while (iter.haySiguiente()) {
        if (iter.nodo->dato == *u) {
            users.borra(iter);
            return true;
        }
        iter.siguiente();
    }
    return false;
}



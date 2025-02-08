#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Coche.h"
#include "VDinamico.h"

/**  @author Carlota Calderon Suarez ccs00064@red.ujaen.es
      @author Lucia Masats Aroza lma00072@red.ujaen.es */

int main(int argc, const char * argv[]) {
    VDinamico<Coche> v(10000);

    std::ifstream is;
    std::stringstream  columnas;
    std::string fila;
    int contador=0;

    std::string id_matricula = "";
    std::string marca="";
    std::string modelo="";


    is.open("../coches.csv"); //carpeta de proyecto
    if ( is.good() ) {

        clock_t t_ini = clock();

        while ( getline(is, fila ) ) {

            //¿Se ha leído una nueva fila?
            if (fila!="") {

                columnas.str(fila);

                //formato de fila: id_matricula;marca;modelo;

                getline(columnas, id_matricula, ','); //leemos caracteres hasta encontrar y omitir ';'
                getline(columnas, marca,',');
                getline(columnas, modelo,' ');

                Coche coche(id_matricula, marca, modelo);
                //Coche coche;
                v.escribir(contador,coche);

                fila="";
                columnas.clear();

                std::cout << " Coche: ( Matricula=" << v[contador].getId_matricula()
                          << " Marca=" << v[contador].getMarca() << " Modelo=" << v[contador].getModelo()
                          << ")" << std::endl;

                contador++;
            }
        }

        is.close();

        std::cout << "Tiempo lectura: " << ((clock() - t_ini) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;
    } else {
        std::cout << "Error de apertura en archivo" << std::endl;
    }


    clock_t t_ini = clock();

    std::cout << "\nOrdenacion de los 30 primeros coches : " << std::endl;

    v.ordenar();

    for(int i=0;i<30;i++) {
        std::cout << " Coche: ( Matricula=" << v[i].getId_matricula()
                          << " Marca=" << v[i].getMarca() << " Modelo=" << v[i].getModelo()
                          << ")" << std::endl;
    }

    std::cout << "Tiempo lectura: " << ((clock() - t_ini) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;


    t_ini = clock();

    std::cout << "\nBusqueda de coches :" << std::endl;

    Coche busqueda;
    std::string cocheBuscar[]={"4562 HWG","6574 DJD","8326 CBR","4672 KTS", "2838 GBT"};
    for (int i = 0; i < 5; i++) {
        busqueda.setId_matricula(cocheBuscar[i]);
        int dato=v.busquedaBin(busqueda);
        if(dato != -1) {
            std::cout << " Coche: ( Matricula=" << v[dato].getId_matricula()
                              << " Marca=" << v[dato].getMarca() << " Modelo=" << v[dato].getModelo()
                              << ")  Posicion : " <<dato<< std::endl;
        }else {
            std::cout << "Matricula no encontrada.";
        }
    }
    std::cout << "Tiempo lectura: " << ((clock() - t_ini) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;


    t_ini = clock();

    VDinamico<Coche> vGolf;
    int cont=0, tam_v=v.getTamLogico();

    std::cout << "\nBorrar  GOLF : " << std::endl;

    for (int j = 0; j < v.getTamLogico(); j++) {
        if (v[j].getModelo() == "Golf") {
        vGolf.insertar(v.borrar(j), cont);
        cont++;
        }
    }


    for(int i = 0; i < 20; i++) {
        std::cout << " Coche: ( Matricula=" << vGolf[i].getId_matricula()
                              << " Marca=" << vGolf[i].getMarca() << " Modelo=" << vGolf[i].getModelo()
                              << ")" << std::endl;
    }

    std::cout << "\nTamaño del vector antes de borrar los Golf : " << tam_v<< std::endl;
    std::cout << "Tamaño del vector despues de borrar los Golf : " << v.getTamLogico()<< std::endl;
    std::cout << "Tamaño del vector de los Golf : " << vGolf.getTamLogico()<< std::endl;

    std::cout << "Tiempo lectura: " << ((clock() - t_ini) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;


    return 0;
}

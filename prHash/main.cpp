#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <list>
#include <map>
#include <vector>
#include <stdlib.h>

#include "Coche.h"
#include "Usuario.h"
#include "ReanelCar.h"


using namespace std;

/**  @author Carlota Calderón Suárez ccs00064@red.ujaen.es
      @author Lucía Masats Aroza lma00072@red.ujaen.es */

int main(int argc, const char * argv[]) {


    //PROGRAMA DE PRUEBA 1

    //Ajuste de la tabla completado en el md
    std::cout<<"PROGRAMA DE PRUEBA 1:"<<endl<<endl;
    ReanelCar rcar;
    rcar.mostrarEstadoTabla();

    //Prueba de rendimiento

    list<Usuario*> listaW = rcar.buscarUsrNomb("W");
    list<string> nifsW=rcar.ObtenerNifs(listaW);

    std::cout<<endl<<endl;

    clock_t t_ini = clock();
    for (auto i = nifsW.begin(); i != nifsW.end(); ++i) {
        rcar.buscarUsrNif(*i);
    }
    std::cout << "Tiempo lectura de la busqueda mediante lista: " << ((clock() - t_ini) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;

    t_ini = clock();
    for (auto i = nifsW.begin(); i != nifsW.end(); ++i) {
        rcar.buscarUsrNifTHash(*i);
    }
    std::cout << "Tiempo lectura de la busqueda mediante la tabla hash: " << ((clock() - t_ini) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;



    //PROGRAMA DE PRUEBA 2

    std::cout<<endl<<endl<<endl<<"PROGRAMA DE PRUEBA 2:"<<endl<<endl;

    std::cout << "Ejercicio 3: " << std::endl;
    rcar.asociaCocheAPRecarga();

    rcar.asignaCocheAUsrYCreaTrayecto(listaW);

    std::cout <<"Los datos de los 10 primeros usuarios que empiezan por W son:\n ";
    int cont=0;
    for(auto iterL = listaW.begin(); iterL != listaW.end();iterL++) {
        std::cout << std::endl << cont << ". Nif: " << (*iterL)->getNif()
                  << "\n" << "   Clave: " << (*iterL)->getClave()
                  << "\n" << "   Nombre: " << (*iterL)->getNombre()
                  << "\n" << "   Direccion: " << (*iterL)->getDireccion()
                  << "\n" << "   Coche alquilado: " << (*iterL)->getCoche()->getId_matricula()
                  << "\n" << "   Origen del Trayecto: " << (*iterL)->getCoche()->getPuntoR()->getId()
                  << "\n" << "   Destino del Trayecto: " << (*iterL)->getCoche()->getPuntoD()->getId() << std::endl;
        cont++;
        if (cont == 10) break;
    }

    std::cout <<std::endl<<std::endl<< "Ejercicio 4: " << std::endl;
    std::list<Usuario*> lusuWi;
    lusuWi=rcar.buscarUsrNomb("Wi");

    rcar.aparcarCochesRetraso(lusuWi,2);

    std::cout <<std::endl<<std::endl<< "Ejercicio 5: " << std::endl;

    Usuario* usus8 = rcar.buscarUsrNifTHash("84538382N");
    std::cout << std::endl  << ".  Nif: " << (usus8)->getNif()
              << "\n" << "   Clave: " << (usus8)->getClave()
              << "\n" << "   Nombre: " << (usus8)->getNombre()
              << "\n" << "   Direccion: " << (usus8)->getDireccion()
              << "\n" << "   Coche alquilado: " << (usus8)->getCoche()->getId_matricula()
              << "\n" << "   Origen del Trayecto: " << (usus8)->getCoche()->getPuntoR()->getId()
              << "\n" << "   Destino del Trayecto: " << (usus8)->getCoche()->getPuntoD()->getId() << std::endl;

    std::cout <<std::endl<<std::endl<< "Ejercicio 6: " << std::endl;
    rcar.borrarUsuarioTHash("84538382N");
    if (rcar.buscarUsrNifTHash("84538382N") == nullptr) {
        std::cout << "El usuario no se encuentra en la lista" << std::endl;
        rcar.insertarUser(usus8);
    } else {
        std::cout << "Usuario encontrado con éxito!!" << std::endl;

    }



    std::cout <<std::endl<<std::endl<< "Ejercicio 7: " << std::endl;
    std::list<Usuario*> lusuWa;
    lusuWa=rcar.buscarUsrNomb("Wa");
    std::list<std::string> nifsLusuwa;
    nifsLusuwa = rcar.ObtenerNifs(lusuWa);

    std::cout << "Numero antes de borrar Wa: " << rcar.numeroUsuariosTH() << std::endl;
    for (auto i = nifsLusuwa.begin(); i != nifsLusuwa.end(); i++) {
        rcar.borrarUsuarioTHash(*i);
    }
    std::cout << "Numeros despues de borrar Wa: " << rcar.numeroUsuariosTH()<< std::endl;

    std::cout <<std::endl<<std::endl<< "Ejercicio 8: " << std::endl;

    rcar.asignaCocheAUsrYCreaTrayecto(lusuWi);

    std::cout <<"Los datos de los 10 primeros usuarios que empiezan por Wi son:\n ";
    int conti=0;
    for(auto iterL = lusuWi.begin(); iterL != lusuWi.end();iterL++) {
        std::cout << std::endl << conti << ".  Nif: " << (*iterL)->getNif()
                  << "\n" << "   Clave: " << (*iterL)->getClave()
                  << "\n" << "   Nombre: " << (*iterL)->getNombre()
                  << "\n" << "   Direccion: " << (*iterL)->getDireccion()
                  << "\n" << "   Coche alquilado: " << (*iterL)->getCoche()->getId_matricula()
                  << "\n" << "   Origen del Trayecto: " << (*iterL)->getCoche()->getPuntoR()->getId()
                  << "\n" << "   Destino del Trayecto: " << (*iterL)->getCoche()->getPuntoD()->getId() << std::endl;
        conti++;
        if (conti == 10) break;
    }

    std::cout <<std::endl<<std::endl<< "Ejercicio 9: " << std::endl;

    std::list<Usuario*> lusuWil;
    lusuWil=rcar.buscarUsrNomb("Wil");
    rcar.aparcarCochesRetraso(lusuWil,4);

    return 0;
}
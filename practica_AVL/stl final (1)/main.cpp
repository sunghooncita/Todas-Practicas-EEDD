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


    //PROGRAMA DE PRUEBA



    // 1.
    std::cout << "Ejercicio 1: " << std::endl;
    ReanelCar rcar;

    rcar.Ejercicio1();



    //2.
    std::cout <<std::endl<<std::endl<< "Ejercicio 2: " << std::endl;
    std::list<Usuario*> lusu;
    lusu=rcar.buscarUsrNomb("W");

    rcar.Ejercicio2(lusu);
    int cont=0;

    std::cout <<"Los datos de los 10 primeros usuarios que empiezan por W son:\n ";

    for(auto iterL = lusu.begin(); iterL != lusu.end();iterL++){
        std::cout <<std::endl<<cont++<< ".  Nif: " << (*iterL)->getNif()
                  <<"\n"<< "   Clave: " << (*iterL)->getClave()
                  <<"\n"<< "   Nombre: " << (*iterL)->getNombre()
                  <<"\n"<< "   Direccion: " << (*iterL)->getDireccion()
                  <<"\n"<< "   Coche alquilado: " << (*iterL)->getCoche()->getId_matricula()
                  <<"\n"<< "   Origen del Trayecto: "   <<   (*iterL)->getCoche()->getPuntoR()->getId()
                  <<"\n"<< "   Destino del Trayecto: "   <<   (*iterL)->getCoche()->getPuntoD()->getId() << std::endl;
        cont++;
        if(cont == 10) break;
    }



    //3.
    std::cout <<std::endl<<std::endl<< "Ejercicio 3: " << std::endl;
    std::list<Usuario*> lusuWa;
    lusuWa=rcar.buscarUsrNomb("Wa");

    rcar.Ejercicio3(lusuWa);


    //4.

    std::cout <<std::endl<<std::endl<< "Ejercicio 4: " << std::endl;

    rcar.Ejercicio4(lusuWa);
    /*
    for(auto iterL = lusuWa.begin(); iterL != lusuWa.end();iterL++){
        std::cout <<std::endl<<cont<< ".  Nif: " << (*iterL)->getNif()
                  <<"\n"<< "   Clave: " << (*iterL)->getClave()
                  <<"\n"<< "   Nombre: " << (*iterL)->getNombre()
                  <<"\n"<< "   Direccion: " << (*iterL)->getDireccion()
                  <<"\n"<< "   Coche alquilado: " << (*iterL)->getCoche()->getId_matricula()
                  <<"\n"<< "   Origen del Trayecto: "   <<   (*iterL)->getCoche()->getPuntoR()->getId()
                  <<"\n"<< "   Destino del Trayecto: "   <<   (*iterL)->getCoche()->getPuntoD()->getId() << std::endl;
        cont++;
        if(cont == 10) break;
    }
*/


    //5 + Trabajo en parejas.

    //Para hacer esta parte usamos el metodo creado en el apartado con parejas y ahi los probamos

    std::cout <<std::endl<<std::endl<< "Ejercicio 5: " << std::endl;

    Fecha fech (29,10,2024);
    std::vector<pair<Usuario*,Trayecto*>> vectorcillo = rcar.trayectosEnFecha(fech);
    std::string nifC = vectorcillo[0].first->getNif();
    cont = 0;
    bool entro = false;
    for(int i=1;i<vectorcillo.size();i++){
        if(nifC == vectorcillo[i].first->getNif() && entro == false){
            cont++;
            entro = true;
        }if(nifC != vectorcillo[i].first->getNif()){
            nifC = vectorcillo[i].first->getNif();
            entro = false;
        }
    }

    std::cout<<"El número de usuarios que han realizado más de un trayecto hoy es de: " << cont << std::endl;


    //6.

    std::cout <<std::endl<<std::endl<< "Ejercicio 6: " << std::endl;

    Coche* cocheMat;
    cocheMat= rcar.buscarCochMat("6698 XKM");
    std::cout<<std::endl<<"Datos de el coche con matricula 6698 XKM : "<<
    "\n\n   Marca: "<<cocheMat->getMarca()<<
    "\n   Modelo: "<<cocheMat->getModelo()<<
    "\n   Bateria: "<<cocheMat->getBateria();
    /* if (cocheMat->getPuntoR()!=nullptr){
    }else std::cout<<"\n No esta siendo alquilado ";*/
    if (cocheMat->getPuntoR()!=nullptr){
        std::cout<<"\n   Esta cargando en el punto de recarga con id: "<<cocheMat->getPuntoR()->getId()
        <<"\n   En este se encuentan cargando los coches: ";
        for (auto i = cocheMat->getPuntoR()->getCoches()->begin(); i != cocheMat->getPuntoR()->getCoches()->end(); ++i) {
            std::cout<<"\n   Matricula: "<<(*i).second->getId_matricula();
        }
    }else std::cout<<"\n   No se encuentra cargando en ningun punto de recarga ";


return 0;
}
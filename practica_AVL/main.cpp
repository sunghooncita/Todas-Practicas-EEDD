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

    ReanelCar rcar;
    std::cout<< "La altura del arbol AVL es de: "<< rcar.cars.altura()<<endl<<endl;

    VDinamico<Coche*> Vcoches  = rcar.cars.recorreInorden();

    std::cout<< "Estas son las 1000 primeras matriculas recorridas en inorden: "<<endl;

    for (int i = 0; i < 1000; ++i) {
        std::cout<<endl<< "Matricula: "<< Vcoches[i]->getId_matricula();
    }

    std::string lc[]={"6028 ZXL", "6795 MLS", "0209 GZT", "2171 ZDC",
"4649 HJH", "8953 YRT", "6698 XKM", "5830 MNZ", "7690 DKN", "6557 BGW",
"4680 BBC", "1045 GYK", "9400 HRX", "9856 FLG", "3704 RWK", "8514 HLL",
"7048 YYY", "2910 ZXN", "7358 DZN", "2966 LTL", "4268 MGX", "4155 DFX",
"7891 XXB", "2140 SNB", "9838 THH", "3168 LNC", "9150 HNB", "1691 FHS"};

    Coche coche[50];
    for (int i = 0; i < 28; ++i) {
        coche[i].setId_matricula(lc[i]);
    }

    Coche *cochete;
    for(int i=0;i<50;i++) {
        cochete = rcar.buscarCochMat(coche[i].getId_matricula());
        rcar.colocarCochePR(cochete);
    }

    std::cout<< "\n\nEstas son las matriculas de los coches que se encuentarn en el punto de recarga: "<<endl;


    for (int i = 0; i < 28; ++i) {
        std::cout<<endl<< "Matricula: "<< rcar.sities->getCoches()[i]->getId_matricula();
    }

    Usuario *usu = rcar.buscarUsrNif("91477235Q");
    usu->cogeCoche();

    if(usu->getCoche()) {
        cout << "\n\nEl usuario tiene el coche: " << usu->getCoche()->getId_matricula() <<" con "<<usu->getCoche()->getBateria()<< " de bateria."<< endl;
    }


    std::cout<< "\n\nEstas son las 1000 primeras matriculas recorridas en preorden: "<<endl;

    VDinamico<Coche*> Vcoches2  = rcar.cars.recorrePreorden();
    for (int i = 0; i < 1000; ++i) {
        std::cout<<endl<< "Matricula: "<< Vcoches2[i]->getId_matricula();
    }


}

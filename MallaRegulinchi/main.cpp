
#include <fstream>
#include <iostream>
#include <vector>
#include "img.h"
#include "ReanelCar.h"

#include <math.h>

using namespace std;

/**  @author Carlota Calderón Suárez ccs00064@red.ujaen.es
      @author Lucía Masats Aroza lma00072@red.ujaen.es */


int main (int argc, const char * argv[]) {
    std::cout << endl << endl << endl << "PROGRAMA DE PRUEBA:" << endl << endl;

    std::cout << "Ejercicio 1: " << std::endl;
    //ejercicio 1:
    ReanelCar rcar;

    //ejercicio 2 y 3:

    std::cout << std::endl << std::endl << "Ejercicio 2: " << std::endl;
    std::cout << std::endl << std::endl << "Ejercicio 3: " << std::endl;


    // inicializamos la malla en el constructor por defecto

    //ejercicio 4:

    std::cout << std::endl << std::endl << "Ejercicio 4: " << std::endl;

    rcar.asociaCocheAPRecarga();

    //ejercicio 5:

    std::cout << std::endl << std::endl << "Ejercicio 5: " << std::endl;


    std::list<Usuario *> usuariosA = rcar.buscarUsrNomb("A");
    rcar.asignaCocheAUsrYCreaTrayecto(usuariosA);
    std::cout << "Los datos de los 10 primeros usuarios que empiezan por A son:\n ";
    int cont = 0;

    for (auto iterL = usuariosA.begin(); iterL != usuariosA.end(); iterL++) {
        std::cout << std::endl << cont << ".  Nif: " << (*iterL)->getNif()
                  << "\n" << "   Nombre: " << (*iterL)->getNombre()
                  << "\n" << "   Direccion: " << (*iterL)->getDireccion()
                  << "\n" << "   Coche alquilado: " << (*iterL)->getCoche()->getId_matricula()
                  << "\n" << "   Origen del Trayecto: " << (*iterL)->getCoche()->getPuntoR()->getId()
                  << "\n" << "   Destino del Trayecto: " << (*iterL)->getCoche()->getPuntoD()->getId() << std::endl;
        cont++;
        if (cont == 10) break;
    }

    //ejercicio 6:

    std::cout << std::endl << std::endl << "Ejercicio 6: " << std::endl;


    std::list<Usuario *> usuariosB = rcar.buscarUsrNomb("B");
    rcar.asignaCocheAUsrYCreaTrayecto(usuariosB);
    std::cout << "Los datos de los 10 primeros usuarios que empiezan por B son:\n ";
    cont = 0;

    for (auto iterL = usuariosB.begin(); iterL != usuariosB.end(); iterL++) {
        std::cout << std::endl << cont << ".  Nif: " << (*iterL)->getNif()
                  << "\n" << "   Nombre: " << (*iterL)->getNombre()
                  << "\n" << "   Direccion: " << (*iterL)->getDireccion()
                  << "\n" << "   Coche alquilado: " << (*iterL)->getCoche()->getId_matricula()
                  << "\n" << "   Origen del Trayecto: " << (*iterL)->getCoche()->getPuntoR()->getId()
                  << "\n" << "   Destino del Trayecto: " << (*iterL)->getCoche()->getPuntoD()->getId() << std::endl;
        cont++;
        if (cont == 10) break;
    }


    //ejercicio 7:

    std::cout << std::endl << std::endl << "Ejercicio 7: " << std::endl;

    rcar.aparcarCochesMalla(usuariosB);


    //ejercicio 8:

    std::cout << std::endl << std::endl << "Ejercicio 8: " << std::endl;


    rcar.aparcarCochesPosicion(usuariosA);

    //ejercicio 9:

    std::cout << std::endl << std::endl << "Ejercicio 9: " << std::endl;

    UTM jaen(37.7692200, -3.7902800);
    /*  std::vector<Coche*> CochesJaen= rcar.buscarCochesRadio(jaen,10);

      std::cout <<"Los datos de los 10 coches aparcados en un radio de 10 kms de Jaén capital son:\n ";
      cont=0;

      for(auto iterL = CochesJaen.begin(); iterL != CochesJaen.end();iterL++){
          std::cout <<std::endl<<cont<< ".  Matricula: " << (*iterL)->getId_matricula()
                    <<"\n"<< "   Modelo: " << (*iterL)->getModelo()
                    <<"\n"<< "   Marca: " << (*iterL)->getMarca()
                    <<"\n"<< "   Bateria: " << (*iterL)->getBateria()
                    <<"\n"<< "   Posicion: Latitud ="   <<   (*iterL)->getPuntoR()->getPos().getLatitud() << " y Longitud ="   <<   (*iterL)->getPuntoR()->getPos().getLongitud() << std::endl;
          cont++;
          if(cont == 10) break;
      }

      Coche* masCerca= rcar.buscarCochesMasCarcano(jaen);

      std::cout <<"El coche más cercano a Jaén capital es:\n ";
      std::cout <<std::endl<<cont<< ".  Matricula: " << masCerca->getId_matricula()
                <<"\n"<< "   Modelo: " << masCerca->getModelo()
                <<"\n"<< "   Marca: " << masCerca->getMarca()
                <<"\n"<< "   Bateria: " << masCerca->getBateria()
                <<"\n"<< "   Posicion: Latitud ="   <<  masCerca->getPuntoR()->getPos().getLatitud() << " y Longitud ="   <<   masCerca->getPuntoR()->getPos().getLongitud() << std::endl;

  */
    //ejercicio 10:

    std::cout << std::endl << std::endl << "Ejercicio 10: " << std::endl;

    PuntoRecarga *punto43 = nullptr;
    for (auto itera = rcar.getSities().begin(); itera != rcar.getSities().end(); itera++) {
        if (itera->getId() == 43) {
            punto43 = &*itera;
        }
    }
    Coche *masCercaID = rcar.buscarCochesMasCarcano(punto43->getPos());

    std::cout << "El coche más cercano al punto de recarga con ID 43 es:\n ";
    std::cout << std::endl << cont << ".  Matricula: " << masCercaID->getId_matricula()
              << "\n" << "   Modelo: " << masCercaID->getModelo()
              << "\n" << "   Marca: " << masCercaID->getMarca()
              << "\n" << "   Bateria: " << masCercaID->getBateria()
              << "\n" << "   Posicion: Latitud =" << masCercaID->getPuntoR()->getPos().getLatitud() << " y Longitud ="
              << masCercaID->getPuntoR()->getPos().getLongitud() << std::endl;



    //ejercicio 11:

    std::cout << std::endl << std::endl << "Ejercicio 11: " << std::endl;


    std::vector<Coche *> CochesJaen15 = rcar.buscarCochesRadio(jaen, 15);

    std::pair<int, PuntoRecarga *> PntMasCoches = rcar.PRmasCochesRadio(CochesJaen15);
    std::cout << "El  punto de recarga tiene más coches en un radio de 15km de Jaén Capital es:\n ";
    std::cout << std::endl << cont << ".  ID: " << PntMasCoches.second->getId()
              << "\n" << "   Numero de Coches: " << PntMasCoches.first
              << "\n" << "   Posicion: Latitud =" << PntMasCoches.second->getPos().getLatitud() << " y Longitud ="
              << PntMasCoches.second->getPos().getLongitud() << std::endl;


    //no sabiamos hacer la segunda parte



    //trabajo por parejas:

    std::cout << std::endl << std::endl << "TRABAJO POR PAREJAS: " << std::endl;

    UTM posisao(37.79143,-3.77716);
    PuntoRecarga* puntique= nullptr;
    for(auto itera = rcar.getSities().begin();itera!=rcar.getSities().end();itera++){
        if(itera->getPos()==posisao){
            puntique=&*itera;
        }
    }

    if(puntique->getNumCoches()>rcar.getLocate().promedioElementosPorCelda()){
        PuntoRecarga* NuevoPuntique();
        NuevoPuntique()->setPos(posisao);
        rcar.getSities().push_back(*NuevoPuntique());
        std::cout << "Se ha insertado correctamente. " << std::endl;

    }


















/*
    RGBColor blanco (255,255,255);

    Img img(700, 1300, blanco); // rectángulo de 700 filas x 1300 columnas

    int nfilas = img.numFilas();
    int ncol = img.numColumnas();


    cout << "Imagen creada con " << nfilas << "filas y " << ncol << " columnas." <<endl;

    int r = 0; // azul
    int g = 0;
    int b = 255;

    // sabemos el tamaño de la caja envolvente de los datos, pero volver a calcular

    double minlat = 35.86688;
    double maxlat = 43.272616;
    double minlon = -9.99443;
    double maxlon = 3.98926;


    // Calculamos el número de pixeles asociados a un grado

    cout << "lat: xmin = " << minlon <<  ", " << "xmax = " << maxlon << endl;
    cout << "lon: ymin = " << minlat <<  ", " << "ymax = " << maxlat << endl;

    double rangoy = maxlat - minlat;
    double rangox = maxlon - minlon;

    cout << "rango x = " << rangox << endl;
    cout << "rango y = " << rangoy << endl;

    cout << "nfilas = " << nfilas << endl;
    cout << "ncol = " << ncol << endl;

    double pixelPorGradoY = (double) (nfilas - 1) / rangoy;
    double pixelPorGradoX = (double) (ncol - 1) / rangox;


    cout << "Pixel por Grado X = " << pixelPorGradoX << endl;
    cout << "Pixel por Grado Y = " << pixelPorGradoY << endl;


    // elegimos las coordenada de un recuadro cualquiera

    double lat1 = 40;
    double lon1 = -8;

    double lat2 = 42.0;
    double lon2 = -5.0;

    //Nota: invertir coordenada Y (latitudes)
    img.pintarRecuadro( ((lon1 - minlon) * pixelPorGradoX), nfilas -1 - (lat1 - minlat) * pixelPorGradoY,
                        ((lon2 - minlon) * pixelPorGradoX), nfilas -1 - (lat2 - minlat) * pixelPorGradoY, 255, 0, 0);


    // ejemplo de punto que debe estar por el centro, lo pintamos acto seguido

    double vlat = 39.569748;
    double vlon = -3.002585;

    int posY = nfilas -1 - (vlat - minlat) * pixelPorGradoY; //Invertir coordenada Y
    int posX = ((vlon -minlon) * pixelPorGradoX);
    img.pintarPixelGrande(posX,posY,r,g,b);
    //img.pintarPixel(posX,posY,r,g,b);


    try {
    img.guardar("../mapaResultado.ppm");
    }
    catch(ErrorEscrituraFichero &e) {
    	cout << "Error al escribir fichero" << endl;
    	return 1;
    }

    cout << "Operación realizada con exito, ahora visualizarlo con cualquier visor de imágenes" << endl;

    return EXIT_SUCCESS;*/
}


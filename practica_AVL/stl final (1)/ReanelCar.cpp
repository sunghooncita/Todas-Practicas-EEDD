#include <sstream>
#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stdexcept>
#include "ReanelCar.h"


/**
 * @brief iniciamos Reanel Car junto con la lista de usuarios y el vector de coches rellenos
 */
ReanelCar::ReanelCar() {
    ///leo los ficheros y lo cargo
    std::ifstream is;
    std::stringstream columnas;
    std::string fila;
    int contador = 0;

    std::string id_matricula = "";
    std::string marca = "";
    std::string modelo = "", bateria_str = "";


    is.open("../coches_v2.csv");

    if (is.good()) {
        clock_t t_ini = clock();

        std::getline(is, id_matricula);

        while (getline(is, fila)) {
            //¿Se ha leído una nueva fila?
            if (fila != "") {
                columnas.str(fila);


                getline(columnas, id_matricula, ','); //leemos caracteres hasta encontrar y omitir ';'
                getline(columnas, marca, ',');
                getline(columnas, modelo, ',');
                getline(columnas, bateria_str, ' ');

                int bateria = std::stoi(bateria_str);


                Coche coche(id_matricula, marca, modelo, bateria);
                cars[id_matricula] = coche;


                fila = "";
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
    std::stringstream columnas1;
    std::string fila1;
    int contador1 = 0;


    std::string nif = "";
    std::string clave = "";
    std::string nombre = "";
    std::string direccion = "";

    iu.open("../usuarios1.csv"); //carpeta de proyecto
    if (iu.good()) {
        clock_t t_ini = clock();
        std::atomic<int> id=0;
        while (getline(iu, fila1)) {
            //¿Se ha leído una nueva fila?
            if (fila1 != "") {
                columnas1.str(fila1);


                getline(columnas1, nif, ','); //leemos caracteres hasta encontrar y omitir ';'
                getline(columnas1, clave, ',');
                getline(columnas1, nombre, ',');
                getline(columnas1, direccion, ' ');
                Usuario usuario(nif, clave, nombre, direccion, nullptr,id++);
                users.push_back(usuario);
                users.back().setCoche(nullptr);
                users.back().setLinkReanel(this);
                fila1 = "";
                columnas1.clear();
                /*
                                                std::cout << " Usuario: ( Nif=" <<users.leer(contador1).getNif()
                                                          << " Clave=" << users.leer(contador1).getClave() << " Nombre=" << users.leer(contador1).getNombre()
                                                          << " Direccion=" << users.leer(contador1).getDireccion() <<")" << std::endl;*/
            }

            contador1++;
        }

        iu.close();

        std::cout << "Tiempo lectura: " << ((clock() - t_ini) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;
    } else {
        std::cout << "Error de apertura en archivo" << std::endl;
    }


    std::ifstream ip;
    std::stringstream columnas2;
    std::string fila2;
    int contador2 = 0;

    std::string id = "0";
    std::string latitude = "0";
    std::string longitude = "0";
    std::string max_cars = "0";

    ip.open("../puntos_recarga.csv"); //carpeta de proyecto
    if (ip.good()) {
        clock_t t_ini = clock();

        std::getline(ip, fila2);
        sities.resize(100);
        int i=0;
        while (getline(ip, fila2)) {
            //¿Se ha leído una nueva fila?
            if (fila2 != "") {
                columnas2.str(fila2);


                getline(columnas2, id, ','); //leemos caracteres hasta encontrar y omitir ';'
                getline(columnas2, latitude, ',');
                getline(columnas2, longitude, ',');
                getline(columnas2, max_cars, ' ');
                int idst= std::stoi(id);
                float latitudef = std::stod(latitude);
                float longitudef = std::stod(longitude);
                int max_car = std::stoi(max_cars);


                PuntoRecarga precarga(idst, latitudef, longitudef, max_car);
                sities[i++] = precarga;

                fila2 = "";
                columnas2.clear();
                /*
                                                std::cout << " Usuario: ( Nif=" <<users.leer(contador1).getNif()
                                                          << " Clave=" << users.leer(contador1).getClave() << " Nombre=" << users.leer(contador1).getNombre()
                                                          << " Direccion=" << users.leer(contador1).getDireccion() <<")" << std::endl;*/
            }


            contador2++;
        }

        ip.close();

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
    for (auto i = users.begin(); i != users.end(); ++i) {
        if (i->getNif() == nif) {
             return &*i;
        }
    }
    return nullptr;
}

/**
 * @brief Buscamos varios usuarios que coincida con el nombre dado
 * @param nom nombre
 * @return un vector con los usuarios del vector que coincida
 */
std::list<Usuario*> ReanelCar::buscarUsrNomb(std::string nom) {
    std::list<Usuario *> nuevo;
    auto iter = users.begin();
    int longitud = nom.length();
    while (iter != users.end()) {
        if (nom == iter->getNombre().substr(0, longitud)) {
            nuevo.push_back(&*iter);
        }
        iter++;
    }
    return nuevo;
}


/**
 * @brief Buscamos un coche que coincida con la matricula dado
 * @param mat matricula
 * @return el coche de la lista que coincida
 */
Coche *ReanelCar::buscarCochMat(std::string mat) {
    for (auto i = cars.begin() ;i != cars.end(); ++i) {
        if (mat == i->second.getId_matricula()) {
            return &i->second;
        }
    }
    return nullptr;
}


/**
 * @brief Buscamos varrios coches que coincidan con el modelo dado
 * @param mod modelo
 * @return una lista con los coches de la lista que coincidan
 */
std::map<std::string,Coche *> ReanelCar::buscarCochModelo(std::string mod) {
    std::map<std::string,Coche *> nuevo;
    int cont = 0;
    for (auto i = cars.begin() ;i != cars.end(); ++i) {
        if (mod == i->second.getModelo()) {
            nuevo.insert(std::pair<std::string,Coche*>(i->first,&i->second));
            cont++;
        }
    }
    return nuevo;
}


/**
 * @brief  enlaza al usuario y al coche que alquila.
 * @param usr usuario
 * @param c coche que enlazamos
 * @return un bool de si se ha podido hacer este enlace o no
 */
Coche *ReanelCar::alquilar(Usuario *u, int idPROrigen, int idPRDestino, Fecha *ini, Fecha *final) {
    PuntoRecarga *prO;
    PuntoRecarga *prD;
    prO = buscarPunto(idPROrigen);
    prD = buscarPunto(idPRDestino);
    Coche *c=prO->getMaxBateria();
    c->setPuntoD(prD);
    u->setCoche(c);
    Trayecto *t=u->crearTrayecto(prO,prD,ini,final);
    //t->setCoche(c);
    return c;
};


void ReanelCar::colocarCochePR(Coche *c, PuntoRecarga *p) {

    for (auto i = sities.begin() ; i != sities.end(); ++i) {
        if(i->getId() == p->getId()) {
            i->addCoche(c);
            c->aparcar(&*i);
        }
    }
};


/**
 * @brief borra el usuario que se indica de la lista
 * @param u usuario
 * @return un bool de si se ha podido eliminar o no
 */
bool ReanelCar::borrar(Usuario *u) {
   auto iter = users.begin();
    for (; iter != users.end(); ++iter) {
        if (*iter == *u) {
            users.erase(iter);
            return true;
        }
        iter++;
    }
    return false;
}

PuntoRecarga *ReanelCar::obtenerPRmenosCoches() {
    PuntoRecarga* prmenos=&sities[0];
    for (auto i = sities.begin() ; i != sities.end(); ++i) {
        if(prmenos->getNumCoches() > i->getNumCoches()) {
            prmenos= &*i;
        }
    }
    return prmenos;
}

PuntoRecarga *ReanelCar::buscarPunto(int id){
    for(int i=0; i<sities.size();i++){
        if(sities[i].getId()==id){
            return &sities[i];
        }
    }
    return nullptr;
};


std::vector<std::pair<Usuario*,Trayecto*>> ReanelCar::trayectosEnFecha(Fecha f){
    std::vector<std::pair<Usuario*,Trayecto*>> tr;
    std::multimap<Fecha,Trayecto> pepe;
    for (auto  i = users.begin(); i != users.end(); ++i) {
        auto rango =(*i).getRoute()->equal_range(f);
        for (auto j = rango.first; j != rango.second ; ++j) {
            std::pair<Usuario*,Trayecto*> alberto(&*i,&j->second);
            tr.push_back(alberto);
        }
    }
    return tr;
}

void ReanelCar::Ejercicio1() {
    int cont = 0;
    for(auto i = cars.begin() ;i != cars.end(); ++i){
        if(cont != 50){
            if(sities[cont].getMax()!=sities[cont].getNumCoches()){
                sities[cont].addCoche(&i->second);
            }//else break;
            cont++;
        }else{
            cont = 0;
        }
    }
};

void ReanelCar::Ejercicio2(std::list<Usuario*> lusu) {
    Fecha fec (29,10,2024);
    Fecha fech2=fec;

    int aleatorio = 0;
    int cont = 0;
    for(auto i = lusu.begin(); i != lusu.end(); ++i){
        if (cont != 50) {
            std::multimap<int,Coche*> *multima=sities[cont].getCoches();
            if(sities[cont].getNumCoches()!=0){
                (*i)->setCoche(multima->begin()->second);
                multima->erase(multima->begin());
                aleatorio = (rand() % 2) + 1;
                fech2.anadirDias(aleatorio);
                if(cont == 49){
                    PuntoRecarga *dest;
                    dest = &sities[0];//(sities[0].getId(),sities[0].getPos().getLatitud(),sities[0].getPos().getLongitud(),sities[0].getNumCoches());
                    (*i)->crearTrayecto(&sities[cont], dest,&fec,&fech2);
                    (*i)->getCoche()->setPuntoR(&sities[cont]);
                    (*i)->getCoche()->setPuntoD(dest);
                }else{
                    PuntoRecarga *dest;
                    dest = &sities[cont+1];//(sities[cont+1].getId(),sities[cont+1].getPos().getLatitud(),sities[cont+1].getPos().getLongitud(),sities[cont+1].getNumCoches());
                    (*i)->crearTrayecto(&sities[cont], dest,&fec,&fech2);
                    (*i)->getCoche()->setPuntoR(&sities[cont]);
                    (*i)->getCoche()->setPuntoD(dest);
                }

                cont++;
            }
        } else {
            cont = 0;
        }
    }
}

void ReanelCar::Ejercicio3(std::list<Usuario*> lusuWa){

    for (auto i = lusuWa.begin(); i != lusuWa.end(); ++i) {
        (*i)->aparcaCoche((*i)->getCoche(),(*i)->getCoche()->getPuntoD());
    }

    auto it = lusuWa.begin();
    std::multimap<Fecha,Trayecto>* mtray=(*it)->getRoute();
    std::cout <<"Los datos de los trayectos de los 10 primeros usuarios que empiezan por Wa son:\n\n ";
    for(int i=0;i<10;i++){
        for (auto j=mtray->begin(); j != mtray->end(); ++j) {
            std::cout <<std::endl<<i++<<".  Id del Origen: " << (*j).second.getOrigin()->getId()<<
                    "\n"<<"    Id del destino: " << (*j).second.getDestination()->getId()<<
                    "\n"<<"    Matricula coche alquilado: " << (*j).second.getInthecar()->getId_matricula()<<
                    "\n"<<"    Fecha de inicio: " << (*j).second.getFechaInicio().verDia()<<"/"<< (*j).second.getFechaInicio().verMes()<<"/"<<(*j).second.getFechaInicio().verAnio()<<
                    "\n"<<"    Fecha final: " << (*j).second.getFechaFinal().verDia()<<"/"<< (*j).second.getFechaFinal().verMes()<<"/"<<(*j).second.getFechaFinal().verAnio()
                    << std::endl;
        }

    }


};

    void ReanelCar::Ejercicio4(std::list<Usuario*> lusuWa){
    auto it = lusuWa.begin();
    auto itCoche = cars.begin();
    int aleatorio=0;
    Fecha fec (29,10,2024);
    Fecha fech2=fec;
    for(int i=0;i<10;){
        if(itCoche->second.getPuntoR() != nullptr){
            aleatorio = (rand() % 2) + 1;
            fech2.anadirDias(aleatorio);
            int idD = itCoche->second.getPuntoR()->getId();
            if(idD == 49){
                idD = 0;
            }else{
                idD++;
            }
            (*it)->getLinkReanel()->alquilar((*it)->getUsu(),itCoche->second.getPuntoR()->getId(),idD,&fec,&fech2);
            it++;
            i++;
        }
        itCoche++;
    }


 };


#include "ThashUsuario.h"


/*
unsigned long ThashUsuario::hash(unsigned long clave, int intento) {
    unsigned long h1=((10*clave)%tamtotal);
    unsigned long h2=(6 + (clave % CalcularPrimoMen()));

    return ((h1 - (intento*h2))) % tamtotal;
}
*/

/*
unsigned long ThashUsuario::hash2(unsigned long clave, int intento) {
    unsigned long hash = ( ( (clave)+(intento*intento)) % tamtotal);
    return hash;
}
*/
//Este es el hash 3 pero le ponemos hash para que cuadre con todos los metodos

unsigned long ThashUsuario::hash(unsigned long clave, int intento) {
    unsigned long h1=((18*clave)%tamtotal);
    unsigned long h2=(5*CalcularPrimoMen() - (clave % CalcularPrimoMen()));

    return ((h1-(intento*h2))%tamtotal);
}

/**
 * @brief funcion paracalcular el siguiente numero primo por debajo del tamaño de nuestra tabla
 * @return devuelve el primo menor
 */
unsigned long ThashUsuario::CalcularPrimoMen() {
    unsigned long primMen=tamtotal;
    do{
        --primMen;
    }while(esPrimo(primMen)!=true);
    return primMen;
}

/**
 * @brief Calcula el segundo primo mayor del numero que se pasa por la cabecera
 */
unsigned long ThashUsuario::CalcularPrimoMay(unsigned long primMay) {
    bool encontrado=false;
    do{
        ++primMay;
        if(esPrimo(primMay)==true){
            if(encontrado==true){
                break;
            }
            encontrado=true;
        }
    }while(esPrimo(primMay)==false || encontrado==true);
    return primMay;

}

/**
 * @brief Funcion que indica si el numero es primo o no
 */
bool ThashUsuario::esPrimo(unsigned long numero) {
    if (numero == 0 || numero == 1 || numero == 4) {
        return false;
    }
    for (int x = 2; x < numero / 2; x++) {
        if (numero % x == 0) {
            return false;
        }
    }
    return true;
}


/**
 * @brief constructor por defecto
 */
ThashUsuario:: ThashUsuario(int maxElementos, float lambda)
        :TAM_vector(maxElementos){
    tamtotal=CalcularPrimoMay((CalcularPrimoMay(maxElementos)/lambda)); ///Solo lo he usado para ver el tamtotal
    table.resize(tamtotal,Entrada());
    };

/**
 * @brief constructor copia
 */
ThashUsuario::ThashUsuario(ThashUsuario &thash):TAM_vector(thash.TAM_vector),table(thash.table),num_colisiones(thash.num_colisiones),
    num_usuarios(thash.num_usuarios),DatoMasColisiones(thash.DatoMasColisiones),
    tamtotal(thash.tamtotal) {};

/**
 * @brief Sobrecarga de operador de asignacion
 */
ThashUsuario ThashUsuario::operator=(ThashUsuario &thash){
    if (this != &thash ) {
        TAM_vector=thash.TAM_vector;
        num_usuarios=thash.num_usuarios;
        num_colisiones=thash.num_colisiones;
        tamtotal=thash.tamtotal;
        MaxColisiones=thash.MaxColisiones;
        DatoMasColisiones=thash.DatoMasColisiones;
        table=thash.table;
    }
    return *this;
};

/**
 * @brief Destructor
 */
ThashUsuario::~ThashUsuario(){};


/**
 * @brief funcion que redispersa la tabla a un nuevo tamaño
 */
void ThashUsuario::redispersa(unsigned long tam) {
    std::vector<Entrada> aux=this->table;
    table.clear();
    num_usuarios=0;
    num_colisiones=0;
    tamtotal=CalcularPrimoMay(tam);
    MaxColisiones=0;
    numRedispersiones++;

    table.resize(tamtotal,Entrada());
    for(int i=0;i<aux.size();++i){
        unsigned long clave=aux[0].dato->djb2((unsigned char*)aux[i].dato->getNif().c_str());
        this->insertar(clave,aux[i].dato);
    }
}

/**
 * @brief metodo de insertar
 */
bool ThashUsuario::insertar(unsigned long clave,  Usuario *usuario){
    unsigned long D_inserta;
    int i=0;
    bool introducida=false;
    while(introducida!=true) {
        D_inserta = hash(clave, i); //Cambiar hash
        if((table.at(D_inserta).estado_c1==true && table.at(D_inserta).estado_c2==true) || (table.at(D_inserta).estado_c1==true && table.at(D_inserta).estado_c2==false)){
            table.at(D_inserta).dato = usuario;
            table.at(D_inserta).clave = i;
            table.at(D_inserta).estado_c1 = false;
            table.at(D_inserta).estado_c2 = false;
            ++num_usuarios;
            if(i>DatoMasColisiones){
                DatoMasColisiones=i;
            }
            if(i>10){
                numMas10++;
            }
            if((float)num_colisiones/(float)TAM_vector>0.6186){
                redispersa(tamtotal*1.3); ///Aumentar la tabla un 30%
            }
            return true;
        }else if((table.at(D_inserta).estado_c1==false && table.at(D_inserta).estado_c2==false)){
            ++i;
            ++num_colisiones;
        }
    }
    return false;
};

/**
 * @brief metodo para buscar
 */
Usuario* ThashUsuario::buscar(unsigned long clave, std::string &dato){
    unsigned long D_busca;
    int i=0;
    bool encontrado=false;
    while (encontrado!=true){
        D_busca=hash(clave,i);
        if((table.at(D_busca).estado_c1==false && table.at(D_busca).estado_c2==false) && (table.at(D_busca).clave == i)){
            MaxColisiones=i;
            return (table.at(D_busca).dato);
        }else if(table.at(D_busca).estado_c1==true && table.at(D_busca).estado_c2==true){ ///la casilla está vacía por tanto no puede existir ese dato
            return nullptr;
        }else if((table.at(D_busca).estado_c1==true && table.at(D_busca).estado_c2==false)||(table.at(D_busca).estado_c1==false && table.at(D_busca).estado_c2==false)){
            ++i;
        }
    }
    return nullptr;
};

/**
 * @brief metodo de borrar
 */
bool ThashUsuario::borrar(unsigned long clave, std::string &dato){
    unsigned long D_borra;
    int i=0;
    bool borrada=false;
    while(borrada!=true ){
        D_borra= hash(clave,i);
        if((table.at(D_borra).estado_c1==false && table.at(D_borra).estado_c2==false) && i==table.at(D_borra).clave /*&& table.at(D_borra).dato->getNif() == dato*/) {
            table.at(D_borra).dato = nullptr;
            table.at(D_borra).clave = 0;
            table.at(D_borra).estado_c1 = true;
            --num_usuarios;
            return true;
        }else if((table.at(D_borra).estado_c1==true && table.at(D_borra).estado_c2==true))
            return false;
        else if(table.at(D_borra).estado_c1==true && table.at(D_borra).estado_c2==false) {
            ++i;
        }
        else i++;
    }
    return false;
};

/**
 * @brief metodo que devuelve el numero de elementos(usuarios)
 */
unsigned int ThashUsuario::numElementos(){
    return num_usuarios;
};

/**
 * @brief devuelve el número máximo de colisiones que se han producido en
 * la operación de inserción más costosa realizada sobre la tabla.
 */
unsigned int ThashUsuario::maxColisiones(){
    return DatoMasColisiones;
};

/**
 * @brief devuelve el número de veces que se superan 10 colisiones al intentar
 * realizar la operación de inserción sobre la tabla de un dato.
 */
unsigned int ThashUsuario::numMax10(){
    return numMas10;
};

/**
 * @brief funcion que calcula el promedio de colisiones
 */
double ThashUsuario::promedioColisiones(){
    return ((float)num_colisiones/(float)TAM_vector);
};

/**
 * @brief devuelve el factor de carga de la tabla de dispersión.
 */
float ThashUsuario::factorCarga(){
    return ((float)num_usuarios/(float)TAM_vector);
};

/**
 * @brief muestra por pantalla los diferentes parámetros
 * anteriores de la tabla interna de usuarios
 */

unsigned int ThashUsuario::tamTabla(){
    return tamtotal;
};

unsigned long ThashUsuario::numColisiones() {
    return num_colisiones;
}
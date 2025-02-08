//
// Created by lucia on 02/12/2024.
//

#ifndef COCHE_H
#define COCHE_H


#include <string>
#include "UTM.h"

class PuntoRecarga;


class Coche {
public:
    Coche();
    Coche(std::string id_matricula ,  std::string marca ,  std::string modelo, int bateria);
    Coche(const Coche &other);
    std::string getId_matricula() const;
    void setId_matricula(const std::string &id_matricula);
    std::string getMarca() const;
    void setMarca(const std::string &marca);
    std::string getModelo() const;
    void setModelo(const std::string &modelo);
    void setPuntoD(PuntoRecarga* desti);
    int getBateria() const;
    void setBateria(int bateria);

    PuntoRecarga *getPuntoR() const;
    PuntoRecarga *getPuntoD() const;

    void setIdMatricula( std::string &idMatricula);

    void setPuntoR(PuntoRecarga *puntoR);

    void setDest(PuntoRecarga *dest);

    void circular();
    bool aparcar(PuntoRecarga *pr);
    virtual ~Coche() = default;
    bool operator<(const Coche &car);
    bool operator==(Coche car);
    bool operator<=(const Coche &car);
    Coche &operator=(Coche car);
    bool operator!=(Coche origen);

    UTM getUTM() ;

private:
    std::string id_matricula;
    std::string marca;
    std::string modelo;
    int bateria;
    PuntoRecarga *puntoR = nullptr;
    PuntoRecarga *dest = nullptr;

};




#endif //COCHE_H

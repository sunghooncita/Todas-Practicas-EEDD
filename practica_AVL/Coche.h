//
// Created by Usuario on 27/10/2024.
//

#ifndef PR3_EEDD_COCHE_H
#define PR3_EEDD_COCHE_H

#include <string>
#include "UTM.h"
#include "PuntoRecarga.h"

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
    int getBateria() const;
    void setBateria(int bateria);
    void circular();
    virtual ~Coche() = default;
    bool operator<(const Coche &car);
    bool operator==(Coche car);
    bool operator<=(const Coche &car);
    Coche &operator=(const Coche& car);
    bool operator!=(Coche origen);

private:
    std::string id_matricula;
    std::string marca;
    std::string modelo;
    int bateria;
    PuntoRecarga *puntoR = nullptr;

};



#endif //PR3_EEDD_COCHE_H

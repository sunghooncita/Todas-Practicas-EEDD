//
// Created by lucia on 07/10/2024.
//

#ifndef COCHE_H
#define COCHE_H


#include <string>

class Coche {

public:
    Coche();

    Coche(std::string id_matricula ,  std::string marca ,  std::string modelo);

    Coche(const Coche &other);

    std::string getId_matricula() const;

    void setId_matricula(const std::string &id_matricula);

    std::string getMarca() const;

    void setMarca(const std::string &marca);

    std::string getModelo() const;

    void setModelo(const std::string &modelo);

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

};



#endif //COCHE_H

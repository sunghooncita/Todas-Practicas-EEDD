//
// Created by lucia on 02/12/2024.
//

#ifndef UTM_H
#define UTM_H

class UTM {
private:
    float latitud;
    float longitud;
public:

    UTM(): latitud(0), longitud(0){};
    UTM(float latitud, float longitud) : latitud(latitud), longitud(longitud) {}


    bool operator==(const UTM &origen) const {
        return latitud == origen.latitud &&
               longitud == origen.longitud;
    }

    bool operator!=(const UTM &origen) const {
        return !(origen == *this);
    }

    float getLongitud()  {
        return longitud;
    }

    float getLatitud()  {
        return latitud;
    }

    UTM &operator=(UTM orig){
        latitud=orig.latitud;
        longitud=orig.longitud;
        return *this;
    }

};

#endif //UTM_H

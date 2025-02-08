//
// Created by Usuario on 27/10/2024.
//

#ifndef PR3_EEDD_UTM_H
#define PR3_EEDD_UTM_H

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
};

#endif //PR3_EEDD_UTM_H

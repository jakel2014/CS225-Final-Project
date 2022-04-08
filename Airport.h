#pragma once

typedef unsigned int ID;

class Airport {
private:
    ID id;
    double latitude, longitude;

public:
    Airport(unsigned int id, double latitude, double longitude)
        : id(id), latitude(latitude), longitude(longitude) {}

    Airport() : id(0), latitude(0.0), longitude(0.0) {}

    unsigned int getID() {return id;}

    double getLong() {return longitude;}

    double getLat() {return latitude;}
};
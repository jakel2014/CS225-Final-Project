#pragma once

#include "Airport.h"
#include <cstdlib>
#include <math.h>
#include <iostream>

class Route {
private:
    ID startID, endID;
    double distance;

public:
    Route() : startID(0), endID(0), distance(0.0) {}

    Route(ID startID,ID endID, double distance)
        : startID(startID), endID(endID), distance(distance) {}

    Route(Airport start, Airport end) : startID(start.getID()), endID(end.getID()) {
        distance = calcDistance(start.getLat(), start.getLong(), end.getLat(), end.getLong());
    }

    unsigned int getStart() {return startID;}

    unsigned int getEnd() {return endID;}

    double getDist() {return distance;}

    void setDist(double dist) {distance = dist;}

    void setStart(ID id) {startID = id;}

    void setEnd(ID id) {endID = id;}

    bool operator<(Route r) const {return distance < r.distance;}

    bool operator>(Route r) const {return distance > r.distance;}

    bool operator==(Route r) const {return distance == r.distance;}

    double calcDistance(double slatitude, double slongitude, double elatitude, double elongitude){
        double slatRads = slatitude*M_PI/180;   //Convert all of the lats and longs to radians
        double slonRads = slongitude*M_PI/180;
        double elatRads = elatitude*M_PI/180;
        double elonRads = elongitude*M_PI/180;

        double latdistance = elatRads - slatRads;   //haversine formula needs these
        double londistance = elonRads - slonRads;

        double radius = 1;   //Update to the radius of the earth in whatever units we want it to be in

        double ret = 2 * radius * asin(sqrt(pow(sin(latdistance/2), 2) + cos(slatRads) * cos(elatRads) * pow(sin(londistance/2), 2)));
        //The above line is haversine formula
        
        return ret;
    }
};
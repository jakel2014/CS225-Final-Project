#pragma once

#include <math.h>


double calcDistance(double slatitude, double slongitude, double elatitude, double elongitude){
        double slatRads = slatitude*M_PI/180;   //Convert all of the lats and longs to radians
        double slonRads = slongitude*M_PI/180;
        double elatRads = elatitude*M_PI/180;
        double elonRads = elongitude*M_PI/180;

        double latdistance = elatRads - slatRads;   //haversine formula needs these
        double londistance = elonRads - slonRads;

        double radius = 6378.1;   //Update to the radius of the earth in whatever units we want it to be in

        double ret = 2 * radius * asin(sqrt(pow(sin(latdistance/2), 2) + cos(slatRads) * cos(elatRads) * pow(sin(londistance/2), 2)));
        //The above line is haversine formula
        
        return ret;
    }

double linearDistance(double x1, double y1, double x2, double y2){  //Distance formula for finding the correct point to plot on map
    double ret = sqrt(pow((x2-x1),2)+pow((y2-y1),2));
    return ret;
}

std::vector<std::pair<double, double>> convertToCoords(double lat, double lon){ //Convert latitude and longitude to x and y coordinates. Returns a vector with both possible points.
    std::vector<std::pair<double, double>> ret;
    std::pair<double, double> point1{floor((lat/90)*1022.5 + 1022.5), floor((lon/180)*510 + 510)};  //Normalize each point and then add offset
    std::pair<double, double> point2{floor((lat/90)*1022.5 + 3067.5), floor((lon/180)*510 + 510)};
    ret.push_back(point1);
    ret.push_back(point2);
    return ret;
}
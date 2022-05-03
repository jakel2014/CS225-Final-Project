#include "Visual.h"



void Visual::createLine(int x1, int y1, int x2, int y2) {

}

    //return is [{x_left, y_left}, {x_right, y_right}]
std::vector<std::pair<double, double>> Visual::convertToCoords(double lat, double lon){ //Convert latitude and longitude to x and y coordinates. Returns a vector with both possible points.
    std::vector<std::pair<double, double>> ret;
    std::pair<double, double> point1{floor((lon/180)*1022.5 + 1022.5), floor(510 - (lat/90)*510)};  //Normalize each point and then add offset
    std::pair<double, double> point2{floor((lon/180)*1022.5 + 3067.5), floor(510 - (lat/90)*510)};
    ret.push_back(point1);
    ret.push_back(point2);
    return ret;
}


Visual::Visual(Image world_map) : map(world_map, 1) { //sets worldMap as base of map

    //map = StickerSheet(world_map, 1);
    worldMap = world_map;
}

    //creates the shortest line between two lat, long pts. Prefers left side (Prio = 0)
void Visual::addLine(double lat1, double long1, double lat2, double long2, unsigned prio = 0) {
    //First, create the points
    std::vector<std::pair<double, double> pair1 = convertToCoords(lat1, lon1);
    std::vector<std::pair<double, double> pair1 = convertToCoords(lat1, lon1);
    //Then, find the combination that yields the shortest distance (Prioritize the side that its already on from plot. 0 = left, 1 = right)
    double distance1 = linearDistance(pair1[0]->first, pair1[0]->second, pair2[1]->first, pair2[1]->second);    //Point 1 on left, Point 2 on right
    double distance2 = linearDistance(pair2[0]->first, pair2[0]->second, pair1[1]->first, pair2[1]->second);    //Point 2 on left, Point 1 on right
    //The next distance is the same for both types of inputs, but prio determines which is used
    double priodistance = linearDistance(pair1[prio]->first, pair1[prio]->second, pair2[prio]->first, pair2[prio]->second); //Both points on same side
    //Create the line of shortest distance
    if(distance1 < distance2 && distance1 < priodistance){
        createLine(pair1[0]->first, pair1[0]->second, pair2[1]->first, pair2[1]->second);
    }
    else if(distance2 < priodistance){
        createLine(pair2[0]->first, pair2[0]->second, pair1[1]->first, pair2[1]->second);
    }
    else{
        createLine(pair1[prio]->first, pair1[prio]->second, pair2[prio]->first, pair2[prio]->second);
    }
}

void Visual::addTour(std::queue<Airport> path) {

}

void Visual::getVisualOutput(Image & img) {
    
}

double Visual::linearDistance(double x1, double y1, double x2, double y2){  //Distance formula for finding the correct point to plot on map
    double ret = sqrt(pow((x2-x1),2)+pow((y2-y1),2));
    return ret;
}
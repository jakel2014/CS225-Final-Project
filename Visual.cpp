#include "Visual.h"
#include <algorithm>



void Visual::createLine(int x1, int y1, int x2, int y2) {
    cs225::HSLAPixel red(0, 1, .5); //Desired color of the line to draw
    //Find and draw equation of line using point slope formula
    double m;
    if((x2 - x1) != 0){
        m = ((double) y2 - (double) y1)/((double) x2 - (double) x1); //Slope of the line
    }
    else{
        m = 0;
    }
    if(abs(m) <= 3 && (x1 - x2) != 0){
        double leftbound = fmin(x1, x2);
        double rightbound = fmax(x1, x2);

        for(double x = leftbound; x < rightbound; x++){
            double y = floor(m*(x - x1) + y1);
            for(int index = -1; index <= 1; index++){
                cs225::HSLAPixel & temp = worldMap.getPixel(x, y + index);
                temp = red;
            }
        }
    }
    else{
        double botbound = fmin(y1, y2);
        double topbound = fmax(y1, y2);

        for(double y = botbound; y < topbound; y++){
            double x = floor((1/m)*(y-y1) + x1);
            for(int index = -1; index <=1; index++){
                cs225::HSLAPixel & temp = worldMap.getPixel(x + index, y);
                temp = red;
            }
        }
    }
    drawCircle(x1, y1); //Add on the circles to denote the airports
    drawCircle(x2, y2);
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


Visual::Visual(Image world_map){ //sets worldMap as base of map and initialized priority side

    worldMap = world_map;
    priority = 0;  //0 = left, 1 = right
}

    //creates the shortest line between two lat, long pts. Prefers left side (Prio = 0). lat1 and long1 = current lat/long, lat2 and long2 = target lat/long
void Visual::addLine(double lat1, double long1, double lat2, double long2) {
    //First, create the points
    std::vector<std::pair<double, double>> pair1 = convertToCoords(lat1, long1);
    std::vector<std::pair<double, double>> pair2 = convertToCoords(lat2, long2);
    //Then, find the combination that yields the shortest distance (Prioritize the side that its already on from plot. 0 = left, 1 = right)
    double distance1 = linearDistance(pair1[0].first, pair1[0].second, pair2[1].first, pair2[1].second);    //Point 1 on left, Point 2 on right
    double distance2 = linearDistance(pair2[0].first, pair2[0].second, pair1[1].first, pair2[1].second);    //Point 2 on left, Point 1 on right
    //The next distance is the same for both types of inputs, but prio determines which is used
    double priodistance = linearDistance(pair1[priority].first, pair1[priority].second, pair2[priority].first, pair2[priority].second); //Both points on same side
    //Create the line of shortest distance
    if(distance1 < distance2 && distance1 < priodistance){
        createLine(pair1[0].first, pair1[0].second, pair2[1].first, pair2[1].second);
        priority = 1;   //Update the priority side
    }
    else if(distance2 < priodistance){
        createLine(pair1[1].first, pair1[1].second, pair2[0].first, pair2[0].second);
        priority = 0;
    }
    else{
        createLine(pair1[priority].first, pair1[priority].second, pair2[priority].first, pair2[priority].second);
    }
}

void Visual::addTour(std::vector<Airport> path) {
    if(path[0].getLong() - path[path.size() - 1].getLong() < -90){
        std::reverse(path.begin(), path.end());
    }
    for (size_t i = 0; i < path.size() - 1; ++i) {
    	Airport &cur    = path[i];
    	Airport &target = path[i + 1];
    	addLine(cur.getLat(), cur.getLong(), target.getLat(), target.getLong());
    }
}

void Visual::getVisualOutput(Image & img) {
    img = worldMap;
}

double Visual::linearDistance(double x1, double y1, double x2, double y2){  //Distance formula for finding the correct point to plot on map
    double ret = sqrt(pow((x2-x1),2)+pow((y2-y1),2));
    return ret;
}

void Visual::drawCircle(double x1, double y1, double r){
    double ymaxbound = y1 + r;    //Bounds of area to draw circle
    double yminbound = y1 - r;
    double xmaxbound = x1 + r;
    double xminbound = x1 - r;
    
    cs225::HSLAPixel green(120, 1, .5); //Desired color of the circle to draw

    for(double x = xminbound; x < xmaxbound; x++){
        for(double y = yminbound; y < ymaxbound; y++){
            if(linearDistance(x, y, x1, y1) <= 5){
                cs225::HSLAPixel & temp = worldMap.getPixel(x, y);
                temp = green;
            }
        }
    }
}

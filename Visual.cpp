#include "Visual.h"



void Visual::createLine(int x1, int y1, int x2, int y2) {

}

    //return is [x_left, y_left, x_right, y_right]
std::vector<int> Visual::getPixelPosition(double latitude, double longitude) {
    return {};
}


Visual::Visual(Image world_map) : map(world_map, 1) { //sets worldMap as base of map

    //map = StickerSheet(world_map, 1);
    worldMap = world_map;
}

    //creates the shortest line between two lat, long pts. Prefers left side
void Visual::addLine(double lat1, double long1, double lat2, double long2) {

}

void Visual::addTour(std::queue<Airport> path) {

}

void Visual::getVisualOutput(Image & img) {
    
}
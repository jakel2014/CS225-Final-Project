#pragma once

#include <queue>
#include "Route.h"
#include "Image.h"

class Visual {
    private:
    Image worldMap;
    unsigned priority;

    //adds and generates Image of line to stickersheet 
    void createLine(int x1, int y1, int x2, int y2); 

    //return is {{x_left, y_left}, {x_right, y_right}}
    std::vector<std::pair<double, double>> convertToCoords(double lat, double lon);

    //Calculates the distances between linear points, usually pixels
    double linearDistance(double x1, double y1, double x2, double y2);  

    //Draw a circle at the given x and y coordinates, with a default radius of 10
    void drawCircle(double x1, double y1, double r = 10);

    public:
    Visual(Image world_map); //sets worldMap as base of map

    //creates the shortest line between two lat, long pts. Prefers left side
    void addLine(double lat1, double long1, double lat2, double long2);

    //Generates an image based given a path of airports
    void addTour(std::vector<Airport> path);

    //Returns image to map with path on it
    void getVisualOutput(Image & img);
};

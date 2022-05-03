#include "StickerSheet.h"
#include <queue>
#include "Route.h"


class Visual {
    private:
    Image worldMap;
    unsigned priority;

    //adds and generates Image of line to stickersheet 
    void createLine(int x1, int y1, int x2, int y2); 

    //return is [x_left, y_left, x_right, y_right]
    std::vector<std::pair<double, double>> convertToCoords(double lat, double lon);

    double linearDistance(double x1, double y1, double x2, double y2);

    

    public:
    Visual(Image world_map); //sets worldMap as base of map

    //creates the shortest line between two lat, long pts. Prefers left side
    void addLine(double lat1, double long1, double lat2, double long2);

    void addTour(std::queue<Airport> path);

    void getVisualOutput(Image & img);

    void drawCircle(double lat, double lon, double r = 10);    //Draw a circle at the given lat and long
    //This is public for now for testing but it can probably go to private for final product
};
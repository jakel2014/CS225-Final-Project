#include "StickerSheet.h"
#include "WeightedGraph.h"

class Visual {
    private:
    StickerSheet map;
    Image worldMap;

    //adds and generates Image of line to stickersheet 
    void createLine(int x1, int y1, int x2, int y2); 

    //return is [x_left, y_left, x_right, y_right]
    std::vector<int> getPixelPosition(double latitude, double longitude);

    public:
    Visual(Image world_map); //sets worldMap as base of map

    //creates the shortest line between two lat, long pts. Prefers left side
    void addLine(double lat1, double long1, double lat2, double long2);

    void addTour(std::queue<Airport> path);

    void getVisualOutput(Image & img);


};
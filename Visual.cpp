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
        m = 0;  //Test case when a divide by 0 error could be met
    }
    if(abs(m) <= 3 && (x1 - x2) != 0){  //Based on the slop of the line, plots out the lone on worldMap.
        double leftbound = fmin(x1, x2);
        double rightbound = fmax(x1, x2);

        for(double x = leftbound; x < rightbound; x++){ //Plot the line within the given bounds
            double y = floor(m*(x - x1) + y1);
            for(int index = -1; index <= 1; index++){
                cs225::HSLAPixel & temp = worldMap.getPixel(x, y + index);
                temp = red;
            }
        }
    }
    else{   //This is the same thing as above, but for more vertical cases
        double botbound = fmin(y1, y2);
        double topbound = fmax(y1, y2);
        if(m != 0){ //Handles another divide by 0 error.
            m = 1/m;
        }
        for(double y = botbound; y < topbound; y++){
            double x = floor(m*(y-y1) + x1);
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
    std::pair<double, double> point1{floor((lon/180)*1022.5 + 1022.5), floor(510 - (lat/90)*510)};  //Normalize each point and then multiply and add offset
    std::pair<double, double> point2{floor((lon/180)*1022.5 + 3067.5), floor(510 - (lat/90)*510)};
    ret.push_back(point1);  //Push the points into the queue indexed by side, 0 = left, 1 = right, similar to priority
    ret.push_back(point2);
    return ret;
}


Visual::Visual(Image world_map){ //sets worldMap as base of map and initialized priority side
    worldMap = world_map;
    priority = 0;  //0 = left, 1 = right. 0 is always default, input will be corrected to match
    dt.LoadFont("fonts/fixed-6x13.bdf");
}

    //creates the shortest line between two lat, long pts. Prefers left side (Prio = 0). lat1 and long1 = current lat/long, lat2 and long2 = target lat/long
std::tuple<int, int, int, int> Visual::addLine(double lat1, double long1, double lat2, double long2) {
    //First, create the points
    std::vector<std::pair<double, double>> pair1 = convertToCoords(lat1, long1);
    std::vector<std::pair<double, double>> pair2 = convertToCoords(lat2, long2);
    //Then, find the combination that yields the shortest distance (Prioritize the side that its already on from plot. 0 = left, 1 = right)
    double distance1 = linearDistance(pair1[0].first, pair1[0].second, pair2[1].first, pair2[1].second);    //Point 1 on left, Point 2 on right
    double distance2 = linearDistance(pair2[0].first, pair2[0].second, pair1[1].first, pair2[1].second);    //Point 2 on left, Point 1 on right
    //The next distance is the same for both types of inputs, but prio determines which is used
    double priodistance = linearDistance(pair1[priority].first, pair1[priority].second, pair2[priority].first, pair2[priority].second); //Both points on same side
    //Create the line of shortest distance
    int x1, y1, x2, y2;
    if(distance1 < distance2 && distance1 < priodistance){
        x1 = pair1[0].first,
        y1 = pair1[0].second,
        x2 = pair2[1].first,
        y2 = pair2[1].second;

        priority = 1;   //Update the priority side
    }
    else if(distance2 < priodistance){
        x1 = pair1[1].first,
        y1 = pair1[1].second,
        x2 = pair2[0].first,
        y2 = pair2[0].second;

        priority = 0;
    }
    else {
        x1 = pair1[priority].first,
        y1 = pair1[priority].second,
        x2 = pair2[priority].first,
        y2 = pair2[priority].second;
    }
    createLine(x1, y1, x2, y2);
    return std::make_tuple(x1, y1, x2, y2);
}

void Visual::addTour(std::vector<Airport> path) {
    std::cout << path.size() << std::endl;
    if(path[0].getLong() - path[path.size() - 1].getLong() < -90){  //Ensure that the default priority is 0
        std::reverse(path.begin(), path.end());
    }
    std::cout << path[0].getName() << std::endl;
    for (size_t i = 0; i < path.size() - 1; ++i) {      //Iterate through airports drawing a line between each!
        Airport &cur    = path[i];
        Airport &target = path[i + 1];
        std::cout << target.getName() << std::endl;

        auto px_vals = addLine(cur.getLat(), cur.getLong(), target.getLat(), target.getLong());
        drawText(std::get<0>(px_vals) + 5, std::get<1>(px_vals) + 5, cur.getName()); // draw name of cur
        if (i == path.size() - 2) // draw name of target, but only for the last line in the path
            drawText(std::get<2>(px_vals) + 5, std::get<3>(px_vals) + 5, target.getName());
    }
}

void Visual::getVisualOutput(Image & img) { //Returns the output image of the map
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

    for(double x = xminbound; x < xmaxbound; x++){  //Iterate through specified bounds to draw circle
        for(double y = yminbound; y < ymaxbound; y++){
            if(linearDistance(x, y, x1, y1) <= 5){
                cs225::HSLAPixel & temp = worldMap.getPixel(x, y);
                temp = green;
            }
        }
    }
}

void Visual::drawText(unsigned int x, unsigned int y, const std::string text) {
	cs225::HSLAPixel px_white(0, 0, 1),
	                 px_black(0, 0, 0);
	// drop shadow
	dt.DrawTextPNG(worldMap, px_black, x - 1, y, text);
	dt.DrawTextPNG(worldMap, px_black, x + 1, y, text);
	dt.DrawTextPNG(worldMap, px_black, x, y - 1, text);
	dt.DrawTextPNG(worldMap, px_black, x, y + 1, text);
	// primary text
	dt.DrawTextPNG(worldMap, px_white, x, y, text);
}

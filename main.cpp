#include "WeightedGraph.h"
#include "Airport.h"
#include "DataParser.h"
#include "Visual.h"
#include <iostream>


int main() {
    DataParser parser("data/airports-preprocessed.csv", "data/routes-preprocessed.csv");

    WeightedGraph new_graph(parser);


    //get airport input from from terminal 
    std::string port1, port2;
    std::cout << "Please enter a valid XXXX airport code: ";
    std::cin >> port1;

    std::cout << "Please enter another valid XXXX airport code: ";
    std::cin >> port2;

    std::vector<std::string> portNames; //Initialize all our variables for airports
    std::vector<ID> portID;
    std::vector<double> portLatitudes;
    std::vector<double> portLongitudes;
    parser.getAirportsData(portNames, portID, portLatitudes, portLongitudes);

    bool found1=0, found2=0;
    ID id1 = 0, id2=0;

    for (size_t i=0; i<portNames.size(); i++) {
        if (portNames[i] == port1) {
            found1 = 1;
            id1 = portID[i];
        }

        if (portNames[i] == port2) {
            found2=1;
            id2 = portID[i];
        }

        if (found1 & found2)
            break;
    }

    if (!(found1 & found2))
        return 0;

    std::stack<Route> path = new_graph.getShortestPath(id1, id2);

    int i=0;
    std::cout << path.top().getStart(); 
    while (!path.empty()) {
        Route curr = path.top();
        
        std::cout <<  " -> " << curr.getEnd();
        i++;
        if (i==0) {
            std::cout << std::endl;
            i=0;
        }
        path.pop();
    }
  
    //
    return 0;
}


/*int main2() { //djikstras with visual output
    DataParser parser("airports-preprocessed.csv", "routes-preprocessed.csv");
    WeightedGraph graph(parser);

    Image worldMap;
    worldMap.readFromFile("STRING THAT REPRESENTS PATH TO WORLD MAP");
    Visual visual(worldMap);

    std::vector<std::string> portNames; //Initialize all our variables for airports
    std::vector<ID> portID;
    std::vector<double> portLatitudes;
    std::vector<double> portLongitudes;
    parser.getAirportsData(portNames, portID, portLatitudes, portLongitudes);

    std::map<ID, Airport> airports;
    std::map<std::string, ID> name_to_id;
    for (unsigned i=0; i<portNames.size(); i++) {
        airports[portID[i]] = Airport(portID[i], portLatitudes[i], portLongitudes[i], portNames[i]);
        name_to_id[portNames[i]] = portID[i];
    }


    // TODO request user for airports and output to variables below
    std::string beginName, endName;
    ID beginID = name_to_id[beginName];

    std::stack<Route> path = graph.getShortestPath(beginID, name_to_id[endName]);

    std::vector<Airport> visualPath;
    visualPath.push_back(airports[beginID]);
    while (!path.empty()) {
        Route curr = path.top();
        visualPath.push_back(airports[curr.getEnd()]);
        path.pop();
    } //initialize vector representing Aiports that represent shorted path


    //visual tour algorithm either directly in here or by function



    return 0;
}*/


/*int main() { //visual output, only one route
    DataParser parser("data/airports-preprocessed.csv", "data/routes-preprocessed.csv");

    Image worldMap;
    worldMap.readFromFile("STRING THAT REPRESENTS PATH TO WORLD MAP");
    Visual visual(worldMap);


    //get airport input from from terminal 
    std::string port1, port2;
    std::cout << "Please enter a valid XXXX airport code: ";
    std::cin >> port1;

    std::cout << "Please enter another valid XXXX airport code: ";
    std::cin >> port2;

    std::vector<std::string> portNames; //Initialize all our variables for airports
    std::vector<ID> portID;
    std::vector<double> portLatitudes;
    std::vector<double> portLongitudes;
    parser.getAirportsData(portNames, portID, portLatitudes, portLongitudes);

    bool found1=0, found2=0;
    double lat1=0, long1=0, lat2=0, long2=0;

    for (size_t i=0; i<portNames.size(); i++) {
        if (portNames[i] == port1) {
            found1 = 1;
            lat1 = portLatitudes[i];
            long1 = portLongitudes[i];
        }

        if (portNames[i] == port2) {
            found2=1;
            lat2 = portLatitudes[i];
            long2 = portLongitudes[i];
        }

        if (found1 & found2)
            break;
    }

    visual.addLine(lat1, long1, lat2, long2);

    Image img;
    visual.getVisualOutput(img);

    img.writeToFile("STRING THAT REPRESENTS PATH TO OUTOUT MAP");

    //
    return 0;
}*/

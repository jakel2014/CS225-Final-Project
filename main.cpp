#include "WeightedGraph.h"
#include "Airport.h"
#include "DataParser.h"
#include "Visual.h"
#include <iostream>


/*int main() {
    DataParser parser("data/airports-preprocessed.csv", "data/routes-preprocessed.csv");

    WeightedGraph new_graph(parser);


    //get airport input from from terminal 
    std::string port1, port2;
    std::cout << "Please enter a valid ICAO airport code for your departure: ";
    std::cin >> port1;

    std::cout << "Please enter another valid ICAO airport code for your arrival: ";
    std::cin >> port2;

    std::vector<std::string> portNames; //Initialize all our variables for airports
    std::vector<ID> portID;
    std::vector<double> portLatitudes;
    std::vector<double> portLongitudes;
    parser.getAirportsData(portNames, portID, portLatitudes, portLongitudes);

    bool found1=0, found2=0;
    ID id1=0, id2=0; //URSS, UWKD
    std::map<ID, std::string> id_to_name;

    for (size_t i=0; i<portNames.size(); i++) {
        if (portNames[i] == port1) {
            found1 = 1;
            id1 = portID[i];
        }

        if (portNames[i] == port2) {
            found2=1;
            id2 = portID[i];
        }

        id_to_name[portID[i]] = portNames[i];
    }

    if (!(found1 && found2)) {
        std::cout << "Invalid name/s. Try again" << std::endl;
        return 0;
    }

    std::stack<Route> path = new_graph.getShortestPath(id1, id2);

    int i=0;
    std::cout << id_to_name[path.top().getStart()]; 
    double dist = 0;
    while (!path.empty()) {
        Route curr = path.top();
        
        std::cout <<  " -> " << id_to_name[curr.getEnd()];
        i++;
        if (i==0) {
            std::cout << std::endl;
            i=0;
        }
        dist = curr.getDist();
        path.pop();
    }
    std::cout << std::endl << "Total Distance: " << dist << " km" << std::endl;
  
    //
    return 0;
}*/


int main() { //djikstras with visual output
    DataParser parser("data/airports-preprocessed.csv", "data/routes-preprocessed.csv");
    WeightedGraph graph(parser);

    Image worldMap;
    worldMap.readFromFile("images/world-map.png");
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

    //get airport input from from terminal 
    std::cout << "Please enter a valid ICAO airport code: ";
    std::cin >> beginName;

    std::cout << "Please enter another valid ICAO airport code: ";
    std::cin >> endName;

    ID beginID = name_to_id[beginName];
    ID endID = name_to_id[endName];
    std::stack<Route> path = graph.getShortestPath(beginID, endID);

    std::vector<Airport> visualPath;
    visualPath.push_back(airports[beginID]);
    while (!path.empty()) {
        Route curr = path.top();
        visualPath.push_back(airports[curr.getEnd()]);
        path.pop();
    } //initialize vector representing Aiports that represent shorted path

	visual.addTour(visualPath);

    //visual tour algorithm either directly in here or by function

    Image img;
    visual.getVisualOutput(img);

    img.writeToFile("images/path_map.png");

    return 0;
}


/*int main() { //visual output, only one route
    DataParser parser("data/airports-preprocessed.csv", "data/routes-preprocessed.csv");

    Image worldMap;
    worldMap.readFromFile("images/world-map.png");
    Visual visual(worldMap);

    //get airport input from from terminal 
    std::string port1, port2;
    std::cout << "Please enter a valid ICAO airport code: ";
    std::cin >> port1;

    std::cout << "Please enter another valid ICAO airport code: ";
    std::cin >> port2;

    std::vector<std::string> portNames; //Initialize all our variables for airports
    std::vector<ID> portID;
    std::vector<double> portLatitudes;
    std::vector<double> portLongitudes;
    parser.getAirportsData(portNames, portID, portLatitudes, portLongitudes);

    bool found1=0, found2=0; //URSS, UWKD
    double lat1=0, long1=0, lat2=0, long2=0;

    ID id1, id2;
    for (size_t i=0; i<portNames.size(); i++) {
        if (portNames[i] == port1) {
            found1 = 1;
            id1 = i;
            lat1 = portLatitudes[i];
            long1 = portLongitudes[i];
        }

        if (portNames[i] == port2) {
            found2=1;
            id2 = i;
            lat2 = portLatitudes[i];
            long2 = portLongitudes[i];
        }

        if (found1 && found2)
            break;
    }

    if (!(found1 && found2))
        return 0;

    Image img;
    visual.getVisualOutput(img);

    img.writeToFile("images/path_map.png");

     
    WeightedGraph w(parser);
    std::stack<Route> path = w.getShortestPath(id1, id2);
    std::queue<Airport> airports = w.routesToAirports(path);
	std::cout << airports.size() << std::endl;
	visual.addTour(airports);

    std::queue<ID> dfs_traversal = w.DFS(3830);

    std::map<ID, std::string> id_to_name;

    for (size_t i=0; i<portNames.size(); i++) {
        id_to_name[portID[i]] = portNames[i];
    }

    for(unsigned i = 0; i < dfs_traversal.size(); i++){
        std::cout<<id_to_name[dfs_traversal.front()];
        if(i != dfs_traversal.size() - 1){
            std::cout<<"-->";
        }
        dfs_traversal.pop();
    }

    std::cout<<std::endl;
    
    return 0;
    //
}*/

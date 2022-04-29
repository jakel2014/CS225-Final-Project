#include "WeightedGraph.h"
#include "Airport.h"
#include "DataParser.h"
#include "Visual"


int main() {
    WeightedGraph new_graph;

    DataParser parser("airports-preprocessed.csv", "routes-preprocessed.csv");  //Set up our Data Parser class
    parser.airports_helper();   //Initialize both our airports
    parser.routes_helper();     //and our routes

    std::vector<std::string> portNames; //Initialize all our variables for airports
    std::vector<ID> portID;
    std::vector<double> portLatitudes;
    std::vector<double> portLongitudes;
    parser.getAirportsData(portNames, portID, portLatitudes, portLongitudes);

    for(unsigned i = 0; i < portID.size() - 1; i++){    //Add all airports to our graph
        new_graph.addAirport(portID[i]);
    }

    std::vector<double> distances;  //Initialize all our variables for routes
    std::vector<ID> sourceID;
    std::vector<ID> destinationID;
    parser.getRoutesData(distances, sourceID, destinationID);

    for(unsigned j = 0; j < distances.size() - 1; j++){ //Add all routes to our graph
        new_graph.addRoute(sourceID[j], destinationID[j], distances[j]);
    }

    return 0;
}


int main2() {
    DataParser parser("airports-preprocessed.csv", "routes-preprocessed.csv");
    parser.airports_helper();   //Initialize both our airports
    parser.routes_helper();     //and our routes
    
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
    for (int i=0; i<portNames.size(); i++) {
        airports[portID[i]] = Airport(portID[i], portLatitudes[i], portLongitudes[i], portNames[i]);
        name_to_id[portNames[i]] = portID[i];
    }


    // TODO request user for airports and output to variables below
    std::string beginName, endName;
    ID beginID = name_to_id[beginName];

    std::stack<Route> path = graph.getShortestPath(beginID, name_to_id[endName]);

    std::vector<Airport> visualPath;
    visualPath.push_back(aiports[beginID]);
    while (!path.empty()) {
        Route curr = path.top();
        visualPath.push_back(airports[curr.getEnd()]);
        path.pop();
    } //initialize vector representing Aiports that represent shorted path


    //visual tour algorithm either directly in here or by function



    return 0;
}

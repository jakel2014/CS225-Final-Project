#include "WeightedGraph.h"
#include "Airport.h"
#include "DataParser.h"


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

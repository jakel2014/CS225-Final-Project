#include "WeightedGraph.h"
#include "Airport.h"
#include "lazycsv.hpp"



int main() {


    //import airports
    //import routes

    WeightedGraph new_graph;

    lazycsv::parser parser("data/airports.csv");

    for(const auto row: parser){
        const auto [id, name, lattitude, longitude] = row.cells(0, 1, 6, 7);
        Airport cur_airport(id.trimed(), lattitude.trimed(), longitude.trimed(), name.trimed());
        new_graph.addAirport(cur_airport); 
    }

    //need to add routes

    return 0;
}
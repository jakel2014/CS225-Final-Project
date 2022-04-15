#include "WeightedGraph.h"
#include "Airport.h"
#include "rapidcsv.h"



int main() {


    //import airports
    //import routes

    WeightedGraph new_graph;

    //This should be for Airports
    rapidcsv::Document doc("data/routes.csv", rapidcsv::LabelParams(-1, -1));
    std::vector<double> latitudes = doc.GetColumn<double>(1);
    std::vector<double> longitudes = doc.GetColumn<double>(2);
    

    return 0;
}
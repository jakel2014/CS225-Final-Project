#include "WeightedGraph.h"
#include "Airport.h"
#include "rapidcsv.h"



int main() {


    //import airports
    //import routes

    WeightedGraph new_graph;

    //This stuff is for Airports
    //Stuff goes here


    //Loop setting up airports

    //This stuff should be for Routes
    rapidcsv::Document doc("data/out.csv");
    std::vector<double> srclatitudes = doc.GetColumn<double>("src airport lat");
    std::vector<double> srclongitudes = doc.GetColumn<double>("src airport long");
    std::vector<double> dstlatitudes = doc.GetColumn<double>("dst airport lat");
    std::vector<double> dstlongitudes = doc.GetColumn<double>("dst airport long");
    
    std::vector<int> srcID = doc.GetColumn<int>("src airport ID");
    std::vector<int> dstID = doc.GetColumn<int>("dst airport ID");

    //Loop here setting up the routes




    return 0;
}
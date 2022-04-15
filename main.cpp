#include "WeightedGraph.h"
#include "Airport.h"
#include "rapidcsv.h"



int main() {


    //import airports
    //import routes

    WeightedGraph new_graph;

    //This stuff is for Airports
    //Stuff goes here
    /*rapidcsv::Document doc1("data/airports-preprocessed.csv");

    
    */

    //Loop setting up airports

    //This stuff should be for Routes
    rapidcsv::Document doc2("data/routes-preprocessed.csv");
    std::vector<double> srclatitudes = doc2.GetColumn<double>("src airport lat");
    std::vector<double> srclongitudes = doc2.GetColumn<double>("src airport long");
    std::vector<double> dstlatitudes = doc2.GetColumn<double>("dst airport lat");
    std::vector<double> dstlongitudes = doc2.GetColumn<double>("dst airport long");
    
    std::vector<int> srcID = doc2.GetColumn<int>("src airport ID");
    std::vector<int> dstID = doc2.GetColumn<int>("dst airport ID");

    //Loop here setting up the routes
    for(unsigned i = 0; i < srclatitudes.size() - 1; i++){   //all the vectors should be the same size, so
        double tempdistance = calcDistance(srclatitudes[i], srclongitudes[i], dstlatitudes[i], dstlongitudes[i]);
        new_graph.addRoute(srcID[i], dstID[i], tempdistance);
    }

    return 0;
}

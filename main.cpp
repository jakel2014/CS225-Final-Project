#include "WeightedGraph.h"
#include "Airport.h"


int main() {


    //import airports
    //import routes

    WeightedGraph new_graph;

    //This stuff is for Airports
    //Stuff goes here
    /*rapidcsv::Document doc1("data/airports-preprocessed.csv");
    std::vector<std::string> names = doc1.GetColumn<std::string>("name");
    std::vector<std::string> IATAs = doc1.GetColumn<std::string>("IATA");
    std::vector<std::string> ICAOs = doc1.GetColumn<std::string>("ICAO");

    std::vector<int> IDs = doc1.GetColumn<int>("ID");

    for (int i=0; i<5; i++) {     //Test to see that rapicsv works for airports
        std::cout << IDs[i] << " " << names[i] << " " << IATAs[i] << ICAOs[i] << std::endl; 
    }

    //Loop setting up airports

    for(unsigned i = 0; i < IDs.size() - 1; i++){
        new_graph.addAirport(id);
    }

    */

    //This stuff should be for Routes
    rapidcsv::Document doc2("data/routes-preprocessed.csv");
    std::vector<double> srclatitudes = doc2.GetColumn<double>("src airport lat");
    std::vector<double> srclongitudes = doc2.GetColumn<double>("src airport long");
    std::vector<double> dstlatitudes = doc2.GetColumn<double>("dst airport lat");
    std::vector<double> dstlongitudes = doc2.GetColumn<double>("dst airport long");
    
    std::vector<int> srcID = doc2.GetColumn<int>("src airport ID");
    std::vector<int> dstID = doc2.GetColumn<int>("dst airport ID");

    /*for (int i=0; i<5; i++) {     //Test to see that rapicsv works for routes
        double tempdistance = calcDistance(srclatitudes[i], srclongitudes[i], dstlatitudes[i], dstlongitudes[i]);
        std::cout << srcID[i] << " " << dstID[i] << " " << tempdistance << std::endl; 
    }*/

    //Loop here setting up the routes
    for(unsigned i = 0; i < srclatitudes.size() - 1; i++){   //all the vectors should be the same size, so
        double tempdistance = calcDistance(srclatitudes[i], srclongitudes[i], dstlatitudes[i], dstlongitudes[i]);
        new_graph.addRoute(srcID[i], dstID[i], tempdistance);
    }

    return 0;
}

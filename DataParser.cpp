#include "DataParser.h"

void DataParser::airports_helper(){
    //This stuff is for Airports
    rapidcsv::Document doc1("data/airports-preprocessed.csv");  //Load file with rapidcsv
    name = doc1.GetColumn<std::string>("name");
    iata = doc1.GetColumn<std::string>("IATA");
    icao = doc1.GetColumn<std::string>("ICAO");
    lat = doc1.GetColumn<double>("lat");
    lon = doc1.GetColumn<double>("long");

    id = doc1.GetColumn<ID>("ID");

    /*for (int i=0; i<5; i++) {     //Test to see that rapicsv works for airports
        std::cout << IDs[i] << " " << names[i] << " " << IATAs[i] << ICAOs[i] << std::endl; 
    }*/
}
void DataParser::routes_helper(){
    //This stuff should be for Routes
    rapidcsv::Document doc2("data/routes-preprocessed.csv");    //Load file with rapidcsv
    std::vector<double> srclatitudes = doc2.GetColumn<double>("src airport lat");   //Needed for distance calcs
    std::vector<double> srclongitudes = doc2.GetColumn<double>("src airport long");
    std::vector<double> dstlatitudes = doc2.GetColumn<double>("dst airport lat");
    std::vector<double> dstlongitudes = doc2.GetColumn<double>("dst airport long");
    
    srcID = doc2.GetColumn<ID>("src airport ID");
    dstID = doc2.GetColumn<ID>("dst airport ID");


    /*for (int i=0; i<5; i++) {     //Test to see that rapicsv works for routes
        double tempdistance = calcDistance(srclatitudes[i], srclongitudes[i], dstlatitudes[i], dstlongitudes[i]);
        std::cout << srcID[i] << " " << dstID[i] << " " << tempdistance << std::endl; 
    }*/

    //Loop here setting up the distances
    for(unsigned i = 0; i < srclatitudes.size() - 1; i++){   //all the vectors should be the same size, so
        double tempdistance = calcDistance(srclatitudes[i], srclongitudes[i], dstlatitudes[i], dstlongitudes[i]);
        distance.push_back(tempdistance);
    }
}

void DataParser::getRoutesData(std::vector<double> & distances, std::vector<ID> & sourceID,
    std::vector<ID> & destinationID){
        distances = this->distance;
        sourceID = this->srcID;
        destinationID = this->dstID;
    }


void DataParser::getAirportsData(std::vector<std::string> & portNames, std::vector<ID> & portID,
    std::vector<double> & portLatitudes, std::vector<double> & portLongitudes){
        portNames= this->name;
        portID = this->id;
        portLatitudes = this->lat;
        portLongitudes = this->lon;
    }

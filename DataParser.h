#pragma once

#include "rapidcsv.h"
#include "WeightedGraph.h"

class DataParser{
    public:
        DataParser(std::string airports_file, std::string routes_file);

        void getRoutesData(std::vector<double> & distances, std::vector<ID> & sourceID,
             std::vector<ID> & destinationID);
        void getAirportsData(std::vector<std::string> & portNames, std::vector<ID> & portID,
             std::vector<double> & portLatitudes, std::vector<double> & portLongitudes);

    private:

        void airports_helper();
        void routes_helper();

        rapidcsv::Document airports;
        rapidcsv::Document routes;

    //routes stats
        std::vector<double> distance;
        std::vector<ID> srcID, dstID;

    //airports stats
        std::vector<std::string> name;
        std::vector<double> lat, lon;
        std::vector<ID> id;

};
#include "WeightedGraph.h"
#include "Airport.h"
#include "DataParser.h"
#include "Visual.h"
#include <string>
#include <iostream>

void runDFS(std::string routes_path, std::string ports_path) {
    DataParser parser(ports_path, routes_path);
    WeightedGraph w(parser);

    std::vector<std::string> portNames; //Initialize all our variables for airports
    std::vector<ID> portID;
    std::vector<double> portLatitudes;
    std::vector<double> portLongitudes;
    parser.getAirportsData(portNames, portID, portLatitudes, portLongitudes);

    std::string port_name;
    std::cout << "Please enter a valid ICAO airport code for the DFS start point: ";
    std::cin >> port_name;
    ID port = 0;

    bool found = 0;
    std::map<ID, std::string> id_to_name;
    for (size_t i=0; i<portNames.size(); i++) {
        id_to_name[portID[i]] = portNames[i];

        if (!found && (portNames[i] == port_name)) {
            found = 1;
            port = portID[i];
        }
    }

    if (!found) {
        std::cout << "Invalid Input. Terminating Program." << std::endl;
        return;
    }

    std::queue<ID> dfs_traversal = w.DFS(port);
    for(unsigned i = 0; i < dfs_traversal.size(); i++){
        std::cout<<id_to_name[dfs_traversal.front()];
        if(i != dfs_traversal.size() - 1){
            std::cout<<"-->";
        }

        if (i%15 == 0) {
            std::cout << std::endl;
        }


        dfs_traversal.pop();
    }
    std::cout << std::endl;
    

}

void runDykstras(std::string routes_path, std::string ports_path) {
    DataParser parser(ports_path, routes_path);
    WeightedGraph w(parser);

    std::vector<std::string> portNames; //Initialize all our variables for airports
    std::vector<ID> portID;
    std::vector<double> portLatitudes;
    std::vector<double> portLongitudes;
    parser.getAirportsData(portNames, portID, portLatitudes, portLongitudes);

    std::string port1_name;
    std::cout << "Please enter a valid ICAO airport code for the Shortest Paths start point: ";
    std::cin >> port1_name;

    std::string port2_name;
    std::cout << "Please enter a valid ICAO airport code for the Shortest Paths end point: ";
    std::cin >> port2_name;

    ID port1 = 0, port2 = 0;

    bool found1 = 0, found2;
    std::map<ID, std::string> id_to_name;
    for (size_t i=0; i<portNames.size(); i++) {
        id_to_name[portID[i]] = portNames[i];

        if (!found1 && (portNames[i] == port1_name)) {
            found1 = 1;
            port1 = portID[i];
        }

        if (!found2 && (portNames[i] == port2_name)) {
            found2 = 1;
            port2 = portID[i];
        }
    }

    if (!(found1 & found2)) {
        std::cout << "Invalid Input/s. Terminating Program." << std::endl;
        return;
    }

    std::stack<Route> path = w.getShortestPath(port1, port2);


    int i=0;
    std::cout << id_to_name[path.top().getStart()]; 
    double dist = 0;
    while (!path.empty()) {
        Route curr = path.top();
        
        std::cout <<  " -> " << id_to_name[curr.getEnd()];
        i++;
        if (i==5 && path.size() != 1) {
            std::cout << std::endl;
            i=0;
        }
        if (path.size() == 1)
            dist = curr.getDist();
        path.pop();
    }
    std::cout << std::endl << "Total Distance: " << dist << " km" << std::endl;


}

void runDykstrasWithVisual(std::string routes_path, std::string ports_path, std::string image_path) {
    DataParser parser(ports_path, routes_path);
    WeightedGraph w(parser);

    Image worldMap;
    worldMap.readFromFile("images/world-map.png");
    Visual visual(worldMap);

    std::vector<std::string> portNames; //Initialize all our variables for airports
    std::vector<ID> portID;
    std::vector<double> portLatitudes;
    std::vector<double> portLongitudes;
    parser.getAirportsData(portNames, portID, portLatitudes, portLongitudes);

    std::string port1_name;
    std::cout << "Please enter a valid ICAO airport code for the Shortest Paths start point: ";
    std::cin >> port1_name;

    std::string port2_name;
    std::cout << "Please enter a valid ICAO airport code for the Shortest Paths end point: ";
    std::cin >> port2_name;

    ID port1 = 0, port2 = 0;

    bool found1 = 0, found2;
    std::map<ID, Airport> id_to_airport;
    for (size_t i=0; i<portNames.size(); i++) {
        id_to_airport[portID[i]] = Airport(portID[i], portLatitudes[i], portLongitudes[i], portNames[i]);


        if (!found1 && (portNames[i] == port1_name)) {
            found1 = 1;
            port1 = portID[i];
        }

        if (!found2 && (portNames[i] == port2_name)) {
            found2 = 1;
            port2 = portID[i];
        }
    }

    if (!(found1 & found2)) {
        std::cout << "Invalid Input/s. Terminating Program." << std::endl;
        return;
    }

    std::stack<Route> path = w.getShortestPath(port1, port2);

    std::vector<Airport> visualPath;
    visualPath.push_back(id_to_airport[port1]);
    while (!path.empty()) {
        Route curr = path.top();
        visualPath.push_back(id_to_airport[curr.getEnd()]);
        path.pop();
    } //initialize vector representing Aiports that represent shorted path

	visual.addTour(visualPath);

    //visual tour algorithm either directly in here or by function

    Image img;
    visual.getVisualOutput(img);

    img.writeToFile(image_path);

    std::cout << "Map generated at " << image_path << std::endl;


}

void runBasicVisual(std::string routes_path, std::string ports_path, std::string image_path) {
    DataParser parser(ports_path, routes_path);

    Image worldMap;
    worldMap.readFromFile("images/world-map.png");
    Visual visual(worldMap);

    std::vector<std::string> portNames; //Initialize all our variables for airports
    std::vector<ID> portID;
    std::vector<double> portLatitudes;
    std::vector<double> portLongitudes;
    parser.getAirportsData(portNames, portID, portLatitudes, portLongitudes);

    std::string port1_name;
    std::cout << "Please enter a valid ICAO airport code for the Shortest Paths start point: ";
    std::cin >> port1_name;

    std::string port2_name;
    std::cout << "Please enter a valid ICAO airport code for the Shortest Paths end point: ";
    std::cin >> port2_name;

    double lat1=0, long1=0, lat2=0, long2=0;

    ID id1, id2;
    bool found1=0, found2=0;
    for (size_t i=0; i<portNames.size(); i++) {
        if (portNames[i] == port1_name) {
            found1 = 1;
            lat1 = portLatitudes[i];
            long1 = portLongitudes[i];
        }

        if (portNames[i] == port2_name) {
            found2=1;
            lat2 = portLatitudes[i];
            long2 = portLongitudes[i];
        }

        if (found1 && found2)
            break;
    }

    if (!(found1 && found2)) {
        std::cout << "Invalid Input/s. Terminating Program." << std::endl;
        return;
    }

    visual.addLine(lat1, long1, lat2, long2);

    Image img;
    visual.getVisualOutput(img);

    img.writeToFile(image_path);

    std::cout << "Map generated at " << image_path << std::endl;

}

int main() {
    std::string routes_path, ports_path, image_path;
    routes_path = "data/routes-preprocessed.csv";
    ports_path = "data/airports-preprocessed.csv";
    image_path = "images/path_map.png";

    std::cout << "Hello CS225 Staff." << std::endl <<
        "This is the Route Planner created by Lucian Bontumasi, Jake Li, Eli Konopinski, and Satvik Yellanki"
        << std::endl << std::endl;

    std::string yes_no;
    std::cout << "Would you like to use a custom dataset? [Y/n] ";
    std::cin >> yes_no;
    std::transform(yes_no.begin(), yes_no.end(), yes_no.begin(), ::toupper);


    if(yes_no[0] == 'Y') {
        std::cout << "Enter the path to Airports CSV dataset you would like to use: " << std::endl;
        std::cin >> ports_path;
        
        std::cout << "Enter the path to Routes CSV dataset you would like to use: " << std::endl;
        std::cin >> routes_path;
    }

    std::ifstream ports_file(ports_path), routes_file(routes_path);

    if(!ports_file.is_open() || !routes_file.is_open()) {
        std::cout << "Invalid Input. Terminating Program." << std::endl;
        return 0;
    }



    std::cout << "1: Run a DFS traversal on the OpenFlights dataset." << std:: endl;
    std::cout << "2: Get Shortest Path between 2 aiports with a text output." << std::endl;
    std::cout << "3: Get the Shortest Path between 2 airports with a PNG output." << std::endl;
    std::cout << "4: Get an Image with the shortest line between two airports." << std::endl;

    std::string option;
    bool visual = 0;
    std::cout << "Please choose between the above 4 options by typing 1,2,3 or 4 and pressing Enter: ";
    std::cin >> option;

    if (option == "1") {
        runDFS(routes_path, ports_path);
        return 0;
    }
    
    if (option == "2") {
        runDykstras(routes_path, ports_path);
        return 0;
    }

    if(option != "3" && option != "4") {
        std::cout << "Invalid Input. Terminating Program." << std::endl;
        return 0;
    }

    std::string yes_no1;
    std::cout << "Would you like to output the image a custom path? [Y/n] ";
    std::cin >> yes_no1;
    std::transform(yes_no1.begin(), yes_no1.end(), yes_no1.begin(), ::toupper);


    if(yes_no1[0] == 'Y') {
        std::cout << "Enter the path to Image you would like to use: " << std::endl;
        std::cin >> image_path;
        
    }

    std::ifstream image_file(image_path);

    if(!image_file.is_open()) {
        std::cout << "Invalid Input. Terminating Program." << std::endl;
        return 0;
    }



    if (option == "3") {
        runDykstrasWithVisual(routes_path, ports_path, image_path);
        return 0;
    }

    if (option == "4") {
        runBasicVisual(routes_path, ports_path, image_path);
        return 0;
    }

    std::cout << "Invalid Input. Terminating Program." << std::endl;
    return 0;
}
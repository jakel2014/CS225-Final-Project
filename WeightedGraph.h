#pragma once

#include <iostream>
#include "Route.h"
#include <vector>
#include <queue>
#include <stack>
#include <map>


class WeightedGraph {
private:
    std::vector<ID> ports;
    std::map<ID, std::map<ID,double> > routes;
    std::map<ID, bool> marked;

    void markAirport(ID id);
    void markAirport(Airport port);

    bool isMarked(ID id);
    bool isMarked(Airport port);

    void clearMarks();

public:
    void addAirport(ID id);
    void addAirport(Airport port);

    void addRoute(ID startID, ID endID, double dist);
    void addRoute(Airport start, Airport end);
    void addRoute(Route route);

    std::vector<Route> allPaths(ID startID, ID endID);
    std::vector<Route> allPaths(Airport start, Airport end);

    std::stack<Route> getShortestPath(ID startID, ID endID);
    std::stack<Route> getShortestPAth(Airport start, Airport end);

    std::queue<ID> getAdjacentAirports(ID id);
    std::queue<ID> getAdjacentAirports(Airport port);

    std::queue<ID> DFS(Airport port);
};


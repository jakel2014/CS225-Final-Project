#include "WeightedGraph.h"

void WeightedGraph::markAirport(ID id) {
    marked[id] = true;
}
void WeightedGraph::markAirport(Airport port) {
    markAirport(port.getID());
}

bool WeightedGraph::isMarked(ID id) {
    return marked[id];
}
bool WeightedGraph::isMarked(Airport port) {
    return isMarked(port.getID());
}

void WeightedGraph::clearMarks() {
    for (std::pair<ID, bool> mark : marked)
        mark.second = false;
}

void WeightedGraph::addAirport(ID id) {
    marked[id] = false;
    ports.push_back(id);
}
void WeightedGraph::addAirport(Airport port) {
    addAirport(port.getID());
}

void WeightedGraph::addRoute(ID startID, ID endID, double dist) {
    routes[startID][endID] = dist;
}
void WeightedGraph::addRoute(Airport start, Airport end) {
    routes[start.getID()][end.getID()] = 
        calcDistance(start.getLat(), start.getLong(), end.getLat(), end.getLong());
}
void WeightedGraph::addRoute(Route route) {
    routes[route.getStart()][route.getEnd()] = route.getDist();
}

std::vector<Route> WeightedGraph::allPaths(ID startID, ID endID) {
    clearMarks();

    std::vector<Route> paths;
    std::queue<ID> ports;
    std::priority_queue<Route, std::vector<Route>, std::greater< std::vector<Route>::value_type> > pq;

    Route curr(startID, startID, 0.0);
    pq.push(curr);

    while(!pq.empty()) {
        curr = pq.top();
        pq.pop();
        ID end = curr.getEnd();

        if(!isMarked(end)) {
            markAirport(end);

            paths.push_back(curr);
            if (end == endID)
                return paths;
            curr.setStart(end);

            double min = curr.getDist();
            ports = getAdjacentAirports(curr.getStart());
            while(!ports.empty()) {
                ID adjacent = ports.front();

                if(!isMarked(adjacent))
                    pq.push(Route(end, adjacent, routes[end][adjacent]+min));
                pq.pop();
            }

        }


    }

    return paths;
}
std::vector<Route> WeightedGraph::allPaths(Airport start, Airport end) {
    return allPaths(start.getID(), end.getID());
}

std::stack<Route> WeightedGraph::getShortestPath(ID startID, ID endID) {
    std::vector<Route> paths = allPaths(startID, endID);
    std::stack<Route> shortestPath;

    clearMarks();

    ID search = endID;
    for (auto r = paths.rbegin(); r != paths.rend() && startID != search; ++r) {
        if (r->getEnd() == search) {
            shortestPath.push(*r);
            search = r->getStart();
        }
    }

    return shortestPath;
}
std::stack<Route> WeightedGraph::getShortestPAth(Airport start, Airport end) {
    return getShortestPath(start.getID(), end.getID());
}

std::queue<ID> WeightedGraph::getAdjacentAirports(ID id) {
    std::queue<ID> adjacentPorts;
    for (std::pair<ID, double> r : routes[id])
        adjacentPorts.push(r.first);

    return adjacentPorts;
}
std::queue<ID> WeightedGraph::getAdjacentAirports(Airport port) {
    return getAdjacentAirports(port.getID());
}

std::queue<ID> WeightedGraph::DFS(Airport port){
    std:queue<ID> dfs_traversal;
    clearMarks();

    ID id = port.getID();

    return DFS_helper(id, dfs_traversal);
}

std::queue<ID> WeightedGraph::DFS_helper(ID id, std::queue<ID> dfs_traversal){
     markAirport(id);

     dfs_traversal.push(id);
     std::queue<ID> adjacent = getAdjacentAirports(id);

     std::vector<ID> adj;

     while(!(adjacent.empty())){
        adj.push_back(adjacent.front());
        adjacent.pop();
     }

     for(ID & i : adj){
         if(!(isMarked(i))){
             DFS_helper(i, dfs_traversal);
         }
     }


}
#include "WeightedGraph.h"

WeightedGraph::WeightedGraph(DataParser & data) {

    std::vector<ID> portIDs;
    std::vector<std::string> names;
    std::vector<double> pt1, pt2;
    data.getAirportsData(names, portIDs, pt1, pt2);
    for (auto & id : portIDs) {
        addAirport(id);
    }
    
    std::vector<double> distances;
    std::vector<ID> sourceID, destinationID; 
    data.getRoutesData(distances, sourceID, destinationID);
    for (unsigned i=0; i<distances.size(); i++)
        addRoute(sourceID[i], destinationID[i], distances[i]);

}

WeightedGraph::WeightedGraph(){
    
}

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
    for (auto & mark : marked)
        mark.second = false;
}

void WeightedGraph::addAirport(ID id) {
    marked[id] = false;
    ports.push_back(id);
}
void WeightedGraph::addAirport(Airport port) {
    //ports_map[port.getID()] = port;
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
            std::queue<ID> ports = getAdjacentAirports(curr.getStart());
            while(!ports.empty()) {
                ID adjacent = ports.front();

                if(!isMarked(adjacent))
                    pq.push(Route(end, adjacent, routes[end][adjacent]+min));
                ports.pop();
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
std::stack<Route> WeightedGraph::getShortestPath(Airport start, Airport end) {
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

std::queue<ID> WeightedGraph::DFS(ID id){
    std::queue<ID> dfs_traversal; 

    std::set<ID> s_val;

    for(ID & i : ports){
        s_val.insert(i);
    }

    std::stack<ID> s; 
    s.push(id);

    while(!(s_val.empty())){
        s_val.erase(s.top());
        while(!(s.empty())){ 
            ID cur = s.top(); 
            s.pop(); 
            dfs_traversal.push(cur); 
            std::queue<ID> adjacent = getAdjacentAirports(cur); 

            while(!(adjacent.empty())){ 
                ID neighbor = adjacent.front(); 
                if(s_val.find(neighbor) != s_val.end()){ 
                    s.push(neighbor); 
                    s_val.erase(neighbor);
                }
                adjacent.pop();
            }
        }
        if(!(s_val.empty())){
            auto it = s_val.begin();
            ID cur = *it;
            s.push(cur);
        }
 
    }

    return dfs_traversal;
}



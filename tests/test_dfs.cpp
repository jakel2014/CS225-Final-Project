#include "../cs225/catch/catch.hpp"
#include "../WeightedGraph.h"


void load_graph(WeightedGraph & w) { //basic graph
    for (int i=1; i<6; i++)
        w.addAirport(i);
   
    w.addRoute(1,2,1);
    w.addRoute(1,3,5);
    w.addRoute(2,3,2);
    w.addRoute(2,4,7);
    w.addRoute(3,4,2);
    w.addRoute(4,5,3); 
}

TEST_CASE("DFS Basic Test", "[weight=1][part=1]") {
    WeightedGraph w;
    load_graph(w);
    
    std::queue<ID> dfs_traversal = w.DFS(1);

    REQUIRE(dfs_traversal.size() == 5);

    REQUIRE(dfs_traversal.front() == 1);

    dfs_traversal.pop();

    REQUIRE(dfs_traversal.front() == 3);

    dfs_traversal.pop();

    REQUIRE(dfs_traversal.front() == 4);

    dfs_traversal.pop();

    REQUIRE(dfs_traversal.front() == 5);

    dfs_traversal.pop();

    REQUIRE(dfs_traversal.front() == 2);
    /*REQUIRE(path.size() == 2);

    REQUIRE(path.top().getStart() == 1);
    REQUIRE(path.top().getEnd() == 2);
    path.pop();

    REQUIRE(path.top().getStart() == 2);
    REQUIRE(path.top().getEnd() == 3);
    REQUIRE(path.top().getDist() == 3);
    path.pop();

    REQUIRE( path.empty() == true );*/
}
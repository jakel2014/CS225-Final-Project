#include "../cs225"
#include "../WeightedGraph.h"

using namespace cs225;

TEST_CASE("Graph A, 1 to 3", "[weight=1][part=1]") {
    WeightedGraph w;
    for (int i=1; i<6; i++)
        w.addAirport(i);
   
    w.addRoute(1,2,1);
    w.addRoute(1,3,5);
    w.addRoute(2,3,2);
    w.addRoute(2,4,7);
    w.addRoute(3,4,2);
    w.addRoute(4,5,3);
    
    std::stack<Route> path = w.getShortestPath(1,3);

    REQUIRE(path.size() == 2);

    REQUIRE(path.top().getStart() == 1);
    REQUIRE(path.top().getStart() == 2);
    path.pop();

    REQUIRE(path.top().getStart() == 2);
    REQUIRE(path.top().getStart() == 3);
    path.pop();

    REQUIRE( path.empty() == true );
}

TEST_CASE("Graph A, 1 to 5", "[weight=1][part=1]") {
    WeightedGraph w;
    for (int i=1; i<6; i++)
        w.addAirport(i);
   
    w.addRoute(1,2,1);
    w.addRoute(1,3,5);
    w.addRoute(2,3,2);
    w.addRoute(2,4,7);
    w.addRoute(3,4,2);
    w.addRoute(4,5,3);
    
    std::stack<Route> path = w.getShortestPath(1,5);

    REQUIRE(path.size() == 4);

    REQUIRE(path.top().getStart() == 1);
    REQUIRE(path.top().getStart() == 2);
    path.pop();

    REQUIRE(path.top().getStart() == 2);
    REQUIRE(path.top().getStart() == 3);
    path.pop();

    REQUIRE(path.top().getStart() == 3);
    REQUIRE(path.top().getStart() == 4);
    path.pop();

    REQUIRE(path.top().getStart() == 4);
    REQUIRE(path.top().getStart() == 5);
    path.pop();

    REQUIRE( path.empty() == true );
}

TEST_CASE("Graph A, 1 to 3,5", "[weight=1][part=1]") {
    WeightedGraph w;
    for (int i=1; i<6; i++)
        w.addAirport(i);
   
    w.addRoute(1,2,1);
    w.addRoute(1,3,5);
    w.addRoute(2,3,2);
    w.addRoute(2,4,7);
    w.addRoute(3,4,2);
    w.addRoute(4,5,3);
    
    std::stack<Route> path13 = w.getShortestPath(1,3);
    std::stack<Route> path15 = w.getShortestPath(1,5);


    REQUIRE(path13.size() == 2);

    REQUIRE(path13.top().getStart() == 1);
    REQUIRE(path13.top().getStart() == 2);
    path13.pop();

    REQUIRE(path13.top().getStart() == 2);
    REQUIRE(path13.top().getStart() == 3);
    path13.pop();

    REQUIRE( path13.empty() == true );


    REQUIRE(path15.size() == 4);

    REQUIRE(path15.top().getStart() == 1);
    REQUIRE(path15.top().getStart() == 2);
    path15.pop();

    REQUIRE(path15.top().getStart() == 2);
    REQUIRE(path15.top().getStart() == 3);
    path15.pop();

    REQUIRE(path15.top().getStart() == 3);
    REQUIRE(path15.top().getStart() == 4);
    path15.pop();

    REQUIRE(path15.top().getStart() == 4);
    REQUIRE(path15.top().getStart() == 5);
    path15.pop();

    REQUIRE( path15.empty() == true );
}

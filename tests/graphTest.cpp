/**
 * @file: graphTest.cpp
 * @author: 0Ykahil
 * 
 * Tests for Graph class
 */

#define CATCH_CONFIG_MAIN
#include <fstream>
#include <iostream>
#include "catch.hpp"
#include "../include/Graph.h"
#include "../include/Airport.h"

TEST_CASE("Graph with 1 vertex") {
    size_t numAirports = 1;

    Airport a1("YOW", "Ottawa", "medium_airport", 45.3225, -75.6692);

    Graph g(numAirports);
    g.addVertex(a1);

    std::ostringstream outputstream;
    g.printGraph(outputstream);

    std::string expected = "Airport YOW (Ottawa) -> \n";

    REQUIRE(outputstream.str() == expected);
}

TEST_CASE("Graph with multiple vertices and edges") {
    size_t numAirports = 3;

    Airport a1("YOW", "Ottawa", "medium_airport", 45.3225, -75.6692);
    Airport a2("JFK", "New York", "large_airport", 40.6413, -73.7781);
    Airport a3("LAX", "Los Angeles", "large_airport", 33.9416, -118.4085);

    Graph g(numAirports);
    g.addVertex(a1);
    g.addVertex(a2);
    g.addVertex(a3);

    g.addEdge(a1, a2);
    g.addEdge(a2, a3);
    g.addEdge(a1, a3);

    std::ostringstream outputstream;
    g.printGraph(outputstream);

    std::string expected =
        "Airport YOW (Ottawa) -> JFK (293), LAX (2063), \n"
        "Airport JFK (New York) -> YOW (293), LAX (2145), \n"
        "Airport LAX (Los Angeles) -> JFK (2145), YOW (2063), \n";

    REQUIRE(outputstream.str() == expected);
}

TEST_CASE("Graph handles self-loop") {
    size_t numAirports = 1;

    Airport a1("YOW", "Ottawa", "medium_airport", 45.3225, -75.6692);

    Graph g(numAirports);
    g.addVertex(a1);
    g.addEdge(a1, a1);

    std::ostringstream outputstream;
    g.printGraph(outputstream);

    std::string expected = "Airport YOW (Ottawa) -> YOW (0), YOW (0), \n";

    REQUIRE(outputstream.str() == expected);
}

TEST_CASE("Generate graph from airport json (SINGLE airport, THRESHOLD = 250)") {

    std::ifstream file("testairports_single.json");
    nlohmann::json jsonData;
    file >> jsonData; 

    Graph g(jsonData.size());
    g.generateAirportGraph(jsonData, 250);

    std::ostringstream output;
    g.printGraph(output);

    std::string expected = "Airport CYOW (Ottawa Macdonald-Cartier International Airport) -> \n";

    REQUIRE(output.str() == expected);
}

TEST_CASE("Generate graph from airport json (MULTI airport, THRESHOLD = 250)") {

    std::ifstream file("testairports_multi.json");
    nlohmann::json jsonData;
    file >> jsonData; 

    Graph g(jsonData.size());
    g.generateAirportGraph(jsonData, 250);

    std::ostringstream output;
    g.printGraph(output);

    std::string expected = "Airport CYOW (Ottawa Macdonald-Cartier International Airport) -> CYYZ (196), KIAG (193), \n"
                           "Airport KMDW (Chicago Midway International Airport) -> \n"
                           "Airport CYYZ (Lester B. Pearson International Airport) -> CYOW (196), KCLE (167), KIAG (45), \n"
                           "Airport KCLE (Cleveland Hopkins International Airport) -> CYYZ (167), KIAG (164), \n"
                           "Airport KIAG (Niagara Falls International Airport) -> CYOW (193), CYYZ (45), KCLE (164), \n";

    REQUIRE(output.str() == expected);
}

TEST_CASE("Generate graph from airport json (MULTI airport, THRESHOLD = 280)") {

    std::ifstream file("testairports_multi.json");
    nlohmann::json jsonData;
    file >> jsonData; 

    Graph g(jsonData.size());
    g.generateAirportGraph(jsonData, 280);

    std::ostringstream output;
    g.printGraph(output);

    std::string expected = "Airport CYOW (Ottawa Macdonald-Cartier International Airport) -> CYYZ (196), KIAG (193), \n"
                           "Airport KMDW (Chicago Midway International Airport) -> KCLE (265), \n"
                           "Airport CYYZ (Lester B. Pearson International Airport) -> CYOW (196), KCLE (167), KIAG (45), \n"
                           "Airport KCLE (Cleveland Hopkins International Airport) -> KMDW (265), CYYZ (167), KIAG (164), \n"
                           "Airport KIAG (Niagara Falls International Airport) -> CYOW (193), CYYZ (45), KCLE (164), \n";

    REQUIRE(output.str() == expected);
}

TEST_CASE("Generate graph from airport json (MULTI airport, THRESHOLD = 100)") {

    std::ifstream file("testairports_multi.json");
    nlohmann::json jsonData;
    file >> jsonData; 

    Graph g(jsonData.size());
    g.generateAirportGraph(jsonData, 100);

    std::ostringstream output;
    g.printGraph(output);

    std::string expected = "Airport CYOW (Ottawa Macdonald-Cartier International Airport) -> \n"
                           "Airport KMDW (Chicago Midway International Airport) -> \n"
                           "Airport CYYZ (Lester B. Pearson International Airport) -> KIAG (45), \n"
                           "Airport KCLE (Cleveland Hopkins International Airport) -> \n"
                           "Airport KIAG (Niagara Falls International Airport) -> CYYZ (45), \n";

    REQUIRE(output.str() == expected);
}



/**
 * @file: flightPathOptimizer.cpp
 * @author: 0Ykahil
 * 
 * Handles JSON data parsing, implements edge calculations, and utilizes 
 * Dijkstra's algorithm to find the shortest path between a given start 
 * point and destination airport.
 */
#include <fstream>
#include <iostream>
#include <chrono>
#include "../include/Graph.h"

/**
 * THRESHOLD will control the cutoff for the edge creation for the graph
 * and dictate when an edge will be made (distance between both locations <= THRESHOLD).
 *
 * NOTE: This will typically be what you will change depending on the aircraft's
 *       MAX range after calculating for fuel burning, wind, etc.
 */
const int THRESHOLD = 280;

int main() {
    // Read the json file into jsonData
    std::cout << "reading file... ";
    std::ifstream file("./datasets/testairports.json");
    nlohmann::json jsonData;
    file >> jsonData; // read the airports file into json object
    std::cout << "done" << std::endl;

    // Creating AirportGraph

    std::cout << "generating airport graph... ";
    auto t1 = std::chrono::high_resolution_clock::now();

    Graph g(jsonData.size());
    g.generateAirportGraph(jsonData, THRESHOLD, true);

    auto t2 = std::chrono::high_resolution_clock::now();

    // Creating visual dot file of graph found in ./dot_files/
    g.toDOT("./dot_files/airports.dot");


    // Calculating time taken to generate the graph
    std::chrono::duration<double, std::milli> ms_double = t2 - t1;
    std::cout << "done" << std::endl;
    std::cout << "time taken: " << ms_double.count() << "ms" << std::endl;
    g.printGraph();

}
/**
 * @file: graph.h
 * @author: 0Ykahil
 * 
 * Declaration of Graph
 */
#pragma once

#include <fstream>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <limits>
#include <list>
#include <utility>
#include <thread>
#include <mutex>
#include "Airport.h"
#include "Edge.h"
#include "../external/json.hpp" 

typedef std::pair<int, int> iPair;

/**
 * @class Graph 
 * Represents a Graph of airports represented by an adjacency list of airports.
 */
class Graph {
    public:
        /**
         * Constructs an empty graph with given numVertices and if it is weighted.
         * 
         * @param numVertices the number of vertices.
         */
        Graph(size_t numVertices);

        /**
         * Adds an Airport vertex to the graph and maps it to an id in vertices
         * 
         * @param airport The airport vertex being added
         */
        void addVertex(const Airport& airport);

        /**
         * Adds an edge to the graph given a source airport and destination airport, and calculates its weight (distance)
         * 
         * @param source The source airport. 
         * @param dest The destination airport.
         */
        void addEdge(const Airport& source, const Airport& dest);

        /**
         * Prints out the graph in the format "Airport n (identifier) -> ..."
         * and displays it in the console.
         */
        void printGraph() const;

        // Print the graph to a given output stream
        void printGraph(std::ostream& os) const;

        /**
         * Generates an airport graph with airports as the vertices and distances as the edges 
         * represented by an adjacency list, ONLY creating edges where the **distance < threshold**.
         * 
         * @param jsonData The JsonData containing airport identifier, name, location, etc. data to be parsed.
         * @param threshold The threshold in nautical miles, where edges will be created if below it (realistic range of aircraft).
         * @param useMultithreading If True, the function will use multithreading when creating the edge list, this is to speed up the generating for dense sets
         */
        void generateAirportGraph(const nlohmann::json& jsonData, const int threshold, bool useMultithreading);

        /**
         * Finds the shortest path from start airport to destination airport using Dijkstra's algorithm
         * and prints out the path in order if it is reachable.
         * If NOT reachable, prints (cannot reach)
         * 
         * @param start The starting Airport
         * @param destination The destination Airport
         */
        std::pair <std::vector<int>, double> findShortestPath(const Airport& start, const Airport& destination);

        /**
         * Converts startID and destID to their corresponding airports, and 
         * Maps the elements of the resulting array of findShortestPath() on the given ids
         * back to strings, and prints them out
         * 
         * @param startID The id of the starting Airport (e.g. CYYZ, CYOW)
         * @param destID The id of the destination Airport
         */
        void printShortestPath(const std::string startID, const std::string destID);
        void printShortestPath(const std::string startID, const std::string destID, std::ostream& os); // ostream version for testing purposes

        // Creates a dot diagram to be used with graphviz for visualizing the graphs
        void toDOT(const std::string& filename) const;

        // Returns the list containing the airport objects
        std::vector<Airport> getAirports() const;
    private:
        size_t numVertices; // The current number of vertices in the graph.
        std::vector<std::list<Edge>> adjList; // the adjacency list containing the edges.
        std::vector<Airport> vertices; // The vertices (airports) in the graph.
        std::unordered_map<std::string, size_t> airportToIndex; // Maps airport id to an index
        std::mutex mtx; // Mutex for thread-safe operations
};

#ifndef GRAPH_H_
#define GRAPH_H_

#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <exception>
#include "json.hpp"

using std::vector;
using std::string;
using std::unordered_map;
using std::unordered_set;
using nlohmann::json;

class Graph {
private:
    unordered_set<string> vertices;

    // edges["a"]["b"] == vector of weights of edge from "a" to "b"
    // Note: The use of a vector is in the event there are multiple edges between two vertices.
    //       For simple graphs, the size of this vector will always be 1.
    // Note: if graph is not weighted, all weights are considered to be 1.
    unordered_map<string, unordered_map<string, vector<double>>> edges;

    bool weighted, directed;

    string jsonAnalysis(const json&);

    void processQuery(string);

public:
    Graph(const string);
    void readQueries();
};

#endif
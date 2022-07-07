#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <string>
#include <unordered_map>

using std::vector;
using std::string;
using std::unordered_map;

class Graph {
private:
    vector<string> vertices;

    unordered_map<string, unordered_map<string, int>> edges; // edges["a"]["b"] == weight of edge from "a" to "b"
    // Note: if graph is not weighted, all weights are considered to be 1.

    bool weighted, directed;

    bool jsonIsValid();

    void processQuery(string);

public:
    Graph(const char*);
    void readQueries();
};

#endif
#ifndef GRAPH_H_
#define GRAPH_H_

#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <exception>
#include <queue>
#include "json.hpp"

using std::vector;
using std::string;
using std::unordered_map;
using std::unordered_set;
using nlohmann::json;
using std::pair;

class Graph {
private:
    class Summary {
    private:
        Graph &g;
        unordered_map<string, bool> graph_facts; // TODO
        int simple, connected, bipartite, complete, planar, eulerian, containsCycle = -1;

        // T must have ".name" ability
        template <typename T>
        void bfs(bool, T (*)(T, pair<string, vector<double>>));

    public:
        Summary(Graph &g) : g(g) {}
        bool isSimple();

        // Basic info: simple/multi, connected/disconnected, bipartite, complete, planar, eulerian, [hamiltonian?], cycle detection
        void produceSummary();
    };

    Summary graphInfo;

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
#include "Graph.h"
using namespace std;

Graph::Graph(const string filename) {
    ifstream file(filename);
    if (!file.good())
        throw runtime_error("Could not locate file " + filename);
    json j;
    file >> j;
    
    file.close();
}

string Graph::jsonAnalysis(const json& j) {
    // Check all keys exist, and that each has proper value type
    unordered_map<string, nlohmann::detail::value_t> keysAndTypes = {
        {"vertices", json::value_t::array},
        {"edges", json::value_t::array},
        {"directed", json::value_t::boolean},
        {"weighted", json::value_t::boolean}
    };

    for (auto& s : j.items()) {
        if (!keysAndTypes.count(s.key()) || j[s.key()].type() != keysAndTypes[s.key()])
            return "Key " + s.key() + " is undefined, or has invalid type";
        keysAndTypes.erase(s.key());
    }
    if (!keysAndTypes.empty())
        return "Missing one or more of the following: vertices, edges, directed, weighted";

    directed = j["directed"];
    weighted = j["weighted"];

    for (auto& s : j["vertices"]) {
        if (s.type() != json::value_t::string)
            return "Vertex names must be strings";
        if (vertices.count(string(s)))
            return "Duplicate vertex names detected";
        vertices.insert(string(s));
    }

    int required_size = (weighted) ? 3 : 2;

    for (auto& v : j["edges"]) {
        // Error checking for edge
        if (v.type() != json::value_t::array)
            return "Edge must be represented as json array";
        else if (v.size() != required_size)
            return "Invalid array size for one or more edges";
        else if (v[0].type() != json::value_t::string || v[1].type() != json::value_t::string)
            return "Edge must be represented as [string, string, (int, if weighted)]";
        else if (!vertices.count(string(v[0])))
            return "Edge includes non-existent vertex " + string(v[0]);
        else if (!vertices.count(string(v[1])))
            return "Edge includes non-existent vertex " + string(v[1]);
        else if (required_size == 3 && v[2].type() != json::value_t::number_float)
            return "Edge weight must be a floating point value";
        else {
            double val = (required_size == 3) ? double(v[2]) : 1.0;
            edges[string(v[0])][string(v[1])].push_back(val);
        }
    }

    return "";
}
#pragma once
#include "graph.h"
#include "dijkstra.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>

// JSON exporter for web UI: writes graph.json and route.json
// Simple handcrafted JSON to avoid external libs.

struct PlaceInfo {
    std::string name;
    double lat;
    double lng;
};

inline void writeGraphJson(const Graph& g, const std::string& path) {
    std::ofstream out(path);
    if (!out.is_open()) return;
    out << "{\n  \"nodes\": {\n";
    bool firstNode = true;
    // Assign real Delhi place names and coordinates (closer together for real roads)
    std::unordered_map<char, PlaceInfo> places = {
        {'A', {"Connaught Place", 28.6308, 77.2177}},
        {'B', {"Palika Bazar", 28.6315, 77.2185}},
        {'C', {"Janpath", 28.6295, 77.2190}},
        {'D', {"Barakhamba", 28.6320, 77.2150}},
        {'E', {"Bengali Market", 28.6285, 77.2200}},
        {'F', {"Parliament Street", 28.6270, 77.2140}},
        {'G', {"India Gate", 28.6297, 77.2245}},
        {'H', {"Patel Chowk", 28.6330, 77.2160}},
        {'I', {"Rajiv Chowk", 28.6310, 77.2190}},
        {'J', {"Barakhamba Road", 28.6325, 77.2175}},
        {'K', {"Moolchand", 28.5696, 77.2194}},
        {'L', {"Lajpat Nagar", 28.5672, 77.2433}},
        {'M', {"South Extension", 28.5696, 77.2194}},
        {'N', {"Defence Colony", 28.5805, 77.2315}},
        {'O', {"Greater Kailash", 28.5438, 77.2489}},
        {'P', {"Hauz Khas", 28.5539, 77.2081}},
        {'Q', {"Green Park", 28.5642, 77.2034}},
        {'R', {"Saket", 28.5285, 77.2069}},
        {'S', {"Kalkaji", 28.5400, 77.2500}},
        {'T', {"Nehru Place", 28.5470, 77.2510}}
    };
    for (char u : g.nodes()) {
        if (!firstNode) out << ",\n";
        out << "    \"" << u << "\": {\"name\": \"" << places[u].name << "\", \"coords\": [" << places[u].lat << ", " << places[u].lng << "]}";
        firstNode = false;
    }
    out << "\n  },\n  \"edges\": [\n";
    bool firstEdge = true;
    for (auto& e : g.edgesUniqueUndirected()) {
        if (!firstEdge) out << ",\n";
        char a, b; int w; std::tie(a, b, w) = e;
        out << "    {\"from\": \"" << a << "\", \"to\": \"" << b << "\", \"weight\": " << w << "}";
        firstEdge = false;
    }
    out << "\n  ]\n}\n";
}

inline void writeRouteJson(const PathResult& res, const std::string& path) {
    std::ofstream out(path);
    if (!out.is_open()) return;
    if (res.path.empty() || res.distance == std::numeric_limits<int>::max()) {
        out << "{\"error\": \"No path found\"}\n";
        return;
    }
    out << "{\n  \"path\": [";
    for (size_t i = 0; i < res.path.size(); ++i) {
        out << "\"" << res.path[i] << "\"";
        if (i + 1 < res.path.size()) out << ", ";
    }
    out << "],\n  \"distance\": " << res.distance << "\n}\n";
}

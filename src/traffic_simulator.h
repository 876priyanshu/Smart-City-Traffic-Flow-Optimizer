#pragma once
#include "graph.h"
#include "json_exporter.h"
#include <random>
#include <vector>
#include <string>
#include <tuple>
#include <fstream>
#include <iostream>

// Traffic simulator ~80 LOC
// - Randomly changes weights (bounded deltas)
// - Logs changes to data/traffic_logs.txt
// - Provides summary trend (avg delta)

struct TrafficChange { char u; char v; int delta; int newWeight; };

inline void simulateTraffic(Graph& g) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(-3, 5);
    
    std::cout << "\n🚦 Simulating traffic...\n";
    for (auto& e : g.edgesUniqueUndirected()) {
        char u = std::get<0>(e); char v = std::get<1>(e);
        int w = g.getWeight(u, v);
        int change = dist(gen);
        int newWeight = std::max(1, w + change);
        g.setWeight(u, v, newWeight);
        std::cout << "  Edge " << u << "-" << v << ": " << w << " -> " << newWeight << " min\n";
    }
    
    // Re-export JSON with updated weights
    writeGraphJson(g, "web/graph.json");
    std::cout << "\n✅ JSON updated with new traffic data!\n";
    std::cout << "💡 Refresh the web page to see updated traffic conditions.\n";
}

class TrafficSimulator {
    std::mt19937 rng;
    std::string logPath;
public:
    explicit TrafficSimulator(std::string logFile = "data/traffic_logs.txt")
        : rng(std::random_device{}()), logPath(std::move(logFile)) {}

    std::vector<TrafficChange> apply(Graph& g, int changes=4, int minDelta=-3, int maxDelta=6){
        std::vector<TrafficChange> out; auto edges=g.edgesUniqueUndirected(); if(edges.empty()) return out;
        std::uniform_int_distribution<int> idx(0,(int)edges.size()-1); std::uniform_int_distribution<int> del(minDelta,maxDelta);
        for(int i=0;i<changes;i++){
            auto tup = edges[idx(rng)]; char a=std::get<0>(tup); char b=std::get<1>(tup);
            int d = del(rng); if(d==0) d=1; g.addWeightDelta(a,b,d);
            TrafficChange tc{a,b,d,g.getWeight(a,b)}; out.push_back(tc);
        }
        appendLog(out); return out;
    }

    void appendLog(const std::vector<TrafficChange>& changes){
        std::ofstream out(logPath, std::ios::app); if(!out.is_open()) return;
        for(auto &c: changes){ out << c.u << ' ' << c.v << ' ' << c.delta << ' ' << c.newWeight << "\n"; }
    }

    static double averageDelta(const std::vector<TrafficChange>& v){ if(v.empty()) return 0.0; long long s=0; for(auto &c:v) s+=c.delta; return (double)s/v.size(); }
};

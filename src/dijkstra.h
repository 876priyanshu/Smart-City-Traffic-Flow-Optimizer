#pragma once
#include "graph.h"
#include <queue>
#include <unordered_map>
#include <limits>
#include <functional>
#include <algorithm>
#include <iostream>

// Dijkstra module ~130 LOC including extras:
// - Computes shortest path from src to dst
// - Prints distance table when requested
// - Supports on-visit callback for visualization

struct PathResult {
    int distance = std::numeric_limits<int>::max();
    std::vector<char> path;
};

inline void printDistanceTable(const std::unordered_map<char,int>& dist){
    std::vector<std::pair<char,int>> v(dist.begin(), dist.end());
    std::sort(v.begin(), v.end(), [](auto&a, auto&b){return a.first<b.first;});
    std::cout << "+------+-----------+\n";
    std::cout << "| Node | Distance |\n";
    std::cout << "+------+-----------+\n";
    for(auto &p: v){
        std::cout << "|  "<<p.first<<"   | ";
        if(p.second==std::numeric_limits<int>::max()) std::cout << "INF";
        else std::cout << p.second;
        std::cout << std::string(9,' ').substr(0,9) << "|\n";
    }
    std::cout << "+------+-----------+\n";
}

inline PathResult dijkstra(const Graph& g, char src, char dst,
                           std::function<void(char,int)> onVisit=nullptr,
                           bool verbose=false){
    using P = std::pair<int,char>; // (dist, node)
    std::priority_queue<P, std::vector<P>, std::greater<P>> pq;
    std::unordered_map<char,int> dist;
    std::unordered_map<char,char> parent;

    auto nodes = g.nodes();
    for(char u: nodes) dist[u]=std::numeric_limits<int>::max();
    if(!g.hasNode(src) || !g.hasNode(dst)) return {};

    dist[src]=0; pq.push(P(0,src));
    while(!pq.empty()){
        P top = pq.top(); pq.pop();
        int d = top.first; char u=top.second;
        if(d!=dist[u]) continue; // stale
        if(onVisit) onVisit(u,d);
        if(u==dst) break;
        for(const auto &e: g.neighbors(u)){
            char v=e.v; int w=e.w;
            if(dist[v] > dist[u] + w){
                dist[v] = dist[u] + w; parent[v]=u; pq.push(P(dist[v], v));
            }
        }
    }

    if(verbose) printDistanceTable(dist);

    PathResult res; res.distance = dist.count(dst)? dist[dst] : std::numeric_limits<int>::max();
    if(res.distance==std::numeric_limits<int>::max()) return res;

    // Reconstruct
    std::vector<char> rev; char cur=dst; rev.push_back(cur);
    while(cur!=src){ auto it=parent.find(cur); if(it==parent.end()){ rev.clear(); break; } cur=it->second; rev.push_back(cur);} 
    std::reverse(rev.begin(), rev.end()); res.path=rev; return res;
}

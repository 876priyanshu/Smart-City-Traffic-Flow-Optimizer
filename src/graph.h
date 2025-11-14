#pragma once
#include <unordered_map>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <set>
#include <iostream>

// Graph module (adjacency list) ~120 LOC including comments
// - Load from file (u v w per line)
// - Validate nodes
// - Display adjacency and degree
// - Provide helpers for algorithms and visualization

struct Edge { char v; int w; };

class Graph {
public:
    // adjacency list: node -> list of (neighbor, weight)
    std::unordered_map<char, std::vector<Edge>> adj;

    bool hasNode(char u) const { return adj.find(u)!=adj.end(); }

    std::vector<char> nodes() const {
        std::set<char> s;
        for (auto &kv: adj) s.insert(kv.first);
        return std::vector<char>(s.begin(), s.end());
    }

    const std::vector<Edge>& neighbors(char u) const {
        static const std::vector<Edge> empty;
        auto it=adj.find(u); return it==adj.end()? empty : it->second;
    }

    void addEdge(char u, char v, int w){
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }

    bool setWeight(char u, char v, int w){
        bool ok=false;
        auto upd=[&](char a,char b){
            auto it=adj.find(a); if(it==adj.end()) return; 
            for(auto &e: it->second) if(e.v==b){ e.w=w; ok=true; }
        }; upd(u,v); upd(v,u); return ok;
    }

    bool addWeightDelta(char u, char v, int d){
        bool ok=false;
        auto upd=[&](char a,char b){
            auto it=adj.find(a); if(it==adj.end()) return; 
            for(auto &e: it->second) if(e.v==b){ e.w = std::max(1, e.w + d); ok=true; }
        }; upd(u,v); upd(v,u); return ok;
    }

    int getWeight(char u, char v) const {
        auto it=adj.find(u); if(it==adj.end()) return -1;
        for(auto &e: it->second) if(e.v==v) return e.w; return -1;
    }

    std::vector<std::tuple<char,char,int>> edgesUniqueUndirected() const {
        std::set<std::pair<char,char>> seen; std::vector<std::tuple<char,char,int>> out;
        for (auto &kv: adj){ char u=kv.first; for(auto &e: kv.second){ char v=e.v; int w=e.w; char a=std::min(u,v), b=std::max(u,v); if(!seen.count({a,b})){ seen.insert({a,b}); out.emplace_back(a,b,w);} }}
        return out;
    }

    void clear(){ adj.clear(); }

    // Load: each line "U V W"; lines starting with # ignored
    bool loadFromFile(const std::string& path){
        std::ifstream in(path); if(!in.is_open()) return false; clear();
        std::string line; while(std::getline(in,line)){
            if(line.empty() || line[0]=='#') continue; std::stringstream ss(line);
            char u,v; int w; if(ss>>u>>v>>w){ addEdge(u,v,w);} }
        return true;
    }

    // Debug/Display: print adjacency info
    void printSummary(std::ostream& os=std::cout) const{
        os << "Nodes: "; auto ns=nodes(); for(char u: ns) os<<u<<" "; os<<"\n";
        for(char u: ns){ os<<u<<": "; for(auto &e: neighbors(u)) os<<"("<<e.v<<","<<e.w<<") "; os<<"\n"; }
    }

    // Simple ASCII adjacency table
    void printTable(std::ostream& os=std::cout) const{
        auto ns = nodes(); os << "+------+---------------------------+\n";
        os << "| Node | Neighbors (v:w)          |\n";
        os << "+------+---------------------------+\n";
        for(char u: ns){ os << "|  "<<u<<"   | "; bool first=true; for(auto &e: neighbors(u)){ if(!first) os<<", "; first=false; os<<e.v<<":"<<e.w; } os << std::string(27, ' ').substr(0,27) << "|\n"; }
        os << "+------+---------------------------+\n";
    }
};

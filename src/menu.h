#pragma once
#include "graph.h"
#include "dijkstra.h"
#include "traffic_simulator.h"
#include "visualize.h"
#include "file_manager.h"
#include "json_exporter.h"
#include <iostream>
#include <cstdlib>

// Menu ~90 LOC
// - Top-level navigation
// - Routing flow
// - Visualization screen

class Menu{
    Graph& graph; TrafficSimulator sim; std::string histPath;
public:
    Menu(Graph& g, std::string history): graph(g), sim("data/traffic_logs.txt"), histPath(std::move(history)){}

    static void cls(){ std::system("cls"); }

    void title(){
        using namespace UI; std::cout << "===============================\n";
        std::cout << " " << GREEN << "SMART CITY TRAFFIC OPTIMIZER" << RESET << "\n";
        std::cout << "===============================\n";
    }

    void showMain(){
        title();
        std::cout << "1. Display City Map\n2. Find Shortest Route\n3. Simulate Traffic\n4. View Route History\n5. Visualize Path\n6. Exit\nSelect option: ";
    }

    void showGraph(){ loading("Rendering city..."); drawCity(graph, {}); pause(); }

    void findRoute(){
        using namespace UI; char s,d; std::cout<<"Enter source (A-J): "; std::cin>>s; std::cout<<"Enter destination (A-J): "; std::cin>>d; loading("Finding route...");
        std::vector<char> visit; auto res = dijkstra(graph,s,d,[&](char u,int dist){ visit.push_back(u); }, true);
        if(res.path.empty() || res.distance==std::numeric_limits<int>::max()){ std::cout<<UI::RED<<"No path found."<<UI::RESET<<"\n"; pause(); return; }
        std::cout<<UI::GREEN<<"Shortest Path: "<<UI::RESET; for(size_t i=0;i<res.path.size();++i){ std::cout<<res.path[i]; if(i+1<res.path.size()) std::cout<<" -> "; }
        std::cout<<"\nTime: "<<res.distance<<" minutes\n"; drawCity(graph, res.path);
        std::string route; for(size_t i=0;i<res.path.size();++i){ route.push_back(res.path[i]); if(i+1<res.path.size()) route+="->"; }
        appendHistory(histPath, route, res.distance); std::cout<<UI::GREEN<<"Saved to history."<<UI::RESET<<"\n";
        // Export route JSON for web UI
        writeRouteJson(res, "data/route.json");
        std::cout << UI::GREEN << "Exported route to data/route.json for web UI." << UI::RESET << "\n";
        pause();
    }

    void simulate(){ loading("Updating road conditions..."); auto changes = sim.apply(graph, 4); using namespace UI; if(changes.empty()){ std::cout<<RED<<"No edges to update."<<RESET<<"\n"; }
        else { for(auto &c: changes){ if(c.delta>0) std::cout<<RED<<"Traffic increased on "<<c.u<<"-"<<c.v<<" by "<<c.delta<<" min. New="<<c.newWeight<<RESET<<"\n"; else std::cout<<GREEN<<"Traffic eased on "<<c.u<<"-"<<c.v<<" by "<<-c.delta<<" min. New="<<c.newWeight<<RESET<<"\n"; } }
        // Re-export graph after simulation
        writeGraphJson(graph, "data/graph.json");
        std::cout << UI::GREEN << "Updated data/graph.json for web UI." << UI::RESET << "\n";
        pause(); }

    void history(){ auto lines=readHistory(histPath); if(lines.empty()) std::cout<<"No history yet.\n"; else { std::cout<<"Past Routes:\n"; for(auto &s: lines) std::cout<<"- "<<s<<"\n"; } pause(); }

    void visualize(){ char s,d; std::cout<<"Enter source (A-J): "; std::cin>>s; std::cout<<"Enter destination (A-J): "; std::cin>>d; loading("Visualizing..."); auto res=dijkstra(graph,s,d,nullptr,false); drawCity(graph, res.path); pause(); }

    static void pause(){ std::cout<<"\nPress Enter to continue..."; std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); std::cin.get(); }
};

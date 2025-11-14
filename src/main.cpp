#include "graph.h"
#include "menu.h"
#include "visualize.h"
#include "json_exporter.h"
#include <iostream>

int main(){
    using namespace UI;
    std::cout<< BLUE << "Loading Smart City graph..." << RESET << "\n";
    Graph g; if(!g.loadFromFile("data/city_map.txt")){ std::cout<<RED<<"Failed to load data/city_map.txt"<<RESET<<"\n"; return 1; }
    loading("Initializing modules...", 800);
    // Export graph for web UI
    writeGraphJson(g, "data/graph.json");
    std::cout << GREEN << "Exported graph to data/graph.json for web UI." << RESET << "\n";

    Menu menu(g, "data/routes_history.txt");
    while(true){
        std::system("cls"); menu.showMain(); int ch; if(!(std::cin>>ch)) break; if(ch==6){ std::cout<<GREEN<<"Goodbye!"<<RESET<<"\n"; break; }
        switch(ch){
            case 1: std::system("cls"); menu.showGraph(); break;
            case 2: std::system("cls"); menu.findRoute(); break;
            case 3: std::system("cls"); menu.simulate(); break;
            case 4: std::system("cls"); menu.history(); break;
            case 5: std::system("cls"); menu.visualize(); break;
            default: std::cout<<RED<<"Invalid option."<<RESET<<"\n"; std::cin.clear(); std::cin.ignore(1024,'\n'); break;
        }
    }
    return 0;
}

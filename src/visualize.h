#pragma once
#include "graph.h"
#include <vector>
#include <string>
#include <iostream>
#include <map>
#if defined(_WIN32)
#include <windows.h>
#else
#include <chrono>
#include <thread>
#endif

// Visualization ~70 LOC
// - Draw ASCII city layout
// - Highlight path
// - Simple loading animation and colors (ANSI)

namespace UI{
    static const std::string RESET="\033[0m";
    static const std::string GREEN="\033[32m";
    static const std::string RED="\033[31m";
    static const std::string YELLOW="\033[33m";
    static const std::string BLUE="\033[34m";
    static const std::string CYAN="\033[36m";
}

#if defined(_WIN32)
inline void sleepms(int ms){ Sleep(ms); }
#else
inline void sleepms(int ms){ std::this_thread::sleep_for(std::chrono::milliseconds(ms)); }
#endif

struct Layout{ int H=17,W=40; std::map<char,std::pair<int,int>> pos; };

inline Layout defaultLayout(){ Layout L; 
    L.pos['A']={2,4}; L.pos['B']={2,18}; L.pos['C']={6,4}; L.pos['D']={6,18};
    L.pos['E']={6,30}; L.pos['F']={2,30}; L.pos['G']={11,12}; L.pos['H']={11,30};
    L.pos['I']={14,6}; L.pos['J']={14,20};
    return L; }

inline void drawLine(std::vector<std::string>& grid, int y1,int x1,int y2,int x2){
    if(y1==y2){ int a=std::min(x1,x2), b=std::max(x1,x2); for(int x=a+1;x<b;x++) grid[y1][x]='-'; }
    else if(x1==x2){ int a=std::min(y1,y2), b=std::max(y1,y2); for(int y=a+1;y<b;y++) grid[y][x1]='|'; }
    else { int dy=(y2>y1)?1:-1, dx=(x2>x1)?1:-1; int y=y1+dy,x=x1+dx; while(y!=y2 && x!=x2){ grid[y][x]=(dx==dy?'/':'\\'); y+=dy; x+=dx; } }
}

inline void drawCity(const Graph& g, const std::vector<char>& highlightPath={}){
    using namespace std; auto L=defaultLayout(); vector<string> grid(L.H, string(L.W,' '));
    auto edges=g.edgesUniqueUndirected(); for(auto &t: edges){ char u,v; int w; std::tie(u,v,w)=t; auto pu=L.pos.count(u)?L.pos.at(u):make_pair(0,0); auto pv=L.pos.count(v)?L.pos.at(v):make_pair(0,0); drawLine(grid, pu.first,pu.second,pv.first,pv.second);} 
    for(auto &kv: L.pos) grid[kv.second.first][kv.second.second]=kv.first;
    cout << UI::BLUE << "\n    CITY MAP" << UI::RESET << "\n"; for(auto &row: grid) cout<<row<<"\n";
    if(!highlightPath.empty()){ cout<< UI::CYAN << "\nPath: "; for(size_t i=0;i<highlightPath.size();++i){ cout<<highlightPath[i]; if(i+1<highlightPath.size()) cout<<" -> "; } cout<< UI::RESET << "\n"; }
}

inline void loading(const std::string& label, int ms=600){ using namespace std; cout<<UI::YELLOW<<label<<UI::RESET<<"\n"; const int N=22; for(int i=0;i<=N;i++){ int pct=(i*100)/N; cout << "["; for(int j=0;j<i;j++) cout<<"#"; for(int j=i;j<N;j++) cout<<" "; cout << "] "<<pct<<"%\r"; cout.flush(); sleepms(ms/N);} cout<<"\n"; }

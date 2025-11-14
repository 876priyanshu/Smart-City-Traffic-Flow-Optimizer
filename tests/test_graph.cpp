#include "../src/graph.h"
#include <iostream>
int main(){ Graph g; g.addEdge('A','B',3); g.addEdge('B','C',2); if(!g.hasNode('A')||!g.hasNode('C')){ std::cout<<"hasNode failed\n"; return 1;} if(g.getWeight('A','B')!=3){ std::cout<<"weight failed\n"; return 1;} auto e=g.edgesUniqueUndirected(); if(e.size()!=2){ std::cout<<"edges size failed\n"; return 1;} std::cout<<"OK\n"; return 0; }

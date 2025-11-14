#include "../src/graph.h"
#include "../src/dijkstra.h"
#include <iostream>
int main(){ Graph g; g.addEdge('A','B',1); g.addEdge('B','C',2); g.addEdge('A','C',5); auto res=dijkstra(g,'A','C'); if(res.distance!=3){ std::cout<<"distance failed\n"; return 1;} if(res.path.size()!=3){ std::cout<<"path len failed\n"; return 1;} std::cout<<"OK\n"; return 0; }

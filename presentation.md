# Smart City Traffic Flow Optimizer — Slides

## Overview
- Goal: Optimize travel time in a city using Dijkstra
- Modules: Graph, Dijkstra, Simulator, Visualization, File I/O, Menu

## Data Model
- Undirected weighted graph (char nodes A–J)
- Load from file (u v w)

## Algorithm
- Dijkstra with min-heap (distance, parent)
- Reconstruct path and time

## Simulation
- Random deltas on edges; ensure positive weights
- Log changes to traffic_logs.txt

## UI/Visualization
- Windows CMD friendly
- ASCII map + path highlight
- Simple loading bar and colors

## Tests
- test_graph: edges, weights, nodes
- test_dijkstra: path length and distance

## Build/Run
- mingw32-make
- bin/traffic.exe

## Future Work
- Multi-criteria (traffic lights, closures)
- A* heuristic for speed
- CSV/JSON data formats

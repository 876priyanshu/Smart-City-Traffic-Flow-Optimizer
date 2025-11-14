# Smart City Traffic Flow Optimizer — Report

Author: Team SmartCity
Date: 2025-11-13

## Abstract
This report describes the design and implementation of a Windows CMD-based Smart City Traffic Flow Optimizer. It uses a weighted, undirected graph to model roads, Dijkstra’s algorithm for shortest-path routing, and a traffic simulator that perturbs edge weights to reflect congestion.

## Introduction
Urban mobility requires dynamic routing to mitigate congestion. Our console application demonstrates core concepts using a compact, dependency-free C++ implementation with an ASCII UI.

## System Architecture
- Graph (Adjacency List): nodes A–J, edges with integer minutes
- Dijkstra: min-heap priority queue, parent map reconstruction
- Traffic Simulator: random deltas, ensures positive weights, logs changes
- Visualization: ASCII grid layout, edge drawing, path highlight
- File I/O: route history append/read, timestamping
- Menu/UI: number-based navigation, animations via Sleep/chrono

## Data Model
Edges are specified as lines of the form `U V W` in data files. The runtime loads edges, builds symmetric adjacency lists, and exposes helpers for algorithms and visualization.

## Algorithm Details
Dijkstra maintains a min-heap of (distance, node) pairs. Distances are updated greedily when a shorter path is found. The parent map is then used to reconstruct the path once the destination is settled.

## Traffic Simulation
Each simulation step samples random edges and deltas, applying them to weights while clamping at 1 minute. Changes are appended to a log for auditability.

## Visualization and UI
The city is drawn on a fixed ASCII grid. Paths are printed as sequences of nodes. The UI provides menu navigation, loading bars, and color output using ANSI escape sequences.

## Testing
- test_graph: verifies edge insertion, lookup, and unique-edge listing
- test_dijkstra: validates computed distance and path length on a small graph

## Build and CI
A MinGW Makefile compiles sources with `-std=gnu++14`. A GitHub Actions workflow builds and runs tests on Windows via MSYS2.

## Results
The application successfully loads maps, computes shortest routes, simulates traffic, and shows history of routes.

## Future Work
- Larger datasets and real-time feeds
- A* for heuristic search
- Multi-criteria optimization (closures, turn penalties)

## Conclusion
We delivered a functional, modular, and testable Windows CMD application demonstrating core smart-city routing capabilities with a clean console UI and ASCII visualization.

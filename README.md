Smart City Traffic Flow Optimizer

A hybrid C++ + Web-based traffic management system that computes optimal routes, simulates congestion, and visualizes real Delhi traffic flow using real road data.

1. Problem Statement

Delhi faces heavy and unpredictable traffic congestion, making daily commuting difficult.

Traditional route planners usually calculate only the shortest distance, but fail to consider:

Real-time congestion

Real-world map constraints

Dynamic traffic variations

Visual route display

This project solves:

How to compute the fastest route between two Delhi locations

How to simulate & visualize dynamic congestion

How to integrate C++ graph algorithms with real maps

How to provide a clean, user-friendly route visualization

2. Proposed Solution

A combined C++ backend + Web frontend system.

C++ Backend

Optimized Dijkstra’s shortest path algorithm

Custom traffic simulator updating edge weights

JSON exporter to send graph + route data to frontend

Web Frontend

Interactive Delhi map (Leaflet.js)

Real-road routing (OSRM)

Traffic heatmap visualization

Path animation + alternative routes

Output Provided to User

Shortest graph path (from C++)

Actual Delhi road route (via OSRM)

3. Features

Real-time traffic simulation

Dijkstra shortest path algorithm

Real-road routing with OSRM

Route animation (0.6s intervals)

Traffic heatmap (green → red → maroon)

Route history logging

20+ Delhi locations supported

Clean and interactive UI

4. Code Walkthrough
4.1 C++ Algorithms
graph.h

Stores adjacency list for Delhi nodes

Handles weighted (traffic-based) edges

dijkstra.h

Implements Dijkstra

Time Complexity: O(V²)

Records travel time + path

traffic_simulator.h

Generates random congestion

Dynamically updates weights

json_exporter.h

Converts graph + results → JSON

main.cpp

Menu-driven console interface:

Display map

Find shortest path

Simulate traffic

View history

Visualize path

4.2 Web Frontend
index.html

Loads Leaflet map

app.js

Reads JSON

Draws graph edges + traffic

Calls OSRM for real-road route

Animates movement

style.css

Dark thick line styling

Clean and responsive UI

5. Working Demo
Step 1: Load Map

Open:

web/index.html

Step 2: Select Locations

Source

Destination

Step 3: Compute Route

Click Find Route
Shows:

Graph shortest path

OSRM real-road path

Step 4: Visualization

Route in dark red

Traffic in green/red/maroon

Shows:
Graph time
Road distance
Estimated time

Step 5: Animate Path

Click Animate Path
Marker moves every 0.6 seconds.

Step 6: Simulate Traffic

Click Simulate Traffic
Edges change color every 2 seconds.

6. Traffic Color System
Color	Meaning
Dark Green (#006400)	Light traffic (≤ 10 min)
Firebrick (#B22222)	Moderate traffic (11–15 min)
Maroon (#800000)	Heavy traffic (> 15 min)

Traffic edges: 4px

Highlighted route: 6px

Opacity: 70%

7. Delhi Supported Locations
Central Delhi

Connaught Place

Palika Bazar

Janpath

Barakhamba

Bengali Market

Parliament Street

India Gate

Patel Chowk

Rajiv Chowk

Barakhamba Road

South Delhi

Moolchand

Lajpat Nagar

South Extension

Defence Colony

Greater Kailash

Hauz Khas

Green Park

Saket

Nitika Nagar

Nehru Place

8. Installation & Reproducibility
8.1 Clone Repository
git clone https://github.com/yourteam/SmartCityTrafficFlowOptimizer.git
cd SmartCityTrafficFlowOptimizer

8.2 Build C++ Backend
mkdir -p bin
g++ -std=c++17 -o bin/traffic_optimizer src/*.cpp

8.3 Run Web Version

Open:

web/index.html

9. Usage (Console)

Run:

./bin/traffic_optimizer.exe

Menu Options

Display city map

Find shortest route

Simulate traffic

View route history

Visualize paths

10. Project Structure
SmartCityTrafficFlowOptimizer/
├── src/
│   ├── graph.h
│   ├── dijkstra.h
│   ├── traffic_simulator.h
│   ├── json_exporter.h
│   └── main.cpp
├── web/
│   ├── index.html
│   ├── app.js
│   └── style.css
├── data/
│   ├── graph.json
│   ├── city_map.txt
│   └── routes_history.txt
└── tests/

11. Algorithm Performance

Time Complexity: O(V²)

Nodes: 20+

Edges: 40+ weighted

Response time: <100 ms

Animation speed: 0.6 sec/waypoint

12. Team Contributions

Suvarn Patil (B24CS1073)

Graph structures

Dijkstra implementation

Unit testing

Priyansu Rajput (B24CM1083)

Traffic simulator

File I/O

Backend integration

Sai Manav (B24EE1066)

Web interface

OSRM integration

JSON logic

Ankit Vaniya (B24CM1064)

Documentation

Build system

Project coordination

13. Technologies Used
Backend

C++17

Dijkstra Algorithm

JSON Serialization

Frontend

Leaflet.js

Leaflet Routing Machine

OSRM API

HTML, CSS, JavaScript

14. Testing
Unit Tests
./bin/traffic_optimizer.exe --test-graph
./bin/traffic_optimizer.exe --test-dijkstra
./bin/traffic_optimizer.exe --test-simulation

Integration Tests

Load web UI

Verify route rendering

Check animation

Test traffic updates

15. Final Implementation Status

✔ Fully working C++ backend
✔ Complete web interface
✔ Real-road routing with OSRM
✔ Dynamic traffic simulation
✔ Clean repository structure
✔ Reproducible build
✔ Ready for 10-minute presentation

16. License

MIT License

17. Acknowledgments

OpenStreetMap

Leaflet.js

OSRM

Delhi traffic datasets

Open-source community

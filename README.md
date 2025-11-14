Smart City Traffic Flow Optimizer

A hybrid C++ + Web-based traffic management system that computes optimal routes, simulates congestion, and visualizes real Delhi traffic flow using real road data.

1. Problem Statement

Delhi faces heavy and unpredictable traffic congestion, making daily commuting difficult.
Traditional route planners show shortest distance but fail to consider real-time congestion, and most student-level graph projects do not integrate real maps, dynamic traffic, or visual routing.

This project aims to solve:

How to compute the fastest route between two Delhi locations.

How to simulate and visualize traffic congestion dynamically.
Smart City Traffic Flow Optimizer

A hybrid C++ + Web-based traffic management system that computes optimal routes, simulates congestion, and visualizes real Delhi traffic flow using real road data.

1. Problem Statement

Delhi faces heavy and unpredictable traffic congestion, making daily commuting difficult.
Traditional route planners usually compute the shortest distance but fail to consider real-time congestion, and most student-level graph projects do not integrate:

Real maps

Dynamic traffic simulation

Visual routing on actual roads

This project aims to solve:

How to compute the fastest route between two Delhi locations

How to simulate and visualize dynamic congestion

How to integrate C++ graph algorithms with real-world maps

How to provide a clear, visual, user-friendly route display

2. Proposed Solution

The system combines a C++ backend and a JavaScript web frontend.

C++ Backend

Optimized Dijkstra’s shortest path algorithm

Custom traffic simulator that updates edge weights dynamically

JSON exporter to send C++ data to the Web UI

Web Frontend

Interactive Delhi map using Leaflet.js

Real road routing via OSRM

Live traffic visualization with color-coded edges

Route animation + alternative path suggestions

The user gets both:

Graph shortest path output (from C++)

Real-road navigation (via OSRM)

3. Features

Real-time traffic simulation (light → moderate → heavy)

Optimized Dijkstra shortest path computation

Real-road routing with OSRM

Animated route playback on interactive map

Traffic heatmap visualization

Route history logging

Alternative path suggestions

Supports 20+ major Delhi locations

4. Code Walkthrough
4.1 C++ Algorithms
graph.h

Stores adjacency list for 20+ locations

Handles weighted edges (traffic-based)

dijkstra.h

Classical Dijkstra

Time complexity: O(V²)

Stores path + total time

traffic_simulator.h

Generates random congestion

Updates weights in real-time

json_exporter.h

Converts paths and graph data → JSON

Used by frontend to visualize results

main.cpp

Menu-driven UI with features:

Display map

Shortest path finder

Traffic simulation

Route history

Path visualization

4.2 Web Frontend
index.html

Loads Leaflet interactive map

app.js

Reads JSON from backend

Draws traffic edges

Calls OSRM for real-road routing

Animates path

style.css

Dark thick lines

Clean UI layout

5. Working Demo
Step 1: Load the Map

Open:

web/index.html


Interactive Delhi map loads with 20+ locations.

Step 2: Select Locations

Choose:

Source

Destination

Step 3: Compute Route

Click Find Route
Displays:

Shortest graph route (C++)

Real OSRM road route

Step 4: Visualization

Route shown in dark red

Traffic shown in green/red/maroon

Stats include:

Graph travel time

Road distance

Estimated road travel time

Step 5: Animate Path

Click Animate Path
Marker moves every 0.6 sec per waypoint.

Step 6: Simulate Traffic

Click Simulate Traffic
Edge colors update every 2 seconds.

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

Connaught Place, Palika Bazar, Janpath, Barakhamba, Bengali Market, Parliament Street, India Gate, Patel Chowk, Rajiv Chowk, Barakhamba Road

South Delhi

Moolchand, Lajpat Nagar, South Extension, Defence Colony, Greater Kailash, Hauz Khas, Green Park, Saket, Nitika Nagar, Nehru Place

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


Features include:

Display map

Find shortest route

Simulate traffic

View route history

Visualize path

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

Edges: 40+

Response Time: <100 ms

Animation Speed: 0.6 sec/waypoint

12. Team Contributions
Suvarn Patil (B24CS1073)

Graph structures

Dijkstra

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

HTML/CSS/JavaScript

14. Testing
Unit Tests
./bin/traffic_optimizer.exe --test-graph
./bin/traffic_optimizer.exe --test-dijkstra
./bin/traffic_optimizer.exe --test-simulation

Integration Tests

Load web UI

Verify map rendering

Test routes

Test animation & traffic updates

15. Final Implementation Status

 Fully working C++ backend
 Complete web interface
 Real map routing with OSRM
 Dynamic traffic simulation
 Clean repository structure
 Reproducible build
 Ready for 10-minute presentation

16. License

MIT License

17. Acknowledgments

OpenStreetMap

Leaflet.js

OSRM

Delhi traffic datasets

Open-source community
How to integrate C++ graph algorithms with real-world map navigation.

How to provide a clear, visual, user-friendly route display.

2. Proposed Solution

We built a system that combines:

C++ Backend

Optimized Dijkstra’s shortest path algorithm

Custom traffic simulator that updates edge weights

JSON exporter to bridge C++ output to Web UI

Web Frontend

Interactive Delhi map using Leaflet.js

Real road routing via OSRM

Live traffic visualization using color-coded edges

Path animation and alternate route suggestions

This gives the user both:

Graph shortest path output (from C++), and

Real-road navigation (from OSRM)

3. Features

Real-time traffic simulation (light → moderate → heavy)

Shortest path computation using optimized Dijkstra

Real road routing with OSRM

Interactive map with animated route playback

Traffic heatmap on Delhi roads

Route history logging

Alternative path suggestions

20+ major Delhi landmarks supported

4. Code Walkthrough
4.1 C++ Algorithms

graph.h

Stores adjacency list of 20+ Delhi nodes

Handles weighted edges (traffic weights)

dijkstra.h

Classical Dijkstra with O(V²) performance

Records path + total travel time

traffic_simulator.h

Randomized congestion generator

Updates weights every cycle

json_exporter.h

Converts graph + computed path → JSON

Frontend reads this JSON to display routes

main.cpp

Menu-driven console UI

Supports:

Show map

Find shortest route

Simulate traffic

View route history

Visualize resulting path

4.2 Web Frontend

index.html
Loads the interactive map (Leaflet)

app.js

Reads exported JSON

Draws edges with traffic colors

Calls OSRM for real-road routing

Animates the path

style.css
UI/UX styling (dark thick edges, clean layout)

5. Working Demo
Step 1: Load the Map

Open:

web/index.html


Delhi map loads with 20+ predefined locations.

Step 2: Select Locations

Choose:

Source location

Destination location

Step 3: Compute Route

Click Find Route to compute:

Graph shortest path (C++)

Real road path (OSRM)

Step 4: View Visualization

Path appears in dark red

Traffic lines appear in green/red/maroon

Stats shown:

Graph travel time

Road distance

Estimated road travel time

Step 5: Animate Path

Click Animate Path
Marker moves every 0.6 seconds per waypoint.

Step 6: Simulate Traffic

Click Simulate Traffic
Edges update colors every 2 seconds.

6. Traffic Color System
Color	Meaning
Dark Green (#006400)	Light traffic (≤ 10 minutes)
Firebrick (#B22222)	Moderate traffic (11–15 minutes)
Maroon (#800000)	Heavy traffic (> 15 minutes)

Line Thickness:

4px → traffic edges

6px → highlighted route

Opacity: 70% for visibility

7. Delhi Supported Locations
Central Delhi

Connaught Place, Palika Bazar, Janpath, Barakhamba, Bengali Market, Parliament Street, India Gate, Patel Chowk, Rajiv Chowk, Barakhamba Road

South Delhi

Moolchand, Lajpat Nagar, South Extension, Defence Colony, Greater Kailash, Hauz Khas, Green Park, Saket, Nitika Nagar, Nehru Place

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
./bin/traffic_optimizer.exe


Menu includes:

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

Response Time: <100 ms

Animation Speed: 0.6 sec/waypoint

12. Team Contributions

Suvarn Patil (B24CS1073)
Graph structures, Dijkstra, unit testing

Priyansu Rajput (B24CM1083)
Traffic simulator, file I/O, backend integration

Sai Manav (B24EE1066)
Web interface, OSRM integration, JSON logic

Ankit Vaniya (B24CM1064)
Documentation, build system, project coordination

13. Technologies Used
Backend

C++17

Dijkstra Algorithm

JSON Serialization

Frontend

Leaflet.js

Leaflet Routing Machine

OSRM API

HTML/CSS/JavaScript

14. Testing
Unit Tests
./bin/traffic_optimizer.exe --test-graph
./bin/traffic_optimizer.exe --test-dijkstra
./bin/traffic_optimizer.exe --test-simulation

Integration Tests

Load web UI

Verify routes, traffic updates, animation

15. Final Implementation Status

 Fully working C++ backend
 Complete web interface
 Real map routing with OSRM
 Dynamic traffic simulation
 Clean repository structure 
 Reproducible build
 Ready for 10-minute presentation demo

16. License

MIT License

17. Acknowledgments

OpenStreetMap, Leaflet.js, OSRM, Delhi traffic references, open-source community

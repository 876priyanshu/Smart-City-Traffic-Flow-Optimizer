# Smart City Traffic Flow Optimizer

A traffic management system that combines C++ routing algorithms with an interactive web map to help find optimal routes through Delhi.

## Features

- Real-time traffic simulation
- Shortest path finding using Dijkstra's algorithm
- Interactive map with real road routing
- Traffic heatmap visualization
- Route history tracking
- Alternative route suggestions
- Animated route demonstration

## Delhi Locations

**Central Delhi:**
Connaught Place, Palika Bazar, Janpath, Barakhamba, Bengali Market, Parliament Street, India Gate, Patel Chowk, Rajiv Chowk, Barakhamba Road

**South Delhi:**
Moolchand, Lajpat Nagar, South Extension, Defence Colony, Greater Kailash, Hauz Khas, Green Park, Saket, Nitika Nagar, Nehru Place

## Getting Started

### Web Version
1. Clone this repository
2. Open [web/index.html](cci:7://file:///C:/Users/yashr/CascadeProjects/SmartCityTrafficFlowOptimizer/web/index.html:0:0-0:0) in your browser
3. Start using the traffic optimizer

### Console Version
```bash
g++ -std=c++17 -o bin/traffic_optimizer src/*.cpp
./bin/traffic_optimizer.exe
```*

How It Works

Select your source and destination from the dropdown menus
Click "Find Route" to get the optimal path
The route will be displayed on the map following actual roads
Click "Animate Path" to see a visual demonstration
Use "Simulate Traffic" to see real-time congestion updates

Traffic Colors
Green: Light traffic
Orange: Moderate traffic
Red: Heavy traffic


Team
This project was developed by a team of 4 members:


Member 1: Graph algorithms and data structures(Ankit vaniya B24CM1064)
Member 2: Traffic simulation and system integration(Priyansu rajput B24CM1083)
Member 3: Web interface and visualization(Sai manav B24EE1066)
Member 4: Documentation and build management(Sai manav B24CS1073)


Technology
Backend: C++17 with Dijkstra's algorithm
Frontend: Leaflet.js for mapping, OSRM for real routing


Data: JSON format for communication between backend and frontend

License
MIT License

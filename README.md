# Smart City Traffic Flow Optimizer

A traffic management system that combines C++ routing algorithms with an interactive web map to help find optimal routes through Delhi.

## Features

- Real-time traffic simulation with dynamic congestion updates
- Shortest path finding using optimized Dijkstra's algorithm
- Interactive map with real road routing via OSRM
- Traffic heatmap visualization showing congestion levels
- Complete route history tracking and logging
- Alternative route suggestions with time comparisons
- Animated route demonstration with fast 0.6s intervals
- Dark, thick traffic lines for better visibility
- Support for 20+ Delhi locations with real coordinates

## Delhi Locations

**Central Delhi:**
Connaught Place, Palika Bazar, Janpath, Barakhamba, Bengali Market, Parliament Street, India Gate, Patel Chowk, Rajiv Chowk, Barakhamba Road

**South Delhi:**
Moolchand, Lajpat Nagar, South Extension, Defence Colony, Greater Kailash, Hauz Khas, Green Park, Saket, Nitika Nagar, Nehru Place

## Getting Started

### Web Version (Recommended)
1. Clone this repository
2. Navigate to the `web/` directory
3. Open [index.html](cci:7://file:///C:/Users/yashr/CascadeProjects/SmartCityTrafficFlowOptimizer/web/index.html:0:0-0:0) in Chrome, Firefox, or Edge
4. The interactive map will load with Delhi locations
5. Start using the traffic optimizer immediately

### Console Version
```bash
# Build the C++ backend
g++ -std=c++17 -o bin/traffic_optimizer src/*.cpp

# Run the console application
./bin/traffic_optimizer.exe

# Follow the menu options to:
# 1. Display city map
# 2. Find shortest route
# 3. Simulate traffic
# 4. View route history
# 5. Visualize paths
```*


How It Works

Select Locations: Choose source and destination from dropdown menus
Find Route: Click "Find Route" to get optimal path using Dijkstra's algorithm
Real Roads: Route follows actual Delhi streets via OSRM routing
Visual Display: Path shown in dark red on the interactive map
Route Info: See both graph time and real road distance/time
Animate: Click "Animate Path" to see marker traverse the route
Traffic Sim: Use "Simulate Traffic" for real-time congestion updates


Traffic Visualization
 Dark Green (#006400): Light traffic (weight ≤ 10 minutes)
 Firebrick Red (#B22222): Moderate traffic (11-15 minutes)
 Maroon (#800000): Heavy traffic (weight > 15 minutes)


Line Thickness: 4px for traffic edges, 6px for route lines
Opacity: 70% for clear visibility at all zoom levels


Technical Details
Algorithm Performance
Time Complexity: O(V²) Dijkstra implementation
Graph Size: 20 nodes, 40+ weighted edges
Response Time: Under 100ms for route calculations
Animation Speed: 0.6 seconds per waypoint
Map Coverage: Delhi NCR region (28.5°N to 28.7°N, 77.1°E to 77.3°E)


Data Flow
C++ backend loads graph from data/city_map.txt
Dijkstra algorithm finds optimal path
JSON exporter converts data to web format
Frontend reads JSON and displays on Leaflet map
OSRM provides real road routing between waypoints
Traffic simulator updates edge weights dynamically


Project Structure
SmartCityTrafficFlowOptimizer/
├── src/                    # C++ source code
│   ├── graph.h            # Graph data structure
│   ├── dijkstra.h         # Shortest path algorithm
│   ├── traffic_simulator.h # Traffic simulation
│   ├── json_exporter.h    # Data serialization
│   └── main.cpp           # Console application
├── web/                   # Web interface
│   ├── index.html        # Main page
│   ├── app.js           # Map and routing logic
│   └── style.css        # Styling
├── data/                 # Configuration and data
│   ├── graph.json       # Web format graph data
│   ├── city_map.txt     # Console format graph
│   └── routes_history.txt # Query history
└── tests/               # Unit and integration tests


Team Contributions
This project was developed collaboratively by 4 team members:

Member 1 (Algorithm Engineer): Graph data structures, Dijkstra optimization, unit testing(Ankit vaniya B24CM1064)
Member 2 (Simulation Engineer): Traffic simulation engine, file I/O, system integration(Priyansu rajput B24CM1083)
Member 3 (Frontend Developer): Web interface, map integration, JSON export, user experience(Sai manav B24EE1066)
Member 4 (Integration Lead): Documentation, build system, project coordination, utilities(Suvarn patil)(B24CS1073)


Technology Stack
Backend
C++17: Core routing algorithms and traffic simulation
Dijkstra Algorithm: Optimized shortest path finding
JSON Export: Seamless data serialization for web interface

Frontend
Leaflet.js: Interactive mapping with OpenStreetMap tiles
Leaflet Routing Machine: Real road routing via OSRM API
Vanilla JavaScript: No framework dependencies for maximum compatibility
CSS3: Modern styling with responsive design


External APIs
OpenStreetMap: Free map tiles and geographic data
OSRM (Open Source Routing Machine): Real road routing and turn-by-turn directions
Installation & Setup


Prerequisites
C++17 compatible compiler (GCC 7+, Clang 5+, MSVC 2017+)
Modern web browser with JavaScript enabled
Git for version control
Internet connection for map tiles and routing


Build Instructions
bash
# Clone the repository
git clone https://github.com/yourteam/SmartCityTrafficFlowOptimizer.git
cd SmartCityTrafficFlowOptimizer

# Build C++ backend
mkdir -p bin
g++ -std=c++17 -o bin/traffic_optimizer src/*.cpp

# Run web version (no build required)
# Simply open web/index.html in browser


Usage Examples

Basic Route Finding
Open 
web/index.html
Select "Connaught Place" as source
Select "India Gate" as destination
Click "Find Route"
See optimal path displayed on map

Traffic Simulation
Find any route first
Click "Simulate Traffic"
Watch traffic colors change dynamically
See congestion alerts appear
Observe real-time updates every 2 seconds

Route Comparison
Find initial route
Click "Alternative Routes"
Compare multiple path options
See time and distance for each
Click any route to display it

Testing
Unit Tests
bash
# Test graph algorithms
./bin/traffic_optimizer.exe --test-graph

# Test Dijkstra implementation
./bin/traffic_optimizer.exe --test-dijkstra

# Test traffic simulation
./bin/traffic_optimizer.exe --test-simulation


Integration Tests
Open 
web/index.html
 in browser
Test all UI features interactively
Verify map loading and route display
Check animation and simulation functions

Contributing Guidelines
Fork the repository
Create feature branch (git checkout -b feature/amazing-feature)
Make your changes with clear commit messages
Test thoroughly (both console and web versions)
Push to your branch (git push origin feature/amazing-feature)
Create Pull Request with detailed description
Wait for code review before merging


License
This project is licensed under the MIT License - see the LICENSE file for complete details.

Acknowledgments
OpenStreetMap contributors for free map tiles
Leaflet.js developers for excellent mapping library
OSRM team for real road routing capabilities
Delhi traffic authorities for realistic traffic patterns
Open source community for inspiring tools and libraries
Built with passion by Team Smart City Optimizers

Making urban navigation smarter, one route at a time! 

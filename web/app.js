/* Interactive map and routing UI */
let map, graphData = {}, routeLayer, nodeMarkers = {};
let currentRoute = null, animationMarker = null, animationPath = null;
let trafficInterval = null, history = [], alternativeRoutes = [], heatmapLayer = null;
let routingControl = null; // For real road routing

function initMap() {
    map = L.map('map').setView([28.60, 77.20], 10);
    L.tileLayer('https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png', {
        attribution: '&copy; OpenStreetMap contributors'
    }).addTo(map);
    loadData();
}

async function loadData() {
    try {
        console.log('Loading graph data...');
        const graphResp = await fetch('graph.json');
        if (!graphResp.ok) throw new Error('Graph response not ok');
        const graph = await graphResp.json();
        console.log('Graph loaded:', graph);
        graphData = graph;
        buildSelects();
        drawGraph();
        
        console.log('Loading route history...');
        const histResp = await fetch('route.json');
        if (histResp.ok) {
            history = [await histResp.json()];
            updateHistory();
        }
    } catch (e) {
        console.error('Failed to load data:', e);
        document.getElementById('routeInfo').textContent = 'Error loading data. Ensure C++ backend has exported JSON.';
    }
}

function buildSelects() {
    const src = document.getElementById('source');
    const dest = document.getElementById('dest');
    src.innerHTML = dest.innerHTML = '';
    Object.keys(graphData.nodes).forEach(id => {
        const placeName = graphData.nodes[id].name || id;
        const opt1 = new Option(`${id} - ${placeName}`, id);
        const opt2 = new Option(`${id} - ${placeName}`, id);
        src.add(opt1);
        dest.add(opt2);
    });
    src.value = 'A';
    dest.value = 'J';
}

function drawGraph() {
    // Clear all existing layers first
    map.eachLayer(l => {
        if (l instanceof L.CircleMarker || (l instanceof L.Polyline && l.options.className === 'traffic-edge')) {
            map.removeLayer(l);
        }
    });
    
    // Draw nodes
    for (let node in graphData.nodes) {
        const nodeData = graphData.nodes[node];
        const [lat, lng] = nodeData.coords;
        const placeName = nodeData.name || node;
        nodeMarkers[node] = L.circleMarker([lat, lng], { 
            radius: 5, 
            color: '#2c3e50', 
            fillColor: '#3498db', 
            fillOpacity: 0.5 
        }).addTo(map).bindPopup(`<strong>${placeName}</strong><br>Node ${node}`);
    }
    
    // Draw traffic edges
    for (let edge of graphData.edges) {
        const u = edge.from;
        const v = edge.to;
        const w = edge.weight;
        const [lat1, lng1] = graphData.nodes[u].coords;
        const [lat2, lng2] = graphData.nodes[v].coords;
        const color = w > 15 ? '#800000' : w > 10 ? '#B22222' : '#008000';
        L.polyline([[lat1, lng1], [lat2, lng2]], { 
            color: color, 
            weight: 4, 
            opacity: 0.7,
            className: 'traffic-edge'
        }).addTo(map).bindPopup(`${graphData.nodes[u].name} → ${graphData.nodes[v].name}: ${w} min`);
    }
    updateStats();
}

function clearRoute() {
    // Remove routing control if exists
    if (routingControl) {
        map.removeControl(routingControl);
        routingControl = null;
    }
    
    // Remove only route polylines (not traffic edges)
    map.eachLayer(l => {
        if (l instanceof L.Polyline && l.options.className !== 'traffic-edge') {
            map.removeLayer(l);
        }
    });
}

function showRoute(path, total) {
    clearRoute();
    const placeNames = path.map(node => graphData.nodes[node].name);
    console.log('showRoute called with path:', path);
    console.log('Place names:', placeNames);
    
    // Get start and end coordinates for real road routing
    const startCoords = graphData.nodes[path[0]].coords;
    const endCoords = graphData.nodes[path[path.length - 1]].coords;
    
    // Create real road routing using OSRM
    routingControl = L.Routing.control({
        waypoints: [
            L.latLng(startCoords[0], startCoords[1]),
            L.latLng(endCoords[0], endCoords[1])
        ],
        routeWhileDragging: false,
        addWaypoints: false,
        createMarker: function() { return null; }, // Hide default markers
        lineOptions: {
            styles: [{ color: '#800000', weight: 6, opacity: 0.8 }]
        }
    }).on('routesfound', function(e) {
        const routes = e.routes;
        const summary = routes[0].summary;
        console.log('Real road route found:', summary);
        
        // Update route info with real road distance
        const realDistance = (summary.totalDistance / 1000).toFixed(1);
        const realTime = Math.round(summary.totalTime / 60);
        
        document.getElementById('routeInfo').textContent = 
            `Path: ${placeNames.join(' → ')}\n` +
            `Graph time: ${total} min\n` +
            `Real road: ${realDistance} km, ${realTime} min\n` +
            `🛣️ Following actual roads`;
        
        addToHistory(placeNames.join(' → '), total);
        
        // Store route coordinates for animation
        currentRoute = { 
            path, 
            coords: routes[0].coordinates,
            realDistance: realDistance,
            realTime: realTime
        };
        
        console.log('Real road route coordinates:', currentRoute.coords.length, 'points');
        
    }).addTo(map);
    
    // Fit map to show the full route area
    map.fitBounds([startCoords, endCoords], { padding: [50, 50] });
}

function animateRoute() {
    if (!currentRoute) {
        alert('Please find a route first!');
        return;
    }
    console.log('Starting animation for route:', currentRoute);
    console.log('Route coordinates:', currentRoute.coords);
    
    // Remove previous animation marker if exists
    if (animationMarker) {
        map.removeLayer(animationMarker);
    }
    
    // Create a highly visible animation marker
    animationMarker = L.marker(currentRoute.coords[0], {
        icon: L.divIcon({
            className: 'animated-marker',
            html: '<div style="background: #ff0000; width: 30px; height: 30px; border-radius: 50%; border: 4px solid white; box-shadow: 0 0 20px rgba(255,0,0,0.9); z-index: 10000; animation: pulse 1s infinite;"></div>',
            iconSize: [30, 30],
            iconAnchor: [15, 15]
        })
    }).addTo(map);
    
    console.log('Animation marker created at first coordinate:', currentRoute.coords[0]);
    
    let index = 0;
    const totalPoints = currentRoute.coords.length;
    console.log('Animation starting with', totalPoints, 'points to visit');
    
    // Show initial popup
    animationMarker.bindPopup(`Starting animation<br>Point 1/${totalPoints}`).openPopup();
    
    const interval = setInterval(() => {
        index++;
        
        if (index >= totalPoints) {
            clearInterval(interval);
            console.log('Animation completed!');
            animationMarker.bindPopup('🎯 Destination Reached!').openPopup();
            return;
        }
        
        const newCoord = currentRoute.coords[index];
        console.log(`Moving to point ${index + 1}/${totalPoints}:`, newCoord);
        
        // Move marker to new position
        animationMarker.setLatLng(newCoord);
        
        // Update popup
        animationMarker.bindPopup(`Point ${index + 1}/${totalPoints}<br>🚶 Moving along route`).openPopup();
        
        // Add a temporary circle at each position for visibility
        L.circle(newCoord, {
            radius: 50,
            fillColor: '#ff0000',
            fillOpacity: 0.3,
            stroke: false
        }).addTo(map).bindPopup('Visited!').openPopup();
        
    }, 600); // 0.6 seconds between moves (faster)
}

function updateStats() {
    const totalNodes = Object.keys(graphData.nodes).length;
    const totalEdges = graphData.edges.length;
    const avgTraffic = (graphData.edges.reduce((sum, e) => sum + e.weight, 0) / totalEdges).toFixed(1);
    const congestedRoads = graphData.edges.filter(e => e.weight > 15).length;
    
    document.getElementById('totalNodes').textContent = totalNodes;
    document.getElementById('totalEdges').textContent = totalEdges;
    document.getElementById('avgTraffic').textContent = avgTraffic;
    document.getElementById('congestedRoads').textContent = congestedRoads;
    
    updateTrafficAlerts();
}

function findAlternativeRoutes() {
    const src = document.getElementById('source').value;
    const dst = document.getElementById('dest').value;
    if (!src || !dst) { alert('Select source and destination'); return; }
    
    console.log('Finding alternative routes from', src, 'to', dst);
    
    // Find 3 different routes by temporarily removing edges
    alternativeRoutes = [];
    const originalEdges = [...graphData.edges];
    
    for (let i = 0; i < 3; i++) {
        // Remove some edges to find alternative paths
        const modifiedEdges = originalEdges.filter((edge, index) => index % (i + 2) !== 0);
        
        // Create temporary graph for calculation
        const tempGraphData = graphData;
        graphData = { ...graphData, edges: modifiedEdges };
        
        const result = dijkstraClient(src, dst);
        
        // Restore original graph
        graphData = tempGraphData;
        
        if (result && result.total !== Infinity) {
            const placeNames = result.path.map(node => graphData.nodes[node].name);
            alternativeRoutes.push({
                path: result.path,
                total: result.total,
                name: `Route ${i + 1} (${result.total} min)`,
                coords: result.path.map(node => graphData.nodes[node].coords),
                placeNames: placeNames
            });
            console.log('Found alternative route:', placeNames, 'Time:', result.total);
        }
    }
    
    displayRouteComparison();
}

function displayRouteComparison() {
    const comparisonDiv = document.getElementById('routeComparison');
    if (alternativeRoutes.length === 0) {
        comparisonDiv.innerHTML = '<p>No alternative routes found.</p>';
        return;
    }
    
    comparisonDiv.innerHTML = alternativeRoutes.map((route, index) => `
        <div class="route-option" onclick="selectAlternativeRoute(${index})">
            <strong>${route.name}</strong><br>
            Path: ${route.placeNames.join(' → ')}<br>
            <span style="color: ${route.total < 10 ? '#27ae60' : route.total < 15 ? '#f39c12' : '#e74c3c'}">
                ⏱️ ${route.total} minutes
            </span>
        </div>
    `).join('');
}

function selectAlternativeRoute(index) {
    const route = alternativeRoutes[index];
    currentRoute = { path: route.path, coords: route.coords };
    
    // Update UI to show selected route
    document.querySelectorAll('.route-option').forEach(el => el.classList.remove('selected'));
    document.querySelectorAll('.route-option')[index].classList.add('selected');
    
    document.getElementById('routeInfo').textContent = `Selected: ${route.name}\nPath: ${route.path.join(' → ')}\n🚦 Click "Animate Path" to visualize`;
    
    // Fit map to this route
    map.fitBounds(L.latLngBounds(route.coords));
}

function toggleTrafficHeatmap() {
    if (heatmapLayer) {
        map.removeLayer(heatmapLayer);
        heatmapLayer = null;
        document.getElementById('heatmapBtn').textContent = 'Traffic Heatmap';
        console.log('Heatmap hidden');
        return;
    }
    
    console.log('Creating traffic heatmap...');
    document.getElementById('heatmapBtn').textContent = 'Hide Heatmap';
    
    // Create heatmap based on edge weights
    heatmapLayer = L.layerGroup();
    
    graphData.edges.forEach(edge => {
        const [lat1, lng1] = graphData.nodes[edge.from].coords;
        const [lat2, lng2] = graphData.nodes[edge.to].coords;
        const intensity = edge.weight / 20; // Normalize to 0-1
        
        // Add multiple points along the edge for better heatmap
        for (let i = 0; i <= 5; i++) {
            const lat = lat1 + (lat2 - lat1) * (i / 5);
            const lng = lng1 + (lng2 - lng1) * (i / 5);
            
            const color = intensity > 0.75 ? '#e74c3c' : intensity > 0.5 ? '#f39c12' : '#27ae60';
            const radius = 100 + intensity * 200;
            
            L.circle([lat, lng], {
                radius: radius,
                fillColor: color,
                fillOpacity: 0.2,
                stroke: false,
                className: 'heatmap-circle'
            }).addTo(heatmapLayer);
        }
    });
    
    heatmapLayer.addTo(map);
    console.log('Heatmap added to map');
}

async function getRoadRoute(coords) {
    if (coords.length < 2) return coords;
    
    console.log('Getting road route for coordinates:', coords);
    
    try {
        // For simplicity, we'll create a more realistic path by adding intermediate points
        // In a real application, you would use a routing API like OpenRouteService or Mapbox
        const routeCoords = [];
        
        for (let i = 0; i < coords.length - 1; i++) {
            const start = coords[i];
            const end = coords[i + 1];
            
            // Add intermediate points to make it look more like roads
            const intermediatePoints = generateRoadLikePath(start, end);
            routeCoords.push(...intermediatePoints);
            
            // Avoid duplicate points
            if (i < coords.length - 2) {
                routeCoords.pop();
            }
        }
        
        console.log('Generated road-like route with', routeCoords.length, 'points');
        return routeCoords;
        
    } catch (error) {
        console.error('Error getting road route:', error);
        return coords; // Fallback to straight line
    }
}

function generateRoadLikePath(start, end) {
    const points = [];
    const steps = 8; // Number of intermediate points
    
    for (let i = 0; i <= steps; i++) {
        const t = i / steps;
        
        // Add some curvature to make it look like a road
        const lat = start[0] + (end[0] - start[0]) * t;
        const lng = start[1] + (end[1] - start[1]) * t;
        
        // Add slight curve using sine wave
        const curveAmount = 0.002; // Small curve in degrees
        const perpendicularAngle = Math.atan2(end[0] - start[0], end[1] - start[1]) + Math.PI / 2;
        const curveOffset = Math.sin(t * Math.PI) * curveAmount;
        
        const curvedLng = lng + Math.cos(perpendicularAngle) * curveOffset;
        const curvedLat = lat + Math.sin(perpendicularAngle) * curveOffset;
        
        points.push([curvedLat, curvedLng]);
    }
    
    return points;
}

function toggleRoadMode() {
    roadMode = !roadMode;
    const btn = document.getElementById('roadToggleBtn');
    btn.textContent = roadMode ? '🛣️ Road Mode: ON' : '📏 Road Mode: OFF';
    btn.style.background = roadMode ? '#27ae60' : '#95a5a6';
    
    console.log('Road mode toggled to:', roadMode);
    
    // If there's a current route, recalculate it with new mode
    if (currentRoute) {
        const src = document.getElementById('source').value;
        const dest = document.getElementById('dest').value;
        if (src && dest) {
            console.log('Recalculating route with new mode...');
            findRoute();
        }
    }
}

function updateTrafficAlerts() {
    const alertsDiv = document.getElementById('trafficAlerts');
    const congestedEdges = graphData.edges.filter(e => e.weight > 15);
    const moderateEdges = graphData.edges.filter(e => e.weight > 10 && e.weight <= 15);
    
    let alerts = [];
    
    if (congestedEdges.length > 0) {
        alerts.push(`<div class="alert-item high">🚨 High Alert: ${congestedEdges.length} heavily congested roads detected!</div>`);
    }
    
    if (moderateEdges.length > 3) {
        alerts.push(`<div class="alert-item">⚠️ Warning: ${moderateEdges.length} roads with moderate traffic</div>`);
    }
    
    if (alerts.length === 0) {
        alerts.push('<p>🚦 No traffic alerts currently.</p>');
    }
    
    alertsDiv.innerHTML = alerts.join('');
}

function simulateTraffic() {
    if (trafficInterval) {
        clearInterval(trafficInterval);
        trafficInterval = null;
        document.getElementById('simBtn').textContent = 'Simulate Traffic';
        document.getElementById('simBtn').style.background = '#3498db';
        console.log('Traffic simulation stopped');
        return;
    }
    
    console.log('Starting traffic simulation...');
    document.getElementById('simBtn').textContent = 'Stop Simulation';
    document.getElementById('simBtn').style.background = '#e74c3c';
    
    trafficInterval = setInterval(() => {
        console.log('Updating traffic...');
        
        // Update edge weights with more dramatic changes
        graphData.edges = graphData.edges.map(edge => {
            const change = Math.floor(Math.random() * 11) - 5; // -5 to +5
            const newWeight = Math.max(1, Math.min(20, edge.weight + change));
            return { from: edge.from, to: edge.to, weight: newWeight };
        });
        
        // Redraw the entire graph with new traffic colors
        drawGraph();
        
        // Show notification
        const routeInfo = document.getElementById('routeInfo');
        routeInfo.textContent = routeInfo.textContent.replace(/\n🚦 Traffic updated!.*/, '') + '\n🚦 Traffic updated! ' + new Date().toLocaleTimeString();
        
        if (currentRoute) {
            console.log('Recalculating route due to traffic changes...');
            setTimeout(() => {
                const src = document.getElementById('source').value;
                const dest = document.getElementById('dest').value;
                findRoute();
            }, 500);
        }
    }, 2000); // Update every 2 seconds for more visible changes
}

function dijkstraClient(src, dst) {
    const dist = {};
    const prev = {};
    const Q = [];
    for (const node of Object.keys(graphData.nodes)) {
        dist[node] = Infinity;
        prev[node] = null;
        Q.push(node);
    }
    dist[src] = 0;
    while (Q.length) {
        Q.sort((a, b) => dist[a] - dist[b]);
        const u = Q.shift();
        if (u === dst) break;
        const neighbors = graphData.edges.filter(e => e.from === u || e.to === u);
        for (const e of neighbors) {
            const v = e.from === u ? e.to : e.from;
            const alt = dist[u] + e.weight;
            if (alt < dist[v]) {
                dist[v] = alt;
                prev[v] = u;
            }
        }
    }
    if (dist[dst] === Infinity) return null;
    const path = [];
    let u = dst;
    while (u) {
        path.unshift(u);
        u = prev[u];
    }
    return { path, total: dist[dst] };
}

function findRoute() {
    const src = document.getElementById('source').value;
    const dst = document.getElementById('dest').value;
    if (!src || !dst) { alert('Select source and destination'); return; }
    console.log('Finding route from', src, 'to', dst);
    const result = dijkstraClient(src, dst);
    console.log('Dijkstra result:', result);
    if (!result || result.total === Infinity) {
        document.getElementById('routeInfo').textContent = 'No path found.';
        currentRoute = null;
    } else {
        showRoute(result.path, result.total);
    }
}

document.getElementById('routeBtn').addEventListener('click', findRoute);
document.getElementById('altRoutesBtn').addEventListener('click', findAlternativeRoutes);
document.getElementById('heatmapBtn').addEventListener('click', toggleTrafficHeatmap);
document.getElementById('animateBtn').addEventListener('click', animateRoute);
document.getElementById('simBtn').addEventListener('click', simulateTraffic);
document.getElementById('resetBtn').addEventListener('click', () => {
    if (trafficInterval) clearInterval(trafficInterval);
    clearRoute();
    document.getElementById('source').value = 'A';
    document.getElementById('dest').value = 'J';
    document.getElementById('routeInfo').textContent = 'Select source and destination to see the shortest path.';
    currentRoute = null;
});

function addToHistory(path, total) {
    const timestamp = new Date().toLocaleTimeString();
    history.unshift({ path, total, timestamp });
    if (history.length > 5) history.pop(); // Keep only last 5 routes
    updateHistory();
}

function updateHistory() {
    const histEl = document.getElementById('historyList');
    if (!histEl) return;
    if (history.length === 0) {
        histEl.innerHTML = '<li>No history yet.</li>';
    } else {
        histEl.innerHTML = history.map(h => `<li>${h.path} (${h.total} min) - ${h.timestamp}</li>`).join('');
    }
}

window.addEventListener('DOMContentLoaded', initMap);

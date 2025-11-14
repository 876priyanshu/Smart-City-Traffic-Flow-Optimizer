BUILD INSTRUCTIONS (Windows CMD)

Prerequisites:
- MinGW g++ installed and in PATH
- VS Code (optional but recommended)

Steps:
1) Open Command Prompt (cmd) or PowerShell.
2) Navigate to the project folder:
   cd C:\Users\yashr\CascadeProjects\SmartCityTrafficFlowOptimizer
3) Build the C++ core:
   mingw32-make
   OR, if make is not available:
   if not exist bin mkdir bin
   g++ -std=gnu++14 -O2 -I src src\*.cpp -o bin\traffic.exe
4) Verify the executable:
   dir bin\traffic.exe

Result:
- bin/traffic.exe (C++ backend)
- data/graph.json exported for web UI
- data/route.json exported for web UI

To run the C++ console app:
   bin\traffic.exe

To open the web UI:
- Open web/index.html in a browser (or use a simple HTTP server).

Troubleshooting:
- If g++ is not found, add MinGW/bin to your PATH.
- If the web UI cannot fetch JSON, ensure the C++ app has run once to export data/graph.json and data/route.json.

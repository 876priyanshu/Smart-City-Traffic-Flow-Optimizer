#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <ctime>

// File I/O ~60 LOC
// - route history append/read
// - timestamp helper

inline std::string nowTimestamp(){
    auto t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::tm tm{}; 
    #if defined(_MSC_VER)
        localtime_s(&tm, &t);
    #else
        std::tm* p = std::localtime(&t); if(p) tm=*p;
    #endif
    std::ostringstream os; os<< std::put_time(&tm, "%Y-%m-%d %H:%M:%S"); return os.str();
}

inline void appendHistory(const std::string& path, const std::string& route, int minutes){
    std::ofstream out(path, std::ios::app); if(!out.is_open()) return; out << nowTimestamp() << " | " << route << " | " << minutes << " min\n";
}

inline std::vector<std::string> readHistory(const std::string& path){
    std::vector<std::string> lines; std::ifstream in(path); std::string s; if(!in.is_open()) return lines; while(std::getline(in,s)) if(!s.empty()) lines.push_back(s); return lines;
}

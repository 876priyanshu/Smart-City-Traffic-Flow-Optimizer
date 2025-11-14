# Windows MinGW Makefile
# Usage:
#   mingw32-make         (builds)
#   mingw32-make run     (builds and runs)
#   mingw32-make clean   (removes exe)

CXX=g++
CXXFLAGS=-std=gnu++14 -O2 -I src
SRC=$(wildcard src/*.cpp)
BIN=bin/traffic.exe

all: $(BIN)

bin:
	@if not exist bin mkdir bin

$(BIN): bin $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(BIN)

run: all
	@cd bin && traffic.exe

clean:
	@if exist bin\traffic.exe del /q bin\traffic.exe

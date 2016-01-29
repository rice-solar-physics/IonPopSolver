#set compiler and some options
UNAME=$(shell uname)
CXX=g++
CXXFLAGS=-Wall -g -O3
ifeq ($(UNAME),Darwin)
LFLAGS=-L /opt/local/lib -lboost_program_options-mt
else
LFLAGS=-L /usr/lib/x86_64-linux-gnu -lboost_program_options
endif
#set source and object files
SOURCES=$(wildcard src/*cpp)
SOURCES_RAD=$(wildcard Radiation_Model/src/*.cpp)
OBJECTS=$(subst .cpp,.o,$(SOURCES))
OBJECTS_RAD=$(subst .cpp,.o,$(SOURCES_RAD))

all: bin/Ion_Pop_Solver

bin/Ion_Pop_Solver: make_src make_rad_src
	$(CXX) $(OBJECTS) $(OBJECTS_RAD) -o $@ $(LFLAGS)
	
make_src:
	cd src; make
	
make_rad_src:
	cd Radiation_Model/src; make

clean:
	cd src; make clean
	cd Radiation_Model/src; make clean
	$(RM) bin/Ion_Pop_Solver
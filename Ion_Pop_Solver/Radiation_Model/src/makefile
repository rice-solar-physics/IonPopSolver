#set compiler and some options
CXX=g++
CXXFLAGS=-Wall -g -I /usr/include/malloc -O3
#sources and objects
SOURCES=$(wildcard *.cpp)
OBJECTS=$(subst .cpp,.o,$(SOURCES))

all: $(OBJECTS)
	
$(OBJECTS):%.o:%.cpp
	$(CXX) -c $(CXXFLAGS) $<
	
clean:
	$(RM) $(OBJECTS)
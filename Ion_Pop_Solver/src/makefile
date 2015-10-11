#set compiler and some options
CXX=g++
CXXFLAGS=-Wall -g -O3
IFLAGS=-I /usr/include/malloc -I /opt/local/include
#sources and objects
SOURCES=$(wildcard *.cpp)
OBJECTS=$(subst .cpp,.o,$(SOURCES))

all: $(OBJECTS)
	
$(OBJECTS):%.o:%.cpp
	$(CXX) -c $(CXXFLAGS) $(IFLAGS) $<
	
clean:
	$(RM) $(OBJECTS)
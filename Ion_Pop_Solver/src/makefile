#set compiler and some options
UNAME=$(shell uname)
CXX=g++
CXXFLAGS=-Wall -g -O3
ifeq ($(UNAME),Darwin)
IFLAGS=-I /usr/include/malloc -I /opt/local/include
else
IFLAGS=-I /usr/include
endif
#sources and objects
SOURCES=$(wildcard *.cpp)
OBJECTS=$(subst .cpp,.o,$(SOURCES))

all: $(OBJECTS)
	
$(OBJECTS):%.o:%.cpp
	$(CXX) -c $(CXXFLAGS) $(IFLAGS) $<
	
clean:
	$(RM) $(OBJECTS)
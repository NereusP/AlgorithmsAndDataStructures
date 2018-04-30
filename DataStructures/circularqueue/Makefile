#Makefile for building:udp
#Debug

MAKEFILE          = Makefile

FLAG = release

CC                = gcc
CXX               = g++
ifeq ($(FLAG),debug)
CFLAGS            = -g -Wall -pipe
CXXFLAGS          = -g -Wall -std=gnu++11 -pipe
TARGET            = cirqueue_d
else
CFLAGS            = -g -Wall -pipe -O2
CXXFLAGS          = -g -Wall -std=gnu++11 -pipe -O2
TARGET            = cirqueue_r
endif
INCPATH           = ./
LIBS              = -lpthread
CLEAN             = -rm -f

OBJECTS           = main.o

$(TARGET): $(OBJECTS)
	$(CXX) $(LIBS) $(OBJECTS) -o $(TARGET)
$(OBJECTS): main.cpp $(INCPATH)circularqueue.hpp $(INCPATH)atomiclock.hpp
	$(CXX) -c $(CXXFLAGS) -I$(INCPATH) -o $(OBJECTS) main.cpp

clean:
	$(CLEAN) $(TARGET) $(OBJECTS)

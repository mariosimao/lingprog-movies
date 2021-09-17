LD = g++
LFLAGS = -std=c++11 -Wall

INCLUDES = main.cpp Catalog.cpp Movie.cpp

EXECUTABLE = catalog

all:
	$(LD) $(LFLAGS) -g -o $(EXECUTABLE) $(INCLUDES)

clean:
	rm -rf *.o $(EXECUTABLE)
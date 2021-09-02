LD = g++
LFLAGS = -Wall

INCLUDES = main.cpp Catalog.cpp

EXECUTABLE = catalog

all:
	$(LD) $(LFLAGS) -g -o $(EXECUTABLE) $(INCLUDES)

clean:
	rm -rf *.o $(EXECUTABLE)
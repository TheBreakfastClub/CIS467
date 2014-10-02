# Template found on: http://mrbook.org/tutorials/make/
CC=g++
CFLAGS=-Wall -std=c++11 -g
LDFLAGS=-L ~/lib/SDL2/lib -I ~/lib/SDL2/include -lSDL2
SOURCES=game.cpp engine/world_definition/*.cpp engine/graphics/*.cpp
EXECUTABLE=game

all: $(EXECUTABLE)
	
$(EXECUTABLE): $(SOURCES)
	$(CC) $(CFLAGS) $(LDFLAGS) $(SOURCES) -o $(EXECUTABLE)

clean:
	rm $(EXECUTABLE)

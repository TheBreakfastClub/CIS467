# Template found on: http://mrbook.org/tutorials/make/
CC=g++
CFLAGS=-std=c++11 -g
SDL_LINKER_FLAGS = -L ~/lib/SDL2/lib -I ~/lib/SDL2/include/SDL2 -lSDL2 -I ~/lib/SDL2/include
SDL_IMAGE_LINKER_FLAGS = -L ~/lib/SDL2_image/lib -I ~/lib/SDL2_image/include -lSDL2_image
SOURCES=game.cpp engine/*/*.cpp util/*.cpp
HEADERS=game.h engine/*/*.h util/*.h
EXECUTABLE=game

all: $(EXECUTABLE)
	
$(EXECUTABLE): $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) $(SDL_LINKER_FLAGS) $(SDL_IMAGE_LINKER_FLAGS) $(SOURCES) -o $(EXECUTABLE)

clean:
	rm $(EXECUTABLE)

mac:
	make -f makefilemac
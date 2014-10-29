CXX = g++
SDL_LINKER_FLAGS = -framework SDL2
SDL_IMAGE_LINKER_FLAGS = -framework SDL2_image
# If your compiler is a bit older you may need to change -std=c++11 to -std=c++0x
CXXFLAGS = -std=c++11 -g -v
FRAMEFLAGS = $(SDL_LINKER_FLAGS) $(SDL_IMAGE_LINKER_FLAGS)
SOURCES=game.cpp engine/*/*.cpp util/*.cpp
HEADERS=game.h engine/*/*.h util/*.h
EXE = PixelGame

all: $(EXE)

$(EXE): $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(FRAMEFLAGS) $(SOURCES) $< -o $(EXE)

clean:
	rm *.o && rm $(EXE)
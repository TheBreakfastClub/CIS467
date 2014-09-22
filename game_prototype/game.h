#ifndef GAME_H
    #define GAME_H
 
#include <SDL2/SDL.h>
#include <iostream>
#include "engine/grid.h"

class Game {

	private:

		// SDL members -- all of this would ultimately end up in the graphics engine
		SDL_Window* window;
		SDL_Surface* screen;
        SDL_Renderer* renderer;

		// Game logic members
		Grid grid;
		bool running;
 
    public:
 
        Game(int dim_x, int dim_y);
        int run();
        void update();
        void draw();
        void handle_input();

        /* SDL graphics and asset management methods */
        bool setup();
        void cleanup();
 
};
 
#endif
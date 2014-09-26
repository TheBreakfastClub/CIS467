/**
 * The main controller of the game.
 */

#pragma once
 
#include <SDL2/SDL.h>
#include <iostream>
#include "engine/world_definition/gameWorld.h"
#include "engine/graphics/drawing.h"

class Game {

	private:

		/* Graphics engine */
        Drawing drawing;

		/* Game engine */
		GameWorld world;
		bool running;
 
    public:
 
        Game(int dim_x, int dim_y);

        int run();
        void update();
        void handle_input();

        /* SDL graphics and asset management methods */
        bool setup();
        void cleanup();

        // for TESTING event timing
        //int z;
        //Uint32 inc_z(Uint32 interval, void* param);
 
};

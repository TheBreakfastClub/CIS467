/*********************************************************
File Name:	    game.h
Author:		    The Breakfast Club
Description:    The main controller of the game.
************************************************************/

#pragma once
 
#include <SDL2/SDL.h>
#include <iostream>
#include "engine/world_definition/gameWorld.h"
#include "engine/graphics/graphicsEngine.h"

class Game {

	private:

		/* Graphics engine */
        GraphicsEngine graphics;

		/* Game engine */
		GameWorld world;
		bool gameIsRunning;
 
    public:
 
        Game();

        int run();
        void update();
        void handle_input();

        /* SDL graphics and asset management methods */
        bool setup(const char *gameName, int width, int height);
        void cleanup();
};


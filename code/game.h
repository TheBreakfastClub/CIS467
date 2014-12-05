/*********************************************************
File Name:	    game.h
Author:		    The Breakfast Club
Description:    The main controller of the game.
************************************************************/

#pragma once
 
#include <SDL2/SDL.h>
#include <iostream>
#include "engine/world_definition/gameUniverse.h"
#include "engine/graphics/graphicsEngine.h"
#include "util/clock.h"
#include "util/configurations.h"
#include "engine/world_definition/enemyType.h"

class Game {

	private:

		/* Graphics engine */
        GraphicsEngine graphics;

		/* Game engine */
        GameUniverse universe;
		bool gameIsRunning;

        /* Utility */
        Clock clock;

        /* Holds the configurations */
        Configurations config;

    public:
 
        Game();

	int xMomentum;
	int yMomentum;
	int maxXMomentum;
	int maxYMomentum;
	int nonButterMomentum;
	int momentumIncrease;
        int run();
        void update();
        void handle_input();
        
        Image *collMap;
        void generateCollMap();

        /* SDL graphics and asset management methods */
        bool setup(const char *gameName, int width, int height);
        void cleanup();
};


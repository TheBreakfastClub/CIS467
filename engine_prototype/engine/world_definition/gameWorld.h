/*********************************************************
File Name:	    gameWorld.h
Author:		    The Breakfast Club
Creation Date:  09-25-2014
Description:    Holds the data defining the world
************************************************************/

#pragma once

// Includes
#include "grid.h"

class GameWorld {
    
    public:
        GameWorld(int dim_x, int dim_y, int tile_dim);
        
        /** Defines the world environment */
        Grid world;
        // Add items such as array of enemies, the hero, items, etc.

};


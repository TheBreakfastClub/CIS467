/*********************************************************
File Name:	    gameWorld.h
Author:		    The Breakfast Club
Creation Date:  09-25-2014
Description:    Holds the data defining the world
************************************************************/

#pragma once

// Includes
#include "gameMap.h"

class GameWorld {
    
    public:
        GameWorld(int dim_x, int dim_y, int tile_dim, int hRes_x, int hRes_y);
        
        /** World properties */
        int dim_x;
        int dim_y;
        int tile_dim;
        
        /** Defines the world environment */
        GameMap highRes;
        GameMap medRes;
        GameMap lowRes;
        GameMap *currentRes;
        int currentResLevel;


        // Add items such as array of enemies, the hero, items, etc.

};


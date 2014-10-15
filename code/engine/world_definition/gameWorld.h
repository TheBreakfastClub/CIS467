/*********************************************************
File Name:	    gameWorld.h
Author:		    The Breakfast Club
Creation Date:  09-25-2014
Description:    Holds the data defining the sublevel
************************************************************/

#pragma once

// Includes
#include "gameMap.h"
#include "item.h"
#include "enemy.h"
#include <string>
#include <vector>

using namespace std;

class GameWorld {
    
    public:
        GameWorld(string world_name);
        
        string worldName;

        /** The entities that will inhabit the world */
        vector<Item> item;
        vector<Enemy> enemy;
        //TODO: Pixelation algorithm
        
        /** Defines the world environment */
        GameMap highRes;
        GameMap medRes;
        GameMap lowRes;
        GameMap *currentRes;
        int currentResLevel;

        // Methods to change the resolution
        void next_resolution(); // selects the next GameMap
        void prev_resolution(); //             prev
    private:
        void _set_current_res();

};


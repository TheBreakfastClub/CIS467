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
#include "enemies.h"
#include "hero.h"
#include "worldGrid.h"
#include <string>
#include <vector>
#include <list>

using namespace std;

enum Resolution { LOW, MED, HIGH };

class GameWorld {
    
    public:
        GameWorld(string world_name);
        ~GameWorld();
        bool init(const char *background_filename, 
                  const char *collision_filename,
                  const char *top_filename, Hero &hero); // TODO: Add pixelation algorithm parameter
        
        /** Properties of the world */
        string worldName;

        /** The entities that will inhabit the world */
        list<Item*> items;
        vector<Enemy*> enemies;

        /** Defines the world environment */
        GameMap *highRes;
        GameMap *medRes;
        GameMap *lowRes;
        
        /** Pointer to the GameMap that currently defines the world */ 
        GameMap *currentRes;

        int w;
        int h;

        // Amount to divide the dimensions by for resolutions
        int medCut, lowCut;

        Resolution currentResLevel;

        // representation of the world in a grid. used for enemy AI
        WorldGrid grid;

        // Methods to change the resolution
        void next_resolution(); // selects the next GameMap
        void prev_resolution(); //             prev
        void set_resolution(Resolution res);
    private:
        void _set_current_res();
        
        

};


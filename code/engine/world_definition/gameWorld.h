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
#include <SDL2/SDL_image.h>
#include <string>
#include <vector>

using namespace std;

class GameWorld {
    
    public:
        GameWorld(int dim_x, int dim_y, int pix_dim, int pix_length, int pix_height);
        
        /** World properties */
        int dim_x;
        int dim_y;
        int pix_length;
        int pix_height;
        int pix_dim;
        string worldName;
        vector<Item> item;
        vector<Enemy> enemy;
        //TODO: Pixelation algorithm
        
        /** Defines the world environment */
        //GameMap highRes;
        SDL_Texture* highRes;
        GameMap medRes;
        GameMap lowRes;
        GameMap *currentRes;
        int currentResLevel;


        // Add items such as array of enemies, the hero, items, etc.

        void next_resolution(); // selects the next GameMap
        void prev_resolution(); //             prev

        bool setup(SDL_Renderer *r);
        bool set_map(SDL_Renderer *r);
        void pixelize(SDL_Surface* image, GameMap &map, int pix_dim);
        void pixelize(GameMap &higher_res, GameMap &lower_res, int block_dim);

        // Add items such as array of enemies, the hero, items, etc.

    private:
        void _set_current_res();

};


/*********************************************************
File Name:	    gameMap.h
Author:			The Breakfast Club
Creation Date:  09-26-2014
Description:	Holds definitions about the pixels that make
                up the game world. It defines the game world
                environment at one resolution level.
************************************************************/

#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include "../render/image.h"
#include "../render/gfx.h"

class GameMap {

    public:
        GameMap();
        ~GameMap();
        
        Image *backgroundLayer;
        Image *collisionLayer;
        Image *topLayer;

        bool loadBackgroundLayer(const char* filename);
        bool loadCollisionLayer(const char* filename);
        bool loadTopLayer(const char* filename);

        void setBackgroundLayer(Image *img);
        void setCollisionLayer(Image *img);
        void setTopLayer(Image *img);

        int w();
        int h();
};



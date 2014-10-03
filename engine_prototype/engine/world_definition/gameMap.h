/*********************************************************
File Name:	    gameMap.h
Author:			The Breakfast Club
Creation Date:  09-26-2014
Description:	Holds definitions about the pixels that make
                up the game world. It defines the game world
                environment at one resolution level.
************************************************************/

#pragma once

#include "pixel.h"

typedef Pixel* MapLayer; // 2D array of Pixels
                         // mapLayer[row][col] = mapLayer[row * width + col];

class GameMap {

    public:
        GameMap(int width, int height);
        ~GameMap();
        
        MapLayer topLayer;
        MapLayer collisionLayer;
        MapLayer backgroundLayer;

        /** Size of each layer, in terms of the Pixel class */
        int width;
        int height;

};



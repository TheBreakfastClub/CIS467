/*********************************************************
File Name:	    gameMap.cpp
Author:			The Breakfast Club
Creation Date:  09-26-2014
Description:	Holds definitions about the pixels that make
                up the game world. It defines the game world
                environment at one resolution level.
************************************************************/

#include "gameMap.h"


GameMap::GameMap(int width, int height) : width(width), height(height) {

    int size = width * height * sizeof(Pixel);
    topLayer = (Pixel*) malloc(size);
    collisionLayer = (Pixel*) malloc(size);
    backgroundLayer = (Pixel*) malloc(size);
}

GameMap::~GameMap() {
    free(topLayer);
    free(collisionLayer);
    free(backgroundLayer);
}

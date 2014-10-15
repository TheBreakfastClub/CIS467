/*********************************************************
File Name:	    gameMap.cpp
Author:			The Breakfast Club
Creation Date:  09-26-2014
Description:	Holds definitions about the pixels that make
                up the game world. It defines the game world
                environment at one resolution level.
************************************************************/

#include "gameMap.h"
#include "gfx.h"

// The constructor
GameMap::GameMap() {

    backgroundLayer = NULL;
    collisionLayer = NULL;
    topLayer = NULL;
}

// The destructor
GameMap::~GameMap() {
    
    // Free the images if allocated
    if (backgroundLayer) {
        delete(backgroundLayer);
    }
    if (collisionLayer) {
        delete(collisionLayer);
    }
    if (topLayer) {
        delete(topLayer);
    }
}

/**
 * This function loads in the image stored in filename,
 * placing it in the Background Layer of the Game Map.
 * It returns false if it encountered an error in loading
 * the image.
 */
bool GameMap::loadBackgroundLayer(const char* filename) {

    // Free the image if allocated
    if (backgroundLayer) {
        delete(backgroundLayer);
    }
    backgroundLayer = loadImage(filename);
    return (backgroundLayer != NULL);
}

/**
 * This function loads in the image stored in filename,
 * placing it in the Collision Layer of the Game Map.
 * It returns false if it encountered an error in loading
 * the image.
 */
bool GameMap::loadCollisionLayer(const char* filename) {

    // Free the image if allocated
    if (collisionLayer) {
        delete(collisionLayer);
    }
    collisionLayer = loadImage(filename);
    return (collisionLayer != NULL);
}

/**
 * This function loads in the image stored in filename,
 * placing it in the Top Layer of the Game Map.
 * It returns false if it encountered an error in loading
 * the image.
 */
bool GameMap::loadTopLayer(const char* filename) {

    // Free the image if allocated
    if (topLayer) {
        delete(topLayer);
    }
    topLayer = loadImage(filename);
    return (topLayer != NULL);
}

/**
 * Returns the width of the game map.
 */
int GameMap::w() {
    
    // Define the width based on collision layer, the primary layer
    if (collisionLayer) {
        return collisionLayer->w;
    }
    else return 0;
}

/**
 * Returns the height of the game map.
 */
int GameMap::h() {
    
    // Define the height based on collision layer, the primary layer
    if (collisionLayer) {
        return collisionLayer->h;
    }
    else return 0;
}



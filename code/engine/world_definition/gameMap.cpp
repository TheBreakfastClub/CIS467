/*********************************************************
File Name:	    gameMap.cpp
Author:			The Breakfast Club
Creation Date:  09-26-2014
Description:	Holds definitions about the pixels that make
                up the game world. It defines the game world
                environment at one resolution level.
************************************************************/

#include "gameMap.h"

// The constructor
GameMap::GameMap() {

    backgroundLayer = NULL;
    collisionLayer = NULL;
    topLayer = NULL;
    mapImg = NULL;
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
    if (mapImg) {
        delete(mapImg);
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
    backgroundLayer = Gfx::loadImage(filename);
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
    collisionLayer = Gfx::loadImage(filename);
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
    topLayer = Gfx::loadImage(filename);
    return (topLayer != NULL);
}

/**
 * If img is not null, this function sets the current
 * background layer to img, freeing the previous
 * background layer if one exists. 
 *
 * This GameMap now gets complete control over the
 * Image pointed to by img and GameMap becomes responsible
 * for freeing its memory when it is no longer needed.
 */
void GameMap::setBackgroundLayer(Image *img) {
    
    if (img == NULL) return;
    if (backgroundLayer) {
        delete(backgroundLayer);
    }
    backgroundLayer = img;
}

/**
 * If img is not null, this function sets the current
 * collision layer to img, freeing the previous
 * collision layer if one exists. 
 *
 * This GameMap now gets complete control over the
 * Image pointed to by img and GameMap becomes responsible
 * for freeing its memory when it is no longer needed.
 */
void GameMap::setCollisionLayer(Image *img) {
    
    if (img == NULL) return;
    if (collisionLayer) {
        delete(collisionLayer);
    }
    collisionLayer = img;
}

/**
 * If img is not null, this function sets the current
 * top layer to img, freeing the previous
 * top layer if one exists. 
 *
 * This GameMap now gets complete control over the
 * Image pointed to by img and GameMap becomes responsible
 * for freeing its memory when it is no longer needed.
 */
void GameMap::setTopLayer(Image *img) {
    
    if (img == NULL) return;
    if (topLayer) {
        delete(topLayer);
    }
    topLayer = img;
}

/**
 * This method creates the map image containing the background and
 * collision layers, scaled to the correct size of the world.
 * If the background or collision layer is null, then this does nothing.
 */
void GameMap::createMapImage(int worldWidth, int worldHeight) {
    
    if (backgroundLayer && collisionLayer) {
        if (mapImg) delete mapImg;
        mapImg = new Image(worldWidth, worldHeight);
        mapImg->scaleblit(backgroundLayer);
        mapImg->ascaleblit(collisionLayer);
    }
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



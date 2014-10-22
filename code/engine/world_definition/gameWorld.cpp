/*********************************************************
File Name:	    gameWorld.cpp
Author:		    The Breakfast Club
Creation Date:  09-25-2014
Description:    Holds the data defining the world
************************************************************/

#include "gameWorld.h"
#include "../render/blend.h"
#include "../render/gfx.h"
#include <SDL2/SDL.h>
#include <iostream> 
#include <numeric>
#include <cstdlib>

/**
 * Default constructor for the world. Must call GameWorld::init()
 * before using the GameWorld instance.
 */
GameWorld::GameWorld(string world_name) : worldName(world_name), items(), enemies() 
{
    highRes = NULL;
    medRes = NULL;
    lowRes = NULL;
    currentRes = NULL;
}

// The deconstructor
GameWorld::~GameWorld() {

    if (highRes) {
        delete(highRes);
        delete(medRes);
        delete(lowRes);
    }
}

/**
 * This function initializes the game world using the passed images as the
 * high resolution game world. It returns false it any errors are encountered
 * while initializing, true otherwise.
 *
 * top_filename may be null
 *
 * This method must be called before any other GameWorld functions.
 */
bool GameWorld::init(const char *background_filename, 
    const char *collision_filename, const char *top_filename) {
    
    // Do nothing if already initialized
    if (highRes != NULL) return true;

    // Initialize the high resolution game map
    highRes = new GameMap();
    if (!highRes->loadBackgroundLayer(background_filename)) {
       std::cerr << "Error loading <" << background_filename << ">\n";
       return false;
    }
    if (!highRes->loadCollisionLayer(collision_filename)) {
       std::cerr << "Error loading <" << collision_filename << ">\n";
       return false;
    }
    if (top_filename) {
        if (!highRes->loadTopLayer(top_filename)) {
           std::cerr << "Error loading <" << top_filename << ">\n";
           return false;
        }
    }

    w = highRes->w();
    h = highRes->h();

    // Initialize Medium and Low Resolution Game Maps
    // TODO: Use pixelation to dynamically create and set these maps
    
    // Until pixelation algorithms get set, just create copies of highRes
    medRes = new GameMap();

    Image *tmp = Gfx::downsample(highRes->backgroundLayer, highRes->backgroundLayer->w/8, 
        highRes->backgroundLayer->h/8, blend_average);
    //Image *backMed = new Image(highRes->backgroundLayer->w, highRes->backgroundLayer->h);
    //backMed->scaleblit(tmp);
    //backMed->blit(highRes->backgroundLayer, 0, 0);
    //medRes->setBackgroundLayer(backMed);
    medRes->setBackgroundLayer(tmp);
    //delete tmp;

    //Image *collMed = new Image(highRes->collisionLayer->w, highRes->collisionLayer->h);
    //collMed->blit(highRes->collisionLayer, 0, 0);

    tmp = Gfx::downsample(highRes->collisionLayer, highRes->collisionLayer->w/8, 
        highRes->collisionLayer->h/8, blend_average);
    //Image *collMed = new Image(highRes->backgroundLayer->w, highRes->backgroundLayer->h);
    //collMed->scaleblit(tmp);
    //medRes->setCollisionLayer(collMed);
    medRes->setCollisionLayer(tmp);
    //delete tmp;

    if (top_filename) {
        Image *topMed = new Image(highRes->topLayer->w, highRes->topLayer->h);
        topMed->blit(highRes->topLayer, 0, 0);
        medRes->setTopLayer(topMed);
    }


    lowRes = new GameMap();

    //Image *backLow = new Image(highRes->backgroundLayer->w, highRes->backgroundLayer->h);
    //backLow->blit(highRes->backgroundLayer, 0, 0);
    lowRes->setBackgroundLayer(Gfx::downsample(highRes->backgroundLayer, highRes->backgroundLayer->w/16, 
        highRes->backgroundLayer->h/16, blend_average));

    //Image *collLow = new Image(highRes->collisionLayer->w, highRes->collisionLayer->h);
    //collLow->blit(highRes->collisionLayer, 0, 0);
    lowRes->setCollisionLayer(Gfx::downsample(highRes->collisionLayer, highRes->collisionLayer->w/16,
        highRes->collisionLayer->h/16, blend_average));

    if (top_filename) {
        Image *topLow = new Image(highRes->topLayer->w, highRes->topLayer->h);
        topLow->blit(highRes->topLayer, 0, 0);
        lowRes->setTopLayer(topLow);
    }
    
    currentRes = lowRes;
    currentResLevel = 0; // 0 -- Low, 1 -- Med, 2 -- High

    // create some random items 
    for (int i = 0; i < 12; i++) {
        int x = rand() % w;
        int y = rand() % h;
        items.push_back(Item(x, y, Gfx::loadImage("resources/hero.png"), "hero"));
    }

    return true;
}

/**
 * This function increases the current resolution, unless the world is
 * already at its highest resolution.
 */
void GameWorld::next_resolution()
{
	if (currentResLevel < 2)
		currentResLevel++;
	_set_current_res();
}

/**
 * This function decreases the current resolution, unless the world is
 * already at its lowest resolution.
 */
void GameWorld::prev_resolution()
{
	if (currentResLevel > 0)
		currentResLevel--;
	_set_current_res();
}

/**
 * This function is used to update the world's game map when the resolution
 * changes.
 */
void GameWorld::_set_current_res()
{
	switch (currentResLevel) {
		case 0:
			currentRes = lowRes; 
            break;
		case 1:
			currentRes = medRes; 
            break;
		case 2:
			currentRes = highRes; 
            break;
	}
}


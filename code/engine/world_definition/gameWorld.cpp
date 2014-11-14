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

    while (!items.empty()) {
        delete items.back();
        items.pop_back();
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
    const char *collision_filename, const char *top_filename, Hero &hero) {
    
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
    
    // Get the width and height of the world
    w = highRes->w();
    h = highRes->h();

    // Amount to divide the dimensions by for resolutions
    medCut = 8;
    lowCut = 16;

    // Initialize Medium Resolution
    medRes = new GameMap();
    medRes->setBackgroundLayer(Gfx::downsample(highRes->backgroundLayer, 
        highRes->backgroundLayer->w/medCut, highRes->backgroundLayer->h/medCut, 
        blend_average));
    medRes->setCollisionLayer(Gfx::downsample(highRes->collisionLayer,
        highRes->collisionLayer->w/medCut, highRes->collisionLayer->h/medCut,
        blend_average));
    if (top_filename) {
        medRes->setTopLayer(Gfx::downsample(highRes->topLayer,
            highRes->topLayer->w/medCut, highRes->topLayer->h/medCut, 
            blend_average));
    }

    // Initialize Low Resolution
    lowRes = new GameMap();
    lowRes->setBackgroundLayer(Gfx::downsample(highRes->backgroundLayer,
        highRes->backgroundLayer->w/lowCut, highRes->backgroundLayer->h/lowCut,
        blend_average));
    lowRes->setCollisionLayer(Gfx::downsample(highRes->collisionLayer,
        highRes->collisionLayer->w/lowCut, highRes->collisionLayer->h/lowCut,
        blend_average));
    if (top_filename) {
        lowRes->setTopLayer(Gfx::downsample(highRes->topLayer,
            highRes->topLayer->w/lowCut, highRes->topLayer->h/lowCut, 
            blend_average));
    }

    // Create map images
    highRes->createMapImage(w,h);
    medRes->createMapImage(w,h);
    lowRes->createMapImage(w,h);
    
    // Set resolution
    currentRes = lowRes;
    currentResLevel = Resolution::LOW;

    // create some random items 
    for (int i = 0; i < 4; i++) {
        
        Item *newItem = new Item(rand() % w, rand() % h, Gfx::loadImage("resources/egg.png"), "hero");
        
        while (currentRes->mapImg->collision(newItem->spriteImage, newItem->x, newItem->y)) {
            newItem->x = rand() % w;
            newItem->y = rand() % h;
        }

        items.push_back(newItem);
    }

    // create some enemies (hp, speed, damage, x, y)
    for (int i = 0; i < 3; i++) {
        AutoSentry *e = new AutoSentry(50, 2, 25, rand() % w, rand() % h);

        // set up the grid for AI
        //e->pathfinder.set_grid(&grid);
        //e->pathfinder.path_to_hero(e->x, e->y);

        while (currentRes->mapImg->collision(e->spriteImage, e->x, e->y)) {
            e->x = rand() % w;
            e->y = rand() % h;
        }
        enemies.push_back(e);
    }

    // initialize the WorldGrid & build initial grid
    grid.init(lowRes->collisionLayer, &hero, &enemies, lowCut);
    grid.build_wall_grid(); //_conservative();
    grid.build_grid();

    // Set grid for enemies
    for (Enemy *e : enemies) {
        AutoSentry *a = dynamic_cast<AutoSentry*>(e);
        a->pathfinder.set_grid(&grid);
        //a->pathfinder.path_to_hero_(e->x, e->y);
    }

    return true;
}

/**
 * This function increases the current resolution, unless the world is
 * already at its highest resolution.
 */
void GameWorld::next_resolution()
{
	switch (currentResLevel) {
		case Resolution::LOW:
			currentResLevel = Resolution::MED; 
            break;
		case Resolution::MED:
			currentResLevel = Resolution::HIGH; 
            break;
	}
	_set_current_res();
}

/**
 * This function decreases the current resolution, unless the world is
 * already at its lowest resolution.
 */
void GameWorld::prev_resolution()
{
	switch (currentResLevel) {
		case Resolution::MED:
			currentResLevel = Resolution::LOW; 
            break;
		case Resolution::HIGH:
			currentResLevel = Resolution::MED; 
            break;
	}
	_set_current_res();
}

/**
 * This function sets the current resolution to the resolution
 * passed in.
 */
void GameWorld::set_resolution(Resolution res) {
    currentResLevel = res;
    _set_current_res();
}

/**
 * This function is used to update the world's game map when the resolution
 * changes.
 */
void GameWorld::_set_current_res()
{
	switch (currentResLevel) {
		case Resolution::LOW:
			currentRes = lowRes; 
            break;
		case Resolution::MED:
			currentRes = medRes; 
            break;
		case Resolution::HIGH:
			currentRes = highRes; 
            break;
	}
}


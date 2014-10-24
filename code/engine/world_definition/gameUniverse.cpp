/*********************************************************
File Name:	    gameUniverse.cpp
Author:		      The Breakfast Club
Creation Date:  09-25-2014
Description:    Holds the data defining the universe
************************************************************/

#include "gameUniverse.h"
#include <iostream> 
#include <numeric>

/**
 * Default constructor for the universe. Must call GameUniverse::init()
 * before using the GameUniverse instance.
 */
GameUniverse::GameUniverse(string universe_name) : universeName(universe_name) 
{
  sublevels[Sublevel::HUB] = new GameWorld("hub");
  sublevels[Sublevel::FLOUR] = new GameWorld("flour");
  sublevels[Sublevel::SUGAR] = new GameWorld("sugar");
  sublevels[Sublevel::BAKING_SODA] = new GameWorld("baking_soda");
  sublevels[Sublevel::BUTTER] = new GameWorld("butter");

  currentWorld = sublevels[Sublevel::HUB];
  currentLevel = Sublevel::HUB;
}

/**
 * This method changes the game world to the provided sublevel at the
 * provided resolution. It also moves the hero to the location provided
 * by x, y
 */
void GameUniverse::changeWorld(Sublevel level, Resolution res, int x, int y) {

    if (level == currentLevel) return;

    // adjust the world reference
    currentWorld = sublevels[level];
    currentLevel = level;
    currentWorld->set_resolution(res);

    // Move the hero
    hero.x = x;
    hero.y = y;
}

/**
 * This method checks to see if the hero collides with any items
 * in the currentWorld at the current resolution. If the hero collides
 * with an item, it will pick up the first item it collides with, placing
 * it in the hero's bag and returning true.  If the hero collides with no
 * items, it returns false.
 */
bool GameUniverse::checkCollisionsWithItems() {
    
    auto it = currentWorld->items.begin();
    while (it != currentWorld->items.end()) {

        Item *item = *it;

        // Continue if item is unobtainable
        if (!item->obtainable) {
            ++it;
            continue;
        }

        // Make a copy of the world map, including the item
        Image map(currentWorld->w, currentWorld->h);
        map.blit(currentWorld->currentRes->mapImg, 0,0);
        map.ablit(item->spriteImage, item->x, item->y);

        // Check if item and hero collide
        if (map.collision(hero.spriteImage, hero.x, hero.y)) {
            hero.bag.push_back(item);
            it = currentWorld->items.erase(it);
            return true;
        }
        ++it;
    }
    return false;
}

// The deconstructor
GameUniverse::~GameUniverse() {
    if(sublevels[Sublevel::HUB])
      delete(sublevels[Sublevel::HUB]);
      
    if(sublevels[Sublevel::FLOUR])
      delete(sublevels[Sublevel::FLOUR]);
      
    if (sublevels[Sublevel::SUGAR])
      delete(sublevels[Sublevel::SUGAR]);
      
    if(sublevels[Sublevel::BAKING_SODA])
      delete(sublevels[Sublevel::BAKING_SODA]);
      
    if(sublevels[Sublevel::BUTTER])
      delete(sublevels[Sublevel::BUTTER]);
    
}

/**
 * This function initializes the game universe using the images defined in
 * gameUniverse.h as the high resolution game universe. It returns false 
 * if any errors are encountered while initializing, true otherwise.
 *
 * This method must be called before any other GameUniverse functions.
 */
bool GameUniverse::init() {
    
    // Initializing the game sub levels  
    if(! sublevels[Sublevel::HUB] -> init(hubBackground, hubCollision, hubTop))
      return false;
      
    if(! sublevels[Sublevel::FLOUR] -> init(flourBackground, flourCollision, flourTop))
      return false;
      
    if(! sublevels[Sublevel::SUGAR] -> init(sugarBackground, sugarCollision, sugarTop))
      return false;
      
    if(! sublevels[Sublevel::BAKING_SODA] -> init(baking_sodaBackground, baking_sodaCollision, baking_sodaTop))
      return false;
      
    if(! sublevels[Sublevel::BUTTER] -> init(butterBackground, butterCollision, butterTop))
      return false;
    
    if (!(hero.spriteImage = Gfx::loadImage(heroImage)))
        return false;

    return true;
}


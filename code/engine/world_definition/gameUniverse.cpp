/*********************************************************
File Name:	    gameUniverse.cpp
Author:		      The Breakfast Club
Creation Date:  09-25-2014
Description:    Holds the data defining the universe
************************************************************/

#include "gameUniverse.h"
#include "sublevel.h"
#include <SDL2/SDL.h>
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
 * This function initializes the game universe using the passed images as the
 * high resolution game universe. It returns false it any errors are encountered
 * while initializing, true otherwise.
 *
 *
 * This method must be called before any other GameUniverse functions.
 */
bool GameUniverse::init() {
  int heroHitpoints = 100;
  int heroAttackDmg = 0;
  int heroSpeed = 1;
  bool heroInvincible = false;
  //Initialize game worlds
    
    // Initializing the hero attributes
    hero.hitPoints = heroHitpoints;
    hero.invincible = heroInvincible;
    hero.speed = heroSpeed;
    hero.attackDmg = heroAttackDmg;
    
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
      
    return true;
    
    
}


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
 
 public:
 gameWorld** sublevels = new gameWorld*[Sublevel::COUNT];
 
 sublevels[Sublevel::HUB] = new gameWorld("hub");
 sublevels[Sublevel::FLOUR] = new gameworld("flour");
 sublevels[Sublevel::SUGAR] = new gameworld("sugar");
 sublevels[Sublevel::BAKING_SODA] = new gameworld("baking_soda");
 sublevels[Sublevel::BUTER] = new gameworld("butter");
 
 const char *hubBackground = "resources/background.png";
 const char *hubCollision = "resources/test4cl.png";
 const char *hubTop = NULL;
 
 const char *flourBackground = "resources/background.png";
 const char *flourCollision = "resources/test4cl.png";
 const char *flourTop = NULL;
 
 const char *sugarBackground = "resources/background.png";
 const char *sugarCollision = "resources/test4cl.png";
 const char *sugarTop = NULL;

 const char *baking_sodaBackground = "resources/background.png";
 const char *baking_sodaCollision = "resources/test4cl.png";
 const char *baking_sodaTop = NULL;
 
 const char *butterBackground = "resources/background.png";
 const char *butterCollision = "resources/test4cl.png";
 const char *butterTop = NULL;
 
 const char *heroImage = "resources/hero.png";
 
 
GameUniverse::GameUniverse(string universe_name) : universeName(universe_name) 
{
  hero = NULL;
}

// The deconstructor
GameUniverse::~GameUniverse() {

    if (hero) {
        delete(hero);
    }
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
bool GameUniverse::init(Hero hero) {
  int heroHitpoints = 100;
  int heroAttackDmg = 0;
  int heroSpeed = 1;
  bool heroInvincible = false;
    
    // Do nothing if the universe is already initialized
    if (universe != NULL) return true;

    // Initialize the game universe
    universe = new GameUniverse();
    
    // Initializing the hero attributes
    hero = new Hero();
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


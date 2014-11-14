/*********************************************************
File Name:	    gameUniverse.h
Author:		    The Breakfast Club
Creation Date:  10-13-2014
Description:    This class holds the different sublevels/subworlds
                and other items common to the whole gameUniverse,
                such as the hero.
************************************************************/

#pragma once

#include "gameWorld.h"
#include "hero.h"
#include "sublevel.h"
#include "../../util/clock.h"
    
class GameUniverse{
  public:
    GameUniverse(string universe_name);
    ~GameUniverse();
    bool init();
    
    /** Properties of the universe */
    Hero hero;
    string universeName; 
    GameWorld** sublevels = new GameWorld*[Sublevel::COUNT];

    GameWorld* currentWorld;
    Sublevel currentLevel;

    void changeWorld(Sublevel level, Resolution res, int x, int y);
    bool checkCollisionsWithItems();

    // Keep a reference to the Clock for event scheduling
    Clock *clock;

  private:

const char *hubBackground = "resources/background.png";
const char *hubCollision = "resources/fullBoardTest1.png";
const char *hubTop = NULL;
    
const char *flourBackground = "resources/background.png";
const char *flourCollision = "resources/Test1CL.png";
const char *flourTop = NULL;

const char *sugarBackground = "resources/hero.png";
const char *sugarCollision = "resources/test4cl.png";
const char *sugarTop = NULL;

const char *baking_sodaBackground = "resources/background.png";
const char *baking_sodaCollision = "resources/test4cl.png";
const char *baking_sodaTop = NULL;
    
const char *butterBackground = "resources/background.png";
const char *butterCollision = "resources/test4cl.png";
const char *butterTop = NULL;

const char *heroImage = "resources/hero.png";
};


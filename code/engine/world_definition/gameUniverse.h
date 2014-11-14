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
#include "../../util/configurations.h"
    
class GameUniverse{
  public:
    GameUniverse(string universe_name);
    ~GameUniverse();
    bool init(const Configurations &config);
    
    /** Properties of the universe */
    Hero hero;
    string universeName; 
    GameWorld** sublevels = new GameWorld*[Sublevel::COUNT];

    GameWorld* currentWorld;
    Sublevel currentLevel;

    Resolution currentRes();
    void changeWorld(Sublevel level, Resolution res, int x, int y);
    bool checkCollisionsWithItems();

};


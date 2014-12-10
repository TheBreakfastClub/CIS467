/*********************************************************
File Name: character.h
Author: The Breakfast Club
Creation Date: 10-13-2014
Description: Defines the different types of characters that can
be in the world.
************************************************************/
#pragma once
#include <utility>
#include "object.h"

class Character: public Object {
  public:
    Character();
    Character(int x, int y, GameWorld *world, bool solid = true, 
      bool pushable = false, bool pushes = false, int speed = 1);
    ~Character();
    
    bool move(int dx, int dy);
    
    /** Defines if a sprite is invincible **/
    bool invincible;
    /** Defines the speed of a sprite **/
    int speed;
    bool hit;

    int maxHitPoints;
    bool pushes;

    int getHitPoints();
    bool changeHitPoints(int change);
    bool setHitPoints(int newHitPoints);
    void damage(int d);

  private:
    /** Defines the amount of hitpoints a sprite has **/
    int hitPoints;
    
};


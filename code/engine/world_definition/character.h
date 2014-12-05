/*********************************************************
File Name: character.h
Author: The Breakfast Club
Creation Date: 10-13-2014
Description: Defines the different types of characters that can
be in the world.
************************************************************/
#pragma once
#include <utility>
#include "sprite.h"

using namespace std;

class Character: public Sprite {
  public:
    Character();
    ~Character();
    Character(int hp, int speed, int damage, int x=0, int y=0, bool inv=false);
    Character(Image *charImgH, Image *charImgM, Image *charImgL, int hp, int speed, int damage, int x=0, int y=0, bool inv=false);

    /** Defines if a sprite is invincible **/
    bool invincible;
    /** Defines the speed of a sprite **/
    int speed;
    /** Defines the attack damage of a sprite **/
    int attackDmg;
    /** Used when a Character has taken damage **/
    Image *hitImage;
    bool hit;

    int maxHitPoints;

    int getHitPoints();
    bool changeHitPoints(int change);
    bool setHitPoints(int newHitPoints);

  private:
    /** Defines the amount of hitpoints a sprite has **/
    int hitPoints;
    
};


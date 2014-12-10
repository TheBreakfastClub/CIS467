/*********************************************************
File Name:	    hero.cpp
Author:		    The Breakfast Club
Creation Date:  09-28-2014
Description:	Defines the hero of the game universe.
************************************************************/

#include "hero.h"
#include <iostream>
#include "sprite.h"
#include "gameWorld.h"

Hero::Hero() {
    setHitPoints(200);
    invincible = false;
    speed = 5;
    x = 150;
    y = 150;
    pushable = true;
    hitSprite = 0;
}

Hero::~Hero() {
    while (!bag.empty()) {
        delete bag.back();
        bag.pop_back();
    }
    while (!crystals.empty()) {
        delete crystals.back();
        crystals.pop_back();
    }
}

// world field must be set before calling this function
bool Hero::loadImage(const char *fileName, int medCut, int lowCut, bool rotates) {
  Image *image = ::loadImage(fileName);
  if(!image) {
    std::cout << "could not load image file: " << fileName << '\n';
    return false;
  }
  sprite = new Sprite(image, world->pixelator, medCut, lowCut, rotates);
  Image *hitImage = redTint(image);
  hitSprite = new Sprite(hitImage, world->pixelator, medCut, lowCut, rotates);
  delete hitImage;
  delete image;
  return sprite->angles;
}

void Hero::draw(Image *screen, int panX, int panY) {
  Image *img = hit ? hitSprite->getImage(world->currentResLevel, angle) : getImage();
  float s = hit ? hitSprite->scale[world->currentResLevel] : getScale();
  screen->asblit(img, x - s*img->w/2 - panX, y - s*img->h/2 - panY, s);
}

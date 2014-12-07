#include "object.h"
#include "gameWorld.h"
#include "../render/collision.h"

Object::Object() {
  x = 0;
  y = 0;
  world = 0;
  angle = 0;
  hit = false;
  solid = true;
  pushable = false;
  sprite = 0;
}

Object::Object(int x, int y, GameWorld *world) {
  this->x = x;
  this->y = y;
  this->world = world;
  angle = 0;
  hit = false;
  solid = true;
  pushable = false;
  sprite = 0;
}

Object::~Object() {
  delete sprite;
}

// world field must be set before calling this function
bool Object::loadImage(const char *fileName, int medCut, int lowCut, bool rotates) {
  sprite = new Sprite(fileName, world->pixelator, medCut, lowCut, rotates);
  return sprite->angles;
}

Image* Object::getImage() {
  return sprite->getImage(world->currentResLevel, angle);
}

Image* Object::getImage(int angle) {
  return sprite->getImage(world->currentResLevel, angle);
}

float Object::getScale() {
  return sprite->scale[world->currentResLevel];
}

bool Object::fits(int x, int y, int angle) {
  if(!solid) return true;
  if(!fitsMap(x, y, angle)) return false;
//   for(auto i = world->enemies.begin(); i != world->enemies.end(); ++i)
//     if((*i)->solid && overlaps(*i, angle)) return false;
//   for(auto i = world->items.begin(); i != world->items.end(); ++i)
//     if((*i)->solid && overlaps(*i, angle)) return false;
//   if(world->hero->solid) return !overlaps(world->hero, angle);
  return true;
}


bool Object::fits(int x, int y) {
  return fits(x, y, angle);
}

bool Object::fitsMap(int x, int y, int angle) {
  Image *img = getImage(angle);
  Image *map = world->currentRes->collisionLayer;
  float mapScale = world->scale[world->currentResLevel];
  float s = getScale();
  return !scollision(img, x - s*img->w/2, y - s*img->h/2, s, map, 0, 0, mapScale);
}

bool Object::fitsMap(int x, int y) {
  return fitsMap(x, y, angle);
}

bool Object::moveTo(int x, int y, int a) {
  if(fits(x, y, a)) {
    this->x = x;
    this->y = y;
    angle = a;
    return true;
  }
  return false;
}

bool Object::moveTo(int x, int y) {
  return moveTo(x, y, angle);
}

bool Object::move(int dx, int dy) {
  int na = getAngle(dx, dy) % sprite->angles;
  if(moveTo(x+dx, y+dy, na)) return true;
  if(na != angle) return moveTo(x+dx, y+dy, angle);
  return false;
}

bool Object::overlaps(Object *other) {
  return overlaps(other, angle);
}
 
bool Object::overlaps(Object *other, int angle) {
  if(this == other) return false;
  Image *im1 = getImage(angle);
  Image *im2 = other->getImage();
  float s1 = getScale();
  float s2 = other->getScale();
  return world == other->world && scollision(
    im1, x - s1*im1->w/2, y - s1*im1->h/2, s1, 
    im2, other->x - s2*im2->w/2, other->y - s2*im2->h/2, s2);
}

void Object::draw(Image *screen, int panX, int panY) {
  Image *img = getImage();
  float s = getScale();
  screen->asblit(img, x - s*img->w/2 - panX, y - s*img->h/2 - panY, s);
}

// draw this object with an alternate sprite (maybe a damage sprite...)
void Object::draw(Image *screen, int panX, int panY, Sprite *sprite) {
  Image *img = sprite->getImage(world->currentResLevel, angle);
  float s = sprite->scale[world->currentResLevel];
  screen->asblit(img, x - s*img->w/2 - panX, y - s*img->h/2 - panY, s);
}


int Object::getAngle(int dx, int dy) {
  if(dx  < 0) {
    if(dy < 0) return 1;
    else if(dy == 0) return 2;
    else return 3;
  }
  else if(dx > 0) {
    if(dy < 0) return 7;
    else if(dy == 0) return 6;
    else return 5;
  }
  else if(dy < 0) return 0;
  else return 4;
}
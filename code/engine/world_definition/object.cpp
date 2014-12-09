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
  this->x = x + 16; // dirty hack
  this->y = y + 16; // dirty hack
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
  Image *image = ::loadImage(fileName);
  if(!image) {
    std::cout << "could not load image file: " << fileName << '\n';
    return false;
  }
  sprite = new Sprite(image, world->pixelator, medCut, lowCut, rotates);
  delete image;
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
  for(auto i : world->enemies)
    if(i->solid && overlaps(i, x, y, angle)) return false;
  for(auto i : world->items)
    if(i->solid && overlaps(i, x, y, angle)) return false;
  if(world->hero->solid) return !overlaps(world->hero, x, y, angle);
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

bool Object::turn(int dx, int dy) {
  int na = getAngle(dx, dy) % sprite->angles;
  if(angle == na) return true;
  return moveTo(x, y, na);
}

bool Object::turnMove(int dx, int dy) {
  turn(dx, dy);
  return move(dx, dy);
}

bool Object::turnPush(int dx, int dy) {
  turn(dx, dy);
  return push(dx, dy);
}

bool Object::_move(int dx, int dy) {
  return moveTo(x + dx, y + dy);
}

bool Object::move(int dx, int dy) {
  return moveTo(x + dx, y + dy);
}

bool Object::push(int dx, int dy) {
  if(!fitsMap(x+dx, y+dy)) return false;
  bool s = solid;
  solid = false;
  x += dx;
  y += dy;
  for(auto i : world->enemies)
    if(i->solid && overlaps(i) && (!i->pushable || !i->push(dx,dy))) goto fail; 
  for(auto i : world->items)
    if(i->solid && overlaps(i) && (!i->pushable || !i->push(dx,dy))) goto fail; 
  if(world->hero->solid && overlaps(world->hero) && 
    (!world->hero->pushable || !world->hero->push(dx,dy))) goto fail;
  solid = s;
  return true;
  fail:
  x -= dx;
  y -= dy;
  solid = s;
  return false;
}

bool Object::overlaps(Object *other) {
  return overlaps(other, x, y, angle);
}

bool Object::overlaps(Object *other, int x, int y) {
  return overlaps(other, x, y, angle);
}
 
// x,y,angle are for *this*
bool Object::overlaps(Object *other, int x, int y, int angle) {
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

// are we within the center range of the specified object's center
bool Object::within(float r, Object *o) {
  Image *img = o->getImage();
  float d = o->getScale()*max(img->w, img->h)*r/2; // r*radius
  float dx = x - o->x;
  float dy = y - o->y;
  return (dx*dx + dy*dy) < d*d;
}
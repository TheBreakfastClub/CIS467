#include "portal.h"

Portal::Portal(int x, int y, GameWorld *world, std::string name, bool usable, Sublevel destination, int dstX, int dstY) :
  Object(x, y, world)
{
  this->name = name;
  this->usable = usable;
  this->destination = destination;
  xDest = dstX;
  yDest = dstY;
}

Portal::~Portal() {}
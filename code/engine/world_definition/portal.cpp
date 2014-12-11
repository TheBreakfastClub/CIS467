#include "portal.h"

Portal::Portal(int x, int y, GameWorld *world, std::string name, bool usable, Sublevel destination, int dstX, int dstY) :
  Object(x, y, world, false, false)
{
  this->name = name;
  this->usable = usable;
  this->destination = destination;
  xDest = dstX + 16; // dirty hack
  yDest = dstY + 16; // dirty hack
}

Portal::~Portal() {}
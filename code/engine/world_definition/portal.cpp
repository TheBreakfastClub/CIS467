#include "portal.h"

Portal::Portal(int x, int y, std::string pname, bool usable, Sublevel destination, int xDest, int yDest) 
 : Sprite(x, y ), name(pname), usable(usable), destination(destination), xDest(xDest), yDest(yDest){}
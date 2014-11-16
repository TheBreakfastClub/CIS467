#include "portal.h"

Portal::Portal(int x, int y, std::string pname, bool usable, Sublevel destination) 
 : Sprite(x, y ), name(pname), usable(usable), destination(destination){}
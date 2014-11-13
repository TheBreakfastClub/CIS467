#include "portal.h"

Portal::Portal(int x, int y, Image *image, std::string pname, bool usable, Sublevel destination) 
 : Sprite(x, y , image), name(pname), obtainable(){}
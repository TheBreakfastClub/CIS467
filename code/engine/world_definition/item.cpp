#include "item.h"

Item::Item(int x, int y, Image *image, std::string pname, bool obtainable)
 : Sprite(x, y, image), name(pname), obtainable(obtainable) {}




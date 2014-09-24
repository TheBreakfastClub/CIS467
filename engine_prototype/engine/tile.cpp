#include "tile.h"

Tile::Tile(int x, int y) : xy(x, y)
{
	blocking = false;
	//entity = NULL;
}

std::string Tile::str()
{
	return "(" + std::to_string(xy.first) + ", " + std::to_string(xy.second) + ")";
}
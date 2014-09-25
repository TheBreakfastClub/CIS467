#include "tile.h"

Tile::Tile(int x, int y, TileType *type) : xy(x, y), type(type)
{
}

std::string Tile::str()
{
	return "(" + std::to_string(xy.first) + ", " + std::to_string(xy.second) + ")";
}

#pragma once

#include <utility>
#include <string>
#include "tileType.h"

class Tile {

	private:
		std::pair<int, int> xy;

	public:
		Tile(int x, int y, TileType *type);

        TileType *type;

		std::string str(); // for debugging purposes

};

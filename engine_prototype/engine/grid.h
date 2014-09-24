#pragma once

#include "tile.h"
#include <vector>
#include <cassert>

class Grid {

	public:
		
		std::vector<std::vector<Tile> > grid;
		int dim_x, dim_y, tile_dim;
		Grid(int dim_x, int dim_y, int tile_dim);
		std::vector<Tile>& operator[](int index);

};

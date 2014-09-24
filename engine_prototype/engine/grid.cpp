#include "grid.h"

Grid::Grid(int dim_x, int dim_y, int tile_dim) : grid()
{
	this->dim_x = dim_x;
	this->dim_y = dim_y;
	this->tile_dim = tile_dim;

	// Populate the grid with empty locations
	for (int x = 0; x < dim_x; x++)
	{
		std::vector<Tile> row;
		for (int y = 0; y < dim_y; y++)
		{
			row.push_back(Tile(x, y));
		}
		grid.push_back(row);
	}
}

// Access the Grid as though it were the data structure behind the Grid
std::vector<Tile>& Grid::operator[](int index)
{
	assert(index >= 0 && index < grid.size());
	return grid[index];
}
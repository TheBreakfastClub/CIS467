#include "grid.h"

Grid::Grid(int dim_x, int dim_y, int tile_dim) : tileTypes(TileSet::COUNT)
{
	this->dim_x = dim_x;
	this->dim_y = dim_y;
	this->tile_dim = tile_dim;

    /**
     * Create generic tile types for now. Eventually, the details on the world
     * would be read in from a file or something...
     */
    int pixLevels = 3; // Assuming 3 pixelation levels for now

    // Add floor
    TileType floor("floor", TileSet::TILE_FLOOR);
    for (int i = 0; i < pixLevels; ++i) {
        floor.blocking.push_back(false); // you can always walk across floors. they never block
    }
    tileTypes[TileSet::TILE_FLOOR] = floor;

    // Add water
    TileType water("water", TileSet::TILE_WATER);
    for (int i = 0; i < pixLevels; ++i) {
        water.blocking.push_back(true);  // you cannot walk across water. you aren't Jesus.
    }
    tileTypes[TileSet::TILE_WATER] = water;

	// Populate the grid with empty locations
	for (int x = 0; x < dim_x; x++)
	{
		std::vector<Tile> row;
		for (int y = 0; y < dim_y; y++)
		{
            TileType *type;
            if (y % 2 == x % 2) 
                type = &tileTypes[TileSet::TILE_FLOOR];
            else
                type = &tileTypes[TileSet::TILE_WATER];

			row.push_back(Tile(x, y, type)); // make all tiles floor tiles for now.
		}
		grid.push_back(row);
	}
}

// Access the Grid as though it were the data structure behind the Grid
std::vector<Tile>& Grid::operator[](int index)
{
	assert(index >= 0 && ((unsigned)index) < grid.size());
	return grid[index];
}

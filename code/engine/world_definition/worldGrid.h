#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include <algorithm>
#include "enemy.h"
#include "hero.h"

enum Celltype { GROUND, WALL, HERO, ENEMY };

struct Cell {
	int x, y, id; // ID specifically for ememies
	Celltype type;

	// pathfinding data
	Cell *parent;
	bool open;
	int g_val, f_val;

	bool operator==(const Cell &c) { return c.x == x && c.y == y; }
};

class WorldGrid {
public:
	WorldGrid();
	~WorldGrid();
	Cell operator [](int i) const { return grid[i]; }

	void build_grid();
	void build_wall_grid();
	void build_wall_grid_conservative();
	void init(Image *map, Hero *hero, std::vector<Enemy*> *enemies, int hres_div);
	Cell hero_cell();
	int convert_coordinate(int x);

	int width, height;
	std::vector<Cell> grid;
	std::vector<Cell> wall_grid;

	// need these references to rebuild the grid
	Hero *hero; 
	std::vector<Enemy*> *enemies; 
	Image *map;
	int hres_div;

	// Additionally, keep track of where the Hero is
	int h_x, h_y;
};
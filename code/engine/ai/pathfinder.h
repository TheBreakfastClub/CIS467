#pragma once

#include "../world_definition/worldGrid.h"
#include <functional>
#include <utility>
#include <vector>
#include <string>
#include <math.h>
#include <queue>
#include <map>


class CellComp {
public:
	bool operator()(const Cell *c1, const Cell *c2)
	{
		return c1->f_val > c2->f_val;
	}
};

class Pathfinder {
public:
	Pathfinder(int id);
	void set_grid(WorldGrid *grid);

	void find_hero(int x, int y);
	std::pair<int, int> next_move();
	std::pair<int, int> unstuck(std::string direction, int x, int y, int percent, int magnitude);

	void print_path_to_hero();

	const int dirs[3] = {-1, 0, 1};

	WorldGrid *grid;
	Cell *path; // linked list

	// owner enemy info
	int id;  // id of enemy using the pathfinding algorithm
};

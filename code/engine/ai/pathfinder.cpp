#include "pathfinder.h"
#include <cstdlib>
#include <iostream>


Pathfinder::Pathfinder(int id) : id(id) { path = NULL; }

void Pathfinder::set_grid(WorldGrid *grid) { this->grid = grid; }

void Pathfinder::find_hero(int x, int y)
{
	// First convert the calling Enemy's x&y coordinates to jive with the grid
	x = grid->convert_coordinate(x);
	y = grid->convert_coordinate(y);

	// TODO: take this out when we prevent overlapping of enemies/hero
	if (x == grid->h_x && y == grid->h_y) return;

	// Define our open and closed lists
	std::priority_queue<Cell*, std::vector<Cell*>, CellComp> open_cells;
	std::map<std::string, Cell*> closed_cells;

	// Define utility functionality in some lambdas
	auto diag_move = [](Cell *from, Cell *to) { return from->x != to->x && from->y != to->y; };
	auto add_to_closed = [&](Cell *c) { 
		closed_cells[std::to_string(c->x)+","+std::to_string(c->y)] = c; 
		c->open = false;
	};
	auto add_to_open = [&](std::vector<Cell*> &cells, Cell *parent) {
		for (Cell *c : cells) {

			// Calculate the f and g values
			int g = (diag_move(parent, c) ? 14 : 10); // diagonal moves are more expensive
			g += parent->g_val;
			int h = abs(x - c->x) + abs(y - c->y); // distance heuristic: manhattan distance
			int f = g + h;

			// See if the Cell is already part of the open list
			if (c->open) { 
				if (c->f_val > f) { // "re-parent" Cell in open list if THIS parent offers it a cheaper route
					c->parent = parent;
					c->g_val = g;
					c->f_val = f;
				}
				continue; // already a part of the open list
			}

			// add the scores to the cell
			c->g_val = g;
			c->f_val = f;

			c->open = true;
			c->parent = parent;
			open_cells.push(c);
		}
	};
	auto get_neighbors = [&](Cell *cell, int e_x, int e_y) { // e_x, e_y represents the Enemy's position
		std::vector<Cell*> neighbors;
		for (int offset_y : dirs) {
			for (int offset_x : dirs) {
				if (offset_y == 0 && offset_x == 0) continue;
				int x = cell->x + offset_x;
				int y = cell->y + offset_y;

				// Do bounds checking and make sure a cell isn't already in the closed list
				if (x >= 0 && x < grid->width && y >= 0 && y < grid->height && closed_cells.count(std::to_string(x)+","+std::to_string(y)) == 0) {
					Cell *c = &(grid->grid[y * grid->width + x]);
					if (c->x == e_x && c->y == e_y) {
						neighbors.clear();
						neighbors.push_back(c); // return the Enemy Cell by itself if found
						return neighbors;
					}
					if (c->type == Celltype::GROUND) {
						neighbors.push_back(c);
					}
				}
			}
		}
		return neighbors;
	};

	// Get the Cell at the starting point, starting where the Hero is
	Cell *origin = &(grid->grid[grid->h_y * grid->width + grid->h_x]);
	origin->parent = NULL;

	if (origin->type != Celltype::HERO) {
		std::cout << "Origin cell isn't of Hero celltype\n";
		return;
	}

	// Add origin cell to closed list
	add_to_closed(origin);

	// Get the origin's neighbors and add them to the open list
	std::vector<Cell*> origin_neighbors = get_neighbors(origin, x, y);

	// Initial check to see if we've found the target Enemy
	// NO PATH TO ENEMY
	if (origin_neighbors.empty()) {
		path = NULL;
		std::cout << "NO PATH TO ENEMY (right away at origin too!)\n";
		return; // blocked in from the get-go...
	}
	// FOUND ENEMY
	if (origin_neighbors.size() == 1 && origin_neighbors[0]->x == x && origin_neighbors[0]->y == y) {
		path = origin_neighbors[0];
		path->parent = origin;
		std::cout << "Found Enemy in origin's neighbors\n";
		return;
	}

	// Add out initial neighbor cells to the open list
	add_to_open(origin_neighbors, origin);

	while (!open_cells.empty()) {
		Cell *c = open_cells.top();
		open_cells.pop();

		// Add to closed list now that it's being checked
		add_to_closed(c);

		std::vector<Cell*> neighbors = get_neighbors(c, x, y);

		if (neighbors.empty()) continue;
		if (neighbors.size() == 1 && neighbors[0]->x == x && neighbors[0]->y == y) {
			path = neighbors[0];
			path->parent = c;
			//std::cout << "Found Enemy after " << std::to_string(iterations) << " iterations of A*\n";
			//print_path_to_hero();
			return;
		}

		add_to_open(neighbors, c);
	}

	// Couldn't find a path to the Enemy
	std::cout << "No path to Enemy found :(\n";
	print_path_to_hero();
}

void Pathfinder::print_path_to_hero()
{
	Cell *a;// = path;
	for (int y = 0; y < grid->height; y++) {
		for (int x = 0; x < grid->width; x++) {
			bool in_path = false;
			a = path;
			if (a != NULL) {
				while (a->parent != NULL) {
					if (a->x == x && a->y == y){ 
						std::cout << "* ";
						in_path = true;
						break;
					}
					a = a->parent;
				}
			}
			if (in_path) {
				in_path = false;
				continue;
			}
			switch (grid->grid[y*(grid->width)+x].type) {
				case Celltype::WALL:
					std::cout << "W "; break;
				case Celltype::ENEMY:
					std::cout << grid->grid[y*(grid->width)+x].id << (grid->grid[y*(grid->width)+x].id < 10 ? " " : ""); break;
				case Celltype::HERO:
					std::cout << "H "; break;
				default:
					std::cout << "  ";
			}
		}
		std::cout << std::endl;
	}
	//int depth = 0;
	//Cell *c = path;
	//while (c->parent != NULL) {
	//	c = c->parent;
	//	depth++;
	//}
	//std::cout << "Number of Cells in path: " << std::to_string(depth) << std::endl;
}

std::pair<int, int> Pathfinder::next_move()
{
	std::pair<int, int> next(0, 0);
	Cell *c = path;
	if (c == NULL || c->parent == NULL) return next;
	next.first = (c->parent->x > c->x ? 1 : (c->parent->x < c->x ? -1 : 0));
	next.second = (c->parent->y > c->y ? 1 : (c->parent->y < c->y ? -1 : 0));
	return next;
}

std::pair<int, int> Pathfinder::unstuck(std::string direction, int x, int y, int percent, int magnitude)
{
	std::pair<int, int> move(0, 0);
	auto set_move = [&](int f, int s) {
		move.first = f;
		move.second = s;
	};

	if (direction == "n") {
		if (rand() % 100 < percent) { 
			if (rand() % 2) set_move(1, 0); // east
			else set_move(-1, 0); // west
		}
		else { // rest: nw, ne, se, sw, s
			if (rand() % 2) set_move(-1, -1);
			else if (rand() % 2) set_move(1, -1);
			else if (rand() % 2) set_move(1, 1);
			else if (rand() % 2) set_move(-1, 1);
			else set_move(0, 1);
		}
	}
	else if (direction == "ne") {
		if (rand() % 100 < percent) { // e, n
			if (rand() % 2) set_move(1, 0);
			else set_move(0, -1);
		}
		else { // se, s, sw, w, nw
			if (rand() % 2) set_move(1, 1);
			else if (rand() % 2) set_move(0, 1);
			else if (rand() % 2) set_move(-1, 1);
			else if (rand() % 2) set_move(-1, 0);
			else set_move(-1, -1);
		}
	}
	else if (direction == "e") {
		if (rand() % 100 < percent) { // n, s
			if (rand() % 2) set_move(0, -1);
			else set_move(0, 1);
		}
		else { // ne, se, sw, w, nw
			if (rand() % 2) set_move(1, -1);
			else if (rand() % 2) set_move(1, 1);
			else if (rand() % 2) set_move(-1, 1);
			else if (rand() % 2) set_move(-1, 0);
			else set_move(-1, -1);
		}
	} 
	else if (direction == "se") {
		if (rand() % 100 < percent) { // e, s
			if (rand() % 2) set_move(1, 0);
			else set_move(0, 1);
		}
		else { // ne, n, sw, w, nw
			if (rand() % 2) set_move(1, -1);
			else if (rand() % 2) set_move(0, -1);
			else if (rand() % 2) set_move(-1, 1);
			else if (rand() % 2) set_move(-1, 0);
			else set_move(-1, -1);
		}
	}
	else if (direction == "s") {
		if (rand() % 100 < percent) { // e, w
			if (rand() % 2) set_move(1, 0);
			else set_move(-1, 0);
		}
		else { // ne, n, sw, se, nw
			if (rand() % 2) set_move(1, -1);
			else if (rand() % 2) set_move(0, -1);
			else if (rand() % 2) set_move(-1, 1);
			else if (rand() % 2) set_move(1, 1);
			else set_move(-1, -1);
		}
	}
	else if (direction == "sw") {
		if (rand() % 100 < percent) { // s, w
			if (rand() % 2) set_move(0, 1);
			else set_move(-1, 0);
		}
		else { // ne, n, e, se, nw
			if (rand() % 2) set_move(1, -1);
			else if (rand() % 2) set_move(0, -1);
			else if (rand() % 2) set_move(1, 0);
			else if (rand() % 2) set_move(1, 1);
			else set_move(-1, -1);
		}
	}
	else if (direction == "w") {
		if (rand() % 100 < percent) { // s, n
			if (rand() % 2) set_move(0, 1);
			else set_move(0, -1);
		}
		else { // ne, sw, e, se, nw
			if (rand() % 2) set_move(1, -1);
			else if (rand() % 2) set_move(-1, 1);
			else if (rand() % 2) set_move(1, 0);
			else if (rand() % 2) set_move(1, 1);
			else set_move(-1, -1);
		}
	}
	else if (direction == "nw") {
		if (rand() % 100 < percent) { // w, n
			if (rand() % 2) set_move(-1, 0);
			else set_move(0, -1);
		}
		else { // ne, sw, e, se, s
			if (rand() % 2) set_move(1, -1);
			else if (rand() % 2) set_move(-1, 1);
			else if (rand() % 2) set_move(1, 0);
			else if (rand() % 2) set_move(1, 1);
			else set_move(0, 1);
		}
	}
	move.first *= magnitude;
	move.second *= magnitude;
	return move;
}

/*
std::pair<int, int> Pathfinder::unstuck()
{
	std::pair<int, int> next(0, 0);
	Cell *c = path;
	if (c == NULL || c->parent == NULL || c->parent->parent == NULL) return next;
	next.first = (c->parent->parent->x > c->parent->x ? 1 : (c->parent->parent->x < c->parent->x ? -1 : 0));
	next.second = (c->parent->parent->y > c->parent->y ? 1 : (c->parent->parent->y < c->parent->y ? -1 : 0));
	return next;
}
*/
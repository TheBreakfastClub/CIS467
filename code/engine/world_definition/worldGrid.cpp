#include "worldGrid.h"
#include <iostream>
#include <string>


WorldGrid::WorldGrid() {}

WorldGrid::~WorldGrid()
{
	//delete [] grid;
	//delete [] wall_grid;
}

Cell WorldGrid::hero_cell() { return grid[h_y * width + h_x]; }

int WorldGrid::convert_coordinate(int x) { return x / hres_div; }

void WorldGrid::init(Image *map, Hero *hero, std::vector<Enemy*> *enemies, int hres_div)
{
	// set the grid's size
	width = map->w;
	height = map->h;
	grid.resize(map->w * map->h);
	wall_grid.resize(map->w * map->h);

	//pix_bet_cell = (width * hres_div) / 

	// set references 
	this->hero = hero;
	this->enemies = enemies;
	this->hres_div = hres_div;
	this->map = map;
}

// we set the grid from the lowest-res map for the smallest search space possible.
// this easily gets us the walls from that low-res map, but what about the hero & other enemies?
// if we take the division factor (what high-res width & height was divided by for the low-res) 
// from the high-res map (which is what x & y coordinates from the hero, enemies and items comes from), 
// we can map x & y coords from hero/enemies to low-res grid locations.
void WorldGrid::build_grid()
{
	// first copy wall_grid over to grid
	std::copy(wall_grid.begin(), wall_grid.end(), grid.begin());

	// set hero & ememies
	h_x = hero->x / hres_div;
	h_y = hero->y / hres_div;
	int hero_index = h_y * width + h_x;
	grid[hero_index].type = Celltype::HERO;
	grid[hero_index].open = false;

	int enemy_index;
	for (Enemy *e : *enemies) {
		enemy_index = (e->y / hres_div) * width + (e->x / hres_div);
		grid[enemy_index].type = Celltype::ENEMY;
		grid[enemy_index].id = e->id;
		//std::cout << "Enemy added. ID: " << std::to_string(e->id) << std::endl;
	}

	/*
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			switch (grid[y*width+x].type) {
				case Celltype::WALL:
					std::cout << "W "; break;
				case Celltype::ENEMY:
					std::cout << grid[y*width+x].id << (grid[y*width+x].id < 10 ? " " : ""); break;
				case Celltype::HERO:
					std::cout << "H "; break;
				default:
					std::cout << "  ";
			}
		}
		std::cout << std::endl;
	}
	*/
	
}

// Sets where "walls" (obstructions in the map) are located in the wall_grid. Only needs to be done once.
void WorldGrid::build_wall_grid() 
{
	// initialize all Cells here, but only setting types of wall and ground
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			int index = y*width + x;
			Uint32 alpha = map->pixels[index] >> 24;
			if (alpha > 60) // wild guess on the alpha number here
				wall_grid[index].type = Celltype::WALL;
			else
				wall_grid[index].type = Celltype::GROUND;
			wall_grid[index].x = x;
			wall_grid[index].y = y;
			wall_grid[index].g_val = 0;
			wall_grid[index].f_val = 0;
			wall_grid[index].open = false;
			wall_grid[index].parent = NULL;
		}
	}
}

void WorldGrid::build_wall_grid_conservative()
{
	auto surround_with_walls = [this](int x, int y) {
		for (int x_inc = -1; x_inc < 2; x_inc++) {
			for (int y_inc = -1; y_inc < 2; y_inc++) {
				if (x_inc == 0 && y_inc == 0) continue;
				int new_x = x + x_inc, new_y = y + y_inc;
				if (new_x >= 0 && new_x < this->width && new_y >= 0 && new_y < this->height) {
					int index = new_y * this->width + new_x;
					this->wall_grid[index].type = Celltype::WALL;
				}
			}
		}
	};

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			int index = y * width + x;
			Uint32 alpha = map->pixels[index] >> 24;
			if (alpha > 60) {
				wall_grid[index].type = Celltype::WALL;
				
				// also make surrounding cells walls
				surround_with_walls(x, y);
			}
			else
				wall_grid[index].type = Celltype::GROUND;
			wall_grid[index].x = x;
			wall_grid[index].y = y;
			wall_grid[index].g_val = 0;
			wall_grid[index].f_val = 0;
			wall_grid[index].open = false;
			wall_grid[index].parent = NULL;
		}
	}
}

#pragma once

#include <utility>
#include <string>

class Tile {

	private:
		std::pair<int, int> xy;
		//Entity* entity;

	public:
		Tile(int x, int y);
		//void set_entity(Entity &e);
		std::string str(); // for debugging purposes
		bool blocking; // ie, whether or not the player can pass through this location
					   // default to false

};

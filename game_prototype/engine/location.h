#ifndef LOCATION_H
    #define LOCATION_H

#include <utility>
#include <string>

class Location {

	private:
		std::pair<int, int> xy;
		//Entity *entity;

	public:
		Location(int x, int y);
		//void set_entity(Entity &e);
		std::string str(); // for debugging purposes
		bool blocking; // ie, whether or not the player can pass through this location
					   // default to false

};

#endif
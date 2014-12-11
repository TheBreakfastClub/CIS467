#include "autoSentry.h"
#include "gameWorld.h"
#include <cstdlib> // just for exit() for testing


AutoSentry::AutoSentry(int x, int y, GameWorld *world, bool solid, bool pushable,
  bool pushes, int speed, int touchDamage, int crushDamage) : 
  Enemy(x, y, world, solid, pushable, pushes, speed, touchDamage, crushDamage), 
  pathfinder(id), moves(0), active(false) {}
AutoSentry::~AutoSentry() {}

void AutoSentry::action()
{
	auto direction = [](int x_mov, int y_mov) {
		if (x_mov == 1 && y_mov == 1) return "se";
		if (x_mov == 1 && y_mov == 0) return "e";
		if (x_mov == 1 && y_mov == -1) return "ne";
		if (x_mov == 0 && y_mov == -1) return "n";
		if (x_mov == -1 && y_mov == -1) return "nw";
		if (x_mov == -1 && y_mov == 0) return "w";
		if (x_mov == -1 && y_mov == 1) return "sw";
		if (x_mov == 0 && y_mov == 1) return "s";
		else return "";
	};
	
	// determine how far away we are from the hero
//   float a = x - world->hero->x;
//   float b = y - world->hero->y;
// 	float dist = sqrt(a*a + b*b);
    // let's speed this up...
    long a = x - world->hero->x;
    long b = y - world->hero->y;
    long d2 = a*a + b*b;

	// move in for the kill if Hero is close enough
	if (active || d2 <= 40000l) { //dist <= 200.0f) {
		if (d2 >= 250000l) active = false; //dist >= 500.0f) active = false; // even after AS detected the Hero, Hero can still escape its detection
		else active = true;

		// rebuild the path to the Hero sometimes
		if (moves % 20 == 0) {
			pathfinder.grid->build_grid();
			pathfinder.find_hero(x, y);
		}

		// Get next move from pathfinding alrogithm
		std::pair<int, int> next = pathfinder.next_move();
		int x_inc = next.first * speed, y_inc = next.second * speed;

		bool stuck = false;
		int percent = 100;
		int magnitude = 1;
		int i = 0;
		do {
			//std::cout << "Enemy " << std::to_string(id) << " next move: " << std::to_string(x_inc) << ", " << std::to_string(y_inc) << std::endl;

            // Try to move
//             pair<bool,bool> results = move(hero, map, res, x_inc, y_inc);
//             stuck = !(results.second || results.first);
            stuck = !move(x_inc, y_inc);
            // Try to get unstuck, if you are stuck
            if (stuck) {
			    
                // check for collision before updating position
				std::pair<int, int> u_move = pathfinder.unstuck(direction(next.first, next.second), x, y, percent, magnitude);
				if (u_move.first == 0 && u_move.second == 0) {
					//std::cout << "Nowhere to go...\n";
					break;
				}
				x_inc = u_move.first * speed;
				y_inc = u_move.second * speed;
			}
			percent -= 5;
			if (i % 3 == 0) magnitude++;
			i++;

		} while (stuck && percent >= 0);

		moves++;
	}
}

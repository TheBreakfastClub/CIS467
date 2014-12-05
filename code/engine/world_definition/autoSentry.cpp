#include "autoSentry.h"
#include <cstdlib> // just for exit() for testing


AutoSentry::AutoSentry(int hp, int speed, int damage, int x, int y, bool inv) 
 : Enemy(hp, speed, damage, x, y, inv), pathfinder(id), moves(0), active(false) {}

AutoSentry::AutoSentry(Image *charImgH, Image *charImgM, Image *charImgL, int hp, int speed, int damage, int x, int y, bool inv) 
 : Enemy(charImgH, charImgM, charImgL, hp, speed, damage, x, y, inv), pathfinder(id), moves(0), active(false) {}

void AutoSentry::action(Hero &hero, std::vector<Enemy*> &enemies, Image *map, Resolution res) // TODO: collision with other enemies
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
	float a = abs(x - hero.x);
	float b = abs(y - hero.y);
	float dist = sqrt(a*a + b*b);

	// move in for the kill if Hero is close enough
	if (active || dist <= 200.0f) {
		if (dist >= 500.0f) active = false; // even after AS detected the Hero, Hero can still escape its detection
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
            pair<bool,bool> results = move(hero, map, res, x_inc, y_inc);
            stuck = !(results.second || results.first);

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

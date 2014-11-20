#include "enemies.h"
#include <cstdlib> // just for exit() for testing

AutoSentry::AutoSentry(int hp, int speed, int damage, int x, int y, bool inv, Image *char_img)
 : Enemy(hp, speed, damage, x, y, inv, char_img), pathfinder(id), moves(0), active(false)
{
	spriteImage = Gfx::loadImage("resources/enemy.png");
}

void AutoSentry::action(Hero &hero, std::vector<Enemy*> &enemies, Image *map) // TODO: collision with other enemies
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

			// check for collision before updating position
			if (hero.spriteImage->collision(spriteImage, hero.x - x + x_inc, hero.y - y + y_inc)) {
				if (!hero.hit) {
					hero.hitPoints -= attackDmg;
					hero.hit = true;
					std::cout << "Hero HP: " << std::to_string(hero.hitPoints) << std::endl;
				}
				stuck = false;
			}
			else if (!map->collision(spriteImage, x + x_inc, y + y_inc)) {
				x += x_inc;
				y += y_inc;
				stuck = false;
			}
			else { // get unstuck!
				stuck = true;
				std::pair<int, int> u_move = pathfinder.unstuck(direction(next.first, next.second), x, y, percent, magnitude);
				if (u_move.first == 0 && u_move.second == 0) {
					std::cout << "Nowhere to go...\n";
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
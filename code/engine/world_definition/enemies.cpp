#include "enemies.h"
#include <cstdlib> // just for exit() for testing

AutoSentry::AutoSentry(int hp, int speed, int damage, int x, int y, bool inv, Image *char_img)
 : Enemy(hp, speed, damage, x, y, inv, char_img), pathfinder(id), moves(0)
{
	spriteImage = Gfx::loadImage("resources/enemy.png");
}

void AutoSentry::action(Hero &hero, std::vector<Enemy*> &enemies, Image *map) // TODO: collision with other enemies
{
	// determine how far away we are from the hero
	float a = abs(x - hero.x);
	float b = abs(y - hero.y);
	float dist = sqrt(a*a + b*b);
	//std::cout << "distance from hero: " << std::to_string(c) << std::endl;

	// move in for the kill if Hero is close enough
	if (dist <= 200.0f) {
		// rebuild the path to the Hero sometimes
		if (moves % 10 == 0) {
			pathfinder.grid->build_grid();
			std::cout << "BEGIN PATHFINDING\n";
			pathfinder.find_hero(x, y);
			std::cout << "END PATHFINDING\n";
			//exit(1);
		}

		//pathfinder.path_to_hero(x, y);
		std::pair<int, int> next = pathfinder.next_move();
		int x_inc = next.first * speed, y_inc = next.second * speed;
		//int x_inc = 0, y_inc = 0;
		/*
		if (x_inc == 0 && y_inc == 0) {
			if (x > hero.x) x_inc = -speed;
			else if (x < hero.x) x_inc = speed;
			if (y > hero.y) y_inc = -speed;
			else if (y < hero.y) y_inc = speed;
		}
		*/
		//if (!(x_inc == 0 && y_inc == 0)) pathfinder.print_path_to_hero();
		//else continue;

		// check for collision before updating position
		if (!hero.hit && hero.spriteImage->collision(spriteImage, hero.x - x + x_inc, hero.y - y + y_inc)) {
			hero.hitPoints -= attackDmg;
			hero.hit = true;
			std::cout << "Hero HP: " << std::to_string(hero.hitPoints) << std::endl;
		}
		else if (true || !map->collision(spriteImage, x + x_inc, y + y_inc)) {
			x += x_inc;
			y += y_inc;
		}

		moves++;
	}
}
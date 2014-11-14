#include "enemy.h"


int Enemy::count = 1;

Enemy::Enemy(int hp, int speed, int damage, int x, int y, bool inv, Image *char_img) 
 : Character(hp, speed, damage, x, y, inv, char_img) { id = count++; }
 
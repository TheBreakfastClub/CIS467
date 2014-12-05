#include "enemy.h"
#include "leftRightEnemy.h"
//#include <stdlib.h>
#include <cmath>
#include <iostream>
#include <string>
#include "../render/gfx.h"


    // int hp, int speed, int damage, int x=0, int y=0, bool inv=false

    // Image *charImgH, Image *charImgM, Image *charImgL, int hp, int speed, int damage, int x=0, int y=0, bool inv=false


    // int hp, int speed, int damage, int x=0, int y=0, bool inv=false

    // Image *charImgH, Image *charImgM, Image *charImgL, int hp, int speed, int damage, int x=0, int y=0, bool inv=false



LeftRightEnemy::LeftRightEnemy(int hp, int speed, int damage, int x, int y, bool inv, int dist, int tme)
 : Enemy(hp, speed, damage, x, y, inv)
{
    // spriteImage = Gfx::loadImage("resources/updown.png");
    counter = 0;
    direction = -1;
    x_top = x + dist;
    x_bottom = x - dist;
    pushes = true;
    // cerr << "y top: " << y_top << "\ny bottom: " << y_bottom;
}

// dist = 5
// org = 10   
    // top = 15
    // bottom = 5
// dir = -1
    // (5 + -1) + 10

    //Scenarios
    // moving up or downaway from origin
        // incamenting y
        // checking for distence
    // at distence
        // change direction
        // incramenting y
    // moving towards origin
        // incramenting y
        // checking for origin
    // at origin
        // incramenting y


void LeftRightEnemy::action(Hero &hero, std::vector<Enemy*> &enemies, Image *map, Resolution res)
{
    // in the process of moving
    if (x < x_top && x > x_bottom) {

        // Move in same direction, unless you hit a wall, then change direction
        if (!map->collision(getSpriteImage(res), x + speed * direction, y)) {
            //x += x_inc;
            move(hero, map, res, speed * direction, 0);
        } else {
            // cerr << "collide LR";
            direction = direction * -1;
            move(hero, map, res, speed * direction, 0);
        }
    } 
    // time to turn around
    else {
        direction = direction * -1;
        move(hero, map, res, speed * direction, 0);
    }



    // // determine how far away we are from the hero
    // float a = abs(x - hero.x);
    // float b = abs(y - hero.y);
    // float dist = sqrt(a*a + b*b);
    // //std::cout << "distance from hero: " << std::to_string(c) << std::endl;

    // // move in for the kill if Hero is close enough
    // if (dist <= 200.0f) {
    //     int x_inc = 0, y_inc = 0;
    //     if (x > hero.x) x_inc = -speed;
    //     else if (x < hero.x) x_inc = speed;
    //     if (y > hero.y) y_inc = -speed;
    //     else if (y < hero.y) y_inc = speed;

    //     // check for collision before updating position
    //     if (!hero.hit && hero.spriteImage->collision(spriteImage, hero.x - x + x_inc, hero.y - y + y_inc)) {
    //         hero.hitPoints -= attackDmg;
    //         hero.hit = true;
    //         std::cout << "Hero HP: " << std::to_string(hero.hitPoints) << std::endl;
    //     }
    //     else if (!map->collision(spriteImage, x + x_inc, y + y_inc)) {
    //         x += x_inc;
    //         y += y_inc;
    //     }
    // }
}

#include "enemy.h"
#include "upDownEnemy.h"
//#include <stdlib.h>
#include <cmath>
#include <iostream>
#include <string>
#include "../render/gfx.h"
#include "../render/collision.h"




UpDownEnemy::UpDownEnemy(int hp, int speed, int damage, int x, int y, bool inv, int dist, int tme)
 : Enemy(hp, speed, damage, x, y, inv)
{
    // spriteImage = Gfx::loadImage("resources/updown.png");
    counter = 0;
    direction = -1;
    y_top = y + dist;
    y_bottom = y - dist;
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


void UpDownEnemy::action(Hero &hero, std::vector<Enemy*> &enemies, Image *map, Resolution res, float s)
{
    
    // in the process of moving
    if (y < y_top && y > y_bottom) {
        // counter ++;
        // int y_inc = speed * direction;
        if(!scollision(getSpriteImage(res), x, y + speed*direction, scale[res], map, 0, 0, s)) {
            // y += y_inc;
            move(hero, map, res, 0, speed * direction, s);
        } else {
            direction = direction * -1;
            // y += speed * direction;
            move(hero, map, res, 0, speed * direction, s);
        }
        // cerr << "y: " << y << "\n";
    } 
    // time to turn around
    else {
        direction = direction * -1;
        // y += speed * direction;
        move(hero, map, res, 0, speed * direction, s);
        // cerr << "change direction\n";
    }


    if(!hero.hit && scollision(hero.getSpriteImage(res), hero.x, hero.y, hero.scale[res],
      getSpriteImage(res), x, y, scale[res])) {
            // hero.hitPoints -= attackDmg;
            // hero.hit = true;
            // std::cout << "Hero HP: " << std::to_string(hero.hitPoints) << std::endl;
            // cerr << "hit by updown";
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

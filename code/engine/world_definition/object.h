#pragma once

#include "../render/image.h"
#include "../../util/pixUtil.h"
#include "../render/blend.h"
#include "../render/gfx.h"
#include "resolution.h"
#include "sprite.h"
#include <utility>
class GameWorld;

class Object {
  protected:
    Sprite *sprite;

  public:
    Object();
    Object(int x, int y, GameWorld *world, bool solid = true, bool pushable = false);
    ~Object();
    bool loadImage(const char *fileName, int medCut = 8, int lowCut = 16, bool rotates = false);
  
    GameWorld *world;
    int x;
    int y;
    int angle;
    bool solid;
    bool pushable;

    Image* getImage();
    Image* getImage(int angle);
    float getScale();
    int getAngle(int dx, int dy);
    bool fits(int x, int y);
    bool fits(int x, int y, int angle);
    bool fitsMap(int x, int y);
    bool fitsMap(int x, int y, int angle);
    bool moveTo(int x, int y);
    bool moveTo(int x, int y, int angle);
    bool move(int dx, int dy);
    bool push(int dx, int dy);
    bool push(int dx, int dy, int r);
    bool overlaps(Object *other);
    bool overlaps(Object *other, int x, int y);
    bool overlaps(Object *other, int x, int y, int angle);
    void draw(Image *screen, int panX, int panY);
    void draw(Image *screen, int panX, int panY, Sprite *sprite);
    bool turn(int dx, int dy);
    bool turnMove(int dx, int dy);
    bool within(float r, Object *o);
};

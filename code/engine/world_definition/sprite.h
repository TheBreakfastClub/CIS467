#pragma once

#include "../render/image.h"
#include "../../util/pixUtil.h"
#include "../render/blend.h"
#include "../render/gfx.h"
#include "resolution.h"
#include <utility>

class Sprite {
  private:
    Image **images;

  public:
    Sprite(const char *fileName, pixAlgo pixelator = blend_average,
      int medCut = 8, int lowCut = 16, bool rotates = false);
    ~Sprite();
  
    float scale[3];
    int angles;

    Image* getImage(int resolution);
    Image* getImage(int resolution, int angle);
};

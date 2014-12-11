#include "sprite.h"
#include <iostream>

Sprite::Sprite(Image *image, pixAlgo pixelator,
  int medCut, int lowCut, bool rotates)
{
  angles = rotates ? 8 : 1;
  images = new Image*[angles*3];
  scale[0] = lowCut;
  scale[1] = medCut;
  scale[2] = 1;

  if(rotates) {
    int rwidth = max(image->w, image->h)*2;
    for(int a = 0; a < 8; a++) {
      images[a*3 + 2] = new Image(rwidth, rwidth);
      images[a*3 + 2]->clear();
      images[a*3 + 2]->abrsblit(image, (rwidth-1.0)/2.0, (rwidth-1.0)/2.0, a*45.0, 1.0);
    }
  }
  else {
    images[2] = new Image(image->w, image->h);
    images[2]->blit(image, 0, 0);
  }
  
  // downsample image[s]
  for(int a = 0; a < angles; a++) {
    Image *i = images[a*3 + 2];
    if(pixelator) {
      images[a*3    ] = downsample(i, i->w/lowCut, i->h/lowCut, pixelator);
      images[a*3 + 1] = downsample(i, i->w/medCut, i->h/medCut, pixelator);
    }
    else images[a*3] = images[a*3 + 1] = i;
  }
}

Sprite::~Sprite() {
  int inc = (images && images[1] == images[2]) ? 3 : 1; // don't double delete
  for(int i = 0; i < angles*3; i+=inc) delete images[i]; 
  delete[] images;
}

Image* Sprite::getImage(int resolution, int angle) {
  return images[angle*3 + resolution];
}

Image* Sprite::getImage(int resolution) {
  return images[resolution];
}

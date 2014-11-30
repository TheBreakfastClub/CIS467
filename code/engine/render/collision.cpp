#include "collision.h"
#include "util.h"

bool collision(Image *image1, int x1, int y1, Image *image2, int x2, int y2)
{
  return image1->collision(image2, x2 - x1, y2 - y1);
}

int overlap(Image *image1, int x1, int y1, Image *image2, int x2, int y2)
{
  return image1->overlap(image2, x2 - x1, y2 - y1);
}

// collision with scaling, operating in screen space
//
// this could be optimized for cases where scales are larger than 2 with dynamic 
// antialiasing, operating in the space of one of the images...
// but aint nobody got time for that!

bool scollision(Image *image1, int x1, int y1, float scale1, Image *image2, int x2, int y2, float scale2)
{
  // (s,t) are 16.16 fixed point coordinates in image1's space
  // (u,v) are 16.16 fixed point coordinates in image2's space
  
  if(scale1 <= 0 || scale2 <= 0) return false;
  if(scale1 == 1 && scale2 == 1) return collision(image1, x1, y1, image2, x2, y2);
  
  int ds = 65536/scale1;
  int dt = 65536/scale1;
  
  int du = 65536/scale2;
  int dv = 65536/scale2;
  
  int s1 = max(0, (x2 - x1)*ds);
  int s2 = min(image1->w << 16, (int)(x2 + scale2*image2->w - x1)*ds);
  int t1 = max(0, (y2 - y1)*dt);
  int t2 = min(image1->h << 16, (int)(y2 + scale2*image2->h - y1)*dt);
  
  int u1 = max(0, (x1 - x2)*du);
  int v1 = max(0, (y1 - y2)*dv);
  
  u32 *i1, *i2; // row pointers for image1, image2
  
  int u, v = v1;
  for(int t = t1; t < t2; t+= dt) {
    i1 = image1->pixels + (t >> 16)*image1->w;
    i2 = image2->pixels + (v >> 16)*image2->w;
    u = u1;
    for(int s = s1; s < s2; s+= ds) {
      if(i1[s >> 16] & i2[u >> 16] & 0x80000000) return true;
      u += du;
    }
    v += dv;
  }
  
  return false;
}

// overlap with scaling, operating in screen space
//
// this could be optimized for cases where scales are larger than 2 with dynamic 
// antialiasing, operating in the space of one of the images...
// but aint nobody got time for that!

int soverlap(Image *image1, int x1, int y1, float scale1, Image *image2, int x2, int y2, float scale2)
{
  // (s,t) are 16.16 fixed point coordinates in image1's space
  // (u,v) are 16.16 fixed point coordinates in image2's space
  
  if(scale1 <= 0 || scale2 <= 0) return false;
  if(scale1 == 1 && scale2 == 1) return overlap(image1, x1, y1, image2, x2, y2);
  
  int overlap = 0;
  
  int ds = 65536/scale1;
  int dt = 65536/scale1;
  
  int du = 65536/scale2;
  int dv = 65536/scale2;
  
  int s1 = max(0, (x2 - x1)*ds);
  int s2 = min(image1->w << 16, (int)(x2 + scale2*image2->w - x1)*ds);
  int t1 = max(0, (y2 - y1)*dt);
  int t2 = min(image1->h << 16, (int)(y2 + scale2*image2->h - y1)*dt);
  
  int u1 = max(0, (x1 - x2)*du);
  int v1 = max(0, (y1 - y2)*dv);
  
  u32 *i1, *i2; // row pointers for image1, image2
  
  int u, v = v1;
  for(int t = t1; t < t2; t+= dt) {
    i1 = image1->pixels + (t >> 16)*image1->w;
    i2 = image2->pixels + (v >> 16)*image2->w;
    u = u1;
    for(int s = s1; s < s2; s+= ds) {
      if(i1[s >> 16] & i2[u >> 16] & 0x80000000) overlap++;
      u += du;
    }
    v += dv;
  }
  
  return overlap;
}

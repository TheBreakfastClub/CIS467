#pragma once
#include <string>
#include "types.h"

class Image {
	private:
	bool dealloc;
	void init(int, int, void*, bool);
	
	public:
	int w,h;
	u32 *pixels;
	float cx, cy;
	
	Image();
	Image(int, int);
	Image(int, int, void*);
	~Image();
	
	void resize(int, int);
	void clear();
	void clear(u32);
  u32 bilinear(float, float);
  static u32 blend(u32, u32);
  bool _collision(Image*, int, int);
  bool collision(Image*, int, int);
  bool rcollision(Image*, int, int, float);
  bool scollision(Image*, int, int, float);
  bool rscollision(Image*, int, int, float, float);
  int _overlap(Image*, int, int);
  int overlap(Image*, int, int);
  int roverlap(Image*, int, int, float);
  int soverlap(Image*, int, int, float);
  int rsoverlap(Image*, int, int, float, float);
	void _blit(Image*, int, int);
	void _ablit(Image*, int, int);	
  void blit(Image*, int, int);
	void ablit(Image*, int, int);
	void scaleblit(Image*);
	void ascaleblit(Image*);	
	void asblit(Image*, int, int, float);
	void sblit(Image*, int, int, float);
	void arblit(Image*, float, float, float);
	void arsblit(Image*, float, float, float, float);
	void abrsblit(Image*, float, float, float, float);
	void putchar(unsigned char, int, int, u32);
	void puttext(const char*, int, int, u32);
	void puttext(std::string, int, int, u32);
};

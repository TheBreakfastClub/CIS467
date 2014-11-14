#include <cmath>
#include "font.h"
#include "types.h"
#include "util.h"
#include "image.h"

Image::Image() {
	init(0,0,0,false);
}

Image::Image(int width, int height) {
	init(width, height, new u32[width*height], true);
}

Image::Image(int width, int height, void *buffer) {
	init(width, height, buffer, false);
}		
	
Image::~Image() {
	if(dealloc) delete[] pixels;
}

void Image::init(int width, int height, void *pix, bool d) {
	w = width;
	h = height;
	pixels = (u32*)pix;
	dealloc = d;
	cx = (w-1)/2;
	cy = (h-1)/2;
}

void Image::resize(int width, int height) {
	if(width == w && height == h) return;
	if(dealloc) delete[] pixels;
	init(width, height, new u32[width*height], true);
}

void Image::clear() {
	clear(0);
}

void Image::clear(u32 color) {
	for(int i = 0; i < w*h; i++) pixels[i] = color;
}

// super fast premultiplied alpha
u32 Image::blend(u32 src, u32 dst) {
  u32 rb, ag, invalpha;
	invalpha = 256 - (src >> 24) - (src >> 31);
	ag = (src & 0xff00ff00) + ((invalpha*((dst >> 8) & 0xff00ff)) & 0xff00ff00);
	rb = (src & 0xff00ff) + (((invalpha*(dst & 0xff00ff)) >> 8) & 0xff00ff);
//     return ag | rb;
  return rb | (ag & 0xff00) | (src & 0xff000000); // just for now, we need the source's unmodified alpha...
}

// no clipping
void Image::_blit(Image *src, int x, int y) {
  int a, b, i=0;
  for(b = y*w;b < (y+src->h)*w; b+=w) 
		for(a = b+x; a < b+x+src->w; a++) 
			pixels[a] = src->pixels[i++];
}	

void Image::blit(Image *src, int x, int y) {
	int x1 = max(x, 0);
	int x2 = min(x + src->w, w);
	int y1 = max(y, 0);
	int y2 = min(y + src->h, h);
	
	for(int b=y1; b < y2; b++) {
		int i = (b-y)*src->w + x1 - x;
		for(int a = b*w + x1; a < b*w + x2; a++)
			pixels[a] = src->pixels[i++];
	}
}

// no clipping
void Image::_ablit(Image *src, int x, int y) {
  int a, b, i=0;
  for(b = y*w;b < (y+src->h)*w; b+=w) 
		for(a = b+x;a < b+x+src->w; a++)
			pixels[a] = blend(src->pixels[i++], pixels[a]);
}  

void Image::ablit(Image *src, int x, int y) {
	int x1 = max(x, 0);
	int x2 = min(x + src->w, w);
	int y1 = max(y, 0);
	int y2 = min(y + src->h, h);
	
	for(int b=y1; b < y2; b++) {
		int i = (b-y)*src->w + x1 - x;
		for(int a = b*w + x1; a < b*w + x2; a++)
			pixels[a] = blend(src->pixels[i++], pixels[a]);
	}
}

bool Image::collision(Image *src, int x, int y) {
	int a, b, i=0;
  for(b = y*w;b < (y+src->h)*w; b+=w) 
		for(a = b+x;a < b+x+src->w; a++) 
 			if(pixels[a] & src->pixels[i++] & 0x80000000) return true;
	return false;
}

int Image::overlap(Image *src, int x, int y) {
	int a, b, i=0, overlap=0;
  for(b = y*w;b < (y+src->h)*w; b+=w) 
		for(a = b+x;a < b+x+src->w; a++) 
 			if(pixels[a] & src->pixels[i++] & 0x80000000) overlap++;
	return overlap;
}

bool Image::scollision(Image *src, int x, int y, float scale)
{
	if(scale <= 0) return false;
	
	int du = 65536/scale;
	int dv = 65536/scale;

	int x1 = max(x, 0);
	int y1 = max(y, 0);

	int u1 = max(0, -x*du);
	int v1 = max(0, -y*dv);		
	int u2 = min(src->w << 16, (w-x) * du);
	int v2 = min(src->h << 16, (h-y) * dv);
	
	int j;
	y = y1;
	u32 *o;
	for(int v = v1; v < v2; v+= dv) {
		j = (v >> 16)*src->w;
		o = pixels + y*w + x1;
		for(int u = u1; u < u2; u+=du) {
			if(*o & src->pixels[j + (u >> 16)] & 0x80000000) return true;
			o++;
		}
		y++;
	}
	return false;
}


int Image::soverlap(Image *src, int x, int y, float scale)
{
	if(scale <= 0) return false;
	
	int du = 65536/scale;
	int dv = 65536/scale;

	int x1 = max(x, 0);
	int y1 = max(y, 0);

	int u1 = max(0, -x*du);
	int v1 = max(0, -y*dv);		
	int u2 = min(src->w << 16, (w-x) * du);
	int v2 = min(src->h << 16, (h-y) * dv);
	
	int overlap = 0;	
	int j;
	y = y1;
	u32 *o;
	for(int v = v1; v < v2; v+= dv) {
		j = (v >> 16)*src->w;
		o = pixels + y*w + x1;
		for(int u = u1; u < u2; u+=du) {
			if(*o & src->pixels[j + (u >> 16)] & 0x80000000) overlap++;
			o++;
		}
		y++;
	}
	return overlap;
}

void Image::scaleblit(Image *src)
{
	u32 *i = pixels;
	int du = (src->w << 16)/w;
	int dv = (src->h << 16)/h;
	int u, v = 0;
	int j;
	for(int y = 0; y < h; y++) {
		j = (v >> 16)*src->w;
		u = 0;
		for(int x = 0; x < w; x++) {
			*i++ = src->pixels[j + (u >> 16)];
			u += du;
		}
		v += dv;
	}
}

void Image::ascaleblit(Image *src)
{
	u32 *i = pixels;
	int du = (src->w << 16)/w;
	int dv = (src->h << 16)/h;
	int u, v = 0;
	int j;
	for(int y = 0; y < h; y++) {
		j = (v >> 16)*src->w;
		u = 0;
		for(int x = 0; x < w; x++) {
			*i = blend(src->pixels[j + (u >> 16)], *i);
			i++;
			u += du;
		}
		v += dv;
	}

}

void Image::asblit(Image *src, int x, int y, float scale)
{
	if(scale <= 0) return;
	
	int du = 65536/scale;
	int dv = 65536/scale;

	int x1 = max(x, 0);
	int y1 = max(y, 0);

	int u1 = max(0, -x*du);
	int v1 = max(0, -y*dv);		
	int u2 = min(src->w << 16, (w-x) * du);
	int v2 = min(src->h << 16, (h-y) * dv);
	
	int j;
	y = y1;
	u32 *o;
	for(int v = v1; v < v2; v+= dv) {
		j = (v >> 16)*src->w;
		o = pixels + y*w + x1;
		for(int u = u1; u < u2; u+=du) {
			*o = blend(src->pixels[j + (u >> 16)], *o);
			o++;
		}
		y++;
	}
}

void Image::arblit(Image *src, float x, float y, float angle)
{
	arsblit(src, x, y, angle, 1.0);
}

void Image::arsblit(Image *src, float X, float Y, float angle, float scale)
{
	angle /= M_PI*180.0;
	float S = sin(angle);
	float C = cos(angle);
	int a,b,c,d,e,f;
	
	// reverse transformation matrix (X,Y)->(U,V)
	a = 0x10000 * C/scale;
	b = 0x10000 * -S/scale;
	c = 0x10000 * ((Y*S - X*C )/scale + src->cx);
	d = 0x10000 * S/scale;
	e = 0x10000 * C/scale;
	f = 0x10000 * ((-X*S - Y*C)/scale + src->cy);

	// lower right, rotated
	int vx1 = (src->w - src->cx)*C*scale + (src->h - src->cy)*S*scale + X;
	int vy1 = (src->w - src->cx)*-S*scale + (src->h - src->cy)*C*scale + Y;
	// upper right, rotated
	int vx2 = (src->w - src->cx)*C*scale + (-src->cy)*S*scale + X;
	int vy2 = (src->w - src->cx)*-S*scale + (-src->cy)*C*scale + Y;
	// upper left, rotated
	int vx3 = (-src->cx)*C*scale + (-src->cy)*S*scale + X;
	int vy3 = (-src->cx)*-S*scale + (-src->cy)*C*scale + Y;
	// lower left, rotated
	int vx4 = (-src->cx)*C*scale + (src->h - src->cy)*S*scale + X;
	int vy4 = (-src->cx)*-S*scale + (src->h - src->cy)*C*scale + Y;
	
	// generate screen aligned bounding box
	int x1 = max(0, min(vx1,vx2,vx3,vx4));
	int x2 = min(w, max(vx1,vx2,vx3,vx4)+1);
	int y1 = max(0, min(vy1,vy2,vy3,vy4));
	int y2 = min(h, max(vy1,vy2,vy3,vy4)+1);
	
	int x,y;
	int u,v;
	u32 *i = pixels;
	int W = src->w << 16;
	int H = src->h << 16;

	for(y = y1; y < y2; y++) {
		u = x1*a + y*b + c;
		v = x1*d + y*e + f;
		i = pixels + y*w;
		for(x = x1; x < x2; x++) {
			if(u >= 0 && u < W && v >=0 && v < H)
				i[x] = blend(src->pixels[(v >> 16)*src->w + (u >> 16)], i[x]);
			u += a;
			v += d;
		}
	}
}

void Image::putchar(unsigned char c, int x, int y, u32 color)
{
	if(x < 0 || x > w - 8 || y < 0 || y > h - 16) return;
	int a,i,s;
	i = c << 4;
	for(int b = y*w; b < (y+16)*w; b+= w) {
		s = vga_font[i++];
		for(a = b+x; a < b+x+8; a++) {
			if(s & 0x8000) pixels[a] = color;
			else if(s & 0x80) pixels[a] = (pixels[a] & 0xfefefefe) >> 1;
			s <<= 1;
		}
	}
}

void Image::puttext(const char* text, int x, int y, u32 color)
{
	while(*text) {
		putchar(*text, x, y, color);
		x += 8;
		text++;
	}
}

void Image::puttext(std::string text, int x, int y, u32 color)
{
	for(std::string::iterator i = text.begin(); i != text.end(); ++i) {
		putchar(*i, x, y, color);
		x += 8;
	}
}

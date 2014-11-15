<<<<<<< HEAD

#include "image.h"
#include "point.h"
#include "types.h"
#include "util.h"

// The Image class is a simplified counterpart to the SDL_Surface structure.
// Pixels are always in ARGB8888 format, the pitch is always the width, and
// the clipping rectangle is always the entire image.

    
    void Image::init(int width, int height, void *pix, bool d) {
        w = width;
        h = height;
        pixels = (u32*)pix;
        dealloc = d;
        cx = (w-1)/2;
        cy = (h-1)/2;
    }
    
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
    
  // original version, doesn't preserve alpha
  u32 Image::blend_old(u32 src, u32 dst) {
    u32 r,g,b,alpha,ialpha;
    alpha=(src >> 24) + (src >> 31); // scale from [0..255] to [0..256]
    ialpha=256-alpha;
    //by multiplying primary colors in place, less shifts are needed, while maintaining sufficient numberic headroom
    r=((dst & 0xff0000)*ialpha + (src & 0xff0000)*alpha) >> 8; 
    g=((dst & 0xff00)*ialpha + (src & 0xff00)*alpha) >> 8;
    b=((dst & 0xff)*ialpha + (src & 0xff)*alpha) >> 8;
    return (r & 0xff0000)+(g & 0xff00)+b;
  }

  // super fast version postmultiplied version, doesn't preserve alpha
  u32 Image::blend2(u32 src, u32 dst) {
    u32 rb, g, rb_dst, g_dst, alpha;
        alpha=(src >> 24) + (src >> 31); // scale alpha from [0..255] to [0..256]
        
        rb_dst = dst & 0xff00ff;
        rb = (((((src & 0xff00ff) - rb_dst)*alpha) >> 8) & 0xff00ff) + rb_dst;

        g_dst = dst & 0xff00;
        g = (((((src & 0xff00) - g_dst)*alpha) >> 8) & 0xff00) + g_dst;
        
//     return rb | g;
    return rb | g | (src & 0xff000000); // just for now, we need the source's unmodified alpha...
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
    
    // no clipping yet
  bool Image::collision(Image *src, int x, int y) {
        int x1 = max(x, 0);
        int x2 = min(x + src->w, w);
        int y1 = max(y, 0);
        int y2 = min(y + src->h, h);

        for(int b=y1; b < y2; b++) {
            int i = (b-y)*src->w + x1 - x;
            for(int a = b*w + x1; a < b*w + x2; a++)
                if(pixels[a] & src->pixels[i++] & 0x80000000) return true;
        }
        return false;

  }
    
    // no clipping yet
  int Image::overlap(Image *src, int x, int y) {
        int a, b, i=0, o=0;
    for(b = y*w;b < (y+src->h)*w; b+=w) 
            for(a = b+x;a < b+x+src->w; a++) 
                if(pixels[a] & src->pixels[i++] & 0x80000000) o++;
        return o;
  }
    
    void Image::scaleblit(Image *src)
    {
//  slow version:
//      u32 *i = pixels;
//      for(int y = 0; y < h; y++) {
//          for(int x = 0; x < w; x++) {
//              *i++ = src->pixels[(y*src->h/h)*src->w + x*src->w/w];
//          }
//      }
        
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
//  slow version:
//      u32 *i = pixels;
//      for(int y = 0; y < h; y++) {
//          for(int x = 0; x < w; x++) {
//              *i++ = blend(src->pixels[(y*src->h/h)*src->w + x*src->w/w], *i);
//          }
//      }

        u32 *i = pixels;
        int du = (src->w << 16)/w;
        int dv = (src->h << 16)/h;
        int u, v = 0;
        int j;
        for(int y = 0; y < h; y++) {
            j = (v >> 16)*src->w;
            u = 0;
            for(int x = 0; x < w; x++) {
                *i++ = blend(src->pixels[j + (u >> 16)], *i);
                u += du;
            }
            v += dv;
        }

    }
    
    bool Image::point_compare(const Point& a, const Point& b) {
        if(a.y == b.y) return a.x < b.x;
        else return a.y < b.y;
    }
    
    void Image::triangle(Point a, Point b, Point c, u32 color)
    {
        Point p[3] = {a,b,c};
        int top, middle, bottom, left, right;
        sort(p, p+3, point_compare);
#ifdef WARNING      
        int ab, ac, bc; // slopes
        int x,y,x1,y1,x2,y2;
#else
        int y;
#endif
        
        top = max(0, p[0].y);
        middle = min(h, p[1].y);
        bottom = min(h, p[2].y);
        
        if( (p[1].y-p[2].y)*(p[0].x-p[2].x) - (p[1].x-p[2].x)*(p[0].y-p[2].y) < 0) {
            //top section
            for(y = top; y < middle; y++) {
                left = max(0, p[0].x + (p[1].x - p[0].x)*(y - p[0].y)/(p[1].y - p[0].y));
                right = min(w, p[0].x + (p[2].x - p[0].x)*(y - p[0].y)/(p[2].y - p[0].y));
                for(int i = left; i < right; i++) pixels[y*w + i] = color;
            }
            // bottom section
            for(y = p[1].y; y < bottom; y++) {
                left = max(0, p[1].x + (p[2].x - p[1].x)*(y - p[1].y)/(p[2].y - p[1].y));
                right = min(w, p[0].x + (p[2].x - p[0].x)*(y - p[0].y)/(p[2].y - p[0].y));
                for(int i = left; i < right; i++) pixels[y*w + i] = color;
            }
        }
        else {
            //top section
            for(y = top; y < middle; y++) {
                left = max(0, p[0].x + (p[2].x - p[0].x)*(y - p[0].y)/(p[2].y - p[0].y));
                right = min(w, p[0].x + (p[1].x - p[0].x)*(y - p[0].y)/(p[1].y - p[0].y));
                for(int i = left; i < right; i++) pixels[y*w + i] = color;
            }
            // bottom section
            for(y = p[1].y; y < bottom; y++) {
                left = max(0, p[0].x + (p[2].x - p[0].x)*(y - p[0].y)/(p[2].y - p[0].y));
                right = min(w, p[1].x + (p[2].x - p[1].x)*(y - p[1].y)/(p[2].y - p[1].y));
                for(int i = left; i < right; i++) pixels[y*w + i] = color;
            }
        }
        
    }

    // fixed point, tests full screen
    void Image::ablit(Image *src, double X, double Y, double angle, double scale)
    {
        angle /= M_PI*180.0;
        double S = sin(angle);
        double C = cos(angle);
        int a,b,c,d,e,f;
        
//      reverse transformation matrix (X,Y)->(U,V)
        a = 0x10000 * C/scale;
        b = 0x10000 * -S/scale;
        c = 0x10000 * ((Y*S - X*C )/scale + src->cx);
        d = 0x10000 * S/scale;
        e = 0x10000 * C/scale;
        f = 0x10000 * ((-X*S - Y*C)/scale + src->cy);

        int x,y;
        int u,v;
        u32 *i = pixels;
        int W = src->w << 16;
        int H = src->h << 16;
        
        for(y = 0; y < h; y++) {
            u = y*b + c;
            v = y*e + f;
            for(x = 0; x < w; x++) {
                if(u >= 0 && u < W && v >=0 && v < H)
                    *i = blend(src->pixels[(v >> 16)*src->w + (u >> 16)], *i);
                u += a;
                v += d;
                i++;
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
    
    void Image::puttext(string text, int x, int y, u32 color)
    {
        for(string::iterator i = text.begin(); i != text.end(); ++i) {
            putchar(*i, x, y, color);
            x += 8;
        }
    }

=======
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
//	return ag | rb;
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

// no clipping
bool Image::_collision(Image *src, int x, int y) {
	int a, b, i=0;
  for(b = y*w;b < (y+src->h)*w; b+=w) 
		for(a = b+x;a < b+x+src->w; a++) 
 			if(pixels[a] & src->pixels[i++] & 0x80000000) return true;
	return false;
}

// no clipping
int Image::_overlap(Image *src, int x, int y) {
	int a, b, i=0, overlap=0;
  for(b = y*w;b < (y+src->h)*w; b+=w) 
		for(a = b+x;a < b+x+src->w; a++) 
 			if(pixels[a] & src->pixels[i++] & 0x80000000) overlap++;
	return overlap;
}

bool Image::collision(Image *src, int x, int y) {
	int x1 = max(x, 0);
	int x2 = min(x + src->w, w);
	int y1 = max(y, 0);
	int y2 = min(y + src->h, h);

	for(int b=y1; b < y2; b++) {
		int i = (b-y)*src->w + x1 - x;
		for(int a = b*w + x1; a < b*w + x2; a++)
			if(pixels[a] & src->pixels[i++] & 0x80000000) return true;
	}
	return false;
}

int Image::overlap(Image *src, int x, int y) {
	int o = 0;
	int x1 = max(x, 0);
	int x2 = min(x + src->w, w);
	int y1 = max(y, 0);
	int y2 = min(y + src->h, h);

	for(int b=y1; b < y2; b++) {
		int i = (b-y)*src->w + x1 - x;
		for(int a = b*w + x1; a < b*w + x2; a++)
			if(pixels[a] & src->pixels[i++] & 0x80000000) o++;
	}
	return o;
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
>>>>>>> engine

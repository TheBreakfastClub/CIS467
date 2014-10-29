
#include "blend.h"
// #include "types.h"

u32 blend_point_sample(u32 *colors, int count)
{
    return colors[0];
}

u32 blend_average(u32 *colors, int count)
{
    int a=0, r=0, g=0, b=0;
    for(int i = 0; i < count; i++) {
        a += colors[i] >> 24;
        r += (colors[i] >> 16) & 0xff;
        g += (colors[i] >> 8) & 0xff;
        b += colors[i] & 0xff;
    }
    return (a/count << 24) + (r/count << 16) + (g/count << 8) + b/count;
}       

u32 blend_average_opaque(u32 *colors, int count)
{
    int a=0, r=0, g=0, b=0, c=0;
    for(int i = 0; i < count; i++) {
        if(colors[i] & 0xff000000) {
            a += colors[i] >> 24;
            r += (colors[i] >> 16) & 0xff;
            g += (colors[i] >> 8) & 0xff;
            b += colors[i] & 0xff;
            c++;
        }
    }
    if(c) return (a/c << 24) + (r/c << 16) + (g/c << 8) + b/c;
    else return 0;
}       

u32 blend_most_common(u32 *colors, int count)
{
  map <u32, unsigned int> counts;

    for(int i = 0; i < count; i++) {
        counts[colors[i]]++;
    }

  u32 most_used = 0;
  u32 most_used_count = 0;
  for(auto it = counts.begin(); it != counts.end(); ++it ) {
        if (it->second > most_used_count) {
            most_used = it->first;
            most_used_count = it->second;
        }
  }

    return most_used;
}

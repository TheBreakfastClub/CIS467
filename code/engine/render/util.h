#pragma once

inline int min(int a, int b) 
{	
	return a < b ? a : b; 
}

inline int max(int a, int b) 
{ 
	return a < b ? b : a; 
}

inline int min(int a, int b, int c, int d) 
{ 
	return min(min(a,b), min(c,d));
}

inline int max(int a, int b, int c, int d) 
{ 
	return max(max(a,b), max(c,d));
}

inline float min(float a, float b) 
{ 
	return a < b ? a : b; 
}

inline float max(float a, float b) 
{ 
	return a < b ? b : a; 
}

inline int clamp(int x, int lower, int upper)
{
	if(x < lower) return lower;
	if(x > upper) return upper;
	return x;
}

inline float clamp(float x, float lower, float upper)
{
	if(x < lower) return lower;
	if(x > upper) return upper;
	return x;
}

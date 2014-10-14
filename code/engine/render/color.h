#pragma once

inline int min(int a, int b) 
{	
	return a < b ? a : b; 
}

inline int max(int a, int b) 
{ 
	return a < b ? b : a; 
}

inline double min(double a, double b) 
{ 
	return a < b ? a : b; 
}

inline double max(double a, double b) 
{ 
	return a < b ? b : a; 
}

inline int clamp(int x, int lower, int upper)
{
	if(x < lower) return lower;
	if(x > upper) return upper;
	return x;
}

inline double clamp(double x, double lower, double upper)
{
	if(x < lower) return lower;
	if(x > upper) return upper;
	return x;
}

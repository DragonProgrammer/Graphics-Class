#ifndef COLOR_C
#define COLOR_C
#include <iostream>
using std::ostream;
struct color{
	int r;
	int g;
	int b;

	float r_scale;
	float g_scale;
	float b_scale;
};

ostream& operator << (ostream &os, const color &s) ;

#endif


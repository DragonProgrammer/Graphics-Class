#include "Debug.h"
#include "objects.h"
#include <vector>
#include "frame.h"
#include "globals.h"
#include <string>
#include <cmath>

using std::to_string;
using std::vector;

typedef vector<float> point;
void objects::draw_cube() {
	point v1, v2, v3, v4, v5, v6, v7, v8;
	v1 = {-1, -1, -1};
	v2 = {-1, -1, 1};
	v3 = {-1, 1, -1};
	v4 = {1, -1, -1};
	v5 = {1, 1, -1};
	v6 = {-1, 1, 1};
	v7 = {1, -1, 1};
	v8 = {1, 1, 1};

	// faces
	// v1, v2, v3, v6 i
	// v1, v2, v7, v4 i
	// v1, v4, v5, v3
	// v2, v7, v8, v6
	// v4, v7, v8, v5 i
	// v3, v6, v8, v5 i

	// edges
	// v1 - v2
	// v1 - v3
	// v1 - v4
	// v2 - v6
	// v2 - v7
	// v3 - v5
	// v3 - v6
	// v4 - v5
	// v4 - v7
	// v5 - v8
	// v6 - v8
	// v7 - v8
	float color[3];
	color[0] = .5;
	color[1] = .5;
	color[2] = .5;
//	set_active(color);
	line_pipeline(v1, 'M');
		line_pipeline(v2, 'D');
		line_pipeline(v6, 'D');
		line_pipeline(v3, 'D');
	line_pipeline(v1, 'D');

	color[0] = .25;
	color[1] = .25;
	color[2] = .25;
//	set_active(color);
	line_pipeline(v6, 'M');
	line_pipeline(v8, 'D');
	line_pipeline(v5, 'D');
	line_pipeline(v3, 'D');
	line_pipeline(v6, 'D');

	color[0] = .75;
	color[1] = .75;
	color[2] = .75;
//	set_active(color);
	line_pipeline(v5, 'M');
	line_pipeline(v4, 'D');
	line_pipeline(v7, 'D');
	line_pipeline(v8, 'D');
	line_pipeline(v5, 'D');

	color[0] = 1;
	color[1] = 1;
	color[2] = .5;
//	set_active(color);
	line_pipeline(v4, 'M');
	line_pipeline(v1, 'D');
	line_pipeline(v2, 'D');
	line_pipeline(v7, 'D');
	line_pipeline(v4, 'D');
	
	color[0] = 1;
	color[1] = .5;
	color[2] = 1;
//	set_active(color);
	DB("\nstore V1",0);
	
//	line_pipeline(v1, 'M');
	DB("\nV1 to V3",0);
	color[0] = .5;
	color[1] = .5;
	color[2] = .5;
//	set_active(color);
//	line_pipeline(v3, 'D');

	DB("\nV3 to V5",0);
	color[0] = .25;
	color[1] = .25;
	color[2] = .25;
//	set_active(color);
//	line_pipeline(v5, 'D');
	
	DB("\nV5 to V4 yellow",0);
	color[0] = 1;
	color[1] = 1;
	color[2] = .5;
//	set_active(color);
//	line_pipeline(v4, 'D');

	DB("\nV4 to V1",0);
	color[0] = .75;
	color[1] = .75;
	color[2] = .75;
//	set_active(color);
//	line_pipeline(v1, 'D');
}

 void objects::draw_sphere(int radius){

	float x, x2, y, y2;
	//	float codinate[3] = {x, y, 0};
//DB("center " + to_string(xcenter) + " " + to_string(ycenter),10);
DB( "radius :" << radius ,-2);
int segments = 20;
float theta, theta2;
for(int i = 0; i< segments; i++){
	theta = (float(i)/float(segments)) *2 * M_PI;
	x = radius*sin(theta);
	y = radius*cos(theta);
	point spot;
	vector<float> point;
	point.push_back(x);
	point.push_back(y);
	point.push_back(0);
	line_pipeline(point, 'M');
	
	theta2 = (float(i+1)/float(segments)) *2 * M_PI;
	x2 = radius*sin(theta2);
	y2 = radius*cos(theta2);
	point[0] = x2;
	point[1] = y2;
	line_pipeline(point, 'D');
}
for(int i = 0; i< segments; i++){
	theta = (float(i)/float(segments)) *2 * M_PI;
	x = radius*sin(theta);
	y = radius*cos(theta);
	point spot;
	vector<float> point;
	point.push_back(0);
	point.push_back(x);
	point.push_back(y);
	line_pipeline(point, 'M');
	
	theta2 = (float(i+1)/float(segments)) *2 * M_PI;
	x2 = radius*sin(theta2);
	y2 = radius*cos(theta2);
	point[1] = x2;
	point[2] = y2;
	line_pipeline(point, 'D');
}
for(int i = 0; i< segments; i++){
	theta = (float(i)/float(segments)) *2 * M_PI;
	x = radius*sin(theta);
	y = radius*cos(theta);
	point spot;
	vector<float> point;
	point.push_back(x);
	point.push_back(0);
	point.push_back(y);
	line_pipeline(point, 'M');
	
	theta2 = (float(i+1)/float(segments)) *2 * M_PI;
	x2 = radius*sin(theta2);
	y2 = radius*cos(theta2);
	point[0] = x2;
	point[2] = y2;
	line_pipeline(point, 'D');
}
}


 void objects::draw_cone(int radius, int hieght){
int segments = 20;
float theta, theta2;
float x, x2, y, y2;
for(int i = 0; i< segments; i++){
	theta = (float(i)/float(segments)) *2 * M_PI;
	x = radius*sin(theta);
	y = radius*cos(theta);
	point spot;
	point tip;
	tip.push_back(0);
	tip.push_back(0);
	tip.push_back(hieght);
	spot.push_back(x);
	spot.push_back(y);
	spot.push_back(0);
	line_pipeline(spot, 'M');
	line_pipeline(tip, 'D');

	line_pipeline(spot, 'M');
	theta2 = (float(i+1)/float(segments)) *2 * M_PI;
	x2 = radius*sin(theta2);
	y2 = radius*cos(theta2);
	spot[0] = x2;
	spot[1] = y2;
	line_pipeline(spot, 'D');
}
}
	
void objects::draw_cylinder(int radius, int base, int top ){
int segments = 20;
float theta, theta2;
float x, x2, y, y2;
for(int i = 0; i< segments; i++){
	theta = (float(i)/float(segments)) *2 * M_PI;
	x = radius*sin(theta);
	y = radius*cos(theta);
	point spot;
	point upper_spot;
	vector<float> point;
	spot.push_back(x);
	spot.push_back(y);
	spot.push_back(base);
	upper_spot.push_back(x);
	upper_spot.push_back(y);
	upper_spot.push_back(top);
	line_pipeline(spot, 'M');
	line_pipeline(upper_spot, 'D');

	line_pipeline(spot, 'M');
	theta2 = (float(i+1)/float(segments)) *2 * M_PI;
	x2 = radius*sin(theta2);
	y2 = radius*cos(theta2);
	spot[0] = x2;
	spot[1] = y2;
	line_pipeline(spot, 'D');
	line_pipeline(upper_spot, 'M');
	upper_spot[0] = x2;
	upper_spot[1] = y2;
	line_pipeline(upper_spot, 'D');
}
}
// void objects::draw_disk();
 void objects::draw_disk(int radius, int hieght){
int segments = 20;
float theta, theta2;
float x, x2, y, y2;
for(int i = 0; i< segments; i++){
	theta = (float(i)/float(segments)) *2 * M_PI;
	x = radius*sin(theta);
	y = radius*cos(theta);
	point spot;
	spot.push_back(x);
	spot.push_back(y);
	spot.push_back(hieght);
	line_pipeline(spot, 'M');

	line_pipeline(spot, 'M');
	theta2 = (float(i+1)/float(segments)) *2 * M_PI;
	x2 = radius*sin(theta2);
	y2 = radius*cos(theta2);
	spot[0] = x2;
	spot[1] = y2;
	line_pipeline(spot, 'D');
}
}

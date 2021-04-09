#ifndef TRANSFORM_H
#define TRANSFORM_H
#include <vector>
using std::vector;
typedef vector< vector<float> > xform; //4X4 matrix
typedef vector<float> point; // 3 item vector

class transforms {

	


	public:

	xform identity();

	xform multiply(xform x1, xform x2);
	
	point multiply_point(vector< vector<float> > xform1,  vector<float> point);
	

	xform translate(double x, double y, double z);
	
	xform scale(double x, double y, double z);


	xform rotate_xy(double theta);

	xform rotate_yz(double theta);

	xform rotate_xz(double theta);


	xform world_to_camera( point eye, point at, vector<float> up);
	
	xform camera_to_clip( double fov, double near, double far, double aspect);

	xform clip_to_device( int width, int height);






};
	

#endif


	


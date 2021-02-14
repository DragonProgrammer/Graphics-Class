#ifndef FRAME_H
#define FRAME_H
#include "color.cpp"
#include <vector>
using std::vector;
class Frame{
	int size_X;
	int size_Y;
	int frame_id;
	color back_color;
	color active_color;

	vector< vector<color> > frame_image;

	public:

	void set_back(int color[3]);
	void set_active(int color[3]);
	void set_size(int x, int y);
	void set_frame_image();
	void set_id(int id);
		
	int get_id();
	color get_color();
	color get_color(int x, int y);

	void set_pixel(int x, int y);

};

#endif

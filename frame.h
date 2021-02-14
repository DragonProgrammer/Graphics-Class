#ifndef FRAME_H
#define FRAME_H
#include "color.cpp"
#include <vector>
using std::vector;
class Frame{
	int size_X;
	int size_Y;
	int frame_id;
	int back_color[3] = {0, 0,0};
	int act_color[3] = {1,1,1};

	int frame_image;

	public:

	void set_back(int color[3]);
	void set_active(int color[3]);
	void set_size(int x, int y);
	void set_frame_image();
	void set_id(int id);
		
	int get_id();
	int get_color(char select);

	void set_Pixel(int x, int y);

};

#endif

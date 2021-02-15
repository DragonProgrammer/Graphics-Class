#ifndef FRAME_H
#define FRAME_H
#include "color.cpp"
#include <vector>
using std::vector;
class Frame{
	int frame_id;

	public:

	vector< vector<color> > frame_image;
	void set_id(int id);
		
	int get_id();



};

#endif

#ifndef GLOBALS
#define GLOBALS
#include "frame.h"
#include <vector>
using std::vector;
class Globals{
	int resolution_X;
	int resolution_Y;
	Frame current;
	vector<Frame> images;
	int curent_id;
	vector<int> frame_ids;

	void set_resolution(int x, int y){
		resolution_X = x;
		resolution_Y = y;
	}

	int get_next_Id(){
		if(frame_ids.size() == 0){
			return 0; //return 0 if there is curently no ids
		}
		else
		{
			int current = frame_ids.back();
			current++;
			return current; //curently this should always be 1 
	}
	}

	Frame set_frame(){
		int res_x = resolution_X;
		int res_y = resolution_Y;
		
		Frame temp;
		int black[3] = {0, 0, 0};
		temp.set_back(black);
		temp.set_size(res_x, res_y);
	//	temp.frame_image = new int[res_x][res_y][3];
		temp.set_frame_image();
		int this_id = get_next_Id();
		temp.set_id(this_id);
		frame_ids.push_back(this_id);
		return temp;
	}
		
};
#endif



#ifdef GLOBALS_CPP
#define GLOBALS_CPP
#include "frame.h"
#include "rd_display.h"
#include <vector>
using std::vector;
//	int resolution_X;
//	int resolution_Y;
	Frame current;
	vector<Frame> images;
	int current_id = -1;
	vector<int> frame_ids;

//	void set_resolution(int x, int y){
//		resolution_X = x;
//		resolution_Y = y;
//	}

	int get_next_Id(){
		if(frame_ids.size() == 0){
			return 0; //return 0 if there is curently no ids
		}
		else
		{
			int last_id = frame_ids.back();
			last_id++;
			return last_id; //curently this should always be 1 
	}
	}

	Frame set_frame(int id){
		int res_x = display_xSize;
		int res_y = display_ySize;
		
		Frame temp;
		int black[3] = {0, 0, 0};
		temp.set_back(black);
		temp.set_size(res_x, res_y);
	//	temp.frame_image = new int[res_x][res_y][3];
		temp.set_frame_image();
	//	int this_id = get_next_Id();
		temp.set_id(id);
		frame_ids.push_back(id);
		current_id = id;
		return temp;
	}
		

#endif



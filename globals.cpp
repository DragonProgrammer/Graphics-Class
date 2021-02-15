#include "frame.h"
#include "rd_display.h"
#include "globals.h"
#include <vector>
using std::vector;
int current_id = -1;
Frame current;
vector<Frame> images;
vector<int> frame_ids;
color background;
color active;

void set_active(float color[3]){
	active.r_scale = color[0];
	active.g_scale = color[1];
	active.b_scale = color[2];
}

void set_back(float color[3]){
	background.r_scale = color[0];
	background.g_scale = color[1];
	background.b_scale = color[2];
}

int get_next_id(){
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

void set_pixel(int x, int y){
	current.frame_image[x][y]=active;
}


Frame set_frame(int id){
		
		Frame temp;
		float black[3] = {0, 0, 0};
		set_back(black);
		float white[3] = {1,1,1};
		set_active(white);
		
	for(int x = 0; x< display_xSize; x++){
		for(int y = 0; x< display_ySize; y++){
			temp.frame_image[x][y]=background;
		}
	}	
		temp.set_id(id);
		frame_ids.push_back(id);
		current_id = id;
		return temp;
	
		}

color color_convert(color scale_input){
	color scale = scale_input;
	scale.r = scale.r_scale*255;	
	scale.g = scale.g_scale*255;	
	scale.b = scale.b_scale*255;
	return scale;
}


color color_scale(color digit_input){
	color scale = digit_input;
	scale.r_scale = scale.r/255;
	scale.g_scale = scale.g/255;
	scale.b_scale = scale.b/255;
	return scale;
}

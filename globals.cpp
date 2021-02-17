#include "frame.h"
#include "rd_display.h"
#include "globals.h"
#include <vector>
#include <iostream>
using std::cout;
using std::endl;
using std::to_string;
using std::vector;
int current_id = -1;
Frame current = Frame(background);
vector<Frame> images;
vector<int> frame_ids;
color background;
color active;

void set_active(float color[3]){
//cout << "set_active" << endl;
	active.r_scale = color[0];
	active.g_scale = color[1];
	active.b_scale = color[2];
	active = color_convert(active);
}

void set_back(float color[3]){

//cout << "set_back" << endl;
	background.r_scale = color[0];
	background.g_scale = color[1];
	background.b_scale = color[2];
	background = color_convert(background);
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
//		cout << "set_pixel" << endl;
//	cout << to_string(x) + " " + to_string(y) << endl;
	cout << current.frame_image[x][y] << endl;
	current.frame_image[x][y]=active;
	cout << "end set_pixel" << endl;
	cout << current.frame_image[x][y] << endl;
}


Frame set_frame(int id){
		
//	cout << "\n set_frame" + to_string(id) << endl;
		float black[3] = {0, 0, 0};
		set_back(black);
		float white[3] = {1,1,1};
		set_active(white);
		active= color_convert(active);
		background = color_convert(background);
		Frame temp = Frame(background);
	vector<color> yline;
	for(int y = 0; y< display_ySize; y++){

		yline.push_back(background);
	}
	vector< vector<color> >  xline;
	for(int x = 0; x< display_xSize; x++){
	xline.push_back(yline);	
	}

//	cout << to_string(display_xSize) + " " + to_string(display_ySize) << endl;
	temp.frame_image = xline;
	temp.set_id(id);
		frame_ids.push_back(id);
		current_id = id;

//	cout << temp.frame_image[0][0] << endl;
//	cout << to_string(xline.size()) + " " + to_string(yline.size()) << endl;
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

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
color match;

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
//	cout << current.frame_image[x][y] << endl;
	current.frame_image[x][y]=active;
//	cout << "end set_pixel" << endl;
//	cout << current.frame_image[x][y] << endl;
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

/************************ fill help****************************/


void set_match(const float point[3]){
	match = current.frame_image[point[0]][point[1]];
//	cout << "mathc is " << match << endl;
}


int check_color(float point[3]){
	color test = current.frame_image[point[0]][point[1]];
//	cout << "test is " << test << endl;
	if( match.r == test.r &&  match.g == test.g &&  match.b == test.g){
	     //  cout << "match = test" << endl;
		return 1;	}
return -1;
}

int find_span(float &new_xs, float &new_xe, float y){
//cout << "in span" <<endl;	
	int left = 1, right = 1;  //to tell mei if i need to move forward or backward
	float point[3] = {new_xs, y, 0};
	if(check_color(point) < 0){
//		cout << "done this one already" << endl;
		return -1;
}
	
	while(left == 1){
		point[0] = new_xs-1;
		if(new_xs-1 >= 0 && check_color(point) > 0 ){
//			cout << endl << "left +" << endl;
			new_xs--;
		}
		else{
//			cout << endl << "left Z" << endl;
			left =0;
		}}
	while(right == 1){
		point[0] = new_xe+1;
	
//		cout << to_string(new_xs) + " " + to_string(new_xe) << endl;
		
		if(new_xe+1 < display_xSize && check_color(point) > 0 ){
			new_xe++;
		}
		else{
		
		//	cout << endl << "left Z" << endl;
			right = 0;}
	}
return 0;
}


int flood_fill(float xs, float xe, float y){
	float color[3] = {active.r_scale, active.g_scale, active.b_scale};
	float new_xs, new_xe;
//	cout << endl << "in flood " + to_string(xs) + " " + to_string(xe) << endl;
	for( int x = xs; x < xe; x++){
//		cout << to_string(x) + " " + to_string(xe) << endl;
		rd_write_pixel( x , y, color);}
	for( new_xs= new_xe =xs; new_xe < xe; new_xs = new_xe){
		if(y+1 < display_ySize && find_span(new_xs, new_xe, y+1) == 0){
//			cout << "next flood fill" << endl;
			flood_fill(new_xs, new_xe, y+1);
		}
		else{
			new_xe++;
	}

}
	for( new_xs= new_xe =xs; new_xe < xe; new_xs = new_xe){
		if(y-1 > -1 && find_span(new_xs, new_xe, y-1) == 0){
//			cout << "next flood fill" << endl;
			flood_fill(new_xs, new_xe, y-1);
		}
		else{
			new_xe++;
	//		cout << endl << "1" << endl;
	}
	}
	return 0;
}


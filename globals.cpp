#define DEBUG
#ifdef DEBUG
#include <iostream>
using std::cerr;
using std::end;
#define DB(x) do{cerr<<x<<endl;}while(0)
#else
#define DB(x) do{}while(0)
#endif

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
int active_flag = 0;
int back_flag = 0;
Frame current = Frame(background);
//vector<Frame> images;
//vector<int> frame_ids;
color background;
color active;
color match;

void set_active(float color[3]){
//cout << "set_active" << endl;
	active.r_scale = color[0];
	active.g_scale = color[1];
	active.b_scale = color[2];
	active = color_convert(active);
	DB("active is " << active);
}

void set_back(float color[3]){

//cout << "set_back" << endl;
	background.r_scale = color[0];
	background.g_scale = color[1];
	background.b_scale = color[2];
	background = color_convert(background);
	DB("bacground in " <<background);
}
/*
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
*/
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
		if(back_flag == 0)
			set_back(black);
		float white[3] = {1,1,1};
		if(active_flag == 0)
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
//		frame_ids.push_back(id);
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
	match.r = 0;
	match.g = 0;
	match.b =0;
	match = color_convert(match);
	DB("mathc is " << match);
}


int check_color(float point[3]){
	color test = current.frame_image[point[0]][point[1]];
//	DB(to_string(point[0]) + " " +  to_string(point[1]));
	cout << "test is " << test << endl;
	if( active.r == test.r &&  active.g == test.g &&  active.b == test.g) {
		return -2;
	}
	else if( match.r == test.r &&  match.g == test.g &&  match.b == test.g){
	      cout << "match = test" << endl;
		return 1;	}
//cout << "these do not match" << endl;
	else if( background.r == test.r &&  background.g == test.g &&  background.b == test.g){
	return -1;
	}
	else 
		return -3;
}

int find_span(int &new_xs, int &new_xe, float y){
//cout << "in span" <<endl;	
	int left = 1, right = 1;  //to tell mei if i need to move forward or backward
	float point[3] = {float(new_xs), y, 0};
	DB(to_string(point[0]) + " " +  to_string(point[1]));
	int result = check_color(point);
	if(result == -2){
		DB("done this one already");
		return -1;
}
	else if(result == -1){
		DB("this is background");
		return -1;
	}
	else if (result == -3){
		DB("This a different color");
		return -1;
	}
	
	while(left == 1){
		point[0] = new_xs-1;
		if(new_xs-1 < 0)
			break;
		DB(to_string(point[0]) + " " +  to_string(point[1]));
		result = check_color(point);
		if(new_xs-1 >= 0 && result == 1 ){
//			DB("left +");
			new_xs--;
		}
		else{
//			DB("left end");
			left =0;
		}}
	while(right == 1){
		point[0] = new_xe+1;
		if(new_xe+1 >display_xSize-1){
			right = 0;
			break;
	}
		DB(current.frame_image[point[0]][point[1]]);
		DB(to_string(point[0]) + " " +  to_string(point[1]));
		result = check_color(point);
//		cout << to_string(new_xs) + " " + to_string(new_xe) << endl;
		
		if(new_xe+1 < display_xSize && result == 1 ){
//			DB("right +");
			new_xe++;
		}
		else{
		
			//cout << endl << "left Z" << endl;
//			DB("right end");
			right = 0;}
	}
return 1;
}


int flood_fill(float xs, float xe, float y){
	float color[3] = {active.r_scale, active.g_scale, active.b_scale};
	int new_xs, new_xe;
//	cout << endl << "in flood " + to_string(xs) + " " + to_string(xe) << endl;
//	cout << endl << "in flood " + to_string(display_xSize) + " " + to_string(display_xSize) << endl;
//	cout << " initial        "+  to_string(xs) + " " + to_string(xe)  + " " + to_string(y)<< endl;
	for( int x = xs; x < xe; x++){
//		cout << to_string(x) + " " + to_string(y) << endl;
		rd_write_pixel( x , y, color);}
	for( new_xs= new_xe =xs; new_xe < xe; new_xs = new_xe){
//	cout << "For 1: "+  to_string(new_xs) +" "+ to_string(new_xe)  +" "+ to_string(xe) +" "+ to_string(y)<< endl;
		DB("DOWN");
		if(y+1 <= display_ySize && find_span(new_xs, new_xe, y+1) < 0){
		DB("Down "+  to_string(new_xs) + " " + to_string(new_xe)  + " " + to_string(y));
			flood_fill(new_xs, new_xe+1, y+1);
			new_xe++;
		}
		else{
			new_xe++;
		DB("Down ncrement "+  to_string(new_xs) + " " + to_string(new_xe)  + " " + to_string(y));
		}

	}
//	cout << " Transition "+  to_string(new_xs) + " " + to_string(new_xe)  + " " + to_string(y)<< endl;
	for( new_xs= new_xe =xs; new_xe < xe; new_xs = new_xe){
//	cout << "For 2: "+  to_string(new_xs) +" "+ to_string(new_xe)  +" "+ to_string(xe) +" "+ to_string(y)<< endl;
		if(y-1 >= 0 && find_span(new_xs, new_xe, y-1) < 0){
//		cout << " Up "+  to_string(new_xs) + " " + to_string(new_xe)  + " " + to_string(y)<< endl;
			flood_fill(new_xs, new_xe+1, y-1);
			new_xe++;
		}
		else{
			new_xe++;
//		cout << "up ncrement "+  to_string(new_xs) + " " + to_string(new_xe)  + " " + to_string(y)<< endl;
		}
	}
	return 0;
}


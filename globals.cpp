#include "Debug.h"
#include <math.h>
#include "frame.h"
#include "rd_display.h"
#include "rd_direct.h"
#include "globals.h"
#include <vector>
#include <iostream>
#include "transformations.h"
using std::cout;
using std::sqrt;
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


typedef vector<float> point;















 /******************************Frome assign 2****************/

typedef vector< vector<float> > xform;
double Camera_View;// = 90;
xform current_xform;// transforms.identity();
point camera_eye;// {0,0,0};
float camera_near;// 1.0;
float camera_far;// 1000000,000.0;
point camera_up;// {0, 1.0, 0)
point at_point; // {0, 0, -1.0};

point last_point;

xform W2C;
xform C2C;
xform C2D;
vector<xform> xform_stack;


void draw_depth(point p){
	float color[3];
	color[0] = active.r_scale;	
	color[1] = active.g_scale;	
	color[2] = active.b_scale;
	int middle = display_xSize/2;
	if(p[1] == middle || (middle < p[1] && middle+1 > p[1]) || (middle > p[1] && middle-1 < p[1]))
		DB(p[2], -2);	
	if(compute_point(p) == -1)
		return;
	if(current.frame_depth[p[0]][p[1]] > p[2]){
		set_pixel(p[0], p[1], p[2]);
		rd_write_pixel(p[0], p[1], color);
	}
}











point point_pipeline(point p){
	transforms t;
	point input = p;
//	input.push_back(x);
//	input.push_back(y);
//	input.push_back(z);
	input.push_back(1);
	xform P = current_xform;
	point PP = t.multiply_point(P,input);	
	xform P1 = W2C;
	point PP1 = t.multiply_point(P1, PP);
	// do check stuff
	
	xform P2 = C2C;
	point PP2 = t.multiply_point(P2, PP1);
	xform P3 = C2D;
	point PP3 = t.multiply_point(P3, PP2);
	if(PP3[3] > 1){
		PP3[0] = PP3[0]/PP3[3];
		PP3[1] = PP3[1]/PP3[3];
		PP3[2] = PP3[2]/PP3[3];
		PP3[3] = PP3[3]/PP3[3];
	}
	DB("to make point",2);
	DB("made point",2);

	DB("point 2: " << PP3[0] << " " << PP3[1] << " " << PP3[2] << " " << PP3[3],2);
	draw_depth(PP3);
	return PP3;
}
	
void line_pipeline(point p1, char FLAG){
	REDirect r;

	transforms t;
	point input;
	input.push_back(p1[0]);
	input.push_back(p1[1]);
	input.push_back(p1[2]);
	DB(input[0] << " " << input[1],0);
		float W = 0;
	input.push_back(1);
//	DB("made input point",0);
	xform T = current_xform;
	DB("Curent xform",-1);
//	T[2][3] = -3;	
	DBM(T,-1);
	point P = input;

	DB("Input point: " << P[0] << " " << P[1] << " " << P[2] << " " << P[3],-1);
	P = t.multiply_point(T,P);	
	DB("Point after curent xform: " << P[0] << " " << P[1] << " " << P[2] << " " << P[3],-1);
	DB("World 2 clip",-1);
	T = W2C;
	DBM(T,-1);
	
	P = t.multiply_point(T, P);
	DB("clipping point: " << P[0] << " " << P[1] << " " << P[2] << " " << P[3],2);

	if(FLAG == 'M')
		last_point = P;
	if(FLAG == 'D'){

/***********changes for assignment 3 ****************/
		new_point = P;
	//	int is_clipping = clip_line(P);
	//	DB(is_clipping, 2);
	//	if(is_clipping == -1)
	//		return;
		// set to points to device
		T = C2C;
		DB("\ncamer to clip",-1);
		DBM(T, -1);

		point P2 = t.multiply_point(T, P ); //curent point, new_point was P
		point P1 = t.multiply_point(T, last_point); //saved point

		last_point = P; //was =P
//if(is_clipping != -1){
/**************************************************************/	
	
	DB("C2C point 1: " << P1[0] << " " << P1[1] << " " << P1[2] << " " << P1[3],-1);
	DB("C2C point 2: " << P2[0] << " " << P2[1] << " " << P2[2] << " " << P2[3],-1);
		DB("Clip to divice",-1);
		T = C2D;
		DBM(T, -1);
		
	
		P1 = t.multiply_point(T, P1); //curent point
		P2 = t.multiply_point(T, P2); //curent point
	DB("C2D point 1: " << P1[0] << " " << P1[1] << " " << P1[2] << " " << P1[3],-1);
	DB("C2D point 2: " << P2[0] << " " << P2[1] << " " << P2[2] << " " << P2[3],-1);

		if(P1[3] > 1){
			P1[0] = P1[0]/P1[3];
			P1[1] = P1[1]/P1[3];
			P1[2] = P1[2]/P1[3];
			P1[3] = P1[3]/P1[3];
		}
		if(P2[3] > 1){
			P2[0] = P2[0]/P2[3];
			P2[1] = P2[1]/P2[3];
			P2[2] = P2[2]/P2[3];
			P2[3] = P2[3]/P2[3];
		}
	//	old_point = P1;
	//	int is_clipping = clip_line(P2);
	//	DB(is_clipping, 2);
	// line drawing stuff
 		int x1 = P1[0], x2 = P2[0];
 	//	int x1 = last_point[0], x2 = input[0];
 		int y1 = P1[1], y2 = P2[1];
		float z1 = P1[2], z2 = P2[2];
 	//	int y1 = last_point[1], y2 = input[1];
		float xchan = x2-x1, ychan = y2-y1, zchan = z2-z1;
	DB("\nLine point 1: " << x1 << " " << y1 << " " << P1[2] << " " << P1[3],-2);
	DB("Line point 2: " << x2 << " " << y2 << " " << P2[2] << " " << P2[3],-2);
		DB("changes " << xchan << "    " << ychan << "     " << zchan, -2);
 		DB("piont 1: " << x1 << " " << y1,10);	
 		DB("piont 2: " << x2 << " " << y2,10);	
/*
		if( xchan < 0){
			DB("flipped",0);
			x2 = P1[0]; 
			x1 = P2[0] ;
			y1 = P2[1] ;
			y2 = P1[1] ;

			xchan = x2-x1;
			ychan = y2-y1;
		}
*/

		int no_chan_y = 0, no_chan_x = 0, no_chan_z = 0, end_draw=0;
		float x0 =float(x1), y0 =float(y1), z0 = float(z1);
		int steps;
		float incX, incY, incZ;
		point p;
		p.push_back(0);
		p.push_back(0);
		p.push_back(0);
		
		if(ychan == 0){ no_chan_y = 1;}
		if(xchan == 0){ no_chan_x = 1;}
		if(zchan == 0){ no_chan_z = 1;}
		end_draw = no_chan_x + no_chan_y + no_chan_z;
		DB("no x: " << no_chan_x << " no y: " << no_chan_y << " no z: " << no_chan_z << " end: " <<end_draw, -2); 
		if(end_draw == 3) {return;}
		
		
		
		if(abs(ychan) ==0 && abs(zchan) ==0){
		DB("no change in Z",-2);
				steps = abs(xchan);
				incX = float(xchan)/float(steps);
			while(x0 != x2){
				p[0] = x0;
				p[1] = y0;
				p[2] = z0;
				draw_depth(p);
				x0 += incX;
			}
		}	
		else if(abs(xchan) ==0 && abs(zchan) ==0){
		DB("no change in Z",-2);
				steps = abs(ychan);
				incY = float(ychan)/float(steps);
			while(y0 != y2){
				p[0] = x0;
				p[1] = y0;
				p[2] = z0;
				draw_depth(p);
				y0 += incY;
			}
		}	
		else if(abs(xchan) ==0 && abs(ychan) ==0){
		DB("only change in Z",-2);
				steps = abs(zchan);
				incZ = float(zchan)/float(steps);
			while(y0 != y2){
				p[0] = x0;
				p[1] = y0;
				p[2] = z0;
				draw_depth(p);
				z0 += incZ;
			}
		}	
		else if(abs(xchan) >= abs(ychan)  && abs(xchan) >= abs(zchan)){
		DB("xchange bigest",-2);
		
				steps = abs(xchan);
				incY = float(ychan)/float(steps);
				incX = float(xchan)/float(steps);
				incZ = float(zchan)/float(steps);
		DB(x0 << " " << x2 << "     " << y0 << " " << y2,-2);
		//	while(x0 != x2 && y0 != y2){
			for(int s = 0; s <= steps; s++){
				p[0] = x0;
				p[1] = y0;
				p[2] = z0;
				draw_depth(p);
				x0 += incX;
				y0 += incY;
				z0 += incZ;
		}
		}	
		else if(abs(ychan) >= abs(xchan)  && abs(ychan) >= abs(zchan)){
		DB("ychange bigest",-2);
				steps = abs(ychan);
				incY = float(ychan)/float(steps);
				incX = float(xchan)/float(steps);
				incZ = float(zchan)/float(steps);
			for(int s = 0; s <= steps; s++){
				p[0] = x0;
				p[1] = y0;
				p[2] = z0;
				draw_depth(p);
				x0 += incX;
				y0 += incY;
				z0 += incZ;
				}
		}	
		else if(abs(zchan) >= abs(xchan)  && abs(zchan) >= abs(ychan)){
		DB("zchange bigest",-2); // this one only comes up if major error
				steps = abs(zchan);
				incY = float(ychan)/float(steps);
				incX = float(xchan)/float(steps);
				incZ = float(zchan)/float(steps);
			while(x0 != x2 && y0 != y2){
				p[0] = x0;
				p[1] = y0;
				p[2] = z0;
				draw_depth(p);
				x0 += incX;
				y0 += incY;
				z0 += incZ;
				}
//		}	
				
				
				
}// close clipping part

}
}
 
 void push(xform x1){
	xform_stack.push_back(x1);
}

xform pop(){
	xform to_return = xform_stack[xform_stack.size()-1];
	xform_stack.pop_back();
	return to_return;
}

/****************************Asssignment 3**************/

vector<float> BC0, BC1;
//int[6] borders_crossed = {0, 0, 0, 0, 0, 0};
//planes = left, right, top, bottom, front, back
//values: 0 = not crossed, -1 = croosed on way in, 1 = crossed on way out

float clip_amount1 = 0.0, clip_amount2 = 1.0;
point new_point;
point old_point;

int compute_point(point in_question){
	if(in_question[0] >= 0 && in_question[0] < display_xSize && in_question[1] >= 0 && in_question[1] < display_ySize && in_question[2] >= 0 && in_question[2] < camera_far)
		return 1;
	return -1;
}

int clip_line(point input){
	point p1 = last_point;
	point p2 = input;
//	p1 = {1, -1, 0, 1};
//	last_point = p1;
//	p2 = {2, 1, 3, 2};
	new_point = p2;
	BC0 = compute_boundary_corridinate(p1);
	BC1 = compute_boundary_corridinate(p2);
	DB("Pre-clip 1: " << p1[0] << " " << p1[1] << " " << p1[2] << " " << p1[3],-2);
	DB("Pre-clip 2: " << p2[0] << " " << p2[1] << " " << p2[2] << " " << p2[3],-2);
	DB("1: " << BC0[0] << " " << BC0[1] << " "<< BC0[2] << " "<< BC0[3] << " "<< BC0[4] << " "<< BC0[5], 2);
	DB("2: " << BC1[0] << " " << BC1[1] << " "<< BC1[2] << " "<< BC1[3] << " "<< BC1[4] << " "<< BC1[5], 2);
	vector<int> code_vector1 = compute_boundary_code(BC0);
	vector<int> code_vector2 = compute_boundary_code(BC1);
	int flag = viewable(code_vector1, code_vector2);
	if(flag != 1){
		DB("flag " << flag,-2);
		return flag; //-1 = reject line, 0 = do normaly
}
	for(int i =0; i < 6; i++){
		float a;
		DB("in math loop", 2);
		a = BC0[i]/(BC0[i]-BC1[i]);
		if(code_vector1[i] == 1){
		       if(clip_amount1 < a){
		       		clip_amount1 = a;
		       }
		}		       
		if(a < clip_amount2)
			clip_amount2 = a;
	}
//	if(clip_amount1 > clip_amount2){
//		DB("clipp amount error", -2);
//		return -1;
//	}

DB("out of math loop",-2);
	compute_new_points();
	

}

void compute_new_points(){
	point PM;
	float c;
	DB("in compute point",-2);
	for(int i =0; i <4; i++){
		c = last_point[i] - new_point[i];
		//c = new_point[i] - last_point[i];
		PM.push_back(c);
	}
	DB("PM: " <<PM[0] << " " <<PM[1] << " " <<PM[2] << " " <<PM[3],-2);
	point PA0, PA1;
	for(int i =0; i <4; i++){
	c = PM[i] *clip_amount1;
	PA0.push_back(c);
	c = PM[i] *clip_amount2;
	PA1.push_back(c);
	}
	if(compute_point(last_point) == -1){ // last point is outside
		for(int i =0; i < 4; i++){
			last_point[i] = last_point[i] + PA0[i];
			//new_point[i] = new_point[i] + PA0[i];
		}
	DB("clipped point a: " <<last_point[0] << " " <<last_point[1] << " " <<last_point[2] << " " <<last_point[3],-2);
	}
	if(compute_point(new_point) == -1){
	for(int i =0; i < 4; i++){
		new_point[i] = new_point[i] + PA1[i];
	}
	DB("clipped point b: " <<new_point[0] << " " <<new_point[1] << " " <<new_point[2] << " " <<new_point[3],-2);
	}
}

	
	

vector<float> compute_boundary_corridinate(point p){
	vector<float> bcoord;
	for(int i = 0; i < 3; i++){
		float c;
		c = p[i];
		bcoord.push_back(c);
		c = p[3] - c;
		bcoord.push_back(c);
	}
	return bcoord;
}

vector<int> compute_boundary_code(vector<float> input){
	vector<int> bcode;
	for(int i = 0; i < input.size(); i++){
		int code;
		if(input[i] < 0)
			code = 1;
		else
			code = 0;
		bcode.push_back(code);
	}
	return bcode;
}

int viewable(vector<int> b1, vector<int> b2){
	int flag = 0;
	DB("1: " << b1[0] << " " << b1[1] << " "	<< b1[2] << " "	<< b1[3] << " "	<< b1[4] << " "	<< b1[5], -2);
	DB("2: " << b2[0] << " " << b2[1] << " "	<< b2[2] << " "	<< b2[3] << " "	<< b2[4] << " "	<< b2[5], -2);
	for(int i = 0; i < 4; i++){
		if(b1[i] == b2[i] && b1[i] == 1)
			return -1; // fully out of view
		if(b1[i] != b2[i])
			flag = 1;
	}
	if(flag == 0)
		return 0; //wholy in view
/*
	for(int i = 0; i < b1.size(); i++){
			if(b1[i] > b2[i])
				border_crossed[i] = -1; //point 1 is not visable
			if(b1[i] > b2[i])
				border_crossed[i] = 1; //point 2 is not visable
	}
*/
	return 1;
	}
	


/*****************from assign 1 *******************/



void set_active(float color[3]){
//cout << "set_active" << endl;
	active.r_scale = color[0];
	active.g_scale = color[1];
	active.b_scale = color[2];
	active = color_convert(active);
	DB("active is " << active, 10);
}

void set_back(float color[3]){

//cout << " endl  << endl;
background.r_scale = color[0];
	background.g_scale = color[1];
	background.b_scale = color[2];
	background = color_convert(background);
	DB("bacground in " <<background, 10);
}
void set_pixel(int x, int y, float z){
	DB("in set pixel", 10);	
//	cout << to_string(x) + " " + to_string(y) << endl;
	DB(x << " " << y,10);
	DB( "color before "<<  current.frame_image[x][y],10);
	DB(x << "   " << y << "  " << z << "      " << current.frame_depth[x][y], 2);
	if(current.frame_depth[x][y] < z){
		return;
	}
	else{
		current.frame_image[int(x)][int(y)]=active;
		current.frame_depth[x][y] = z;
	}
	DB("I set the pixel", 10);	

//	DB("color after" << current.frame_image[x][y]);
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
		vector<float> yDepth;
		for(int y = 0; y< display_ySize; y++){

			yline.push_back(background);
			yDepth.push_back(1.0);
		}
		vector< vector<float> > depth;
		vector< vector<color> >  xline;
		for(int x = 0; x< display_xSize; x++){
			xline.push_back(yline);
			depth.push_back(yDepth);	
		}
	DB("Size = " << display_ySize << " " <<display_xSize, 10);
	temp.frame_image = xline;
	temp.frame_depth = depth;
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
//	DB("mathc is " << match);
}


int check_color(float point[3]){
	color test = current.frame_image[point[0]][point[1]];
//	DB("checking cell " + to_string(point[0]) + " " +  to_string(point[1]) + " in a " + to_string(display_xSize) + " " + to_string(display_ySize) + " grid" );
//	DB("test is " << test);
	if( active.r == test.r &&  active.g == test.g &&  active.b == test.g) {
		return -2;
	}
	else if( match.r == test.r &&  match.g == test.g &&  match.b == test.g){
	 //     DB("match = test");
		return 1;	}
//cout << "these do not match" << endl;
	else if( background.r == test.r &&  background.g == test.g &&  background.b == test.g){
	return -1;
	}
	else 
//	DB("test is " << test); // r value in test flucuates
//	DB("Active is " << active);
		return -3;
}

int find_span(int &new_xs, int &new_xe, float y){
	int left = 1, right = 1;  //to tell mei if i need to move forward or backward
	float point[3] = {float(new_xs), y, 0};
//	DB(to_string(point[0]) + " " +  to_string(point[1]));
	int result = check_color(point);
	if(result == -2){
//		DB("done this one already");
		return -1;
}
	else if(result == -1){
//		DB("this is background");
		return -1;
	}
	else if (result == -3){
//		DB("This a different color");
		return -1;
	}
	else{
	while(left == 1){
		point[0] = new_xs-1;
		if(new_xs-1 < 0)
			break;
//		DB(to_string(point[0]) + " " +  to_string(point[1]));
		result = check_color(point);
		if(new_xs-1 >= 0 && result == 1 ){
		//	DB("left +");
			new_xs--;
		}
		else{
		//	DB("left end");
			left =0;
		}}
	while(right == 1){
		point[0] = new_xe+1;
		if(point[0] >display_xSize-1){
			break;
	}
//		DB(current.frame_image[point[0]][point[1]]);
//		DB(to_string(point[0]) + " " +  to_string(point[1]));
		result = check_color(point);
//		cout << to_string(new_xs) + " " + to_string(new_xe) << endl;
		if(new_xe+1 < display_xSize && result == 1 ){
		//	DB("right +");
			new_xe++;
		}
		else{
		//	DB("right end");
			right = 0;}
	}
		return 1;
	}
}





int flood_fill(float xs, float xe, float y){
	//	DB("passed: xs = " + to_string(xs) + " xe = " + to_string(xe) + " into flood");
	
	float color[3] = {active.r_scale, active.g_scale, active.b_scale};
	int new_xs, new_xe;
	for(int x = 0; x < display_xSize; x++){
		for(int y = 0; y < display_ySize; y++){
//			DB("cell " + to_string(x) + " " + to_string(y) + "color " << current.frame_image[x][y]);
		}
	}
	float pigment[3];
	pigment[0] = active.r_scale;
	pigment[1] = active.g_scale;
	pigment[2] = active.b_scale;
	
	
	for( int x = xs; x < xe; x++){
	//	DB( "fill :" +  to_string(x) + " " + to_string(y));
		float point[3] = {x, y, 0};
		//rd_display_  set pixel command
		
		
		set_pixel(x, y, 0);// this will cause problems in flood fill
		rd_write_pixel(x, y, pigment);
		
		}
	for( new_xs= new_xe =xs; new_xe < xe; new_xs = new_xe){
		int span = find_span(new_xs, new_xe, y+1);
//		DB(to_string(span));
		if(y+1 <= display_ySize && span == 1){
//		DB("DOWN");
//		DB("passing: xs = " + to_string(new_xs) + " xe = " + to_string(new_xe) + "to flood");
			flood_fill(new_xs, new_xe+1, y+1);
			new_xe++;
		}
		else{
			new_xe++;
		}

	}
//		DB("reseting: new_xs to " + to_string(xs) + " and new_xe to " + to_string(xs) + " and ex is " + to_string(xe));
	for( new_xs= new_xe =xs; new_xe < xe; new_xs = new_xe){
//		DB("reset: new_xs to " + to_string(new_xs) + " and new_xe to " + to_string(new_xe) + "  and ex is " + to_string(xe));
		int span = find_span(new_xs, new_xe, y-1);
//		DB(to_string(span));
		if(y-1 >= 0 && span == 1){
//		DB("UP");
//		DB("passing: xs = " + to_string(new_xs) + " xe = " + to_string(new_xe) + "to flood");
			flood_fill(new_xs, new_xe+1, y-1);
			new_xe++;
		}
		else{
			new_xe++;
		}
	}
//	DB("Exiting flood");
	return 0;
}

#include "Debug.h"
#include "objects.h"
#include "rd_direct.h"
#include <string>
#include <cstring>
#include "rd_display.h"
#include "frame.h"
#include "globals.h"
#include "rd_error.h"
#include <sstream>
#include <iostream>
#include <stdio.h>
#include <vector>
#include "transformations.h"
using std::getline;
using std::strtok;
using std::string;
using std::to_string;
using std::cout;
using std::endl;
using std::stringstream;

		/**********************   General functions  *******************************/
int REDirect :: rd_display(const string & name, const string & type,  const string & mode){
	
	return RD_OK;
}

int REDirect::rd_format(int xresolution, int yresolution)
{
	return RD_OK;
}

int REDirect::rd_world_begin(void)
{
transforms t;

DB("world begin", 2);
current_xform = t.identity();
DB("Made identity", 2);
if(Camera_View == 0)
	Camera_View = 90;
camera_near = 1.0;
camera_far = 1000000000.0;
if(camera_up.size() != 3)
camera_up = {0, 1.0, 0};
if(at_point.size() != 3)
at_point = {0,0,-1.0};
if(camera_eye.size() != 3)
camera_eye = {0,0,0};


DB("Made Camera elements", 2);
W2C = t.world_to_camera(camera_eye, at_point, camera_up);
DB("Made World to Camera", 2);

DB("Aspect " << display_ySize << "/" << display_xSize, 0);
double aspect = double(display_xSize)/double(display_ySize);
DB(aspect,0);
C2C = t.camera_to_clip(Camera_View, camera_near, camera_far, aspect);
DB("Made Camera to clip", 2);
C2D = t.clip_to_device(display_xSize, display_ySize);

DB("Made Clip to device", 2);
//	if(current_id != -1){   //if there is a frame alredy
//		images.push_back(current); //put it into the vector if frames
//	}

//	int new_id = get_next_id();  // gets next unsused number for id
					//this was added now as we are going to soon be doing multiple frames
	int rd_er = RD_OK;
	rd_er = rd_disp_init_frame(current_id);  // called from rd_display
	if(rd_er != 0){
	cout << rd_er << endl;
	}
	
	//this presumes that rd_format (above) was called to give us size
//	rd_frame_begin(1); // called from below
DB("end world begin",0);
	return rd_er;

}

int REDirect::rd_world_end(void)
{
DB("rd_world_end", 0);	
//	int error1 = rd_disp_end_display();
//	DB(error1);
	int error = rd_frame_end();
//	DB(error);

	
	DB("end rd_world_end",0);	
//	exit(0);
	return RD_OK;
}

int REDirect::rd_frame_begin(int frame_no)
{
	DB("rd_frame_begin",0);
	//this should change nothing
//	if(current_id != frame_no){
//		return-1;}
	current = set_frame(frame_no); //create a new frame in the globals
	current.set_id(frame_no);
		
	return RD_OK;
}

int REDirect::rd_frame_end(void)
{
DB("rd_frame_end",0);	
DB("numer of rejected points " << draw_depth_reject, -2);
for(auto p : rejects){
	DB(p[0] << " " << p[1] << " " << p[2], 2);
}
//	if(current_id != frame_ids.back()){
//		cout << "in check" <<endl;
//	images.push_back(current);
//	frame_ids.push_back(current_id);
//	}
//	rd_disp_end_display();
	rd_disp_end_frame();

	return RD_OK;
}
/*
int REDirect::rd_render_init(void)
{
return 0;
}/i* Initialize renderer */
/*
int REDirect::rd_render_cleanup(void)
{
	return 0;
}

 /s**********************   Camera  ******************************************/

int REDirect::rd_camera_eye(const float eyepoint[3])
{
	vector<float> point;
	
	point.push_back(eyepoint[0]);
	point.push_back(eyepoint[1]);
	point.push_back(eyepoint[2]);
	camera_eye = point;//might be set_camera_point
	
	return RD_OK;
}

int REDirect::rd_camera_at(const float atpoint[3])
{
	vector<float> point;
	
	point.push_back(atpoint[0]);
	point.push_back(atpoint[1]);
	point.push_back(atpoint[2]);
	at_point = point;


	return RD_OK;
}


int REDirect::rd_camera_up(const float up[3])
{
	vector<float> point;
	
	point.push_back(up[0]);
	point.push_back(up[1]);
	point.push_back(up[2]);
	camera_up = point;

	return RD_OK;
}

int REDirect::rd_camera_fov(float fov)
{
	Camera_View = fov;
	return RD_OK;
}

int REDirect::rd_clipping(float znear, float zfar)
{
	camera_near = znear;
	camera_far = zfar;
	return RD_OK;
}
 
 /**********************   Transformations **********************************/

int REDirect::rd_translate(const float offset[3])
{
	DB("Prior xForm",-1);
	DBM(current_xform,-1);
	transforms t;
	xform function = t.translate(double(offset[0]),double(offset[1]),double(offset[2]));
	current_xform =t.multiply(current_xform, function);
	DB("Translated xform",-1);
	DBM(current_xform,-1);
	return RD_OK;
}

int REDirect::rd_scale(const float scale_factor[3])
{
	DB("Prior xform",-1);
	DBM(current_xform,-1);
	transforms t;
	xform function = t.scale(double(scale_factor[0]),double(scale_factor[1]),double(scale_factor[2]));
		current_xform = t.multiply(current_xform, function);
	DB("Scaled xform",-1);
	DBM(current_xform,-1);
		return RD_OK;
}

int REDirect::rd_rotate_xy(float angle)
{
	transforms t;
	xform function = t.rotate_xy(angle);
		current_xform = t.multiply(current_xform, function);
		return RD_OK;
}

int REDirect::rd_rotate_yz(float angle)
{
	transforms t;
	xform function = t.rotate_yz(angle);
		current_xform = t.multiply(current_xform, function);
		return RD_OK;
}

int REDirect::rd_rotate_zx(float angle)
{
	transforms t;
	xform function = t.rotate_xz(angle);
		current_xform = t.multiply(current_xform, function);
		return RD_OK;
}
/*
int REDirect::rd_matrix(const float * mat)
{
	return RD_OK;
}*/
	       
int REDirect::rd_xform_push(void)
{
	push(current_xform);
	return RD_OK;
}

int REDirect::rd_xform_pop(void)
{
	current_xform=pop(); 
	return RD_OK;
}

  /**********************   Geometric Objects  *******************************/
/*

int REDirect::rd_bezier_curve(const string & vertex_type, int degree, const float * vertex)
{
	return 0;
}

int REDirect::rd_bezier_patch(const string & vertex_type, int u_degree, int v_degree, const float * vertex)
{
	return 0;
}

int REDirect::rd_catmull_clark_sds(const string & vertex_type, float * coord, int nvertex, int * vertex_list, int nface, int * crease_list, int ncrease, float *sharpness)
{
	return 0;
}
*/

int REDirect::rd_circle(const float center[3], float radius)
{
struct point {
	float point_x;
	float point_y;
	float point_z;
};

	float xcenter = center[0], ycenter = center[1], r = radius;
	int p = 1 - r;
	float x = 0 , y= r;
	float codinate[3] = {x,y, 0};
	
//	DB("center " + to_string(xcenter) + " " + to_string(ycenter));
	vector<point> circle;
	while(x <= r){
		if(x*x <= y*y){
		point spot;
		spot.point_z = 0;
		
		spot.point_x = xcenter+x;
		spot.point_y = ycenter+y;
//		DB("section 1 " << to_string(spot.point_x) + " " + to_string(spot.point_y));
		circle.push_back(spot);

		
		spot.point_x = xcenter-x;
		spot.point_y = ycenter+y;
//		cout << "section 2 " << to_string(spot.x) + " " + to_string(spot.y) << endl;
		circle.push_back(spot);

		spot.point_x = xcenter+x;
		spot.point_y = ycenter-y;
//		cout << "section 3 " << to_string(spot.x) + " " + to_string(spot.y) << endl;
		circle.push_back(spot);

		spot.point_x = xcenter-x;
		spot.point_y = ycenter-y;
//		cout << "section 4 " << to_string(spot.x) + " " + to_string(spot.y) << endl;
		circle.push_back(spot);

		spot.point_x = xcenter+y;
		spot.point_y = ycenter+x;
//		cout << "section 5 " << to_string(spot.x) + " " + to_string(spot.y) << endl;
		circle.push_back(spot);

		spot.point_x = xcenter-y;
		spot.point_y = ycenter+x;
//		cout << "section 6 " << to_string(spot.x) + " " + to_string(spot.y) << endl;
		circle.push_back(spot);

		spot.point_x = xcenter+y;
		spot.point_y = ycenter-x;
//		cout << "section 7 " << to_string(spot.x) + " " + to_string(spot.y) << endl;
		circle.push_back(spot);

		spot.point_x = xcenter-y;
		spot.point_y = ycenter-x;
//		cout << "section 8 " << to_string(spot.x) + " " + to_string(spot.y) << endl << endl;
		circle.push_back(spot);
		}
		x++;
		if(p < 0)
			p += 2*x +1;
		else{
			p += 2*x-2*y +3;
			y--;
		}
	}
	
	for( auto a : circle)
		if( a.point_x >= 0 &&  a.point_y >= 0){
			float cord[3] = {a.point_x, a.point_y, a.point_z};
	//	cout << to_string(a.point_x) + " " + to_string(a.point_y) << endl;
			rd_point(cord);
		}

	return 0;
}


int REDirect::rd_line(const float start[3], const float end[3])
{
	DB("in line",0);
	vector<float> point_input;
	point_input.push_back(start[0]);
	point_input.push_back(start[1]);
	point_input.push_back(start[2]);
	line_pipeline(point_input, 'M');	
	
	
	DB("did first pipline",2);
	point_input.clear();
	point_input.push_back(end[0]);
	point_input.push_back(end[1]);
	point_input.push_back(end[2]);
	line_pipeline(point_input, 'D');	
	
}	
/*


int REDirect::rd_lineset(const string & vertex_type, int nvertex, const float * vertex, int nseg, const int * seg)
{
	return 0;
}


*/   
   
   int REDirect::rd_point(const float p[3])
{
DB( "in point", 10);
//	vector<float> to_plot = point_pipeline(p[0], p[1], p[2]);
	float pigment[3];
	pigment[0] = active.r_scale;
	pigment[1] = active.g_scale;
	pigment[2] = active.b_scale;
//	set_pixel(to_plot[0], to_plot[1]);
//	rd_write_pixel(to_plot[0], to_plot[1], pigment);

	point p1;
	p1.push_back(p[0]);
	p1.push_back(p[1]);
	p1.push_back(p[2]);
	if(compute_point(p1) == -1)
		return RD_OK;
	p1 = point_pipeline(p1);
DB( p[0] << " " << p[1] << " " << p[2], 10);
DB( "set pixel", 10);


	return RD_OK;
}

int REDirect::rd_pointset(const string & vertex_type, int nvertex, const float * vertex)
{
	DB(vertex_type,0);
	DB(nvertex,0);
	DB(vertex,0);
	stringstream input_stringstream(vertex_type);


	vector<point> point_set;



	for(int lines = 0; lines < (nvertex*3); lines += 3){
		DB(vertex[lines], -2);
		point coord;
		coord.push_back(vertex[lines]);
		coord.push_back(vertex[lines+1]);
		coord.push_back(vertex[lines+2]);
		point_set.push_back(coord);
		DB(vertex[lines] << " " << vertex[lines+1] << " " << vertex[lines+2], -2);
			
		}
	for(auto p : point_set){
		point_pipeline(p);
	}


	return RD_OK;
}

int REDirect::rd_polyset(const string & vertex_type, int nvertex, const float * vertex, int nface,   const int * face)
{
	vector<point> point_set;

	DB(face,-2);


	for(int lines = 0; lines < (nvertex*3); lines += 3){
		DB(vertex[lines], 0);
		point coord;
		coord.push_back(vertex[lines]);
		coord.push_back(vertex[lines+1]);
		coord.push_back(vertex[lines+2]);
		point_set.push_back(coord);
		DB(vertex[lines] << " " << vertex[lines+1] << " " << vertex[lines+2], 0);
			
		}
	vector< vector <int> > faces;
	int p = 0;
	for(int lines2 = 0; lines2 < nface; lines2++){
		vector<int> corners;
		while(face[p] != -1){
			corners.push_back(face[p]);
			DB(face[p], -2);
			p++;
		}
		faces.push_back(corners);
		p++;
	}
	DB("exit setup",-2);
	point start;
	point p2;
	int vector_id;
	vector<int> current_face;
	for(int surface = 0; surface < nface; surface++){
	current_face = faces[surface];
	vector_id = current_face[0];
	start = point_set[vector_id];
	int npoints = current_face.size();
	vector_id = current_face[npoints-1];
	p2 = point_set[vector_id];
	line_pipeline(start, 'M');
	for(int line = 1; line < npoints; line++){
	vector_id = current_face[line];
	p2 = point_set[vector_id];
	DB("line " << line, -2);
	line_pipeline(p2, 'D');

	}
	
	line_pipeline(start, 'D');
	
	}



	return RD_OK;
}

int REDirect::rd_cone(float height, float radius, float thetamax)
{
	objects o;
	o.draw_cone(radius, height);
	return RD_OK;
}

int REDirect::rd_cube(void)
{
	objects o;
	o.draw_cube();
	return RD_OK;
}
int REDirect::rd_cylinder(float radius, float zmin, float zmax, float thetamax)
{
	objects o;
	o.draw_cylinder(radius, zmin, zmax);
	return RD_OK;
}

int REDirect::rd_disk(float height, float radius, float theta)
{
	objects o;
	o.draw_disk(radius, height);
	return RD_OK;
}

/*
int REDirect::rd_hyperboloid(const float start[3], const float end[3], float thetamax)
{
return 0;
}

int REDirect::rd_paraboloid(float rmax, float zmin, float zmax, float thetamax)
{
	return 0;
}
*/
int REDirect::rd_sphere(float radius, float zmin, float zmax, float thetamax)
{
	objects o;
	o.draw_sphere(radius);
	return RD_OK;
}
/*
int REDirect::rd_sqsphere(float radius, float north, float east, float zmin, float zmax, float thetamax)
{
return 0;
}

int REDirect::rd_sqtorus(float radius1, float radius2, float north, float east, float phimin, float phimax, float thetamax)
{
	return 0;
}

int REDirect::rd_torus(float radius1, float radius2, float phimin, float phimax, float thetamax)
{
	return 0;
}

int REDirect::rd_tube(const float start[3], const float end[3], float radius)
{
	return 0;
}

/i********************  Lighting & Shading  ***************************/

int REDirect::rd_background(const float color[])
{

//DB("rd_background");
	//probably do not need all this as background and active are already set on frame init to black and white
//	float default_c[] = {0,0,0};
//	if( color != default_c){
//cout << "ine if" << endl;
	float color_c[3];
	color_c[0] = color[0];
	color_c[1] = color[1];
	color_c[2] = color[2];
	rd_set_background(color_c);
	back_flag = 1;
	set_back(color_c);
//	}
cout << "end rd_background" << endl;
	return RD_OK;
}
   // red, green, blue by default
int REDirect::rd_color(const float color[])
{
//cout << "rd_color" << endl;
//default is already set up in initialization
		active.r_scale = color[0]; 
		active.g_scale = color[1]; 
		active.b_scale = color[2];

		//	}
	       	active = color_convert(active);
 //iout << active << endl;

	return RD_OK;
}
/*
int REDirect::rd_opacity(float opacity)
{
	return 0;
}

int REDirect::rd_emission(const float color[], float intensity)
{
	return 0;
}
*/
int REDirect::rd_fill(const float seed_point[3])
{
	float xs = seed_point[0], y = seed_point[1], xe = xs;
//	cout << "in fill" << endl;
	set_match(seed_point);
	flood_fill(xs, xe+1, y);
	 for(int x = 0; x < display_xSize; x++){
	                   for(int y = 0; y < display_ySize; y++){
//				  DB("cell " + to_string(x) + " " + to_string(y) + "color " << current.frame_image[x][y]);
			   }
	 }		   
	return 0;
}
/*
int REDirect::rd_surface(const string & shader_type)
{
	return 0;
}

int REDirect::rd_cone_light(const float pos[3], const float at[3], float theta_min, float theta_max, const float color[], float intensity)
{
	return 0;
}

int REDirect::rd_point_light(const float pos[3], const float color[], float intensity)
{
	return 0;
}

int REDirect::rd_far_light(const float dir[3], const float color[], float intensity)
{
	return 0;
}

int REDirect::rd_ambient_light(const float color[], float intensity)
{
	return 0;
}


int REDirect::rd_specular_color(const float color[], int exponent)
{
	return 0;
}

int REDirect::rd_k_ambient(float Ka)
{
	return 0;
}

int REDirect::rd_k_diffuse(float Kd)
{
	return 0;
}

int REDirect::rd_k_emission(float Ke)
{
	return 0;
}

int REDirect::rd_k_specular(float Ks)
{
	return 0;
}

int REDirect::rd_attribute_push(void)
{
	return 0;
}

int REDirect::rd_attribute_pop(void)
{
	return 0;
}

****************************   Mapping ******************************/
/*
int REDirect::rd_map_border(const string & map_type, const string & horizontal, const string & vertical)
{
	return 0;
}

int REDirect::rd_map_bound(const string & map_type, float s_min, float t_min, float s_max, float t_max)
{
	return 0;
}

int REDirect::rd_map_load(const string & filename, const string & label)
{
	return 0;
}

int REDirect::rd_map_sample(const string & map_type, const string & intra_level, const string & inter_level)
{
	return 0;
}

int REDirect::rd_map(const string & map_type, const string & label)
{
	return 0;
}

 /i****************************  Options  **********************************/
/*
int REDirect::rd_option_array(const string & name, int n, const float *values)
{
	return 0;
}

int REDirect::rd_option_bool(const string & name, bool flag)
{
	return 0;
}

int REDirect::rd_option_list(const string & name, int n, const string values [])
{
	return 0;
}

int REDirect::rd_option_real(const string & name, float value)
{
	return 0;
}

int REDirect::rd_option_string(const string & name, const string & value)
{
	return 0;
}

int REDirect::rd_custom(const string & label)
{
	return 0;
}

 REDirect::~REDirect(){}

 Some useful helper functions
 int get_vertex_size(const string & vertex_type)
{
	return 0;
}
// Returns the number of components in an attributed vertex type */
//

/*
int REDirect::flood_fill(float xs, float xe, float y){	
	float new_xs, new_xe;	
	DB("in flood");
        for( int x = xs; x < xe; x++){
		DB( "fill :" +  to_string(x) + " " + to_string(y));
		float point[3] = {x, y, 0.0};
		rd_point(point);
	}
*
	float y_down = y-1;
        for( new_xs= new_xe =xs; new_xe < xe; new_xs = new_xe){
		int span = find_span(new_xs, new_xe, y+1);
	        DB(to_string(span));
		
	        if(y+1 <= display_ySize && span == 1){
		        DB("DOWN");
		        flood_fill(new_xs, new_xe+1, y+1);
	                new_xe++;
	                }
	        else{
		        new_xe++;
		}
	 }
	int y_up = y-1;
	for( new_xs= new_xe =xs; new_xe < xe; new_xs = new_xe){
		if(y-1 >= 0 && find_span(new_xs, new_xe, y-1) < 0){
			DB("UP");
			flood_fill(new_xs, new_xe+1, y-1);
			new_xe++;
		}
         else{
	                 new_xe++;
                 }
          }

	return 0;
}
*/

#include "rd_direct.h"
#include <string>
#include "rd_display.h"
#include "frame.h"
#include "globals.h"
#include "rd_error.h"
#include <iostream>
#include <vector>
using std::string;
using std::to_string;
using std::cout;
using std::endl;

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

	return rd_er;

}

int REDirect::rd_world_end(void)
{
cout << "rd_world_end" << endl;	
	images.push_back(current);
	frame_ids.push_back(current_id);
	rd_disp_end_display();
	return RD_OK;
}

int REDirect::rd_frame_begin(int frame_no)
{
	
//	cout << "rd_frame_begin"  << endl;
	//this should change nothing
//	if(current_id != frame_no){
//		return-1;}
	current = set_frame(frame_no); //create a new frame in the globals
	current.set_id(frame_no);
	
	return RD_OK;
}

int REDirect::rd_frame_end(void)
{
cout << "rd_frame_end" << endl;	

//	if(current_id != frame_ids.back()){
//		cout << "in check" <<endl;
//	images.push_back(current);
//	frame_ids.push_back(current_id);
//	}
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
	return RD_OK;
}

int REDirect::rd_camera_at(const float atpoint[3])
{
	return RD_OK;
}

int REDirect::rd_camera_up(const float up[3])
{
	return RD_OK;
}
/*
int REDirect::rd_camera_fov(float fov)
{
	return 0;
}

int REDirect::rd_clipping(float znear, float zfar)
{
	return 0;
}
 
 /s**********************   Transformations **********************************/
/*
int REDirect::rd_translate(const float offset[3])
{
	return 0;
}

int REDirect::rd_scale(const float scale_factor[3])
{
	return 0;
}

int REDirect::rd_rotate_xy(float angle)
{
	return 0;
}

int REDirect::rd_rotate_yz(float angle)
{
	return 0;
}

int REDirect::rd_rotate_zx(float angle)
{
	return 0;
}

int REDirect::rd_matrix(const float * mat)
{
	return 0;
}
	       
int REDirect::rd_xform_push(void)
{
	return 0;
}

int REDirect::rd_xform_pop(void)
{
	return 0;
}

  /i**********************   Geometric Objects  *******************************/
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
	float x;
	float y;
	float z;
};

	float xcenter = center[0], ycenter = center[1], r = radius;
	int p = 1 - r;
	float x = 0 + xcenter, y= r + ycenter;
	float codinate[3] = {x,y, 0};
	vector<point> circle;
	while(x <= r + xcenter){
		point spot;
		spot.z = 0;
		
//		cout << "section 1" << endl;
		spot.x = x;
		spot.y = y;
//		cout << to_string(spot.x) + " " + to_string(spot.y) << endl;
		circle.push_back(spot);

		
//		cout << "section 2" << endl;
		spot.x = -x;
		spot.y = y;
	//	cout << to_string(spot.x) + " " + to_string(spot.y) << endl;
		circle.push_back(spot);

//		cout << "section 3" << endl;
		spot.x = x;
		spot.y = -y;
	//	cout << to_string(spot.x) + " " + to_string(spot.y) << endl;
		circle.push_back(spot);

//		cout << "section 4" << endl;
		spot.x = -x;
		spot.y = -y;
	//	cout << to_string(spot.x) + " " + to_string(spot.y) << endl;
		circle.push_back(spot);

//		cout << "section 5" << endl;
		spot.x = y;
		spot.y = x;
	//	cout << to_string(spot.x) + " " + to_string(spot.y) << endl;
		circle.push_back(spot);

//		cout << "section 6" << endl;
		spot.x = -y;
		spot.y = x;
	//	cout << to_string(spot.x) + " " + to_string(spot.y) << endl;
		circle.push_back(spot);

//		cout << "section 7" << endl;
		spot.x = y;
		spot.y = -x;
	//	cout << to_string(spot.x) + " " + to_string(spot.y) << endl;
		circle.push_back(spot);

//		cout << "section 8" << endl;
		spot.x = -y;
		spot.y = -x;
	//	cout << to_string(spot.x) + " " + to_string(spot.y) << endl;
		circle.push_back(spot);

		x++;
		if(p < 0)
			p += 2*x +1;
		else{
			p += 2*x-2*y +3;
			y--;
		}
	}
	for( auto a : circle)
		if( a.x >= 0 &&  a.y >= 0){
			float cord[3] = {a.x, a.y, a.z};
			rd_point(cord);
	//		cout << a.x << endl;			
		}

	return 0;
}


int REDirect::rd_line(const float start[3], const float end[3])
{
	int x1 = start[0], x2 =end[0];
	int y1 = start[1], y2 =end[1];
	int x0 = x1, y0 = y1;
	int xchan = x2-x1, ychan = y2-y1;
	if( xchan < 0){
	x2 = start[0]; 
	x1 =end[0];
	y2 = start[1];
       	y1 =end[1];
	
	xchan = x2-x1; 
	ychan = y2-y1;
	}
	
	int p0 = 2*ychan - xchan;

	int inc_plower = 2*ychan, inc_pupper = 2*ychan -2*xchan;
//	cout << "x1 = " + to_string(x1) + " x2 = " + to_string(x2) + " xchan = " + to_string(xchan) << endl;
//	cout << "y1 = " + to_string(y1) + " y2 = " + to_string(y2) + " ychan = " + to_string(ychan) << endl;
//	cout << "p0 = " + to_string(p0) + " plower = " + to_string(inc_plower) + " pupper = " + to_string(inc_pupper) << endl;
	while(x0 <= x2){

		float point[3] = {float(x0),float(y0), 0};
	//	cout << to_string(point[0]) + " " + to_string(point[1]) << endl;
		rd_point(point);
		x0++;
		if( p0 < 0)
			p0 += inc_plower;
		else{
			y0++;
			p0 += inc_pupper;
		}
	}	
//	cout << "in line" << endl;
	return RD_OK;
}
/*


int REDirect::rd_lineset(const string & vertex_type, int nvertex, const float * vertex, int nseg, const int * seg)
{
	return 0;
}


*/   
   
   int REDirect::rd_point(const float p[3])
{
//cout << "in point" << endl;
	int x = p[0];
	int y = p[1];
	float pigment[3];
	pigment[0] = active.r_scale;
	pigment[1] = active.g_scale;
	pigment[2] = active.b_scale;

	rd_write_pixel(x, y, pigment);
	return RD_OK;
}
/*
int REDirect::rd_pointset(const string & vertex_type, int nvertex, const float * vertex)
{
	return 0;
}

int REDirect::rd_polyset(const string & vertex_type, int nvertex, const float * vertex, int nface,   const int * face)
{
	return 0;
}

int REDirect::rd_cone(float height, float radius, float thetamax)
{
	return 0;
}

int REDirect::rd_cube(void)
{
	return 0;
}

int REDirect::rd_cylinder(float radius, float zmin, float zmax, float thetamax)
{
	return 0;
}

int REDirect::rd_disk(float height, float radius, float theta)
{
	return 0;
}

int REDirect::rd_hyperboloid(const float start[3], const float end[3], float thetamax)
{
return 0;
}

int REDirect::rd_paraboloid(float rmax, float zmin, float zmax, float thetamax)
{
	return 0;
}

int REDirect::rd_sphere(float radius, float zmin, float zmax, float thetamax)
{
	return 0;
}

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

cout << "rd_background" << endl;
	//probably do not need all this as background and active are already set on frame init
	//to black and white
	float default_c[] = {0,0,0};
	if( color != default_c){
	rd_set_background(color);
	}
	else
		rd_set_background(default_c);

	return RD_OK;
}
   // red, green, blue by default
int REDirect::rd_color(const float color[])
{
cout << "rd_color" << endl;
//default is already set up in initialization
		active.r_scale = color[0]; 
		active.g_scale = color[1]; 
		active.b_scale = color[2];

		//	}
	       	active = color_convert(active);
 cout << active << endl;

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
	int xs = seed_point[0], y = seed_point[1], xe;
	cout << "in fill" << endl;
	set_match(seed_point);
	flood_fill(xs, xs+1, y);	


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

 /****************************   Mapping ******************************/
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

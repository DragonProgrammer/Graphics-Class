#define DEBUG
#ifdef DEBUG
#include <iostream>
using std::cerr;
using std::end;
#define DB(x) do{cerr<<x<<endl;}while(0)
#else
#define DB(x) do{}while(0)
#endif

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
cout << "world begin" << endl;
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
DB("rd_world_end");	
//	int error1 = rd_disp_end_display();
//	DB(error1);
	int error = rd_frame_end();
//	DB(error);

	
	DB("end rd_world_end");	
//	exit(0);
	return RD_OK;
}

int REDirect::rd_frame_begin(int frame_no)
{
	DB("rd_frame_begin");
	//this should change nothing
//	if(current_id != frame_no){
//		return-1;}
	current = set_frame(frame_no); //create a new frame in the globals
	current.set_id(frame_no);
		
	return RD_OK;
}

int REDirect::rd_frame_end(void)
{
DB("rd_frame_end");	

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
		if(2*x*x < r*r+1){
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
	int x1 = start[0], x2 =end[0];
	int y1 = start[1], y2 =end[1];
	int xchan = x2-x1, ychan = y2-y1;
	if( xchan < 0){
		DB("flipped");
	x2 = start[0]; 
	x1 =end[0];
	y2 = start[1];
       	y1 =end[1];
	
	xchan = x2-x1; 
	ychan = y2-y1;
	
	
	}
	int p0 = 2*ychan - xchan;
	int inc_plower = 2*ychan, inc_pupper = 2*ychan -2*xchan;
	if(y2 < y1) {
		p0 = 2*xchan - ychan;
		inc_plower = 2*xchan;
		inc_pupper = 2*xchan - 2*ychan;
	}
	int x0 = x1, y0 = y1;
	
	DB("x1 = " + to_string(x1) + " x2 = " + to_string(x2) + " xchan = " + to_string(xchan));
	DB("y1 = " + to_string(y1) + " y2 = " + to_string(y2) + " ychan = " + to_string(ychan));
// 	DB("p0 = " + to_string(p0) + " plower = " + to_string(inc_plower) + " pupper = " + to_string(inc_pupper));
	while(x0 <= x2){

		float point[3] = {float(x0),float(y0), 0};
		rd_point(point);
		if(xchan > 0)
			x0++;
		if( p0 < 0)
			p0 += inc_plower;
		else{
			if(ychan<0) {
				y0--;
			//	DB("y is negitive");
				if(y0 < y2)
					break;
			}
			else{
				y0++;
			//	DB("y is positive");
				if(y0 > y2)
					break;
			}
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
//DB( "in point");
	int x = p[0];
	int y = p[1];
	float pigment[3];
	pigment[0] = active.r_scale;
	pigment[1] = active.g_scale;
	pigment[2] = active.b_scale;
	set_pixel(x, y);
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

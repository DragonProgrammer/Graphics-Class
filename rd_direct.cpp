#include "rd_direct.h"
#include <string>
#include "rd_display.h"
#include "frame.h"
#include "globals.cpp"
using std::string;

		/**********************   General functions  *******************************/
int REDirect :: rd_display(const string & name, const string & type,  const string & mode){
	return 0;
}

int REDirect::rd_format(int xresolution, int yresolution)
{
	return 0;
}

int REDirect::rd_world_begin(void)
{
	if( current_id != -1){
		images.push_back(current);
	}
	int new_id = get_next_Id();
	rd_disp_init_frame(new_id);
	current = set_frame(new_id);
	rd_frame_begin(new_id);
	return 0;
}

int REDirect::rd_world_end(void)
{
	images.push_back(current);
	frame_ids.push_back(current_id);
	return 0;
}

int REDirect::rd_frame_begin(int frame_no)
{
	//this should change nothing
	if(current_id != frame_no){
		return-1;}
	current.set_id(frame_no);
	
	return 0;
}

int REDirect::rd_frame_end(void)
{
	if(current_id != frame_ids.back()){
	images.push_back(current);
	frame_ids.push_back(current_id);
	}
	return 0;
}

int REDirect::rd_render_init(void)
{
return 0;
}/* Initialize renderer */

int REDirect::rd_render_cleanup(void)
{
	return 0;
}

 /**********************   Camera  ******************************************/

int REDirect::rd_camera_eye(const float eyepoint[3])
{
	return 0;
}

int REDirect::rd_camera_at(const float atpoint[3])
{
	return 0;
}

int REDirect::rd_camera_up(const float up[3])
{
	return 0;
}

int REDirect::rd_camera_fov(float fov)
{
	return 0;
}

int REDirect::rd_clipping(float znear, float zfar)
{
	return 0;
}
 
 /**********************   Transformations **********************************/

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

  /**********************   Geometric Objects  *******************************/

int REDirect::rd_line(const float start[3], const float end[3])
{
	return 0;
}

int REDirect::rd_point(const float p[3])
{
	
	return 0;
}

int REDirect::rd_circle(const float center[3], float radius)
{
	return 0;
}

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


int REDirect::rd_lineset(const string & vertex_type, int nvertex, const float * vertex, int nseg, const int * seg)
{
	return 0;
}


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

/********************  Lighting & Shading  ***************************/
int REDirect::rd_background(const float color[])
{
	return 0;
}
   // red, green, blue by default
int REDirect::rd_color(const float color[])
{
	return 0;
}

int REDirect::rd_opacity(float opacity)
{
	return 0;
}

int REDirect::rd_emission(const float color[], float intensity)
{
	return 0;
}

int REDirect::rd_fill(const float seed_point[3])
{
	return 0;
}

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

 /****************************  Options  **********************************/

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

/*/ Some useful helper functions
 int get_vertex_size(const string & vertex_type)
{
	return 0;
}
// Returns the number of components in an attributed vertex type */

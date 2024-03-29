#ifndef RD_ENGINE_DIRECT_H
#define RD_ENGINE_DIRECT_H
#include <string>
#include "error.h"
using std::string;
#include "rd_enginebase.h"
class REDirect : public RenderEngine
{
	public:

		  /**********************   General functions  *******************************/
int rd_display(const string & name, const string & type,  const string & mode);

int rd_format(int xresolution, int yresolution);

int rd_world_begin(void);

int rd_world_end(void);

int rd_frame_begin(int frame_no);

int rd_frame_end(void);
/*
int rd_render_init(void);  /i* Initialize renderer 

int rd_render_cleanup(void);
*/
 /**********************   Camera  ******************************************/

int rd_camera_eye(const float eyepoint[3]);

int rd_camera_at(const float atpoint[3]);

int rd_camera_up(const float up[3]);

int rd_camera_fov(float fov);

int rd_clipping(float znear, float zfar);
 
 /**********************   Transformations **********************************/

int rd_translate(const float offset[3]);

int rd_scale(const float scale_factor[3]);

int rd_rotate_xy(float angle);

int rd_rotate_yz(float angle);

int rd_rotate_zx(float angle);
/*
int rd_matrix(const float * mat);
*/	       
int rd_xform_push(void);

int rd_xform_pop(void);

  /**********************   Geometric Objects  *******************************/



/*
int rd_bezier_curve(const string & vertex_type, int degree, const float * vertex);

int rd_bezier_patch(const string & vertex_type, int u_degree, int v_degree, const float * vertex);

int rd_catmull_clark_sds(const string & vertex_type, float * coord, int nvertex, int * vertex_list, int nface, int * crease_list, int ncrease, float *sharpness);

*/
int rd_circle(const float center[3], float radius);

int rd_line(const float start[3], const float end[3]);

//int rd_lineset(const string & vertex_type, int nvertex, const float * vertex, int nseg, const int * seg);


int rd_point(const float p[3]);

int rd_pointset(const string & vertex_type, int nvertex, const float * vertex);

int rd_polyset(const string & vertex_type, int nvertex, const float * vertex, int nface,   const int * face);

int rd_cone(float height, float radius, float thetamax);

int rd_cube(void);

int rd_cylinder(float radius, float zmin, float zmax, float thetamax);

int rd_disk(float height, float radius, float theta);

/*
int rd_hyperboloid(const float start[3], const float end[3], float thetamax); 

int rd_paraboloid(float rmax, float zmin, float zmax, float thetamax);
*/
int rd_sphere(float radius, float zmin, float zmax, float thetamax);
/*
int rd_sqsphere(float radius, float north, float east, float zmin, float zmax, float thetamax); 

int rd_sqtorus(float radius1, float radius2, float north, float east, float phimin, float phimax, float thetamax);

int rd_torus(float radius1, float radius2, float phimin, float phimax, float thetamax);

int rd_tube(const float start[3], const float end[3], float radius);

/.********************  Lighting & Shading  ***************************/

int rd_background(const float color[]);
   // red, green, blue by default
int rd_color(const float color[]);
/*
int rd_opacity(float opacity);

int rd_emission(const float color[], float intensity);
*/
int rd_fill(const float seed_point[3]);
/*
int rd_surface(const string & shader_type);

int rd_cone_light(const float pos[3], const float at[3], float theta_min, float theta_max, const float color[], float intensity);

int rd_point_light(const float pos[3], const float color[], float intensity);

int rd_far_light  (const float dir[3], const float color[], float intensity);

int rd_ambient_light(const float color[], float intensity);


int rd_specular_color(const float color[], int exponent);

int rd_k_ambient(float Ka);

int rd_k_diffuse(float Kd);

int rd_k_emission(float Ke);

int rd_k_specular(float Ks);
*/
//int rd_attribute_push(void);

//int rd_attribute_pop(void);
/*
 /.****************************   Mapping ******************************/
/*
int rd_map_border(const string & map_type, const string & horizontal, const string & vertical);

int rd_map_bound(const string & map_type, float s_min, float t_min, float s_max, float t_max);

int rd_map_load(const string & filename, const string & label);

int rd_map_sample(const string & map_type, const string & intra_level, const string & inter_level);

int rd_map(const string & map_type, const string & label);

 /.****************************  Options  **********************************/
/*
int rd_option_array(const string & name, int n, const float *values);

int rd_option_bool(const string & name, bool flag);

int rd_option_list(const string & name, int n, const string values []);

int rd_option_real(const string & name, float value);

int rd_option_string(const string & name, const string & value);

int rd_custom(const string & label);

~REDirect();
*/
//int flood_fill(float xs, float xe, float y);
 };

// Some useful helper functions
//int get_vertex_size(const string & vertex_type);
// Returns the number of components in an attributed vertex type


 #endif /* RD_BASE_ENGINE_H */

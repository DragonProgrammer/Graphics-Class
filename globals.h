#ifndef Globals_H
#define Globals_H
#include "frame.h"
//#include "rd_display.h"
#include <vector>
#include "color.h"
using std::vector;

extern Frame current;
extern vector<Frame> images;

extern int current_id;  // stores curutent frame id

extern vector<int> frame_ids;

extern color background;
extern color active;
extern color match;
extern int back_flag;
extern int active_flag;


extern void set_active(float color[3]);
extern void set_back(float color[3]);
int get_next_id();
extern Frame set_frame(int id);
extern color get_color(int x, int y);
extern void set_pixel(int x, int y, float z);
extern void set_frame_image();
extern color color_scale(color digits_input);
extern color color_convert(color scale_input);

extern void set_match(const float point[3]);
extern int check_color(float point[3]);
extern int find_span(float &new_xs, float &new_xe, float y);
extern int flood_fill(float xs, float xe, float y);

/******************************Frome assign 2****************/
 
typedef vector< vector<float> > xform;
typedef vector<float> point;

extern  double Camera_View;// = 90;
extern  xform current_xform;// transforms.identity();
extern  point camera_eye;// {0,0,0};
extern  float camera_near;// 1.0;
extern  float camera_far;// 1000000,000.0;
extern  point camera_up;// {0, 1.0,
extern  point at_point; // {0, 0, -1.0};

extern xform W2C;
extern xform C2C;
extern xform C2D;
extern vector<xform> xform_stack;

extern xform pop();
extern void push(xform x1);

extern void draw_depth(point p);
extern int draw_depth_reject;
extern vector<point> rejects;
extern point point_pipeline(point p);
extern void line_pipeline(point p1, char FLAG);

/******************************assign 3****************/
extern vector<float> BC0, BC1;
//extern int[] borders_crossed[6];
extern vector<int> code_vector1, code_vector2;
extern float clip_amount1, clip_amount2;
extern point old_point, new_point;

extern point p1_before, p1_after, p2_before, p2_after;

extern int compute_point(point in_question);
extern int compute_point(vector<int> inquestion);
extern int clip_line(point input);
extern vector<float> compute_boundary_corridinate(point p);
extern vector<int> compute_boundary_code(vector<float> input);
extern int viewable(vector<int> b1, vector<int> b2);
extern void compute_new_points();
#endif


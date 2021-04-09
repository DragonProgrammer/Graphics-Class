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
extern void set_pixel(int x, int y);
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

extern point point_pipeline(float x, float y, float z);
extern void line_pipeline(point p1, char FLAG);


#endif


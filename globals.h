#ifndef Globals_H
#define Globals_H
#include "frame.h"
//#include "rd_display.h"
#include <vector>
#include "color.cpp"
using std::vector;

extern Frame current;
extern vector<Frame> images;
extern int current_id;
extern vector<int> frame_ids;
extern color background;
extern color active;
extern void set_active(float color[3]);
extern void set_back(float color[3]);
int get_next_id();
extern Frame set_frame(int id);
extern color get_color(int x, int y);
extern void set_pixel(int x, int y);
extern void set_frame_image();
extern color color_scale(color digits_input);
extern color color_convert(color scale_input);
#endif


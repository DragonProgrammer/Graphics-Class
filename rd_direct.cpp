#include "rd_direct.h"
#include "pnm_display.cpp"

int rd_display(const string& name, const string& type, const string& mode);

int rd_format(int xresolution, int yresolution);

int rd_world_begin(void);

int rd_world_end(void);

int rd_frame_begin(int frame_no);

int rd_frame_end(void);

int rd_point(const float p[3]);

int rd_circle(const float center[3], float radius);

int rd_line(const float start[3], const float end[3]);

int rd_background(const float color[]);

int rd_color(const float color[]);

int rd_fill(const float seed_point[3]);

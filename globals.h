#ifndef Globals_H
#define Globals_H
#include "frame.h"
//#include "rd_display.h"
#include <vector>
using std::vector;

extern Frame current;
extern vector<Frame> images;
extern int current_id;
extern vector<int> frame_ids;

extern int get_next_id();
extern Frame set_frame(int id);

#endif


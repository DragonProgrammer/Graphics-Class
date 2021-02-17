#include "frame.h"
int Frame::get_id(){
	return frame_id;
}

void Frame::set_id(int id){
	frame_id = id;
}

Frame::Frame(color temp){
	frame_id = 0;
	
	frame_image= { {temp} };
}



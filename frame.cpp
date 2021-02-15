#include "frame.h"
/*

void Frame::set_size(int x, int y){
	size_X = x;
	size_Y= y;
}
/*
void Frame::set_frame_image(){

	for(int x = 0; x < size_X; x++){
		for(int y = 0; y < size_Y; y++){
			frame_image[x][y]=back_color;
		}
	}
}
*/
int Frame::get_id(){
	return frame_id;
}

void Frame::set_id(int id){
	frame_id = id;
}




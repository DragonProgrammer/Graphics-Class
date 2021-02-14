#include "frame.h"

void Frame::set_back(int color[3]){
	back_color[3] = color[3];
}

void Frame::set_active(int color[3]){
	act_color[3] = color[3];
}

void Frame::set_size(int x, int y){
	size_X = x;
	size_Y= y;
}

void Frame::set_frame_image(){
//	frame_image = new int[][size_Y][3];
	int x[];
	int y[][3];

	for(int x = 0; x < size_X; x++){
		for(int y = 0; y < size_Y; y++){
			frame_image[x][y]=back_color;
		}
	}
}

int Frame::get_id(){
	return frame_id;
}

void Frame::set_id(int id){
	frame_id = id;
}

int Frame::get_color(char select){
	if(select == 'B')
		return back_color[3];
	else
		return act_color[3];
}

void Frame::set_pixel(int x, int y){
	if ( x > size_X-1 || y > size_Y-1)
		return;
	frame_image[x][y] = active_color;
}



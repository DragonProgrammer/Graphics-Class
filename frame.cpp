#include "frame.h"

void Frame::set_back(int color[3]){
	back_color.r = color[0];
	back_color.g = color[1];
	back_color.b = color[2];
}

void Frame::set_active(int color[3]){
	active_color.r = color[0];
	active_color.g = color[1];
	active_color.b = color[2];
}

void Frame::set_size(int x, int y){
	size_X = x;
	size_Y= y;
}

void Frame::set_frame_image(){
//	frame_image = new int[][size_Y][3];
//	int x[];
//	int y[][3];

	for(int x = 0; x < size_X; x++){
		for(int y = 0; y < size_Y; y++){
			frame_image[x][y]=back_color;
		//	frame_image[x][y][1]=back_color[1];
		//	frame_image[x][y][2]=back_color[2];
		}
	}
}

int Frame::get_id(){
	return frame_id;
}

void Frame::set_id(int id){
	frame_id = id;
}

color Frame::get_color(){
	return active_color;
}

color Frame::get_color(int x, int y){
	color pixel_color = frame_image[x][y];
	return pixel_color;
}

void Frame::set_pixel(int x, int y){
	if ( x > size_X-1 || y > size_Y-1)
		return;
	frame_image[x][y]=active_color;
//	frame_image[x][y][1]=act_color[1];
//	frame_image[x][y][2]=act_color[2];
}



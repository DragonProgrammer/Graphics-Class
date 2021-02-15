#include "pnm_display.h"
#include "rd_display.h"
#include "globals.h"
#include "frame.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
//using std::ofsteam;
using namespace std;
using std::to_string;
int pnm_init_display(void){
	 current = set_frame(get_next_id());
	 
	 return 0;
 }

int pnm_end_display(void){
	images.clear(); // clear images vector
	frame_ids.clear();	
	return 0;
		 }

 int pnm_init_frame(int){
	current.frame_image.clear();
	 return 0;
	 }

 int pnm_end_frame(void){
	 ofstream pnm_file;
	 vector<string> lines;
	 string filename = "pnm" + to_string(current_id) + ".txt";

	 string title_Line = "P3";
	 string size_line = to_string(display_xSize) + " " + to_string(display_ySize);
	 string intensity_line = "255";
	 lines.push_back(title_Line);
	 lines.push_back(size_line);
	 lines.push_back(intensity_line);
	 for(int x = 0; x < display_xSize; x++){
		 string line = "";
	 	for(int y = 0; y < display_ySize; y++)
		{
			color pixel_color = current.frame_image[x][y];
			line = line + to_string(pixel_color.r) + " ";
			line = line + to_string(pixel_color.g) + " ";
			line = line + to_string(pixel_color.b) + " ";
		}
		lines.push_back(line);
	 }
 



	 return 0;
	 }

 int pnm_write_pixel(int x, int y, const float rgb []){
	// the following implemplemetation assumes that you want to prezervew active but want this point to be different
	color temp = active;
	active.r =rgb[0];
	active.g = rgb[1];
	active.b = rgb[2];
	set_pixel(x,y);
	active = temp;
	 
	 return 0;
 }

 int pnm_read_pixel(int x, int y, float rgb []){
	 return 0;
	 }

 int pnm_set_background(const float rgb []){
	 background.r= int(rgb[0]*255);
	 background.g= int(rgb[1]*255);
	 background.b= int(rgb[2]*255);
	 return 0;
	 }

 int pnm_clear(void){
	 return 0;
	 }


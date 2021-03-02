#include "pnm_display.h"
#include "rd_display.h"
#include "globals.h"
#include "frame.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "rd_error.h"
//using std::ofsteam;
using namespace std;
using std::to_string;
int pnm_init_display(void){
//	cout << "pnm_nit_display \n"<< endl;
	// current = set_frame(get_next_id());
	 
	 return RD_OK;
 }

int pnm_end_display(void){
//	cout << "pnm_end_display \n";
//	images.clear(); // clear images vector
//	frame_ids.clear();	
//	current.frame_image.clear();
	return RD_OK;
		 }

 int pnm_init_frame(int){
//	cout << "pnm_nit_frame \n";
//	current.frame_image.clear();
	 return RD_OK;
	 }

 int pnm_end_frame(void){
//	cout << "pnm_end_frame \n"<< endl;
	 ofstream pnm_file;
	 string filename = "pnm" + to_string(current_id) + ".ppm";
	 string line = "P3";
 
	pnm_file.open(filename);
		pnm_file << line << '\n';
	 line = to_string(display_xSize) + " " + to_string(display_ySize);
		pnm_file << line << '\n';
	 line = "255";
		pnm_file << line << '\n';
	 
	color pixel_color;
	 
		for(int x = 0; x < display_xSize; x++){
		 string line = "";
	 	for(int y = 0; y < display_ySize; y++)
		{
			pixel_color = current.frame_image[x][y];
			line = line + to_string(pixel_color.r) + " ";
			line = line + to_string(pixel_color.g) + " ";
			line = line + to_string(pixel_color.b) + " ";
		}
		pnm_file << line << '\n';
	 }
	pnm_file.close();

	 return RD_OK;
	 }

 int pnm_write_pixel(int x, int y, const float rgb []){
//	cout << "pnm_write_pixel \n"<< endl;
	set_pixel(x,y);
	 
	 return RD_OK;
 }

 int pnm_read_pixel(int x, int y, float rgb []){
	 return 0;
	 }

 int pnm_set_background(const float rgb []){
//	cout << "set_background \n";
	 background.r= int(rgb[0]*255);
	 background.g= int(rgb[1]*255);
	 background.b= int(rgb[2]*255);
	 return RD_OK;
	 }

 int pnm_clear(void){
	 return RD_OK;
	 }


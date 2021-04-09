#define DEBUG
#ifdef DEBUG
#include <iostream>
using std::cerr;
using std::endl;
#define DB_FLAG 1
#define DB(x,level) if(DB_FLAG > level) do{cerr << x << endl;}while(0)
#else
#define DB(x,level) if(DB_FLAG > level) do{}while(0)
#endif



#include "objects.h"
#include <vector>
#include "frame.h"
#include "globals.h"
#include <string>
using std::to_string;
using std::vector;

typedef vector<float> point;
void objects::draw_cube() {
	point v1, v2, v3, v4, v5, v6, v7, v8;
	v1 = {-1, -1, -1};
	v2 = {-1, -1, 1};
	v3 = {0, 1, 0};
	v4 = {1, 0, 0};
	v5 = {1, 1, 0};
	v6 = {0, 1, 1};
	v7 = {1, 0, 1};
	v8 = {1, 1, 1};

	// faces
	// v1, v2, v3, v6 i
	// v1, v2, v7, v4 i
	// v1, v4, v5, v3
	// v2, v7, v8, v6
	// v4, v7, v8, v5 i
	// v3, v6, v8, v5 i

	// edges
	// v1 - v2
	// v1 - v3
	// v1 - v4
	// v2 - v6
	// v2 - v7
	// v3 - v5
	// v3 - v6
	// v4 - v5
	// v4 - v7
	// v5 - v8
	// v6 - v8
	// v7 - v8
	float color[3];
	color[0] = .5;
	color[1] = .5;
	color[2] = .5;
//	set_active(color);
	line_pipeline(v1, 'M');
		line_pipeline(v2, 'D');
//		line_pipeline(v6, 'D');
//		line_pipeline(v3, 'D');
//	line_pipeline(v1, 'D');

	color[0] = .25;
	color[1] = .25;
	color[2] = .25;
//	set_active(color);
//	line_pipeline(v6, 'M');
//	line_pipeline(v8, 'D');
//	line_pipeline(v5, 'D');
//	line_pipeline(v3, 'D');
//	line_pipeline(v6, 'D');

	color[0] = .75;
	color[1] = .75;
	color[2] = .75;
//	set_active(color);
//	line_pipeline(v5, 'M');
//	line_pipeline(v4, 'D');
//	line_pipeline(v7, 'D');
//	line_pipeline(v8, 'D');
//	line_pipeline(v5, 'D');

	color[0] = 1;
	color[1] = 1;
	color[2] = .5;
//	set_active(color);
//	line_pipeline(v4, 'M');
//	line_pipeline(v1, 'D');
//	line_pipeline(v2, 'D');
//	line_pipeline(v7, 'D');
//	line_pipeline(v4, 'D');
	
	color[0] = 1;
	color[1] = .5;
	color[2] = 1;
//	set_active(color);
//	DB("\nstore V1",-1);
	
//	line_pipeline(v1, 'M');
//	DB("\nV1 to V3",-1);
	color[0] = .5;
	color[1] = .5;
	color[2] = .5;
//	set_active(color);
//	line_pipeline(v3, 'D');

//	DB("\nV3 to V5",-1);
	color[0] = .25;
	color[1] = .25;
	color[2] = .25;
//	set_active(color);
//	line_pipeline(v5, 'D');
	
//	DB("\nV5 to V4 yellow",-1);
	color[0] = 1;
	color[1] = 1;
	color[2] = .5;
//	set_active(color);
//	line_pipeline(v4, 'D');
	
//	DB("\nV4 to V1",-1);
	color[0] = .75;
	color[1] = .75;
	color[2] = .75;
//	set_active(color);
//	line_pipeline(v1, 'D');
}

 void objects::draw_sphere(int radius){
 	struct point {
      		float point_x;
      		float point_y;
      		float point_z;
       };

	float xcenter = 0, ycenter = 0, r = radius;
	int p = 1 - r;
	float x = 0, y = r;
	float codinate[3] = {x, y, 0};
//DB("center " + to_string(xcenter) + " " + to_string(ycenter),10);
	vector<point> circle;
  	while (x <= r) {
      		if (x * x <= y * y) {
               		point spot;
                 	spot.point_z = 0; // for xy plane
               		spot.point_x = xcenter + x;
                    	spot.point_y = ycenter + y;
//DB( "section 1 " << spot.point_z << " " << spot.point_y,10);
          	        circle.push_back(spot);
                	spot.point_x = xcenter - x;
                      	spot.point_y = ycenter + y;
//DB( "section 2 " << spot.point_z << " " << spot.point_y,10);
                        circle.push_back(spot);
        		spot.point_x = xcenter + x;
        		spot.point_y = ycenter - y;
//DB( "section 3 " << spot.point_z << " " << spot.point_y,10);
               		circle.push_back(spot);
                  	spot.point_x = xcenter - x;
                     	spot.point_y = ycenter - y;
//DB( "section 4 " << spot.point_z << " " << spot.point_y,10);
                        circle.push_back(spot);
		        spot.point_x = xcenter + y;
                	spot.point_y = ycenter + x;
//DB( "section 5 " << spot.point_z << " " << spot.point_y,10);
	                circle.push_back(spot);
        	        spot.point_x = xcenter - y;
                	spot.point_y = ycenter + x;
//DB( "section 6 " << spot.point_z << " " << spot.point_y,10);
                        circle.push_back(spot);
	                spot.point_x = xcenter + y;
        	        spot.point_y = ycenter - x;
//DB( "section 7 " << spot.point_z << " " << spot.point_y,10);
                	 circle.push_back(spot);
                	 spot.point_x = xcenter - y;
               		 spot.point_y = ycenter - x;
//DB( "section 8 " << spot.point_z << " " << spot.point_y,10);
                 	 circle.push_back(spot);

//DB("ZX plane",10); 

			 spot.point_y = 0; // for xy plane
               		spot.point_x = xcenter + x;
                    	spot.point_z = ycenter + y;
//DB( "section 1 " << spot.point_x << " " << spot.point_z,10);
          	        circle.push_back(spot);
                	spot.point_x = xcenter - x;
                      	spot.point_z = ycenter + y;
//DB( "section 2 " << spot.point_x << " " << spot.point_z,10);
                        circle.push_back(spot);
        		spot.point_x = xcenter + x;
        		spot.point_z = ycenter - y;
//DB( "section 3 " << spot.point_x << " " << spot.point_z,10);
               		circle.push_back(spot);
                  	spot.point_x = xcenter - x;
                     	spot.point_z = ycenter - y;
//DB( "section 4 " << spot.point_x << " " << spot.point_z,10);
                        circle.push_back(spot);
		        spot.point_x = xcenter + y;
                	spot.point_z = ycenter + x;
//DB( "section 5 " << spot.point_x << " " << spot.point_z,10);
	                circle.push_back(spot);
        	        spot.point_x = xcenter - y;
                	spot.point_z = ycenter + x;
//DB( "section 6 " << spot.point_x << " " << spot.point_z,10);
                        circle.push_back(spot);
	                spot.point_x = xcenter + y;
        	        spot.point_z = ycenter - x;
//DB( "section 7 " << spot.point_x << " " << spot.point_z,10);
                	 circle.push_back(spot);
                	 spot.point_x = xcenter - y;
               		 spot.point_z = ycenter - x;
//DB( "section 8 " << spot.point_x << " " << spot.point_z,10);
                 	 circle.push_back(spot);
//DB("YZ plane",10); 

			 spot.point_x = 0; // for xy plane
               		spot.point_z = xcenter + x;
                    	spot.point_y = ycenter + y;
//DB( "section 1 " << spot.point_z << " " << spot.point_y,10);
          	        circle.push_back(spot);
                	spot.point_z = xcenter - x;
                      	spot.point_y = ycenter + y;
//DB( "section 2 " << spot.point_z << " " << spot.point_y,10);
                        circle.push_back(spot);
        		spot.point_z = xcenter + x;
        		spot.point_y = ycenter - y;
//DB( "section 3 " << spot.point_z << " " << spot.point_y,10);
               		circle.push_back(spot);
                  	spot.point_z = xcenter - x;
                     	spot.point_y = ycenter - y;
//DB( "section 4 " << spot.point_z << " " << spot.point_y,10);
                        circle.push_back(spot);
		        spot.point_z = xcenter + y;
                	spot.point_y = ycenter + x;
//DB( "section 5 " << spot.point_z << " " << spot.point_y,10);
	                circle.push_back(spot);
        	        spot.point_z = xcenter - y;
                	spot.point_y = ycenter + x;
//DB( "section 6 " << spot.point_z << " " << spot.point_y,10);
                        circle.push_back(spot);
	                spot.point_z = xcenter + y;
        	        spot.point_y = ycenter - x;
//DB( "section 7 " << spot.point_z << " " << spot.point_y,10);
                	 circle.push_back(spot);
                	 spot.point_z = xcenter - y;
               		 spot.point_y = ycenter - x;
//DB( "section 8 " << spot.point_z << " " << spot.point_y,10);
                 	 circle.push_back(spot);
                }
      x++;
       if (p < 0)
                 p += 2 * x + 1;
        else {
                  p += 2 * x - 2 * y + 3;
                   y--;
            }
 }

	for (auto a : circle)
		if (a.point_x >= 0 && a.point_y >= 0) {
//		      DB(to_string(a.point_x) << " " << to_string(a.point_y),10);
		                            //    rd_point(cord);
					    point_pipeline(a.point_x, a.point_y, a.point_z);
			                  }
			   
			     }






// void objects::draw_cone();
// void objects::draw_cylinder();
// void objects::draw_disk();

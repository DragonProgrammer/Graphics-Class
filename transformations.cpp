#include "Debug.h"
#include <vector>
#include <cmath>
#include <math.h>
#include "globals.h"
#include "iostream"
#include "transformations.h"
using std::sqrt;
using std::vector;
using std::cout;
using std::endl;
using std::cos;
using std::sin;
using std::tan;
typedef vector< vector<float> > xform; //4X4 matrix
typedef vector<float> point; // 3 item vector

vector< xform > transformation_stack;
	


xform transforms::identity(){
		return{ {1.0, 0, 0, 0},
		       	{0, 1.0, 0, 0},
			{0, 0, 1.0, 0},
			{0, 0, 0, 1.0} }; }

xform transforms::multiply(xform x1, xform x2){
//		cout << "In multipley" << endl;
		xform prod = { {0, 0, 0, 0},
				{0, 0, 0, 0},
				{0, 0, 0, 0},
				{0, 0, 0, 0} };
//		cout << "Created blank matrix" << endl;
		for(int row =0; row < 4; row++){
			for( int col = 0; col < 4; col++){
				for( int elem = 0; elem < 4; elem++){
//		cout << "In loop" << endl;
					float elem1 = x1[row][elem];
//		cout << row << " " << elem << " " << elem1 << endl;
					float elem2 = x2[elem][col];
//		cout <<  elem2 << endl;
//cout << "prod before " << prod[row][col] << "  +" << elem1 << " * " << elem2 << " = " <<  elem1*elem2 << endl;
					prod[row][col] += elem1*elem2;
//		cout << "Did math" << endl;
				}
			}
		}
	return prod;
	}
			
	
point transforms::multiply_point(xform x1,  point a){
		point after = {0, 0, 0, 0};
		for(int row =0; row < 4; row++){
			for(int elem =0; elem < 4; elem++){
//				cout << row << " " << elem << " " << x1[row][elem] << "     ";
//				cout << "after before " << after[row] << "  +" <<x1[row][elem] << " * " << a[elem] << " = " <<  a[elem]*x1[row][elem] << endl;
			
				after[row] += a[elem]*x1[row][elem];
			}
	//		cout << endl;
		}
//		cout << endl;
		return after;
	}
		
	

xform transforms::translate( double x, double y, double z){
		xform tmatrix = identity();
		tmatrix[0][3] = x;
		tmatrix[1][3] =y;
		tmatrix[2][3] =z;
	return tmatrix;
	}
	
xform transforms::scale(double x, double y, double z){
		xform smatrix = identity();
		smatrix[0][0] = x;
		smatrix[1][1] =y;
		smatrix[2][2] =z;
	return smatrix;
	}

	


xform transforms::rotate_xy(double theta){
		xform rmatrix = identity();
		theta = theta*(3.1415926/180);
		
		
		rmatrix[0][0] = cos(theta);
		rmatrix[1][1] = cos(theta);
		rmatrix[0][1] = -sin(theta);
		rmatrix[1][0] = sin(theta);
	//	if(theta < 0){
	//	rmatrix[0][1] = sin(theta);
	//	rmatrix[1][0] = -sin(theta);
	//	}
			
	return rmatrix;
	}


xform transforms::rotate_yz(double theta){
		xform rmatrix = identity();
		theta = theta*(3.1415926/180);
		rmatrix[2][2] = cos(theta);
		rmatrix[1][1] = cos(theta);
		rmatrix[2][1] = sin(theta);
		rmatrix[1][2] = -sin(theta);
	//	if(theta < 0){
	//	rmatrix[2][1] = -sin(theta);
	//	rmatrix[1][2] = sin(theta);
	//	}
	return rmatrix;
	}

xform transforms::rotate_xz(double theta){
		xform rmatrix = identity();
		theta = theta*(3.1415926/180);
		rmatrix[0][0] = cos(theta);
		rmatrix[2][2] = cos(theta);
		rmatrix[0][2] = sin(theta);
		rmatrix[2][0] = -sin(theta);
	//	if(theta < 0){
	//	rmatrix[0][2] = -sin(theta);
	//	rmatrix[2][0] = sin(theta);
	//	}
	return rmatrix;
	}


xform transforms::world_to_camera( point eye, point at, vector<float> up){
		cout << "in world to camera" << endl;
		xform T1 = identity();
		T1[0][3] = -eye[0];
		T1[1][3] = -eye[1];
		T1[2][3] = -eye[2];
	//	cout << "Made translation matrix" << endl;

		while(1==0){
		for(int row =0; row < 4; row++){
			for( int col = 0; col < 4; col++){
				float elem1 = T1[row][col];
//				cout <<  elem1 << "      ";
			}
//			cout << endl;
		}
	//	cout << "\nEye point" << endl;
	//	for (auto v : eye){
	//		cout << v << "  ";
	//	}
	//	cout << "\nAt point" << endl;
	///	for (auto v : at){
	//		cout << v << "  ";
	//	}

	//	cout << "\nCamera up" << endl;
	//	for (auto v : camera_up){
	//		cout << v << "  ";
	//	}

	}
		// get A
		vector<float> A;
		A.push_back(at[0]-eye[0]);
		A.push_back(at[1]-eye[1]);
		A.push_back(at[2]-eye[2]);
		if(at.size() > 3)
			cout << "at has more than 3 elements" << endl;
		
//		cout << "Made A" << endl;
	//	cout << "\nMade A" << endl;
	//	for (auto v : A){
	//		cout << v << "  ";
	//	}
		//Normaliz A
		float W = 0;
		W += A[0]*A[0];
		W += A[1]*A[1];
		W += A[2]*A[2];
		W = sqrt(W);
		if(W == 0) {W = 1;}
		A[0] = A[0]/W;
		A[1] = A[1]/W;
		A[2] = A[2]/W;
		A.push_back(1.0);
	//	cout << "\nNormalized  A" << endl;
	//	for (auto v : A){
	//		cout << v << " ";
	//	}
		cout << endl;
		//Get V
		vector<float> V;
		float result;
		result = ((A[1]*camera_up[2])-(A[2]*camera_up[1]));

		V.push_back(result);
		result = -((A[0]*camera_up[2])-(A[2]*camera_up[0]));

		V.push_back(result);
		result = ((A[0]*camera_up[1])-(A[1]*camera_up[0]));
		V.push_back(result);
		if(up.size() > 3)
			cout << "up has more than 3 elements" << endl;
		V.push_back(1);
	//	cout << "\nmade V" << endl;
	//	for (auto v : V){
	//		cout << v << "  ";
	//	}
		cout << endl;

		//Normalize V
		W = 0;
		W += V[0]*V[0];
		W += V[1]*V[1];
		W += V[2]*V[2];
		W = sqrt(W);
		if(W == 0) {W = 1;}
		V[0] = V[0]/W;
		V[1] = V[1]/W;
		V[2] = V[2]/W;
	//	cout << "\nNormalized  V" << endl;
	//	for (auto v : V){
	//		cout << v << "  ";
	//	}
		cout << endl;

		//Get U
		vector<float> U;
		result = ((V[1]*A[2])-(V[2]*A[1]));

		U.push_back(result);
		result = -((V[0]*A[2])-(V[2]*A[0]));

		U.push_back(result);
		result = ((V[0]*A[1])-(V[1]*A[0]));
		U.push_back(result);
		if(up.size() > 3)
			cout << "up has more than 3 elements" << endl;
		U.push_back(1);

		cout << "Made  U" << endl;
		for (auto v : U){
			cout << v << "  ";
		}
		//Normalize U
		W = 0;
		W += U[0]*U[0];
		W += U[1]*U[1];
		W += U[2]*U[2];
		W = sqrt(W);
		if(W == 0) {W = 1;}
		U[0] = U[0]/W;
		U[1] = U[1]/W;
		U[2] = U[2]/W;
	//	cout << "\nNormalized  U" << endl;
	//	for (auto v : U){
	//		cout << v << "  ";
	//	}
		cout << endl;


		xform R1 = identity();
		R1[0][0]= V[0];
		R1[0][1] =V[1];
		R1[0][2] =V[2];
		
		R1[1][0] =U[0];
		R1[1][1] =U[1];
		R1[1][2] =U[2];
		
		R1[2][0] =A[0];
		R1[2][1] =A[1];
		R1[2][2] =A[2];
//		cout << "\nMade Rotation" << endl;

		for(int row =0; row < 4; row++){
			for( int col = 0; col < 4; col++){
				float elem1 = R1[row][col];
//				cout <<  elem1 << "      ";
			}
//			cout << endl;
		}
		xform end = multiply(T1,R1);
//		 cout << "multiplied matrices" << endl;
		for(int row =0; row < 4; row++){
			for( int col = 0; col < 4; col++){
				float elem1 = end[row][col];
//				cout <<  elem1 << "      ";
			}
//			cout << endl;
		}

		return multiply(R1,T1);
	}








	
xform transforms::camera_to_clip( double fov, double near, double far, double aspect){
		xform c = identity();
//		cout << "aspect " << aspect << "     field of view " << fov << endl;
//		cout << "Near " << near << "     far " << far << endl;
		float degrees = fov/2;
		float pi = 3.1415926;
		float radian = degrees * (pi/180);
		c[0][0] = 1/((2*aspect)*tan(radian));
	//	c[0][0] = .75;
		c[0][2] = .5;
		c[1][1] = 1/(2*tan(radian));
		c[1][2] = .5;
		c[2][2] = far/(far-near);
		c[2][3] = (-(far*near))/(far-near);
		c[3][3] = 0;
		c[3][2] = 1;
		return c;
	}



	xform transforms::clip_to_device( int width, int height){
		width = width- .001;
		height = height- .001;
		xform cmatrix = identity();
		cmatrix[0][0] = float(width);
		cmatrix[1][1] = float(-height);
		cmatrix[1][3] = float(height);
	return cmatrix;
	}





	




	


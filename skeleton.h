
#include <windows.h> 
#include "NuiApi.h"
#include <opencv2\opencv.hpp>

#include"VerMat.h"

#include <stdlib.h>
#include<iostream>
#include<fstream>
#include<vector>
using namespace std;
using namespace cv;

#define COLOR_WIDTH     640  
#define COLOR_HIGHT     480  
#define DEPTH_WIDTH     320  
#define DEPTH_HIGHT     240  
#define SKELETON_WIDTH 640  
#define SKELETON_HIGHT 480  
#define CHANNEL         3  

Vertex Distance(Vertex p1, Vertex p2);
Vertex unifyvector(Vertex v);
Matrix Rotation(Vertex p1, Vertex p2, Vertex Dis);
Matrix Trans(Vertex p1);
Matrix Transback(Vertex p1);
//ofstream ffout;
//char fn[] = "hi1111.txt";
float eLenth(Vertex V);
void drawSkeleton(Mat &image, CvPoint pointSet[], int whichone);
class skeleton
{

public:
	HANDLE skeletonEvent;
	HRESULT hr;
	CvPoint skeletonPoint[NUI_SKELETON_COUNT][NUI_SKELETON_POSITION_COUNT];
	
	Matrix KK[20];
	Matrix TT[20];
	Matrix T[20];
	bool tracked[NUI_SKELETON_COUNT];
	Mat skeletonImage;
	/*ifstream File;*/
	void init();
	int getDepth(HANDLE h);
	int getColor(HANDLE h);
	Vertex oldPos[20];
	Vertex newPos[20];
	Vertex Dis[20];
	Vertex p1, p2;
	bool count;
	//	Point3f  getSkeleton();
	void  getSkeleton(Vertex ver[20]);

};
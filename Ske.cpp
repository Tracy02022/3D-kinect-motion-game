#pragma once
#include"skeleton.h"


Vertex Distance(Vertex p1, Vertex p2)
{
	Vertex p;
	p.x = p1.x - p2.x;
	p.y = p1.y - p2.y;
	p.z = p1.z - p2.z;
	return p;
}
Vertex unifyvector(Vertex v)
{
	Vertex result;
	result = v;
	float r = sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
	result.x = result.x / r;
	result.y = result.y / r;
	result.z = result.z / r;
	return result;
}
float eLenth(Vertex V)
{
	float len;
	len = 0.0;
	len = sqrt(V.x*V.x + V.y*V.y + V.z*V.z);
	return len;
}
Matrix Trans(Vertex p1)
{
	Matrix T1;
	float elem1[4][4] = { { 1, 0, 0, p1.x }, { 0, 1, 0, p1.y }, { 0, 0, 1, p1.z }, { 0, 0, 0, 1 } };

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			T1.elem[i][j] = elem1[i][j];
		}
	}
	return T1;
}
Matrix Transback(Vertex p1)
{
	Matrix T1;
	float elem1[4][4] = { { 1, 0, 0, -p1.x }, { 0, 1, 0, -p1.y }, { 0, 0, 1, -p1.z }, { 0, 0, 0, 1 } };

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			T1.elem[i][j] = elem1[i][j];
		}
	}
	return T1;
}
Matrix Rotation(Vertex p1, Vertex p2, Vertex Dis)
{
	ofstream out;
	char f1[] = "normal.txt";
	out.open(f1, ofstream::app);
	Vertex p11, p12, p;
	float sintheta, costheta;
	p11.x = p1.x;
	p11.y = p1.y;
	p11.z = p1.z;
	p12.x = p2.x;
	p12.y = p2.y;
	p12.z = p2.z;
	p = p11 + Dis;
	Vertex normal;
	Vertex tmp;
	tmp = p11;
	p11 = p12 - p11;
	p12 = Dis;
	normal = p11.cross(p12);
	normal = unifyvector(normal);
	out << "normal" << endl;
	out << normal.x << " " << normal.y << " " << normal.z << endl;
	float l1, l2;
	l1 = sqrt(p11.x*p11.x + p11.y*p11.y + p11.z*p11.z);
	l2 = sqrt(p12.x*p12.x + p12.y*p12.y + p12.z*p12.z);
	costheta = p11.dotProduct(p12) / (l1*l2);
	sintheta = sqrt(1 - costheta*costheta);
	out << "cos" << endl;
	out << costheta << endl;
	out << "sin" << endl;
	out << sintheta << endl;
	Matrix T1, T2, Ry1, Ry2, Rz1, Rz2, Rx, K;
	float elem1[4][4] = { { 1, 0, 0, -tmp.x }, { 0, 1, 0, -tmp.y }, { 0, 0, 1, -tmp.z }, { 0, 0, 0, 1 } };
	float elem2[4][4] = { { 1, 0, 0, tmp.x }, { 0, 1, 0, tmp.y }, { 0, 0, 1, tmp.z }, { 0, 0, 0, 1 } };
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			T1.elem[i][j] = elem1[i][j];
			T2.elem[i][j] = elem2[i][j];
		}
	}
	Vertex nl = normal - tmp;
	float edge = sqrt(nl.x*nl.x + nl.z*nl.z);
	float elem3[4][4] = { { nl.x / edge, 0, nl.z / edge, 0 }, { 0, 1, 0, 0 }, { -nl.z / edge, 0, nl.x / edge, 0 }, { 0, 0, 0, 1 } };
	float elem4[4][4] = { { nl.x / edge, 0, -nl.z / edge, 0 }, { 0, 1, 0, 0 }, { nl.z / edge, 0, nl.x / edge, 0 }, { 0, 0, 0, 1 } };
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			Ry1.elem[i][j] = elem3[i][j];
			Ry2.elem[i][j] = elem4[i][j];
		}
	}
	edge = sqrt(nl.y*nl.y + nl.x*nl.x);
	float e1[4][4] = { { nl.x / edge, -nl.y / edge, 0, 0 }, { nl.y / edge, nl.x / edge, 0, 0 }, { 0, 0, 1, 0 }, { 0, 0, 0, 1 } };
	float e2[4][4] = { { nl.x / edge, nl.y / edge, 0, 0 }, { -nl.y / edge, nl.x / edge, 0, 0 }, { 0, 0, 1, 0 }, { 0, 0, 0, 1 } };
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			Rz1.elem[i][j] = e1[i][j];
			Rz2.elem[i][j] = e2[i][j];
		}
	}
	float e[4][4] = { { 1, 0, 0, 0 }, { 0, costheta, -sintheta, 0 }, { 0, sintheta, costheta, 0 }, { 0, 0, 0, 1 } };
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			Rx.elem[i][j] = e[i][j];
		}
	}
	K = Ry1*Rz1*Rx*Rz2*Ry2;
	//	K = T1*Ry1*Rz1*Rx*Rz2*Ry2*T2;
	return K;
}
void skeleton::init()
{
	count = false;
	skeletonPoint[NUI_SKELETON_COUNT][NUI_SKELETON_POSITION_COUNT] = { cvPoint(0, 0) };
	skeletonImage.create(240, 320, CV_8UC3);

	tracked[NUI_SKELETON_COUNT] = { FALSE };

	hr = NuiInitialize(NUI_INITIALIZE_FLAG_USES_SKELETON);
	if (FAILED(hr))
	{
		cout << "NuiInitialize failed" << endl;
	}


	skeletonEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	
	hr = NuiSkeletonTrackingEnable(skeletonEvent, 0);
	if (FAILED(hr))
	{
		cout << "Could not open color image stream video" << endl;
		NuiShutdown();
		//	return hr;
	}
	namedWindow("skeletonImage", CV_WINDOW_AUTOSIZE);

	

}
void drawSkeleton(Mat &image, CvPoint pointSet[], int whichone)
{

	CvScalar color;
	switch (whichone)  
	{
	case 0:
		color = cvScalar(255);
		break;
	case 1:
		color = cvScalar(0, 255);
		break;
	case 2:
		color = cvScalar(0, 0, 255);
		break;
	case 3:
		color = cvScalar(255, 255, 0);
		break;
	case 4:
		color = cvScalar(255, 0, 255);
		break;
	case 5:
		color = cvScalar(0, 255, 255);
		break;
	}

	if ((pointSet[NUI_SKELETON_POSITION_HEAD].x != 0 || pointSet[NUI_SKELETON_POSITION_HEAD].y != 0) &&
		(pointSet[NUI_SKELETON_POSITION_SHOULDER_CENTER].x != 0 || pointSet[NUI_SKELETON_POSITION_SHOULDER_CENTER].y != 0))
		line(image, pointSet[NUI_SKELETON_POSITION_HEAD], pointSet[NUI_SKELETON_POSITION_SHOULDER_CENTER], color, 2);
	if ((pointSet[NUI_SKELETON_POSITION_SHOULDER_CENTER].x != 0 || pointSet[NUI_SKELETON_POSITION_SHOULDER_CENTER].y != 0) &&
		(pointSet[NUI_SKELETON_POSITION_SPINE].x != 0 || pointSet[NUI_SKELETON_POSITION_SPINE].y != 0))
		line(image, pointSet[NUI_SKELETON_POSITION_SHOULDER_CENTER], pointSet[NUI_SKELETON_POSITION_SPINE], color, 2);
	if ((pointSet[NUI_SKELETON_POSITION_SPINE].x != 0 || pointSet[NUI_SKELETON_POSITION_SPINE].y != 0) &&
		(pointSet[NUI_SKELETON_POSITION_HIP_CENTER].x != 0 || pointSet[NUI_SKELETON_POSITION_HIP_CENTER].y != 0))
		line(image, pointSet[NUI_SKELETON_POSITION_SPINE], pointSet[NUI_SKELETON_POSITION_HIP_CENTER], color, 2);

	//draw skeleton
	if ((pointSet[NUI_SKELETON_POSITION_SHOULDER_CENTER].x != 0 || pointSet[NUI_SKELETON_POSITION_SHOULDER_CENTER].y != 0) &&
		(pointSet[NUI_SKELETON_POSITION_SHOULDER_LEFT].x != 0 || pointSet[NUI_SKELETON_POSITION_SHOULDER_LEFT].y != 0))
		line(image, pointSet[NUI_SKELETON_POSITION_SHOULDER_CENTER], pointSet[NUI_SKELETON_POSITION_SHOULDER_LEFT], color, 2);
	if ((pointSet[NUI_SKELETON_POSITION_SHOULDER_LEFT].x != 0 || pointSet[NUI_SKELETON_POSITION_SHOULDER_LEFT].y != 0) &&
		(pointSet[NUI_SKELETON_POSITION_ELBOW_LEFT].x != 0 || pointSet[NUI_SKELETON_POSITION_ELBOW_LEFT].y != 0))
		line(image, pointSet[NUI_SKELETON_POSITION_SHOULDER_LEFT], pointSet[NUI_SKELETON_POSITION_ELBOW_LEFT], color, 2);
	if ((pointSet[NUI_SKELETON_POSITION_ELBOW_LEFT].x != 0 || pointSet[NUI_SKELETON_POSITION_ELBOW_LEFT].y != 0) &&
		(pointSet[NUI_SKELETON_POSITION_WRIST_LEFT].x != 0 || pointSet[NUI_SKELETON_POSITION_WRIST_LEFT].y != 0))
		line(image, pointSet[NUI_SKELETON_POSITION_ELBOW_LEFT], pointSet[NUI_SKELETON_POSITION_WRIST_LEFT], color, 2);
	if ((pointSet[NUI_SKELETON_POSITION_WRIST_LEFT].x != 0 || pointSet[NUI_SKELETON_POSITION_WRIST_LEFT].y != 0) &&
		(pointSet[NUI_SKELETON_POSITION_HAND_LEFT].x != 0 || pointSet[NUI_SKELETON_POSITION_HAND_LEFT].y != 0))
		line(image, pointSet[NUI_SKELETON_POSITION_WRIST_LEFT], pointSet[NUI_SKELETON_POSITION_HAND_LEFT], color, 2);

	//draw skeleton  
	if ((pointSet[NUI_SKELETON_POSITION_SHOULDER_CENTER].x != 0 || pointSet[NUI_SKELETON_POSITION_SHOULDER_CENTER].y != 0) &&
		(pointSet[NUI_SKELETON_POSITION_SHOULDER_RIGHT].x != 0 || pointSet[NUI_SKELETON_POSITION_SHOULDER_RIGHT].y != 0))
		line(image, pointSet[NUI_SKELETON_POSITION_SHOULDER_CENTER], pointSet[NUI_SKELETON_POSITION_SHOULDER_RIGHT], color, 2);
	if ((pointSet[NUI_SKELETON_POSITION_SHOULDER_RIGHT].x != 0 || pointSet[NUI_SKELETON_POSITION_SHOULDER_RIGHT].y != 0) &&
		(pointSet[NUI_SKELETON_POSITION_ELBOW_RIGHT].x != 0 || pointSet[NUI_SKELETON_POSITION_ELBOW_RIGHT].y != 0))
		line(image, pointSet[NUI_SKELETON_POSITION_SHOULDER_RIGHT], pointSet[NUI_SKELETON_POSITION_ELBOW_RIGHT], color, 2);
	if ((pointSet[NUI_SKELETON_POSITION_ELBOW_RIGHT].x != 0 || pointSet[NUI_SKELETON_POSITION_ELBOW_RIGHT].y != 0) &&
		(pointSet[NUI_SKELETON_POSITION_WRIST_RIGHT].x != 0 || pointSet[NUI_SKELETON_POSITION_WRIST_RIGHT].y != 0))
		line(image, pointSet[NUI_SKELETON_POSITION_ELBOW_RIGHT], pointSet[NUI_SKELETON_POSITION_WRIST_RIGHT], color, 2);
	if ((pointSet[NUI_SKELETON_POSITION_WRIST_RIGHT].x != 0 || pointSet[NUI_SKELETON_POSITION_WRIST_RIGHT].y != 0) &&
		(pointSet[NUI_SKELETON_POSITION_HAND_RIGHT].x != 0 || pointSet[NUI_SKELETON_POSITION_HAND_RIGHT].y != 0))
		line(image, pointSet[NUI_SKELETON_POSITION_WRIST_RIGHT], pointSet[NUI_SKELETON_POSITION_HAND_RIGHT], color, 2);

	//draw skeleton  
	if ((pointSet[NUI_SKELETON_POSITION_HIP_CENTER].x != 0 || pointSet[NUI_SKELETON_POSITION_HIP_CENTER].y != 0) &&
		(pointSet[NUI_SKELETON_POSITION_HIP_LEFT].x != 0 || pointSet[NUI_SKELETON_POSITION_HIP_LEFT].y != 0))
		line(image, pointSet[NUI_SKELETON_POSITION_HIP_CENTER], pointSet[NUI_SKELETON_POSITION_HIP_LEFT], color, 2);
	if ((pointSet[NUI_SKELETON_POSITION_HIP_LEFT].x != 0 || pointSet[NUI_SKELETON_POSITION_HIP_LEFT].y != 0) &&
		(pointSet[NUI_SKELETON_POSITION_KNEE_LEFT].x != 0 || pointSet[NUI_SKELETON_POSITION_KNEE_LEFT].y != 0))
		line(image, pointSet[NUI_SKELETON_POSITION_HIP_LEFT], pointSet[NUI_SKELETON_POSITION_KNEE_LEFT], color, 2);
	if ((pointSet[NUI_SKELETON_POSITION_KNEE_LEFT].x != 0 || pointSet[NUI_SKELETON_POSITION_KNEE_LEFT].y != 0) &&
		(pointSet[NUI_SKELETON_POSITION_ANKLE_LEFT].x != 0 || pointSet[NUI_SKELETON_POSITION_ANKLE_LEFT].y != 0))
		line(image, pointSet[NUI_SKELETON_POSITION_KNEE_LEFT], pointSet[NUI_SKELETON_POSITION_ANKLE_LEFT], color, 2);
	if ((pointSet[NUI_SKELETON_POSITION_ANKLE_LEFT].x != 0 || pointSet[NUI_SKELETON_POSITION_ANKLE_LEFT].y != 0) &&
		(pointSet[NUI_SKELETON_POSITION_FOOT_LEFT].x != 0 || pointSet[NUI_SKELETON_POSITION_FOOT_LEFT].y != 0))
		line(image, pointSet[NUI_SKELETON_POSITION_ANKLE_LEFT], pointSet[NUI_SKELETON_POSITION_FOOT_LEFT], color, 2);

	//draw skeleton  
	if ((pointSet[NUI_SKELETON_POSITION_HIP_CENTER].x != 0 || pointSet[NUI_SKELETON_POSITION_HIP_CENTER].y != 0) &&
		(pointSet[NUI_SKELETON_POSITION_HIP_RIGHT].x != 0 || pointSet[NUI_SKELETON_POSITION_HIP_RIGHT].y != 0))
		line(image, pointSet[NUI_SKELETON_POSITION_HIP_CENTER], pointSet[NUI_SKELETON_POSITION_HIP_RIGHT], color, 2);
	if ((pointSet[NUI_SKELETON_POSITION_HIP_RIGHT].x != 0 || pointSet[NUI_SKELETON_POSITION_HIP_RIGHT].y != 0) &&
		(pointSet[NUI_SKELETON_POSITION_KNEE_RIGHT].x != 0 || pointSet[NUI_SKELETON_POSITION_KNEE_RIGHT].y != 0))
		line(image, pointSet[NUI_SKELETON_POSITION_HIP_RIGHT], pointSet[NUI_SKELETON_POSITION_KNEE_RIGHT], color, 2);
	if ((pointSet[NUI_SKELETON_POSITION_KNEE_RIGHT].x != 0 || pointSet[NUI_SKELETON_POSITION_KNEE_RIGHT].y != 0) &&
		(pointSet[NUI_SKELETON_POSITION_ANKLE_RIGHT].x != 0 || pointSet[NUI_SKELETON_POSITION_ANKLE_RIGHT].y != 0))
		line(image, pointSet[NUI_SKELETON_POSITION_KNEE_RIGHT], pointSet[NUI_SKELETON_POSITION_ANKLE_RIGHT], color, 2);
	if ((pointSet[NUI_SKELETON_POSITION_ANKLE_RIGHT].x != 0 || pointSet[NUI_SKELETON_POSITION_ANKLE_RIGHT].y != 0) &&
		(pointSet[NUI_SKELETON_POSITION_FOOT_RIGHT].x != 0 || pointSet[NUI_SKELETON_POSITION_FOOT_RIGHT].y != 0))
		line(image, pointSet[NUI_SKELETON_POSITION_ANKLE_RIGHT], pointSet[NUI_SKELETON_POSITION_FOOT_RIGHT], color, 2);
}
void skeleton::getSkeleton(Vertex ver[20])
{
	ofstream ffout;
	char fn[] = "hhhh.txt";
	ffout.open(fn, ofstream::app);
	ffout << "while loop" << endl;
	NUI_SKELETON_FRAME skeletonFrame = { 0 };    
	bool bFoundSkeleton = false;
	if (WaitForSingleObject(skeletonEvent, INFINITE) == 0)
	{
		
		hr = NuiSkeletonGetNextFrame(0, &skeletonFrame);
		if (SUCCEEDED(hr))
		{
			//NUI_SKELETON_COUNT是检测到的骨骼数（即，跟踪到的人数）  
			for (int i = 0; i < NUI_SKELETON_COUNT; i++)
			{
				NUI_SKELETON_TRACKING_STATE trackingState = skeletonFrame.SkeletonData[i].eTrackingState;
				  
				if (trackingState == NUI_SKELETON_TRACKED)
				{
					bFoundSkeleton = true;
				}
			}
		}

		if (!bFoundSkeleton)
		{
			return;
		}

		
		NuiTransformSmooth(&skeletonFrame, NULL);
		skeletonImage.setTo(0);

		for (int i = 0; i < NUI_SKELETON_COUNT; i++)
		{
			if (skeletonFrame.SkeletonData[i].eTrackingState == NUI_SKELETON_TRACKED &&
				skeletonFrame.SkeletonData[i].eSkeletonPositionTrackingState[NUI_SKELETON_POSITION_SHOULDER_CENTER] != NUI_SKELETON_POSITION_NOT_TRACKED)
			{
				float fx, fy;
				
				ffout << "HELLO" << endl;
				ffout << count << endl;
				if (count == false)
				{
					count = true;
					ffout << count << endl;
					for (int j = 0; j < NUI_SKELETON_POSITION_COUNT; j++)
					{
						NuiTransformSkeletonToDepthImage(skeletonFrame.SkeletonData[i].SkeletonPositions[j], &fx, &fy);
						skeletonPoint[i][j].x = (int)fx;
						skeletonPoint[i][j].y = (int)fy;
						oldPos[j].x = skeletonFrame.SkeletonData[i].SkeletonPositions[j].x;
						oldPos[j].y = skeletonFrame.SkeletonData[i].SkeletonPositions[j].y;
						if (j != 0)
							oldPos[j].z = skeletonFrame.SkeletonData[i].SkeletonPositions[j].z - skeletonFrame.SkeletonData[i].SkeletonPositions[0].z;
						else
							oldPos[j].z = skeletonFrame.SkeletonData[i].SkeletonPositions[j].z;
						ffout << "false" << endl;
						ffout << j << " ";
						ffout << skeletonFrame.SkeletonData[i].SkeletonPositions[j].x << " ";
						ffout << skeletonFrame.SkeletonData[i].SkeletonPositions[j].y << " ";
						ffout << skeletonFrame.SkeletonData[i].SkeletonPositions[j].z - skeletonFrame.SkeletonData[i].SkeletonPositions[0].z;

						ffout << endl;

					}
					float ee[4][4] = { { 1, 0, 0, 0 }, { 0, 1, 0, 0 }, { 0, 0, 1, 0 }, { 0, 0, 0, 1 } };
					for (int a = 0; a < 4; a++)
					{
						for (int b = 0; b < 4; b++)
						{
							
							TT[0].elem[a][b] = ee[a][b];
							KK[5].elem[a][b] = ee[a][b];
							KK[6].elem[a][b] = ee[a][b];
							KK[7].elem[a][b] = ee[a][b];
						}
					}
					count == true;
				}
				else
				{
					for (int j = 0; j < NUI_SKELETON_POSITION_COUNT; j++)
					{
						if (skeletonFrame.SkeletonData[i].eSkeletonPositionTrackingState[j] != NUI_SKELETON_POSITION_NOT_TRACKED)//跟踪点一用有三种状态：1没有被跟踪到，2跟踪到，3根据跟踪到的估计到     
						{
							NuiTransformSkeletonToDepthImage(skeletonFrame.SkeletonData[i].SkeletonPositions[j], &fx, &fy);
							skeletonPoint[i][j].x = (int)fx;
							skeletonPoint[i][j].y = (int)fy;
							circle(skeletonImage, skeletonPoint[i][j], 3, cvScalar(0, 255, 255), 1, 8, 0);
							tracked[i] = TRUE;
							ffout << "TRUE" << endl;
							ffout << j << " ";
							ffout << skeletonFrame.SkeletonData[i].SkeletonPositions[j].x << " ";
							ffout << skeletonFrame.SkeletonData[i].SkeletonPositions[j].y << " ";
							ffout << skeletonFrame.SkeletonData[i].SkeletonPositions[j].z - skeletonFrame.SkeletonData[i].SkeletonPositions[0].z;

							ffout << endl;
								if (j == 0)
								{

									p1.x = skeletonFrame.SkeletonData[i].SkeletonPositions[j].x - oldPos[0].x;
									p1.y = skeletonFrame.SkeletonData[i].SkeletonPositions[j].y - oldPos[0].y;
									p1.z = skeletonFrame.SkeletonData[i].SkeletonPositions[j].z - oldPos[0].z;

									float ee[4][4] = { { 1, 0, 0, -p1.x }, { 0, 1, 0, p1.y }, { 0, 0, 1, -p1.z }, { 0, 0, 0, 1 } };
									for (int a = 0; a < 4; a++)
									{
										for (int b = 0; b < 4; b++)
										{
											TT[0].elem[a][b] = ee[a][b];
										}
									}
									float ee2[4][4] = { { 1, 0, 0, p1.x }, { 0, 1, 0, p1.y }, { 0, 0, 1, p1.z }, { 0, 0, 0, 1 } };
									for (int a = 0; a < 4; a++)
									{
										for (int b = 0; b < 4; b++)
										{
											T[0].elem[a][b] = ee[a][b];
										}
									}
									oldPos[0].x = skeletonFrame.SkeletonData[i].SkeletonPositions[j].x;
									oldPos[0].y = skeletonFrame.SkeletonData[i].SkeletonPositions[j].y;
									oldPos[0].z = skeletonFrame.SkeletonData[i].SkeletonPositions[j].z;


								}
								
								else if (j == 1 || j == 2 || j == 3 || j == 5 || j == 6 || j == 7 || j == 9 || j == 10 || j == 11 || j == 13 || j == 14 || j == 15 || j == 17 || j == 18 || j == 19)
								{

									Dis[j].x = Distance(oldPos[j], oldPos[j - 1]).x;
									Dis[j].y = Distance(oldPos[j], oldPos[j - 1]).y;
									Dis[j].z = Distance(oldPos[j], oldPos[j - 1]).z;
									if (eLenth(Dis[j]) == 0.0)
									{
										float ee[4][4] = { { 1, 0, 0, 0 }, { 0, 1, 0, 0 }, { 0, 0, 1, 0 }, { 0, 0, 0, 1 } };
										for (int a = 0; a < 4; a++)
										{
											for (int b = 0; b < 4; b++)
											{
												KK[j].elem[a][b] = ee[a][b];
												TT[j].elem[a][b] = ee[a][b];
												T[j].elem[a][b] = ee[a][b];
											}
										}

									}
									else
									{
										p1.x = skeletonFrame.SkeletonData[i].SkeletonPositions[j].x;
										p1.y = skeletonFrame.SkeletonData[i].SkeletonPositions[j].y;
										p1.z = skeletonFrame.SkeletonData[i].SkeletonPositions[j].z - skeletonFrame.SkeletonData[i].SkeletonPositions[0].z;
										p2.x = skeletonFrame.SkeletonData[i].SkeletonPositions[j - 1].x;
										p2.y = skeletonFrame.SkeletonData[i].SkeletonPositions[j - 1].y;
										p2.z = skeletonFrame.SkeletonData[i].SkeletonPositions[j - 1].z - skeletonFrame.SkeletonData[i].SkeletonPositions[0].z;
										TT[j] = Transback(p2);
										T[j] = Trans(p2);
										KK[j] = Rotation(p1, p2, Dis[j]);
									}

								}
								else if (j == 4)
								{
									Dis[j].x = Distance(oldPos[j], oldPos[j - 2]).x;
									Dis[j].y = Distance(oldPos[j], oldPos[j - 2]).y;
									Dis[j].z = Distance(oldPos[j], oldPos[j - 2]).z;
									if (eLenth(Dis[j]) == 0.0)
									{
										float ee[4][4] = { { 1, 0, 0, 0 }, { 0, 1, 0, 0 }, { 0, 0, 1, 0 }, { 0, 0, 0, 1 } };
										for (int a = 0; a < 4; a++)
										{
											for (int b = 0; b < 4; b++)
											{
												KK[j].elem[a][b] = ee[a][b];
												TT[j].elem[a][b] = ee[a][b];
												T[j].elem[a][b] = ee[a][b];
											}
										}
									}
									else
									{
										p1.x = skeletonFrame.SkeletonData[i].SkeletonPositions[j].x;
										p1.y = skeletonFrame.SkeletonData[i].SkeletonPositions[j].y;
										p1.z = skeletonFrame.SkeletonData[i].SkeletonPositions[j].z - skeletonFrame.SkeletonData[i].SkeletonPositions[0].z;
										p2.x = skeletonFrame.SkeletonData[i].SkeletonPositions[j - 2].x;
										p2.y = skeletonFrame.SkeletonData[i].SkeletonPositions[j - 2].y;
										p2.z = skeletonFrame.SkeletonData[i].SkeletonPositions[j - 2].z - skeletonFrame.SkeletonData[i].SkeletonPositions[0].z;
										KK[j] = Rotation(p1, p2, Dis[j]);
										TT[j] = Transback(p2);
										T[j] = Trans(p2);
									}
								}
								else if (j == 8)
								{
									Dis[j].x = Distance(oldPos[j], oldPos[j - 6]).x;
									Dis[j].y = Distance(oldPos[j], oldPos[j - 6]).y;
									Dis[j].z = Distance(oldPos[j], oldPos[j - 6]).z;
									if (eLenth(Dis[j]) == 0.0)
									{
										float ee[4][4] = { { 1, 0, 0, 0 }, { 0, 1, 0, 0 }, { 0, 0, 1, 0 }, { 0, 0, 0, 1 } };
										for (int a = 0; a < 4; a++)
										{
											for (int b = 0; b < 4; b++)
											{
												KK[j].elem[a][b] = ee[a][b];
												TT[j].elem[a][b] = ee[a][b];
												T[j].elem[a][b] = ee[a][b];
											}
										}
									}
									else
									{
										p1.x = skeletonFrame.SkeletonData[i].SkeletonPositions[j].x;
										p1.y = skeletonFrame.SkeletonData[i].SkeletonPositions[j].y;
										p1.z = skeletonFrame.SkeletonData[i].SkeletonPositions[j].z - skeletonFrame.SkeletonData[i].SkeletonPositions[0].z;
										p2.x = skeletonFrame.SkeletonData[i].SkeletonPositions[j - 6].x;
										p2.y = skeletonFrame.SkeletonData[i].SkeletonPositions[j - 6].y;
										p2.z = skeletonFrame.SkeletonData[i].SkeletonPositions[j - 6].z - skeletonFrame.SkeletonData[i].SkeletonPositions[0].z;
										KK[j] = Rotation(p1, p2, Dis[j]);
										TT[j] = Transback(p2);
										T[j] = Trans(p2);
									}

								}
								else if (j == 12)
								{
									Dis[j].x = Distance(oldPos[j], oldPos[0]).x;
									Dis[j].y = Distance(oldPos[j], oldPos[0]).y;
									Dis[j].z = Distance(oldPos[j], oldPos[0]).z;
									if (eLenth(Dis[j]) == 0.0)
									{
										float ee[4][4] = { { 1, 0, 0, 0 }, { 0, 1, 0, 0 }, { 0, 0, 1, 0 }, { 0, 0, 0, 1 } };
										for (int a = 0; a < 4; a++)
										{
											for (int b = 0; b < 4; b++)
											{
												KK[j].elem[a][b] = ee[a][b];
												TT[j].elem[a][b] = ee[a][b];
												T[j].elem[a][b] = ee[a][b];
											}
										}

									}
									else
									{
										p1.x = skeletonFrame.SkeletonData[i].SkeletonPositions[j].x;
										p1.y = skeletonFrame.SkeletonData[i].SkeletonPositions[j].y;
										p1.z = skeletonFrame.SkeletonData[i].SkeletonPositions[j].z - skeletonFrame.SkeletonData[i].SkeletonPositions[0].z;
										p2.x = skeletonFrame.SkeletonData[i].SkeletonPositions[0].x;
										p2.y = skeletonFrame.SkeletonData[i].SkeletonPositions[0].y;
										p2.z = skeletonFrame.SkeletonData[i].SkeletonPositions[0].z - skeletonFrame.SkeletonData[i].SkeletonPositions[0].z;
										KK[j] = Rotation(p1, p2, Dis[j]);
										TT[j] = Transback(p2);
										T[j] = Trans(p2);
									}

								}
								else
								{
									Dis[j].x = Distance(oldPos[j], oldPos[0]).x;
									Dis[j].y = Distance(oldPos[j], oldPos[0]).y;
									Dis[j].z = Distance(oldPos[j], oldPos[0]).z;
									if (eLenth(Dis[j]) == 0.0)
									{
										float ee[4][4] = { { 1, 0, 0, 0 }, { 0, 1, 0, 0 }, { 0, 0, 1, 0 }, { 0, 0, 0, 1 } };
										for (int a = 0; a < 4; a++)
										{
											for (int b = 0; b < 4; b++)
											{
												KK[j].elem[a][b] = ee[a][b];
												TT[j].elem[a][b] = ee[a][b];
												T[j].elem[a][b] = ee[a][b];
											}
										}

									}
									else
									{
										p1.x = skeletonFrame.SkeletonData[i].SkeletonPositions[j].x;
										p1.y = skeletonFrame.SkeletonData[i].SkeletonPositions[j].y;
										p1.z = skeletonFrame.SkeletonData[i].SkeletonPositions[j].z - skeletonFrame.SkeletonData[i].SkeletonPositions[0].z;
										p2.x = skeletonFrame.SkeletonData[i].SkeletonPositions[0].x;
										p2.y = skeletonFrame.SkeletonData[i].SkeletonPositions[0].y;
										p2.z = skeletonFrame.SkeletonData[i].SkeletonPositions[0].z - skeletonFrame.SkeletonData[i].SkeletonPositions[0].z;
										KK[j] = Rotation(p1, p2, Dis[j]);
										TT[j] = Transback(p2);
										T[j] = Trans(p2);
									}
								}
							}
						}
					}
					Vertex v;
					v.x = ver[0].x;
					v.y = ver[0].y;
					v.z = ver[0].z;
					ver[0].x = ( TT[0] * v).x;
					ver[0].y = ( TT[0] * v).y;
					ver[0].z = (TT[0] * v).z;
					for (int a = 0; a < 4; a++)
					{
						for (int b = 0; b < 4; b++)
						{
						//	ffout << "K5" << KK[5].elem[a][b] << " ";
							ffout<<TT[0].elem[a][b]<<" ";
						}
						ffout << endl;
					}
					ffout << "K5" << endl;
					for (int a = 0; a < 4; a++)
					{
						
						for (int b = 0; b < 4; b++)
						{
							ffout <<KK[5].elem[a][b] << " ";
						}
						ffout << endl;
					}
					ffout << "K6" << endl;
					for (int a = 0; a < 4; a++)
					{
						
						for (int b = 0; b < 4; b++)
						{
							ffout << KK[6].elem[a][b] << " ";
						}
						ffout << endl;
					}
					ffout << "K7" << endl;
					for (int a = 0; a < 4; a++)
					{
						for (int b = 0; b < 4; b++)
						{
							ffout << KK[7].elem[a][b] << " ";
						}
						ffout << endl;
					}
					ffout << "v0 " << ver[0].x << " " << ver[0].y << " " << ver[0].z << endl;
					v.x = ver[1].x;
					v.y = ver[1].y;
					v.z = ver[1].z;
					ver[1].x = ( TT[0] * v).x;
					ver[1].y = ( TT[0] * v).y;
					ver[1].z = ( TT[0] * v).z;
					/*ver[1].x = (T[0] * KK[1] * TT[0] * v).x;
					ver[1].y = (T[0] * KK[1] * TT[0] * v).y;
					ver[1].z = (T[0] * KK[1] * TT[0] * v).z;*/
					ffout << "v1  " << ver[1].x << " " << ver[1].y << " " << ver[1].z << endl;
					v.x = ver[2].x;
					v.y = ver[2].y;
					v.z = ver[2].z;
					ver[2].x = ( TT[0] * v).x;
					ver[2].y = ( TT[0] * v).y;
					ver[2].z = ( TT[0] * v).z;
					/*ver[2].x = (T[1] * KK[2] * TT[1] * T[0] * KK[1] * TT[0] * v).x;
					ver[2].y = (T[1] * KK[2] * TT[1] * T[0] * KK[1] * TT[0] * v).y;
					ver[2].z = (T[1] * KK[2] * TT[1] * T[0] * KK[1] * TT[0] * v).z;*/
					ffout << "v2 " << ver[2].x << " " << ver[2].y << " " << ver[2].z << endl;
					v.x = ver[3].x;
					v.y = ver[3].y;
					v.z = ver[3].z;
					ver[3].x = ( TT[0] * v).x;
					ver[3].y = ( TT[0] * v).y;
					ver[3].z = ( TT[0] * v).z;
					/*ver[3].x = (T[2] * KK[3] * TT[2] * T[1] * KK[2] * TT[1] * T[0] * KK[1] * TT[0] * v).x;
					ver[3].y = (T[2] * KK[3] * TT[2] * T[1] * KK[2] * TT[1] * T[0] * KK[1] * TT[0] * v).y;
					ver[3].z = (T[2] * KK[3] * TT[2] * T[1] * KK[2] * TT[1] * T[0] * KK[1] * TT[0] * v).z;*/
					ffout << "v3 " << ver[3].x << " " << ver[3].y << " " << ver[3].z << endl;
					v.x = ver[4].x;
					v.y = ver[4].y;
					v.z = ver[4].z;
					ver[4].x = ( TT[0] * v).x;
					ver[4].y = ( TT[0] * v).y;
					ver[4].z = ( TT[0] * v).z;
					/*ver[4].x = (T[2] * KK[4] * TT[2] * T[1] * KK[2] * TT[1] * T[0] * KK[1] * TT[0] * v).x;
					ver[4].y = (T[2] * KK[4] * TT[2] * T[1] * KK[2] * TT[1] * T[0] * KK[1] * TT[0] * v).y;
					ver[4].z = (T[2] * KK[4] * TT[2] * T[1] * KK[2] * TT[1] * T[0] * KK[1] * TT[0] * v).z;*/
					ffout << "v4 " << ver[4].x << " " << ver[4].y << " " << ver[4].z << endl;
					v.x = ver[5].x;
					v.y = ver[5].y;
					v.z = ver[5].z;
					ver[5].x = (KK[5] * TT[0] * v).x;
					ver[5].y = (KK[5] * TT[0] * v).y;
					ver[5].z = (KK[5] * TT[0] * v).z;
					/*ver[5].x = (T[4] * KK[5] * TT[4] * T[2] * KK[4] * TT[2] * T[1] * KK[2] * TT[1] * T[0] * KK[1] * TT[0] * v).x;
					ver[5].y = (T[4] * KK[5] * TT[4] * T[2] * KK[4] * TT[2] * T[1] * KK[2] * TT[1] * T[0] * KK[1] * TT[0] * v).y;
					ver[5].z = (T[4] * KK[5] * TT[4] * T[2] * KK[4] * TT[2] * T[1] * KK[2] * TT[1] * T[0] * KK[1] * TT[0] * v).z;*/
					ffout << "v5 " << ver[5].x << " " << ver[5].y << " " << ver[5].z << endl;
					v.x = ver[6].x;
					v.y = ver[6].y;
					v.z = ver[6].z;
					ver[6].x = (KK[6] * KK[5] * TT[0] * v).x;
					ver[6].y = (KK[6] * KK[5] * TT[0] * v).y;
					ver[6].z = (KK[6] * KK[5] * TT[0] * v).z;
					/*ver[6].x = (T[5] * KK[6] * TT[5] * T[4] * KK[5] * TT[4] * T[2] * KK[4] * TT[2] * T[1] * KK[2] * TT[1] * T[0] * KK[1] * TT[0] * v).x;
					ver[6].y = (T[5] * KK[6] * TT[5] * T[4] * KK[5] * TT[4] * T[2] * KK[4] * TT[2] * T[1] * KK[2] * TT[1] * T[0] * KK[1] * TT[0] * v).y;
					ver[6].z = (T[5] * KK[6] * TT[5] * T[4] * KK[5] * TT[4] * T[2] * KK[4] * TT[2] * T[1] * KK[2] * TT[1] * T[0] * KK[1] * TT[0] * v).z;*/
					ffout << "v6 " << ver[6].x << " " << ver[6].y << " " << ver[6].z << endl;
					v.x = ver[7].x;
					v.y = ver[7].y;
					v.z = ver[7].z;
					ver[7].x = (KK[7] * KK[6] * KK[5] * TT[0] * v).x;
					ver[7].y = (KK[7] * KK[6] * KK[5] * TT[0] * v).y;
					ver[7].z = (KK[7] * KK[6] * KK[5] * TT[0] * v).z;
				/*	ver[7].x = (T[6] * KK[7] * TT[6] * T[5] * KK[6] * TT[5] * T[4] * KK[5] * TT[4] * T[2] * KK[4] * TT[2] * T[1] * KK[2] * TT[1] * T[0] * KK[1] * TT[0] * v).x;
					ver[7].y = (T[6] * KK[7] * TT[6] * T[5] * KK[6] * TT[5] * T[4] * KK[5] * TT[4] * T[2] * KK[4] * TT[2] * T[1] * KK[2] * TT[1] * T[0] * KK[1] * TT[0] * v).y;
					ver[7].z = (T[6] * KK[7] * TT[6] * T[5] * KK[6] * TT[5] * T[4] * KK[5] * TT[4] * T[2] * KK[4] * TT[2] * T[1] * KK[2] * TT[1] * T[0] * KK[1] * TT[0] * v).z;*/
					ffout << "v7 " << ver[7].x << " " << ver[7].y << " " << ver[7].z << endl;
					v.x = ver[8].x;
					v.y = ver[8].y;
					v.z = ver[8].z;
					ver[8].x = ( TT[0] * v).x;
					ver[8].y = ( TT[0] * v).y;
					ver[8].z = ( TT[0] * v).z;
					/*ver[8].x = (T[2] * KK[8] * TT[2] * T[1] * KK[2] * TT[1] * T[0] * KK[1] * TT[0] * v).x;
					ver[8].y = (T[2] * KK[8] * TT[2] * T[1] * KK[2] * TT[1] * T[0] * KK[1] * TT[0] * v).y;
					ver[8].z = (T[2] * KK[8] * TT[2] * T[1] * KK[2] * TT[1] * T[0] * KK[1] * TT[0] * v).z;*/
					ffout << "v8 " << ver[8].x << " " << ver[8].y << " " << ver[8].z << endl;
					v.x = ver[9].x;
					v.y = ver[9].y;
					v.z = ver[9].z;
					ver[9].x = ( TT[0] * v).x;
					ver[9].y = ( TT[0] * v).y;
					ver[9].z = ( TT[0] * v).z;
					/*ver[9].x = (T[8] * KK[9] * TT[8] * T[2] * KK[8] * TT[2] * T[1] * KK[2] * TT[1] * T[0] * KK[1] * TT[0] * v).x;
					ver[9].y = (T[8] * KK[9] * TT[8] * T[2] * KK[8] * TT[2] * T[1] * KK[2] * TT[1] * T[0] * KK[1] * TT[0] * v).y;
					ver[9].z = (T[8] * KK[9] * TT[8] * T[2] * KK[8] * TT[2] * T[1] * KK[2] * TT[1] * T[0] * KK[1] * TT[0] * v).z;*/
					ffout << "v9 " << ver[9].x << " " << ver[9].y << " " << ver[9].z << endl;
					v.x = ver[10].x;
					v.y = ver[10].y;
					v.z = ver[10].z;
					ver[10].x = ( TT[0] * v).x;
					ver[10].y = ( TT[0] * v).y;
					ver[10].z = (TT[0] * v).z;
					/*ver[10].x = (T[9] * KK[10] * TT[9] * T[8] * KK[9] * TT[8] * T[2] * KK[8] * TT[2] * T[1] * KK[2] * TT[1] * T[0] * KK[1] * TT[0] * v).x;
					ver[10].y = (T[9] * KK[10] * TT[9] * T[8] * KK[9] * TT[8] * T[2] * KK[8] * TT[2] * T[1] * KK[2] * TT[1] * T[0] * KK[1] * TT[0] * v).y;
					ver[10].z = (T[9] * KK[10] * TT[9] * T[8] * KK[9] * TT[8] * T[2] * KK[8] * TT[2] * T[1] * KK[2] * TT[1] * T[0] * KK[1] * TT[0] * v).z;*/
					ffout << "v10 " << ver[10].x << " " << ver[10].y << " " << ver[10].z << endl;
					v.x = ver[11].x;
					v.y = ver[11].y;
					v.z = ver[11].z;
					ver[11].x = (TT[0] * v).x;
					ver[11].y = (TT[0] * v).y;
					ver[11].z = ( TT[0] * v).z;
					/*ver[11].x = (T[10] * KK[11] * TT[10] * T[9] * KK[10] * TT[9] * T[8] * KK[9] * TT[8] * T[2] * KK[8] * TT[2] * T[1] * KK[2] * TT[1] * T[0] * KK[1] * TT[0] * v).x;
					ver[11].y = (T[10] * KK[11] * TT[10] * T[9] * KK[10] * TT[9] * T[8] * KK[9] * TT[8] * T[2] * KK[8] * TT[2] * T[1] * KK[2] * TT[1] * T[0] * KK[1] * TT[0] * v).y;
					ver[11].z = (T[10] * KK[11] * TT[10] * T[9] * KK[10] * TT[9] * T[8] * KK[9] * TT[8] * T[2] * KK[8] * TT[2] * T[1] * KK[2] * TT[1] * T[0] * KK[1] * TT[0] * v).z;*/
					ffout << "v11 " << ver[11].x << " " << ver[11].y << " " << ver[11].z << endl;
					v.x = ver[12].x;
					v.y = ver[12].y;
					v.z = ver[12].z;
					ver[12].x = ( TT[0] * v).x;
					ver[12].y = ( TT[0] * v).y;
					ver[12].z = ( TT[0] * v).z;
					/*ver[12].x = (T[0] * KK[12] * TT[0] * v).x;
					ver[12].y = (T[0] * KK[12] * TT[0] * v).y;
					ver[12].z = (T[0] * KK[12] * TT[0] * v).z;*/
					ffout << "v12 " << ver[12].x << " " << ver[12].y << " " << ver[12].z << endl;
					v.x = ver[13].x;
					v.y = ver[13].y;
					v.z = ver[13].z;
					ver[13].x = ( TT[0] * v).x;
					ver[13].y = ( TT[0] * v).y;
					ver[13].z = ( TT[0] * v).z;
					/*ver[13].x = (T[12] * KK[13] * TT[12] * T[0] * KK[12] * TT[0] * v).x;
					ver[13].y = (T[12] * KK[13] * TT[12] * T[0] * KK[12] * TT[0] * v).y;
					ver[13].z = (T[12] * KK[13] * TT[12] * T[0] * KK[12] * TT[0] * v).z;*/
					ffout << "v13 " << ver[13].x << " " << ver[13].y << " " << ver[13].z << endl;
					v.x = ver[14].x;
					v.y = ver[14].y;
					v.z = ver[14].z;
					ver[14].x = ( TT[0] * v).x;
					ver[14].y = ( TT[0] * v).y;
					ver[14].z = ( TT[0] * v).z;
					/*ver[14].x = (T[13] * KK[14] * TT[13] * T[12] * KK[13] * TT[12] * T[0] * KK[12] * TT[0] * v).x;
					ver[14].y = (T[13] * KK[14] * TT[13] * T[12] * KK[13] * TT[12] * T[0] * KK[12] * TT[0] * v).y;
					ver[14].z = (T[13] * KK[14] * TT[13] * T[12] * KK[13] * TT[12] * T[0] * KK[12] * TT[0] * v).z;*/
					ffout << "v14 " << ver[14].x << " " << ver[14].y << " " << ver[14].z << endl;
					v.x = ver[15].x;
					v.y = ver[15].y;
					v.z = ver[15].z;
					ver[15].x = ( TT[0] * v).x;
					ver[15].y = ( TT[0] * v).y;
					ver[15].z = ( TT[0] * v).z;
					/*ver[15].x = (T[14] * KK[15] * TT[14] * T[13] * KK[14] * TT[13] * T[12] * KK[13] * TT[12] * T[0] * KK[12] * TT[0] * v).x;
					ver[15].y = (T[14] * KK[15] * TT[14] * T[13] * KK[14] * TT[13] * T[12] * KK[13] * TT[12] * T[0] * KK[12] * TT[0] * v).y;
					ver[15].z = (T[14] * KK[15] * TT[14] * T[13] * KK[14] * TT[13] * T[12] * KK[13] * TT[12] * T[0] * KK[12] * TT[0] * v).z;*/
					ffout << "v15 " << ver[15].x << " " << ver[15].y << " " << ver[15].z << endl;
					v.x = ver[16].x;
					v.y = ver[16].y;
					v.z = ver[16].z;
					ver[16].x = ( TT[0] * v).x;
					ver[16].y = ( TT[0] * v).y;
					ver[16].z = ( TT[0] * v).z;
					/*ver[16].x = (T[0] * KK[16] * TT[0] * v).x;
					ver[16].y = (T[0] * KK[16] * TT[0] * v).y;
					ver[16].z = (T[0] * KK[16] * TT[0] * v).z;*/
					ffout << "v16 " << ver[16].x << " " << ver[16].y << " " << ver[16].z << endl;
					v.x = ver[17].x;
					v.y = ver[17].y;
					v.z = ver[17].z;
					ver[17].x = ( TT[0] * v).x;
					ver[17].y = ( TT[0] * v).y;
					ver[17].z = ( TT[0] * v).z;
					/*ver[17].x = (T[16] * KK[17] * TT[16] * T[0] * KK[16] * TT[0] * v).x;
					ver[17].y = (T[16] * KK[17] * TT[16] * T[0] * KK[16] * TT[0] * v).y;
					ver[17].z = (T[16] * KK[17] * TT[16] * T[0] * KK[16] * TT[0] * v).z;*/
					ffout << "v17 " << ver[17].x << " " << ver[17].y << " " << ver[17].z << endl;
					v.x = ver[18].x;
					v.y = ver[18].y;
					v.z = ver[18].z;
					ver[18].x = ( TT[0] * v).x;
					ver[18].y = ( TT[0] * v).y;
					ver[18].z = ( TT[0] * v).z;
					/*ver[18].x = (T[17] * KK[18] * TT[17] * T[16] * KK[17] * TT[16] * T[0] * KK[16] * TT[0] * v).x;
					ver[18].y = (T[17] * KK[18] * TT[17] * T[16] * KK[17] * TT[16] * T[0] * KK[16] * TT[0] * v).y;
					ver[18].z = (T[17] * KK[18] * TT[17] * T[16] * KK[17] * TT[16] * T[0] * KK[16] * TT[0] * v).z;*/
					ffout << "v18 " << ver[18].x << " " << ver[18].y << " " << ver[18].z << endl;
					v.x = ver[19].x;
					v.y = ver[19].y;
					v.z = ver[19].z;
					ver[19].x = ( TT[0] * v).x;
					ver[19].y = ( TT[0] * v).y;
					ver[19].z = (TT[0] * v).z;
					/*ver[19].x = (T[18] * KK[19] * TT[18] * T[17] * KK[18] * TT[17] * T[16] * KK[17] * TT[16] * T[0] * KK[16] * TT[0] * v).x;
					ver[19].y = (T[18] * KK[19] * TT[18] * T[17] * KK[18] * TT[17] * T[16] * KK[17] * TT[16] * T[0] * KK[16] * TT[0] * v).y;
					ver[19].z = (T[18] * KK[19] * TT[18] * T[17] * KK[18] * TT[17] * T[16] * KK[17] * TT[16] * T[0] * KK[16] * TT[0] * v).z;*/
					ffout << "v19 " << ver[19].x << " " << ver[19].y << " " << ver[19].z << endl;
				drawSkeleton(skeletonImage, skeletonPoint[i], i);
				
			}
		}
		imshow("skeletonImage", skeletonImage); //show image 
	}
	else
	{
		cout << "Buffer length of received texture is bogus\r\n" << endl;
	}

	char c;
	c = waitKey(10);
	if (c == 27)
	{
		NuiShutdown();
		ffout.close();
		exit(1);
	}

}

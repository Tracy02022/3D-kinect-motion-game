
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
Matrix Rotation(Vertex p1, Vertex p2,Vertex Dis)
{
	Vertex p11, p12,p;
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

	float l1, l2;
	l1 = sqrt(p11.x*p11.x + p11.y*p11.y + p11.z*p11.z);
	l2 = sqrt(p12.x*p12.x + p12.y*p12.y + p12.z*p12.z);
	costheta = p11.dotProduct(p12) / (l1*l2);
	sintheta = sqrt(1 - costheta*costheta);
	Matrix T1, T2, Ry1,Ry2,Rz1,Rz2,Rx,K;
	float elem1[4][4] = { { 1, 0, 0, -tmp.x }, {0,1,0,-tmp.y}, {0,0,1,-tmp.z}, {0,0,0,1} };
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
	float e1[4][4] = { { nl.x / edge, -nl.y / edge,0,  0 }, { nl.y/edge,nl.x/edge,  0, 0 }, { 0, 0, 1, 0 }, { 0, 0, 0, 1 } };
	float e2[4][4] = { { nl.x / edge, nl.y / edge, 0, 0 }, { -nl.y / edge, nl.x / edge, 0, 0 }, { 0, 0, 1, 0 }, { 0, 0, 0, 1 } };
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			Rz1.elem[i][j] = e1[i][j];
			Rz2.elem[i][j] = e2[i][j];
		}
	}
	float e[4][4] = { {1, 0, 0, 0 }, { 0, costheta, -sintheta, 0 }, { 0, sintheta, costheta, 0 }, { 0, 0, 0, 1 } };
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
	HRESULT hr = NuiInitialize(NUI_INITIALIZE_FLAG_USES_DEPTH_AND_PLAYER_INDEX | NUI_INITIALIZE_FLAG_USES_COLOR | NUI_INITIALIZE_FLAG_USES_SKELETON);
	if (hr != S_OK)
	{
		cout << "NuiInitialize failed" << endl;
		exit(-1);
	}
	
	h1 = CreateEvent(NULL, TRUE, FALSE, NULL);
	h2 = NULL;
	hr = NuiImageStreamOpen(NUI_IMAGE_TYPE_COLOR, NUI_IMAGE_RESOLUTION_640x480, 0, 2, h1, &h2);
	if (FAILED(hr))
	{
		cout << "Could not open image stream video" << endl;
		exit(-1);
	}
	h3 = CreateEvent(NULL, TRUE, FALSE, NULL);
	h4 = NULL;
	hr = NuiImageStreamOpen(NUI_IMAGE_TYPE_DEPTH_AND_PLAYER_INDEX, NUI_IMAGE_RESOLUTION_320x240, 0, 2, h3, &h4);
	if (FAILED(hr))
	{
		cout << "Could not open depth stream video" << endl;
		exit(-1);
	}
	h5 = CreateEvent(NULL, TRUE, FALSE, NULL);
	hr = NuiSkeletonTrackingEnable(h5, 0);
	if (FAILED(hr))
	{
		cout << "Could not open skeleton stream video" << endl;
		exit(-1);
	}
}

void skeleton::getSkeleton(Vector<Vertex> vt_list1)
{

	skeletonMat =cv:: Mat(SKELETON_HIGHT, SKELETON_WIDTH, CV_8UC3, Scalar(0, 0, 0));
	hr = NuiSkeletonGetNextFrame(0, &SkeletonFrame);
	if (FAILED(hr))
	{
		cout << "Get Skeleton Image Frame Failed" << endl;
	}
	bFoundSkeleton = false;
	for (int i = 0; i < NUI_SKELETON_COUNT; i++)
	{
		if (SkeletonFrame.SkeletonData[i].eTrackingState == NUI_SKELETON_TRACKED)
		{
			bFoundSkeleton = true;		
			/*for (int j = 0; j < NUI_SKELETON_POSITION_COUNT; j++)
			{
				oldPos[j].x = SkeletonFrame.SkeletonData[i].SkeletonPositions[j].x;	
				oldPos[j].y = SkeletonFrame.SkeletonData[i].SkeletonPositions[j].y;
				oldPos[j].z = SkeletonFrame.SkeletonData[i].SkeletonPositions[j].z;
				printf(" distance %f, %f, %f\n", oldPos[j].x, oldPos[j].y, oldPos[j].z);
			}*/
		}
	}
	
	if (bFoundSkeleton)
	{
		NuiTransformSmooth(&SkeletonFrame, NULL);
		Vertex Dis[20];
		Vertex p1, p2;
		for (int i = 0; i <NUI_SKELETON_COUNT; i++)
		{
			if (SkeletonFrame.SkeletonData[i].eTrackingState == NUI_SKELETON_TRACKED&&SkeletonFrame.SkeletonData[i].eSkeletonPositionTrackingState[NUI_SKELETON_POSITION_SHOULDER_CENTER] != NUI_SKELETON_POSITION_NOT_TRACKED)
			{
				
				for (int j = 0; j < NUI_SKELETON_POSITION_COUNT; j++)
				{
					float fx, fy;
					NuiTransformSkeletonToDepthImage(SkeletonFrame.SkeletonData[i].SkeletonPositions[j], &fx, &fy);
					pt[j].x = (int)((fx) * SKELETON_WIDTH) / 320;
					pt[j].y = (int)((fy) * SKELETON_HIGHT) / 240;
					/*printf("point on screen: %d, %d\n", pt[j].x, pt[j].y);*/
					/*oldPos[j].x = SkeletonFrame.SkeletonData[i].SkeletonPositions[j].x;
					oldPos[j].y = SkeletonFrame.SkeletonData[i].SkeletonPositions[j].y;*/
					oldPos[j].x = fx;
					oldPos[j].y = fy;
					oldPos[j].z = SkeletonFrame.SkeletonData[i].SkeletonPositions[j].z * 100;
					printf(" oldPos point:  %f, %f, %f\n", oldPos[j].x, oldPos[j].y, oldPos[j].z);
					circle(skeletonMat, pt[j], 4, CV_RGB(255, 0, 0));
					if (j == 0)
					{
						Dis[j].x = Distance(oldPos[j], oldPos[j - 1]).x;
						Dis[j].y = Distance(oldPos[j], oldPos[j - 1]).y;
						Dis[j].z = Distance(oldPos[j], oldPos[j - 1]).z;
						if (eLenth(Dis[j]) == 0.0)
						{
							float ee[4][4] = { { 1, 0, 0, 0 }, { 0, 1, 0, 0 }, { 0, 0, 1, 0 }, { 0, 0, 0, 1 } };
							for (int i = 0; i < 4; i++)
							{
								for (int j = 0; j < 4; j++)
								{
									KK[j].elem[i][j] = ee[i][j];
								}
							}

						}
						else
						{
							p1.x = SkeletonFrame.SkeletonData[i].SkeletonPositions[j].x;
							p1.y = SkeletonFrame.SkeletonData[i].SkeletonPositions[j].y;
							p1.z = SkeletonFrame.SkeletonData[i].SkeletonPositions[j].z;
							
							float ee[4][4] = { { 1, 0, 0, -p1.x }, { 0, 1, 0, -p1.y }, { 0, 0, 1, -p1.z }, { 0, 0, 0, 1 } };
							for (int i = 0; i < 4; i++)
							{
								for (int j = 0; j < 4; j++)
								{
									KK[j].elem[i][j] = ee[i][j];
								}
							}
							float ee2[4][4] = { { 1, 0, 0, p1.x }, { 0, 1, 0, p1.y }, { 0, 0, 1, p1.z }, { 0, 0, 0, 1 } };
							for (int i = 0; i < 4; i++)
							{
								for (int j = 0; j < 4; j++)
								{
									KK[20].elem[i][j] = ee[i][j];
								}
							}
						//	KK[j] = Rotation(p1, p2, Dis[j]);
						}
					}
					else if (j == 1||j == 2 ||j==3||j == 5||j ==6||j == 7||j==9||j==10||j==11||j == 13||j==14||j == 15||j == 17||j==18||j==19)
					{	
						
						Dis[j].x = Distance(oldPos[j], oldPos[j - 1]).x;
						Dis[j].y = Distance(oldPos[j], oldPos[j - 1]).y;
						Dis[j].z = Distance(oldPos[j], oldPos[j - 1]).z;
						if (eLenth(Dis[j])==0.0)
						{
							float ee[4][4] = { { 1, 0, 0, 0 }, { 0, 1, 0, 0 }, { 0, 0, 1, 0 }, { 0, 0, 0, 1 } };
							for (int i = 0; i < 4; i++)
							{
								for (int j = 0; j < 4; j++)
								{
									KK[j].elem[i][j] = ee[i][j];
								}
							}
							
						}
						else
						{
							p1.x = SkeletonFrame.SkeletonData[i].SkeletonPositions[j].x;
							p1.y = SkeletonFrame.SkeletonData[i].SkeletonPositions[j].y;
							p1.z = SkeletonFrame.SkeletonData[i].SkeletonPositions[j].z;
							p2.x = SkeletonFrame.SkeletonData[i].SkeletonPositions[j - 1].x;
							p2.y = SkeletonFrame.SkeletonData[i].SkeletonPositions[j - 1].y;
							p2.z = SkeletonFrame.SkeletonData[i].SkeletonPositions[j - 1].z;
							KK[j] = Rotation(p1, p2, Dis[j]);
						}
				//		printf("matrix  %f \n", KK[j].elem[1][2]);
						
					}
					else if (j == 4)
					{
						Dis[j].x = Distance(oldPos[j], oldPos[j - 2]).x;
						Dis[j].y = Distance(oldPos[j], oldPos[j - 2]).y;
						Dis[j].z = Distance(oldPos[j], oldPos[j - 2]).z;
						if (eLenth(Dis[j]) == 0.0)
						{
							float ee[4][4] = { { 1, 0, 0, 0 }, { 0, 1, 0, 0 }, { 0, 0, 1, 0 }, { 0, 0, 0, 1 } };
							for (int i = 0; i < 4; i++)
							{
								for (int j = 0; j < 4; j++)
								{
									KK[j].elem[i][j] = ee[i][j];
								}
							}

						}
						else
						{
							p1.x = SkeletonFrame.SkeletonData[i].SkeletonPositions[j].x;
							p1.y = SkeletonFrame.SkeletonData[i].SkeletonPositions[j].y;
							p1.z = SkeletonFrame.SkeletonData[i].SkeletonPositions[j].z;
							p2.x = SkeletonFrame.SkeletonData[i].SkeletonPositions[j - 2].x;
							p2.y = SkeletonFrame.SkeletonData[i].SkeletonPositions[j - 2].y;
							p2.z = SkeletonFrame.SkeletonData[i].SkeletonPositions[j - 2].z;
							KK[j] = Rotation(p1, p2, Dis[j]);
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
							for (int i = 0; i < 4; i++)
							{
								for (int j = 0; j < 4; j++)
								{
									KK[j].elem[i][j] = ee[i][j];
								}
							}

						}
						else
						{
							p1.x = SkeletonFrame.SkeletonData[i].SkeletonPositions[j].x;
							p1.y = SkeletonFrame.SkeletonData[i].SkeletonPositions[j].y;
							p1.z = SkeletonFrame.SkeletonData[i].SkeletonPositions[j].z;
							p2.x = SkeletonFrame.SkeletonData[i].SkeletonPositions[j - 6].x;
							p2.y = SkeletonFrame.SkeletonData[i].SkeletonPositions[j - 6].y;
							p2.z = SkeletonFrame.SkeletonData[i].SkeletonPositions[j - 6].z;
							KK[j] = Rotation(p1, p2, Dis[j]);
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
							for (int i = 0; i < 4; i++)
							{
								for (int j = 0; j < 4; j++)
								{
									KK[j].elem[i][j] = ee[i][j];
								}
							}

						}
						else
						{
							p1.x = SkeletonFrame.SkeletonData[i].SkeletonPositions[j].x;
							p1.y = SkeletonFrame.SkeletonData[i].SkeletonPositions[j].y;
							p1.z = SkeletonFrame.SkeletonData[i].SkeletonPositions[j].z;
							p2.x = SkeletonFrame.SkeletonData[i].SkeletonPositions[0].x;
							p2.y = SkeletonFrame.SkeletonData[i].SkeletonPositions[0].y;
							p2.z = SkeletonFrame.SkeletonData[i].SkeletonPositions[0].z;
							KK[j] = Rotation(p1, p2, Dis[j]);
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
							for (int i = 0; i < 4; i++)
							{
								for (int j = 0; j < 4; j++)
								{
									KK[j].elem[i][j] = ee[i][j];
								}
							}

						}
						else
						{
							p1.x = SkeletonFrame.SkeletonData[i].SkeletonPositions[j].x;
							p1.y = SkeletonFrame.SkeletonData[i].SkeletonPositions[j].y;
							p1.z = SkeletonFrame.SkeletonData[i].SkeletonPositions[j].z;
							p2.x = SkeletonFrame.SkeletonData[i].SkeletonPositions[0].x;
							p2.y = SkeletonFrame.SkeletonData[i].SkeletonPositions[0].y;
							p2.z = SkeletonFrame.SkeletonData[i].SkeletonPositions[0].z;
							KK[j] = Rotation(p1, p2, Dis[j]);
						}
					}
				}
				for (int k = 0; k < vt_list1.size(); k++)
				{
				
					vt_list1[k].x = vt_list1[k].x * (vt_list1[k].weight[1]+vt_list1[k].weight[0]) +
						vt_list1[k].x * (vt_list1[k].weight[2]) +
						vt_list1[k].x * (vt_list1[k].weight[3]) +
						(KK[0] * KK[1] * KK[2] * KK[4] * KK[20] * vt_list1[k]).x * (vt_list1[k].weight[4]) +
						(KK[0] * KK[1] * KK[2] * KK[4] * KK[5] * KK[20] * vt_list1[k]).x * (vt_list1[k].weight[5]) +
						(KK[0] * KK[1] * KK[2] * KK[4] * KK[5] * KK[6] * KK[20] * vt_list1[k]).x * (vt_list1[k].weight[6]) +
						(KK[0] * KK[1] * KK[2] * KK[4] * KK[5] * KK[6] * KK[7] * KK[20] * vt_list1[k]).x * (vt_list1[k].weight[7]) + vt_list1[k].x * (vt_list1[k].weight[8]) +
						vt_list1[k].x * (vt_list1[k].weight[9]) +
						vt_list1[k].x * (vt_list1[k].weight[10]) +
						 vt_list1[k].x * (vt_list1[k].weight[11]) +
						vt_list1[k].x * (vt_list1[k].weight[12]) +
						vt_list1[k].x * (vt_list1[k].weight[13]) +
						vt_list1[k].x * (vt_list1[k].weight[14]) +
						vt_list1[k].x * (vt_list1[k].weight[15]) +
						vt_list1[k].x * (vt_list1[k].weight[16]) +
						vt_list1[k].x * (vt_list1[k].weight[17]) +
						vt_list1[k].x * (vt_list1[k].weight[18]) +
						vt_list1[k].x * (vt_list1[k].weight[19]);
					vt_list1[k].y = vt_list1[k].y * (vt_list1[k].weight[1] + vt_list1[k].weight[0]) +
						vt_list1[k].y * (vt_list1[k].weight[2]) +
						vt_list1[k].y * (vt_list1[k].weight[3]) +
						(KK[0] * KK[1] * KK[2] * KK[4] * KK[20] * vt_list1[k]).y * (vt_list1[k].weight[4]) +
						(KK[0] * KK[1] * KK[2] * KK[4] * KK[5] * KK[20] * vt_list1[k]).y * (vt_list1[k].weight[5]) +
						(KK[0] * KK[1] * KK[2] * KK[4] * KK[5] * KK[6] * KK[20] * vt_list1[k]).y * (vt_list1[k].weight[6]) +
						(KK[0] * KK[1] * KK[2] * KK[4] * KK[5] * KK[6] * KK[7] * KK[20] * vt_list1[k]).y * (vt_list1[k].weight[7]) + vt_list1[k].y * (vt_list1[k].weight[8]) +
						vt_list1[k].y * (vt_list1[k].weight[9]) +
						vt_list1[k].y * (vt_list1[k].weight[10]) +
						vt_list1[k].y * (vt_list1[k].weight[11]) +
						vt_list1[k].y * (vt_list1[k].weight[12]) +
						vt_list1[k].y * (vt_list1[k].weight[13]) +
						vt_list1[k].y * (vt_list1[k].weight[14]) +
						vt_list1[k].y * (vt_list1[k].weight[15]) +
						vt_list1[k].y * (vt_list1[k].weight[16]) +
						vt_list1[k].y * (vt_list1[k].weight[17]) +
						vt_list1[k].y * (vt_list1[k].weight[18]) +
						vt_list1[k].y * (vt_list1[k].weight[19]);
					vt_list1[k].z = vt_list1[k].z * (vt_list1[k].weight[1] + vt_list1[k].weight[0]) +
						vt_list1[k].z * (vt_list1[k].weight[2]) +
						vt_list1[k].z * (vt_list1[k].weight[3]) +
						(KK[0] * KK[1] * KK[2] * KK[4] * KK[20] * vt_list1[k]).z * (vt_list1[k].weight[4]) +
						(KK[0] * KK[1] * KK[2] * KK[4] * KK[5] * KK[20] * vt_list1[k]).z * (vt_list1[k].weight[5]) +
						(KK[0] * KK[1] * KK[2] * KK[4] * KK[5] * KK[6] * KK[20] * vt_list1[k]).z * (vt_list1[k].weight[6]) +
						(KK[0] * KK[1] * KK[2] * KK[4] * KK[5] * KK[6] * KK[7] * KK[20] * vt_list1[k]).z * (vt_list1[k].weight[7]) + vt_list1[k].z * (vt_list1[k].weight[8]) +
						vt_list1[k].z * (vt_list1[k].weight[9]) +
						vt_list1[k].z * (vt_list1[k].weight[10]) +
						vt_list1[k].z * (vt_list1[k].weight[11]) +
						vt_list1[k].z * (vt_list1[k].weight[12]) +
						vt_list1[k].z * (vt_list1[k].weight[13]) +
						vt_list1[k].z * (vt_list1[k].weight[14]) +
						vt_list1[k].z * (vt_list1[k].weight[15]) +
						vt_list1[k].z * (vt_list1[k].weight[16]) +
						vt_list1[k].z * (vt_list1[k].weight[17]) +
						vt_list1[k].z * (vt_list1[k].weight[18]) +
						vt_list1[k].z * (vt_list1[k].weight[19]);
				}	
			}
		}
	}
	imshow("skeleton", skeletonMat);
}

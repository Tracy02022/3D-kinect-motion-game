#include<string>
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <functional> 
#include<math.h>
#include"skeleton.h"
#include <algorithm>

bool ct;
/*color of surface, ambient, phong and light*/
Vertex Cr, Ca, Cl, Cp;
/*light position*/
Vertex l;
/*Switch between different files*/
bool mesh = true;
Vertex ver[20], v;
skeleton sk;
ofstream fout;
char filename[] = "hi.txt";
int Mode;

/*look at point*/
float ex, ey, ez, ox, oy, oz, hx, hy, hz;
float rot, lot;
Matrix T1, T2, T3, T4, T5, T6, Ts, Tss, TS, TSS;
float angle, langle, angle1, langle1;
int mouse_down = 0;
/*0 means change eye position; 1 means change focus position*/
int change_mode = 0;
int current_x = 0, current_y = 0;
vector<Vertex> vt_list1, vt_list2;
bool R, L;
/*store every triangles in the different lists of each file*/
vector<Triangle> tg_list1;
/*center point in bunny_low file*/
vector<Weight> w_list;
float middle1, middle2, middle3;
float m1, m2, m3;
void readFile()
{
	string filename;
	filename = "newcopy.txt";
	ifstream file(filename);
	char c;
	float f1, f2, f3;
	while (!file.eof())
	{
		file >> c >> f1 >> f2 >> f3;
		if (c == 'v')
		{
			Vertex vertex;
			vertex.x = f1;
			vertex.y = f2;
			vertex.z = -f3;
			middle1 += f1;
			middle2 += f2;
			middle3 += -f3;
			/*compute for center using*/

			for (int i = 0; i < 20; i++)
				vertex.weight[i] = 0.0;
			vt_list1.push_back(vertex);
			vt_list2.push_back(vertex);
		}
		else if (c == 'f')
		{
			Triangle triangle;
			triangle.v1 = f1;
			triangle.v2 = f2;
			triangle.v3 = f3;
			tg_list1.push_back(triangle);
		}
		else
		{
			Weight weight;
			weight.num = f1;
			weight.w = f2;
			weight.ske = f3 - 1;
			w_list.push_back(weight);

		}
	}

	for (int i = 0; i < w_list.size(); i++)
	{
		vt_list1[w_list[i].num].weight[w_list[i].ske] = w_list[i].w;

	}
	middle1 = 1.0*middle1 / vt_list1.size();
	middle2 = 1.0*middle2 / vt_list1.size();
	middle3 = 1.0*middle3 / vt_list1.size();


}

/*initialization*/
void initialize()
{
	
	sk.init();
	sk.count = false;
	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, 800, 800);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2.0, 2.0, -2.0, 2.0, -10, 10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, -10, 0, 0, 0, 0, 2, 0);
	//	gluLookAt(0.929, 3, 0.389, 0.929, 0.389, 0.389, 0.0, 0.0, 0.389);
}
void OnIdle()
{

	sk.getSkeleton(ver);

	glutPostRedisplay();
}
/*display and refresh the bunny*/
void onDisplay()
{
	
	
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		/*glMatrixMode(GL_PROJECTION);*/

		glColor3f(0.0, 1.0, 0.0);
		/*glBegin(GL_TRIANGLES);*/


		glBegin(GL_LINES);
		glVertex3f(ver[0].x, ver[0].y, ver[0].z);
		glVertex3f(ver[1].x, ver[1].y, ver[1].z);
		//	glEnd();

		glBegin(GL_LINES);
		glVertex3f(ver[2].x, ver[2].y, ver[2].z);
		glVertex3f(ver[1].x, ver[1].y, ver[1].z);
		//	glEnd();

		glBegin(GL_LINES);
		glVertex3f(ver[2].x, ver[2].y, ver[2].z);
		glVertex3f(ver[3].x, ver[3].y, ver[3].z);
		//	glEnd();

		glBegin(GL_LINES);
		glVertex3f(ver[2].x, ver[2].y, ver[2].z);
		glVertex3f(ver[4].x, ver[4].y, ver[4].z);
		//	glEnd();

		glBegin(GL_LINES);
		glVertex3f(ver[4].x, ver[4].y, ver[4].z);
		glVertex3f(ver[5].x, ver[5].y, ver[5].z);
		//	glEnd();

		glBegin(GL_LINES);
		glVertex3f(ver[6].x, ver[6].y, ver[6].z);
		glVertex3f(ver[5].x, ver[5].y, ver[5].z);

		glBegin(GL_LINES);
		glVertex3f(ver[6].x, ver[6].y, ver[6].z);
		glVertex3f(ver[7].x, ver[7].y, ver[7].z);

		glBegin(GL_LINES);
		glVertex3f(ver[2].x, ver[2].y, ver[2].z);
		glVertex3f(ver[8].x, ver[8].y, ver[8].z);
		//		glEnd();
		glBegin(GL_LINES);
		glVertex3f(ver[8].x, ver[8].y, ver[8].z);
		glVertex3f(ver[9].x, ver[9].y, ver[9].z);
		//	glEnd();

		glBegin(GL_LINES);
		glVertex3f(ver[9].x, ver[9].y, ver[9].z);
		glVertex3f(ver[10].x, ver[10].y, ver[10].z);
		//	glEnd();

		glBegin(GL_LINES);
		glVertex3f(ver[10].x, ver[10].y, ver[10].z);
		glVertex3f(ver[11].x, ver[11].y, ver[11].z);
		//	glEnd();

		glBegin(GL_LINES);
		glVertex3f(ver[0].x, ver[0].y, ver[0].z);
		glVertex3f(ver[16].x, ver[16].y, ver[16].z);
		//		glEnd();

		glBegin(GL_LINES);
		glVertex3f(ver[17].x, ver[17].y, ver[17].z);
		glVertex3f(ver[16].x, ver[16].y, ver[16].z);
		//		glEnd();

		glBegin(GL_LINES);
		glVertex3f(ver[17].x, ver[17].y, ver[17].z);
		glVertex3f(ver[18].x, ver[18].y, ver[18].z);
		//		glEnd();

		glBegin(GL_LINES);
		glVertex3f(ver[18].x, ver[18].y, ver[18].z);
		glVertex3f(ver[19].x, ver[19].y, ver[19].z);
		//		glEnd();

		glBegin(GL_LINES);
		glVertex3f(ver[0].x, ver[0].y, ver[0].z);
		glVertex3f(ver[12].x, ver[12].y, ver[12].z);
		//		glEnd();

		glBegin(GL_LINES);
		glVertex3f(ver[12].x, ver[12].y, ver[12].z);
		glVertex3f(ver[13].x, ver[13].y, ver[13].z);
		//		glEnd();

		glBegin(GL_LINES);
		glVertex3f(ver[13].x, ver[13].y, ver[13].z);
		glVertex3f(ver[14].x, ver[14].y, ver[14].z);
		//		glEnd();

		glBegin(GL_LINES);
		glVertex3f(ver[15].x, ver[15].y, ver[15].z);
		glVertex3f(ver[14].x, ver[14].y, ver[14].z);
		glEnd();

		glutSwapBuffers();//display the buffer
		char c;
		c = waitKey(10);
		if (c == 27)
		{
			NuiShutdown();
			exit(1);
		}
		
	
}
void onKeyboard(unsigned char key, int x, int y)
{
	if (key == 27)
		exit(1);
	else if (key == 'R')
	{

		float m1, m2, m3;
		angle = 10 * 3.14 / 180;

		float elem1[4][4] = { { cos(angle), 0, sin(angle), 0 }, { 0, 1, 0, 0 }, { -sin(angle), 0, cos(angle), 0 }, { 0, 0, 0, 1 } };
		float elem2[4][4] = { { 1, 0, 0, -ver[4].x }, { 0, 1, 0, -ver[4].y }, { 0, 0, 1, -ver[4].z }, { 0, 0, 0, 1 } };
		float elem3[4][4] = { { 1, 0, 0, ver[4].x }, { 0, 1, 0, ver[4].y }, { 0, 0, 1, ver[4].z }, { 0, 0, 0, 1 } };

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				T1.elem[i][j] = elem1[i][j];
				T2.elem[i][j] = elem2[i][j];
				T3.elem[i][j] = elem3[i][j];
				//			T4.elem[i][j] = elem8[i][j];
			}
		}
		v.x = ver[5].x;
		v.y = ver[5].y;
		v.z = ver[5].z;
		ver[5].x = (T3*T1*T2*v).x;
		ver[5].y = (T3*T1*T2*v).y;
		ver[5].z = (T3*T1*T2*v).z;
		float elem4[4][4] = { { 1, 0, 0, -ver[5].x }, { 0, 1, 0, -ver[5].y }, { 0, 0, 1, -ver[5].z }, { 0, 0, 0, 1 } };
		float elem5[4][4] = { { 1, 0, 0, ver[5].x }, { 0, 1, 0, ver[5].y }, { 0, 0, 1, ver[5].z }, { 0, 0, 0, 1 } };
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				Ts.elem[i][j] = elem4[i][j];
				Tss.elem[i][j] = elem5[i][j];

			}
		}
		v.x = ver[6].x;
		v.y = ver[6].y;
		v.z = ver[6].z;
		ver[6].x = (Tss*T1*Ts*T3*T1*T2*v).x;
		ver[6].y = (Tss*T1*Ts*T3*T1*T2*v).y;
		ver[6].z = (Tss*T1*Ts*T3*T1*T2*v).z;
		float elem6[4][4] = { { 1, 0, 0, -ver[6].x }, { 0, 1, 0, -ver[6].y }, { 0, 0, 1, -ver[6].z }, { 0, 0, 0, 1 } };
		float elem7[4][4] = { { 1, 0, 0, ver[6].x }, { 0, 1, 0, ver[6].y }, { 0, 0, 1, ver[6].z }, { 0, 0, 0, 1 } };
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				TS.elem[i][j] = elem6[i][j];
				TSS.elem[i][j] = elem7[i][j];

			}
		}
		v.x = ver[7].x;
		v.y = ver[7].y;
		v.z = ver[7].z;
		ver[7].x = (TSS*TS*Tss*T1*Ts*T3*T1*T2*v).x;
		ver[7].y = (TSS*TS*Tss*Ts*T1*T3*T1*T2*v).y;
		ver[7].z = (TSS*TS*Tss*Ts*T3*T1*T1*T2*v).z;

	}
	else if (key == 'L')
	{
		cout << "hello " << endl;

		angle1 = 10 * 3.14 / 180;
		cout << sin(langle) << endl;
		cout << cos(langle) << endl;

		float elem8[4][4] = { { cos(angle1), 0, -sin(angle1), 0 }, { 0, 1, 0, 0 }, { sin(angle1), 0, cos(angle1), 0 }, { 0, 0, 0, 1 } };
		float m1, m2, m3;
		float elem1[4][4] = { { cos(angle), 0, -sin(angle), 0 }, { 0, 1, 0, 0 }, { sin(angle), 0, cos(angle), 0 }, { 0, 0, 0, 1 } };
		float elem2[4][4] = { { 1, 0, 0, -ver[4].x }, { 0, 1, 0, -ver[4].y }, { 0, 0, 1, -ver[4].z }, { 0, 0, 0, 1 } };
		float elem3[4][4] = { { 1, 0, 0, ver[4].x }, { 0, 1, 0, ver[4].y }, { 0, 0, 1, ver[4].z }, { 0, 0, 0, 1 } };

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				T4.elem[i][j] = elem1[i][j];
				T5.elem[i][j] = elem2[i][j];
				T6.elem[i][j] = elem3[i][j];
				T1.elem[i][j] = elem8[i][j];
			}
		}
		v.x = ver[5].x;
		v.y = ver[5].y;
		v.z = ver[5].z;
		ver[5].x = (T6*T4*T5*v).x;
		ver[5].y = (T6*T4*T5*v).y;
		ver[5].z = (T6*T4*T5*v).z;
		float elem4[4][4] = { { 1, 0, 0, -ver[5].x }, { 0, 1, 0, -ver[5].y }, { 0, 0, 1, -ver[5].z }, { 0, 0, 0, 1 } };
		float elem5[4][4] = { { 1, 0, 0, ver[5].x }, { 0, 1, 0, ver[5].y }, { 0, 0, 1, ver[5].z }, { 0, 0, 0, 1 } };
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				Ts.elem[i][j] = elem4[i][j];
				Tss.elem[i][j] = elem5[i][j];

			}
		}
		v.x = ver[6].x;
		v.y = ver[6].y;
		v.z = ver[6].z;
		ver[6].x = (Tss*T4*Ts*T6*T4*T5*v).x;
		ver[6].y = (Tss*T4*Ts*T6*T4*T5*v).y;
		ver[6].z = (Tss*T4*Ts*T6*T4*T5*v).z;
		float elem6[4][4] = { { 1, 0, 0, -ver[6].x }, { 0, 1, 0, -ver[6].y }, { 0, 0, 1, -ver[6].z }, { 0, 0, 0, 1 } };
		float elem7[4][4] = { { 1, 0, 0, ver[6].x }, { 0, 1, 0, ver[6].y }, { 0, 0, 1, ver[6].z }, { 0, 0, 0, 1 } };
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				TS.elem[i][j] = elem6[i][j];
				TSS.elem[i][j] = elem7[i][j];

			}
		}
		v.x = ver[7].x;
		v.y = ver[7].y;
		v.z = ver[7].z;
		ver[7].x = (TSS*TS*Tss*T4*Ts*T6*T4*T5*v).x;
		ver[7].y = (TSS*TS*Tss*T4*Ts*T6*T4*T5*v).y;
		ver[7].z = (TSS*TS*Tss*T4*Ts*T6*T4*T5*v).z;
	}
	else if (key == 'H')
	{
		cout << "hello" << endl;


		cout << sin(angle) << endl;
		cout << cos(angle) << endl;

		angle1 = 10 * 3.14 / 180;
		cout << angle1 << endl;
		float elem11[4][4] = { { 1, 0, 0, 0 }, { 0, cos(angle1), sin(angle1), 0 }, { 0, -sin(angle1), cos(angle1), 0 }, { 0, 0, 0, 1 } };
		float elem1[4][4] = { { 1, 0, 0, 0 }, { 0, cos(angle1), -sin(angle1), 0 }, { 0, sin(angle1), cos(angle1), 0 }, { 0, 0, 0, 1 } };
		float elem2[4][4] = { { 1, 0, 0, -ver[0].x }, { 0, 1, 0, -ver[0].y }, { 0, 0, 1, -ver[0].z }, { 0, 0, 0, 1 } };
		float elem3[4][4] = { { 1, 0, 0, ver[0].x }, { 0, 1, 0, ver[0].y }, { 0, 0, 1, ver[0].z }, { 0, 0, 0, 1 } };


		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				T1.elem[i][j] = elem1[i][j];
				T2.elem[i][j] = elem2[i][j];
				T3.elem[i][j] = elem3[i][j];
				T4.elem[i][j] = elem11[i][j];
			}
		}
		v.x = ver[12].x;
		v.y = ver[12].y;
		v.z = ver[12].z;
		ver[12].x = (T3*T2*v).x;
		ver[12].y = (T3*T2*v).y;
		ver[12].z = (T3*T2*v).z;
		float elem4[4][4] = { { 1, 0, 0, -ver[12].x }, { 0, 1, 0, -ver[12].y }, { 0, 0, 1, -ver[12].z }, { 0, 0, 0, 1 } };
		float elem5[4][4] = { { 1, 0, 0, ver[12].x }, { 0, 1, 0, ver[12].y }, { 0, 0, 1, ver[12].z }, { 0, 0, 0, 1 } };
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				Ts.elem[i][j] = elem4[i][j];
				Tss.elem[i][j] = elem5[i][j];

			}
		}
		v.x = ver[13].x;
		v.y = ver[13].y;
		v.z = ver[13].z;
		ver[13].x = (Tss*T1*Ts*T3*T2*v).x;
		ver[13].y = (Tss*T1*Ts*T3*T2*v).y;
		ver[13].z = (Tss*T1*Ts*T3*T2*v).z;
		float elem6[4][4] = { { 1, 0, 0, -ver[13].x }, { 0, 1, 0, -ver[13].y }, { 0, 0, 1, -ver[13].z }, { 0, 0, 0, 1 } };
		float elem7[4][4] = { { 1, 0, 0, ver[13].x }, { 0, 1, 0, ver[13].y }, { 0, 0, 1, ver[13].z }, { 0, 0, 0, 1 } };
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				TS.elem[i][j] = elem6[i][j];
				TSS.elem[i][j] = elem7[i][j];

			}
		}
		/*fout << "HELLO WORLD" << endl;
		fout << "HELLO WORLD" << endl;*/
		v.x = ver[14].x;
		v.y = ver[14].y;
		v.z = ver[14].z;
		ver[14].x = (TSS*T4*TS*Tss*T1*Ts*T3*T2*v).x;
		ver[14].y = (TSS*T4*TS*Tss*T1*Ts*T3*T2*v).y;
		ver[14].z = (TSS*T4*TS*Tss*T1*Ts*T3*T2*v).z;

		float elem8[4][4] = { { 1, 0, 0, -ver[14].x }, { 0, 1, 0, -ver[14].y }, { 0, 0, 1, -ver[14].z }, { 0, 0, 0, 1 } };
		float elem9[4][4] = { { 1, 0, 0, ver[14].x }, { 0, 1, 0, ver[14].y }, { 0, 0, 1, ver[14].z }, { 0, 0, 0, 1 } };
		Matrix s, ss;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				s.elem[i][j] = elem8[i][j];
				ss.elem[i][j] = elem9[i][j];

			}
		}
		v.x = ver[15].x;
		v.y = ver[15].y;
		v.z = ver[15].z;
		ver[15].x = (ss*s*TSS*T4*TS*Tss*T1*Ts*T3*T2*v).x;
		ver[15].y = (ss*s*TSS*T4*TS*Tss*T1*Ts*T3*T2*v).y;
		ver[15].z = (ss*s*TSS*T4*TS*Tss*T1*Ts*T3*T2*v).z;

	}
	else if (key == 'J')
	{
		cout << sin(angle) << endl;
		cout << cos(angle) << endl;

		angle1 = 10 * 3.14 / 180;
		cout << angle1 << endl;
		float elem11[4][4] = { { 1, 0, 0, 0 }, { 0, cos(angle1), -sin(angle1), 0 }, { 0, sin(angle1), cos(angle1), 0 }, { 0, 0, 0, 1 } };
		float elem1[4][4] = { { 1, 0, 0, 0 }, { 0, cos(angle1), sin(angle1), 0 }, { 0, -sin(angle1), cos(angle1), 0 }, { 0, 0, 0, 1 } };
		float elem2[4][4] = { { 1, 0, 0, -ver[0].x }, { 0, 1, 0, -ver[0].y }, { 0, 0, 1, -ver[0].z }, { 0, 0, 0, 1 } };
		float elem3[4][4] = { { 1, 0, 0, ver[0].x }, { 0, 1, 0, ver[0].y }, { 0, 0, 1, ver[0].z }, { 0, 0, 0, 1 } };


		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				T1.elem[i][j] = elem1[i][j];
				T2.elem[i][j] = elem2[i][j];
				T3.elem[i][j] = elem3[i][j];
				T4.elem[i][j] = elem11[i][j];
			}
		}
		v.x = ver[12].x;
		v.y = ver[12].y;
		v.z = ver[12].z;
		ver[12].x = (T3*T2*v).x;
		ver[12].y = (T3*T2*v).y;
		ver[12].z = (T3*T2*v).z;
		float elem4[4][4] = { { 1, 0, 0, -ver[12].x }, { 0, 1, 0, -ver[12].y }, { 0, 0, 1, -ver[12].z }, { 0, 0, 0, 1 } };
		float elem5[4][4] = { { 1, 0, 0, ver[12].x }, { 0, 1, 0, ver[12].y }, { 0, 0, 1, ver[12].z }, { 0, 0, 0, 1 } };
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				Ts.elem[i][j] = elem4[i][j];
				Tss.elem[i][j] = elem5[i][j];

			}
		}
		v.x = ver[13].x;
		v.y = ver[13].y;
		v.z = ver[13].z;
		ver[13].x = (Tss*T1*Ts*T3*T2*v).x;
		ver[13].y = (Tss*T1*Ts*T3*T2*v).y;
		ver[13].z = (Tss*T1*Ts*T3*T2*v).z;
		float elem6[4][4] = { { 1, 0, 0, -ver[13].x }, { 0, 1, 0, -ver[13].y }, { 0, 0, 1, -ver[13].z }, { 0, 0, 0, 1 } };
		float elem7[4][4] = { { 1, 0, 0, ver[13].x }, { 0, 1, 0, ver[13].y }, { 0, 0, 1, ver[13].z }, { 0, 0, 0, 1 } };
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				TS.elem[i][j] = elem6[i][j];
				TSS.elem[i][j] = elem7[i][j];

			}
		}

		v.x = ver[14].x;
		v.y = ver[14].y;
		v.z = ver[14].z;
		ver[14].x = (TSS*T4*TS*Tss*T1*Ts*T3*T2*v).x;
		ver[14].y = (TSS*T4*TS*Tss*T1*Ts*T3*T2*v).y;
		ver[14].z = (TSS*T4*TS*Tss*T1*Ts*T3*T2*v).z;

		float elem8[4][4] = { { 1, 0, 0, -ver[14].x }, { 0, 1, 0, -ver[14].y }, { 0, 0, 1, -ver[14].z }, { 0, 0, 0, 1 } };
		float elem9[4][4] = { { 1, 0, 0, ver[14].x }, { 0, 1, 0, ver[14].y }, { 0, 0, 1, ver[14].z }, { 0, 0, 0, 1 } };
		Matrix ss, s;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				s.elem[i][j] = elem8[i][j];
				ss.elem[i][j] = elem9[i][j];

			}
		}
		v.x = ver[15].x;
		v.y = ver[15].y;
		v.z = ver[15].z;
		ver[15].x = (ss*s*TSS*T4*TS*Tss*T1*Ts*T3*T2*v).x;
		ver[15].y = (ss*s*TSS*T4*TS*Tss*T1*Ts*T3*T2*v).y;
		ver[15].z = (ss*s*TSS*T4*TS*Tss*T1*Ts*T3*T2*v).z;
	}
	glutPostRedisplay();
}
void onMouse(int button, int state, int x, int y)
{
	GLint specialKey = glutGetModifiers();
	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN) {
			/*if the button is down change the variable's value*/
			mouse_down = 1;
			current_x = x;
			current_y = y;
			if (specialKey == GLUT_ACTIVE_SHIFT)
			{
				/*translate the bunny*/
				change_mode = 1;
			}
			else if (specialKey == GLUT_ACTIVE_CTRL)
			{
				/*Rotate around the center original*/
				change_mode = 2;
				/*compute the center point each time after refresh the window*/
				middle1 = 0;
				middle2 = 0;
				middle3 = 0;
				for (int i = 0; i < vt_list1.size(); i++)
				{
					middle1 += vt_list1[i].x;
					middle2 += vt_list1[i].y;
					middle3 += vt_list1[i].z;
				}
				middle1 = 1.0*middle1 / vt_list1.size();
				middle2 = 1.0*middle2 / vt_list1.size();
				middle3 = 1.0*middle3 / vt_list1.size();


			}
			else
			{
				/*Rotation the bunny*/
				change_mode = 0;
			}
		}
		else if (state == GLUT_UP)
		{
			mouse_down = 0;
		}
		break;
	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN)
			break;
	default:
		break;
	}
}
void onMouseMotion(int x, int y)
{
	if (mouse_down == 1)
	{
		if (change_mode == 0)
		{
			/*rotate the bunny around Rx and Ry*/
			Matrix Rx, Ry, Tx, Ty;
			Matrix RXRY;
			float theta;
			/*rotate angle*/
			theta = (x - current_x) / 100.f;
			float thetay = (y - current_y) / 100.f;
			float elemy[4][4] = { { cos(theta), 0, sin(theta), 0 }, { 0, 1, 0, 0 }, { -sin(theta), 0, cos(theta), 0 }, { 0, 0, 0, 1 } };
			float elemx[4][4] = { { 1, 0, 0, 0 }, { 0, cos(thetay), -sin(thetay), 0 }, { 0, sin(thetay), cos(thetay), 0 }, { 0, 0, 0, 1 } };
			float trans1[4][4] = { { 1, 0, 0, -middle1 }, { 0, 1, 0, -middle2 }, { 0, 0, 1, -middle3 }, { 0, 0, 0, 1 } };
			float trans2[4][4] = { { 1, 0, 0, middle1 }, { 0, 1, 0, middle2 }, { 0, 0, 1, middle3 }, { 0, 0, 0, 1 } };
			/*translation matrix*/
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					Tx.elem[i][j] = trans1[i][j];
					Ty.elem[i][j] = trans2[i][j];
				}
			}
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					Rx.elem[i][j] = elemy[i][j];
					Ry.elem[i][j] = elemx[i][j];
				}
			}
			/*rotation matrix*/
			RXRY = Ty* Rx*Ry*Tx;
			/*rotate with different situations*/
			for (int i = 0; i < vt_list1.size(); i++)
			{
				vt_list1[i].x = (RXRY*vt_list1[i]).x;
				vt_list1[i].y = (RXRY*vt_list1[i]).y;
				vt_list1[i].z = (RXRY*vt_list1[i]).z;
				//	vt_list1[i] = Rx*Ry*vt_list1[i];
			}
			for (int i = 0; i < 20; i++)
			{
				ver[i] = RXRY*ver[i];
				//		cout << i << " " << ver[i].x << " " << ver[i].y << " " << ver[i].z << endl;
			}

		}
		else if (change_mode == 1)
		{
			Matrix Tx;
			float pos1, pos2;
			pos1 = 1.0*(x - current_x) / 400.f;
			pos2 = 1.0*(y - current_y) / 400.f;
			float trans1[4][4] = { { 1, 0, 0, pos1 }, { 0, 1, 0, -pos2 }, { 0, 0, 1, 0 }, { 0, 0, 0, 1 } };
			/*translation matrix*/
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					Tx.elem[i][j] = trans1[i][j];
				}
			}
			/*translate with different situations*/
			for (int i = 0; i < vt_list1.size(); i++)
			{
				vt_list1[i].x = (Tx*vt_list1[i]).x;
				vt_list1[i].y = (Tx*vt_list1[i]).y;
				vt_list1[i].z = (Tx*vt_list1[i]).z;
				//			vt_list1[i] = Tx*vt_list1[i];
			}
			for (int i = 0; i < 20; i++)
			{
				ver[i] = Tx*ver[i];
				//			cout << i << " " << ver[i].x << " " << ver[i].y << " " << ver[i].z << endl;
			}
		}

		else
		{
			/*rotate with center origin*/
			Matrix T1, T2;
			Matrix Ry, Rx;
			Matrix P;
			float theta;
			theta = (x - current_x) / 100.f;
			float thetax = (y - current_y) / 100.f;
			float elemy[4][4] = { { cos(theta), 0, sin(theta), 0 }, { 0, 1, 0, 0 }, { -sin(theta), 0, cos(theta), 0 }, { 0, 0, 0, 1 } };
			float elemx[4][4] = { { 1, 0, 0, 0 }, { 0, cos(thetax), -sin(thetax), 0 }, { 0, sin(thetax), cos(thetax), 0 }, { 0, 0, 0, 1 } };
			float trans1[4][4] = { { 1, 0, 0, middle1 }, { 0, 1, 0, middle2 }, { 0, 0, 1, middle3 }, { 0, 0, 0, 1 } };
			float trans2[4][4] = { { 1, 0, 0, -middle1 }, { 0, 1, 0, -middle2 }, { 0, 0, 1, -middle3 }, { 0, 0, 0, 1 } };
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					T1.elem[i][j] = trans1[i][j];
					T2.elem[i][j] = trans2[i][j];
					Ry.elem[i][j] = elemy[i][j];
					Rx.elem[i][j] = elemx[i][j];
				}
			}
			/*rotation matrix with center origin*/
			P = T1*(Rx*Ry)*T2;
			for (int i = 0; i < vt_list1.size(); i++)
			{
				vt_list1[i].x = (P*vt_list1[i]).x;
				vt_list1[i].y = (P*vt_list1[i]).y;
				vt_list1[i].z = (P*vt_list1[i]).z;
			}
			for (int i = 0; i < 20; i++)
			{
				ver[i] = P*ver[i];
			}
		}
		current_x = x;
		current_y = y;
	}
	glutPostRedisplay();
}
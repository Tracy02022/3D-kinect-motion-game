#pragma once
#include"robot.h"

int main(int argc, char * argv[])
{
	middle1 = 0;
	middle2 = 0;
	middle3 = 0;
	m1 = m2 = m3 = 0;
	Cr.x = 0.9;
	Cr.y = 0.7;
	Cr.z = 0.1;
	Ca.x = 0.2;
	Ca.y = 0.2;
	Ca.z = 0.2;
	Cl.x = 0.9;
	Cl.y = 0.9;
	Cl.z = 0.9;
	Cp.x = Cp.y = Cp.z = 0.8;
	l.x = 0;
	l.y = 0;
	l.z = 5;
	rot = 0;
	lot = 0;
	ver[0].x = 0.929;
	ver[0].y = 0.389;
	ver[0].z = 0.641;
	ver[1].x = 0.929;
	ver[1].y = 0.653;
	ver[1].z = 0.641;
	ver[2].x = 0.929;
	ver[2].y = 0.812;
	ver[2].z = 0.641;
	ver[3].x = 0.929;
	ver[3].y = 1.048;
	ver[3].z = 0.641;

	ver[4].x = 1.154;
	ver[4].y = 0.812;
	ver[4].z = 0.641;
	ver[5].x = 1.334;
	ver[5].y = 0.777;
	ver[5].z = 0.641;
	ver[6].x = 1.480;
	ver[6].y = 0.751;
	ver[6].z = 0.588;
	ver[7].x = 1.531;
	ver[7].y = 0.751;
	ver[7].z = 0.549;

	ver[8].x = 0.704;
	ver[8].y = 0.812;
	ver[8].z = 0.641;
	ver[9].x = 0.524;
	ver[9].y = 0.777;
	ver[9].z = 0.641;
	ver[10].x = 0.378;
	ver[10].y = 0.751;
	ver[10].z = 0.588;
	ver[11].x = 0.327;
	ver[11].y = 0.751;
	ver[11].z = 0.549;

	ver[12].x = 1.019;
	ver[12].y = 0.389;
	ver[12].z = 0.641;
	ver[13].x = 1.101;
	ver[13].y = 0.235;
	ver[13].z = 0.641;
	ver[14].x = 1.088;
	ver[14].y = 0.081;
	ver[14].z = 0.641;
	ver[15].x = 1.126;
	ver[15].y = 0.026;
	ver[15].z = 0.538;

	ver[16].x = 0.839;
	ver[16].y = 0.386;
	ver[16].z = 0.641;
	ver[17].x = 0.757;
	ver[17].y = 0.235;
	ver[17].z = 0.641;
	ver[18].x = 0.770;
	ver[18].y = 0.081;
	ver[18].z = 0.641;
	ver[19].x = 0.732;
	ver[19].y = 0.026;
	ver[19].z = 0.538;
	for (int i = 0; i < 20; i++)
	{
		ver[i].z -= 1.2766;
		m1 += ver[i].x;
		m2 += ver[i].y;
		m3 += ver[i].z;
	}
	m1 = m1 / 20;
	m2 = m2 / 20;
	m3 = m3 / 20;
	cout << "m1 m2 m3: " << m1 << " " << m2 << " " << m3 << endl;
	ct = false;
	fout.open(filename);
	angle = langle = 0;
	/*Initialization functions*/
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(800, 0);
	glutCreateWindow("Xinhe");
	
	initialize();
	glutIdleFunc(OnIdle);

	/*read files*/
	readFile();
	glutDisplayFunc(onDisplay);
	glutKeyboardFunc(onKeyboard);
	/*glutMouseFunc(onMouse);
	glutMotionFunc(onMouseMotion);*/
	glutMainLoop();
	return 1;
}
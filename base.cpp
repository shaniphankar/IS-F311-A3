#include <stdio.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <GL/glut.h>
#include "glRoutines.h"
using namespace std;

void myDisplay(void)
{
	myInit ();
	glClear (GL_COLOR_BUFFER_BIT);
	glColor3f (0.0, 0.0, 0.0);
	glPointSize(2.0);
	for(int i=0;i<200;i++)
	{
		plot(i,0);
	}
	glutSwapBuffers ();
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize (1000,1000);
	glutInitWindowPosition(100,150);
	glutCreateWindow ("Curve");
	glutDisplayFunc(myDisplay);
	glutMainLoop();
}

#include <iostream>
#include <cmath>
#include <GL/glut.h>
#include "glRoutines.h"
using namespace std;

void plot(float x,float y)
{
	glBegin(GL_POINTS);
	glVertex2f(x,y);
	glEnd();
}

void myInit (void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.0f, 0.0f, 0.0f);
	glPointSize(4.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-500.0, 500.0, -500.0, 500.0);
}


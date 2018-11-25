#include <iostream>
#include <cmath>
#include <GL/glut.h>
#include "glRoutines.h"
using namespace std;
#define SCREEN_WIDTH 1366
#define SCREEN_HEIGHT 768

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
	glPointSize(2.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1*SCREEN_WIDTH/2, SCREEN_WIDTH/2, -1*SCREEN_HEIGHT/2, SCREEN_HEIGHT/2);
}


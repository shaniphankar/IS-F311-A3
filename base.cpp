#include <stdio.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include "glRoutines.h"
using namespace std;

#define SCREEN_WIDTH 1366
#define SCREEN_HEIGHT 720

vector<glm::vec2> controlPoints;
vector<glm::vec3> curvePoints;
glm::vec2 clickPoint;
int currentPointIndex;
int actualWidth;
int actualHeight;
int mouseDown=0;
clock_t beginTime;
clock_t endTime;
float timeDiff;

void addControlPoint(glm::vec2 P, int index)
{
    if (index < 0 || index >= controlPoints.size())
        controlPoints.push_back(P);
    else if (index < controlPoints.size())
        controlPoints.insert(controlPoints.begin() + index, P);
}

void deleteControlPoint(int index)
{
    if (index > -1)
    {
        controlPoints.erase(controlPoints.begin() + index);
    }
}
int closestPointIndex(glm::vec2 P)
{
	int index=-1;
	int minimumDistance=SCREEN_HEIGHT+SCREEN_WIDTH;
	for(int i=0;i<controlPoints.size();i++)
	{
		glm::vec2 P2=controlPoints.at(i);
		float dist= glm::dot(P-P2,P-P2);
		if(dist<minimumDistance)
		{
			minimumDistance=dist;
			index=i;
		}
	}
	return index;
}

void mouseInteraction(int button, int state, int x, int y)
{
	glm::vec2 mousePos=glm::vec2(x-(actualWidth+1)/2,(actualHeight+1)/2-y);//Change these values if the width changes due to resolution
	if(button==GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		currentPointIndex=closestPointIndex(mousePos);
		cout<<mousePos.x<<" "<<mousePos.y<<endl;
		clickPoint=glm::vec2(mousePos);
		beginTime=clock();
	}
	if(button==GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		cout<<mousePos.x<<" "<<mousePos.y<<endl;
		endTime=clock();
		timeDiff=float(endTime-beginTime)/CLOCKS_PER_SEC;
		if(timeDiff<=0.02||currentPointIndex<0)
		{
			addControlPoint(clickPoint);
			timeDiff=0;
		}
		else if(timeDiff>0.02)
		{
			deleteControlPoint(currentPointIndex);
			addControlPoint(mousePos,currentPointIndex);
		}
	}
}

void myDisplay(void)
{
	glClear (GL_COLOR_BUFFER_BIT);
	glColor3f (0.0, 0.0, 0.0);
	glPointSize(2.0);
	for(int i=0;i<200;i++)
	{
		plot(i,0);
	}
	actualWidth=glutGet(GLUT_WINDOW_WIDTH);
	actualHeight=glutGet(GLUT_WINDOW_HEIGHT);
	glutSwapBuffers ();
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize (SCREEN_WIDTH,SCREEN_HEIGHT);
	glutInitWindowPosition(100,150);
	glutCreateWindow ("Curve");
	glutDisplayFunc(myDisplay);
	glutMouseFunc(mouseInteraction);
	myInit ();
	glutMainLoop();
}

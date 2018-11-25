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
#define SCREEN_HEIGHT 768

vector<glm::vec2> controlPoints;
vector<glm::vec2> curvePoints;
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
		cout<<timeDiff<<endl;
		if(timeDiff<=0.02||currentPointIndex<0)
		{
			addControlPoint(clickPoint,controlPoints.size());
			timeDiff=0;
		}
		else if(timeDiff>0.02)
		{
			deleteControlPoint(currentPointIndex);
			addControlPoint(mousePos,currentPointIndex);
		}
	}

	if(button==GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		int i=closestPointIndex(mousePos);
		deleteControlPoint(i);
	}
}

glm::vec2 Lerp(glm::vec2 A,glm::vec2 B,float t)
{
	return (1-t)*A + t*B;
}
glm::vec2 getCurvePoint(int degree, int i, float t)
{
	if(degree==0)
		return controlPoints[i];
	glm::vec2 P1 = getCurvePoint(degree-1,i,t);
	glm::vec2 P2 = getCurvePoint(degree-1,i+1,t);
	return Lerp(P1,P2,t);
}

void drawBezierCurve()
{
	int degree = controlPoints.size() -1;
	if(degree < 0)
		return;
	glPointSize(4.0);	
	for(int i=0;i<controlPoints.size();i++)
	{
		plot(controlPoints[i].x,controlPoints[i].y);
	}
	glPointSize(2.0);
	curvePoints.clear();
	for(float t=0;t<1;t+=0.001)
	{
		glm::vec2 P = getCurvePoint(degree,0,t);
		curvePoints.push_back(P);
		plot(P.x,P.y); 
	}
}
void myDisplay(void)
{
	glClear (GL_COLOR_BUFFER_BIT);
	actualWidth=glutGet(GLUT_WINDOW_WIDTH);
	actualHeight=glutGet(GLUT_WINDOW_HEIGHT);
	drawBezierCurve();
	glutSwapBuffers ();
}

void update(int data)
{
	glutTimerFunc(30,update,0);
	glutPostRedisplay();
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
	glutTimerFunc(30,update,0);
	myInit ();
	glutMainLoop();
}

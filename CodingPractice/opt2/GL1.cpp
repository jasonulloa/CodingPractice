#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include "GL1.h"

int GL1() {
	char* blank[1] = {};
	int a = 0;
	int *numblank = &a;
	glutInit(numblank, blank);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(400, 400);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	glutCreateWindow("Test Window");
	int menu = glutCreateMenu(rtclick1);
	glutSetMenu(menu);
	glutAddMenuEntry("Quit", 0);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutDisplayFunc(display1);
	init1();
	glutMainLoop();

	return 0;
}

void init1() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 1, 0, 1, -1, 1);
	glClearColor(0, 0, 0, 0);
}

void display1() {
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glClearDepth(1.0);
	glLoadIdentity();

	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);
	glVertex3f(-0.5, -0.5, 0.0);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(-0.5, 0.5, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(0.5, 0.5, 0.0);
	glColor3f(1.0, 1.0, 0.0);
	glVertex3f(0.5, -0.5, 0.0);
	glEnd();

	glFlush();
}

void rtclick1(int val) {
	switch (val) {
		case 0:
			glutLeaveMainLoop();
			break;
	}
}
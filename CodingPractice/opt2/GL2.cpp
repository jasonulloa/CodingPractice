#include "GL2.h"

struct Viewpoint {
	double Translate[3];
	double Rotate[3];
	double Scale[3];
};

//Camera view
Viewpoint vp{ {2.0, 2.0, -5.0}, {0.0, 0.0, 0.0}, {1.0, 1.0, 1.0} };

int GL2::GL2() {
	char* blank[1] = {};
	int a = 0;
	int* numblank = &a;
	glutInit(numblank, blank);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
	glutInitWindowPosition(150, 150);
	glutInitWindowSize(640, 480);
	glutCreateWindow("Test Window");
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	int menu = glutCreateMenu(rtclick);
	glutSetMenu(menu);
	glutAddMenuEntry("Quit", 0);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutDisplayFunc(display);
	glutReshapeFunc(resizeWindow);
	glutIdleFunc(idle);
	init();
	glutMainLoop();

	return 0;
}

void GL2::init() {
	glClearColor(0, 0, 0, 0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 1, 0, 1, -1, 1);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);
}

void GL2::display() {
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glClearDepth(1.0);
	glLoadIdentity();
	gluLookAt(vp.Translate[0], vp.Translate[1], vp.Translate[2], 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);  //+X = left, +Y = up, +Z = forward

	glBegin(GL_QUADS);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(1.0, 1.0, -1.0);
	glVertex3f(-1.0, 1.0, -1.0);
	glVertex3f(-1.0, 1.0, 1.0);
	glVertex3f(1.0, 1.0, 1.0);

	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(1.0, -1.0, 1.0);
	glVertex3f(-1.0, -1.0, 1.0);
	glVertex3f(-1.0, -1.0, -1.0);
	glVertex3f(1.0, -1.0, -1.0);

	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(1.0, 1.0, 1.0);
	glVertex3f(-1.0, 1.0, 1.0);
	glVertex3f(-1.0, -1.0, 1.0);
	glVertex3f(1.0, -1.0, 1.0);

	glColor3f(1.0, 1.0, 0.0);
	glVertex3f(1.0, -1.0, -1.0);
	glVertex3f(-1.0, -1.0, -1.0);
	glVertex3f(-1.0, 1.0, -1.0);
	glVertex3f(1.0, 1.0, -1.0);

	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(-1.0, 1.0, 1.0);
	glVertex3f(-1.0, 1.0, -1.0);
	glVertex3f(-1.0, -1.0, -1.0);
	glVertex3f(-1.0, -1.0, 1.0);

	glColor3f(1.0, 0.0, 1.0);
	glVertex3f(1.0, 1.0, -1.0);
	glVertex3f(1.0, 1.0, 1.0);
	glVertex3f(1.0, -1.0, 1.0);
	glVertex3f(1.0, -1.0, -1.0);
	glEnd();

	glutSwapBuffers();
}

void GL2::idle()
{
	glutPostRedisplay();
}

void GL2::resizeWindow(int w, int h) {
	if (h == 0)
		h = 1;

	float ratio = (float)w / (float)h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, ratio, 0.001, 500.0);
	glMatrixMode(GL_MODELVIEW);
}

void GL2::rtclick(int val) {
	switch (val) {
		case 0:
			glutLeaveMainLoop();
			break;
	}
}
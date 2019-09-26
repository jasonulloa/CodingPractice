#include "GL2.h"

struct Viewpoint {  //struct for camera view
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
	glutKeyboardFunc(move);
	glutSpecialFunc(turn);
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
	glRotatef(static_cast<GLfloat>(vp.Rotate[0]), 1.0, 0.0, 0.0);  //rotation about x-axis; up/down
	glRotatef(static_cast<GLfloat>(vp.Rotate[1]), 0.0, 1.0, 0.0);  //rotation about y-axis; left/right
	glRotatef(static_cast<GLfloat>(vp.Rotate[2]), 0.0, 0.0, -1.0);  //rotation about z-axis; clockwise/counter-clockwise
	glScalef(static_cast<GLfloat>(vp.Scale[0]), static_cast<GLfloat>(vp.Scale[1]), static_cast<GLfloat>(vp.Scale[2]));

	glBegin(GL_QUADS);
	glColor3f(0.0, 1.0, 0.0);  //top
	glVertex3f(1.0, 1.0, -1.0);
	glVertex3f(-1.0, 1.0, -1.0);
	glVertex3f(-1.0, 1.0, 1.0);
	glVertex3f(1.0, 1.0, 1.0);

	glColor3f(1.0, 0.0, 0.0);  //bottom
	glVertex3f(1.0, -1.0, 1.0);
	glVertex3f(-1.0, -1.0, 1.0);
	glVertex3f(-1.0, -1.0, -1.0);
	glVertex3f(1.0, -1.0, -1.0);

	glColor3f(0.0, 1.0, 1.0);  //back
	glVertex3f(1.0, 1.0, 1.0);
	glVertex3f(-1.0, 1.0, 1.0);
	glVertex3f(-1.0, -1.0, 1.0);
	glVertex3f(1.0, -1.0, 1.0);

	glColor3f(1.0, 1.0, 0.0);  //front
	glVertex3f(1.0, -1.0, -1.0);
	glVertex3f(-1.0, -1.0, -1.0);
	glVertex3f(-1.0, 1.0, -1.0);
	glVertex3f(1.0, 1.0, -1.0);

	glColor3f(0.0, 0.0, 1.0);  //right
	glVertex3f(-1.0, 1.0, 1.0);
	glVertex3f(-1.0, 1.0, -1.0);
	glVertex3f(-1.0, -1.0, -1.0);
	glVertex3f(-1.0, -1.0, 1.0);

	glColor3f(1.0, 0.0, 1.0);  //left
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

void GL2::move(unsigned char key, int x, int y) {
	if (key == 119) {  //w; go forward
		vp.Translate[2] += 0.1;
	}
	if (key == 115) {  //s; go backward
		vp.Translate[2] -= 0.1;
	}
	if (key == 97) {  //a; go left
		vp.Translate[0] += 0.1;
	}
	if (key == 100) {  //d; go right
		vp.Translate[0] -= 0.1;
	}
}

void GL2::turn(int key, int x, int y) {
	if (key == GLUT_KEY_LEFT) {
		if (glutGetModifiers() == GLUT_ACTIVE_CTRL) {
			vp.Rotate[2] += 0.5;  //rotate counter-clockwise
		}
		else {
			vp.Rotate[1] += 0.5;  //rotate left
		}
	}
	if (key == GLUT_KEY_RIGHT) {
		if (glutGetModifiers() == GLUT_ACTIVE_CTRL) {
			vp.Rotate[2] -= 0.5;  //rotate clockwise
		}
		else {
			vp.Rotate[1] -= 0.5;  //rotate right
		}
	}
	if (key == GLUT_KEY_UP) {
		if (glutGetModifiers() == GLUT_ACTIVE_CTRL) {
			vp.Rotate[0] += 0.5;  //rotate up
		}
		else {
			vp.Translate[1] += 0.1;  //go up
		}
	}
	if (key == GLUT_KEY_DOWN) {
		if (glutGetModifiers() == GLUT_ACTIVE_CTRL) {
			vp.Rotate[0] -= 0.5;  //rotate down
		}
		else {
			vp.Translate[1] -= 0.1;  //go down
		}
	}
	if (key == GLUT_KEY_PAGE_UP) {  //scale up
		vp.Scale[0] += 0.05;
		vp.Scale[1] += 0.05;
		vp.Scale[2] += 0.05;
	}
	if (key == GLUT_KEY_PAGE_DOWN) {  //scale down
		vp.Scale[0] -= 0.05;
		vp.Scale[1] -= 0.05;
		vp.Scale[2] -= 0.05;
	}
}
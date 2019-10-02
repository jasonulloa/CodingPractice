#include "GL3.h"
#include <fstream>
#include <iostream>
#include <string>

constexpr auto PI = 3.14159265358979;
constexpr auto ZERO = 1e-4;
constexpr auto WIDTH = 640;
constexpr auto HEIGHT = 480;
constexpr auto MAX_TRIANGLES = 2000;
constexpr auto MAX_SPHERES = 20;
constexpr auto MAX_LIGHTS = 10;
constexpr auto FOV = 60.0;

struct Vertex {
	double position[3];
	double color_diffuse[3];
	double color_specular[3];
	double normal[3];
	double shininess;
};

typedef struct _Triangle {
	struct Vertex vert[3];
} Triangle;

typedef struct _Sphere {
	double position[3];
	double color_diffuse[3];
	double color_specular[3];
	double shininess;
	double radius;
} Sphere;

typedef struct _Light {
	double position[3];
	double color[3];
} Light;

Triangle triangles[MAX_TRIANGLES];
Sphere spheres[MAX_SPHERES];
Light lights[MAX_LIGHTS];
double ambient_light[3];
int num_triangles;
int num_spheres;
int num_lights;

int GL3::GL3(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	glutCreateWindow("OpenGL Raytracer");
	int menu = glutCreateMenu(rtclick);
	glutSetMenu(menu);
	glutAddMenuEntry("Quit", 0);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutDisplayFunc(display);
	loadScene(argv[1]);
	init();
	glutMainLoop();

	return 0;
}

void GL3::init() {
	glMatrixMode(GL_PROJECTION);
	glOrtho(0, WIDTH, 0, HEIGHT, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClearColor(1, 1, 1, 0);
	glClear(GL_COLOR_BUFFER_BIT);
}

void GL3::display() {
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

void GL3::rtclick(int val) {
	switch (val) {
	case 0:
		glutLeaveMainLoop();
		break;
	}
}

void GL3::loadScene(char* argv) {
	num_lights = num_spheres = num_triangles = 0;
	std::ifstream file(argv);
	if (!file.is_open()) {
		std::cout << "Error opening file: " << argv << std::endl;
		glutLeaveMainLoop();
	}
	
	std::string line;
	getline(file, line);
	std::cout << "The first line says: " << line << std::endl;
	file.close();
}
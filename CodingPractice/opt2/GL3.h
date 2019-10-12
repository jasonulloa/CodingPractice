#pragma once
#ifndef GL3_H
#define GL3_H
#include "GLinclude.h"

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

namespace GL3 {
	int GL3(int argc, char** argv);
	void init();
	void display();
	void rtclick(int val);
	void loadScene(char* argv);
	void parse_check(char* expected, char* found);
	void parse_doubles(FILE* file, char* check, double p[3]);
	void parse_rad(FILE* file, double* r);
	void parse_shi(FILE* file, double* shi);
	void drawScene();
	double* raytracer(double origin[3], double dir[3]);
	bool intersect_sphere(double origin[3], double dir[3], Sphere ball, double& hitdist);
	bool intersect_triangle(double origin[3], double dir[3], Triangle tri, double &hitdist, double &alpha, double &beta, double &gamma);
	void normalize(double v[3]);
	double dot(double a[3], double b[3]);
	void cross(double a[3], double b[3], double result[3]);
}
#endif
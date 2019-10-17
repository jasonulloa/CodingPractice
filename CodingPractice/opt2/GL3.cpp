#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include "GL3.h"

constexpr auto PI = 3.14159265358979;
constexpr auto ZERO = 1e-4;
constexpr auto INFINITY_DBL = 1.79769e+308;
constexpr auto WIDTH = 640;
constexpr auto HEIGHT = 480;
constexpr auto MAX_TRIANGLES = 2000;
constexpr auto MAX_SPHERES = 20;
constexpr auto MAX_LIGHTS = 10;
constexpr auto FOV = 60.0;

Triangle triangles[MAX_TRIANGLES];
Sphere spheres[MAX_SPHERES];
Light lights[MAX_LIGHTS];
double ambient_light[3];
int num_triangles;
int num_spheres;
int num_lights;
int once;

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
	once = 0;
	glMatrixMode(GL_PROJECTION);
	glOrtho(0, WIDTH, 0, HEIGHT, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClearColor(1, 1, 1, 0);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glClearDepth(1.0);
}

void GL3::display() {
	if (!once) {
		drawScene();
	}
	once = 1;
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
	int num_objects = 0;
	char type[50];
	FILE* file;
	Triangle tri;
	Sphere sph;
	Light li;
	fopen_s(&file, argv, "r");  //try to open file

	if (file != nullptr) {
		fscanf_s(file, "%i", &num_objects);
	}
	else {
		std::cout << "Error opening file." << std::endl;
		glutLeaveMainLoop();
	}


	std::cout << "Number of objects: " << num_objects << std::endl;
	parse_doubles(file, "amb:", ambient_light);

	for (int i = 0; i < num_objects; i++) {
		fscanf_s(file, "%s\n", type, _countof(type));
		std::cout << "Type of: " << type << std::endl;

		if (_stricmp(type, "triangle") == 0) {
			std::cout << "Found triangle." << std::endl;

			for (int j = 0; j < 3; j++) {
				parse_doubles(file, "pos:", tri.vert[j].position);
				parse_doubles(file, "nor:", tri.vert[j].normal);
				parse_doubles(file, "dif:", tri.vert[j].color_diffuse);
				parse_doubles(file, "spe:", tri.vert[j].color_specular);
				parse_shi(file, &tri.vert[j].shininess);
			}

			if (num_triangles == MAX_TRIANGLES) {
				std::cout << "Too many triangles; you should increase MAX_TRIANGLES!" << std::endl;
				glutLeaveMainLoop();
			}
			triangles[num_triangles++] = tri;
		}
		else if (_stricmp(type, "sphere") == 0) {
			std::cout << "Found sphere." << std::endl;
			parse_doubles(file, "pos:", sph.position);
			parse_rad(file, &sph.radius);
			parse_doubles(file, "dif:", sph.color_diffuse);
			parse_doubles(file, "spe:", sph.color_specular);
			parse_shi(file, &sph.shininess);

			if (num_spheres == MAX_SPHERES) {
				std::cout << "Too many spheres; you should increase MAX_SPHERES!" << std::endl;
				glutLeaveMainLoop();
			}
			spheres[num_spheres++] = sph;
		}
		else if (_stricmp(type, "light") == 0) {
			std::cout << "Found light." << std::endl;
			parse_doubles(file, "pos:", li.position);
			parse_doubles(file, "col:", li.color);

			if (num_lights == MAX_LIGHTS) {
				std::cout << "Too many lights; you should increase MAX_LIGHTS!" << std::endl;
				glutLeaveMainLoop();
			}
			lights[num_lights++] = li;
		}
		else {
			std::cout << "Unknown type in scene description: " << type << std::endl;
			glutLeaveMainLoop();
		}
	}

	if (file != nullptr) {
		fclose(file);
	}
	else {
		std::cout << "Error closing file." << std::endl;
		glutLeaveMainLoop();
	}

	std::cout << "File loaded." << std::endl;
}

void GL3::parse_check(char* expected, char* found) {
	if (_stricmp(expected, found)) {
		std::cout << "Expected: " << expected << "; found: " << found << std::endl;
		std::cout << "Parse error, abnormal abortion." << std::endl;
		glutLeaveMainLoop();
	}
}

void GL3::parse_doubles(FILE* file, char* check, double p[3]) {
	char str[100];
	fscanf_s(file, "%s", str, _countof(str));
	parse_check(check, str);
	fscanf_s(file, "%lf %lf %lf", &p[0], &p[1], &p[2]);
	printf("%s %lf %lf %lf\n", check, p[0], p[1], p[2]);
}

void GL3::parse_rad(FILE* file, double* r) {
	char str[100];
	fscanf_s(file, "%s", str, _countof(str));
	parse_check("rad:", str);
	fscanf_s(file, "%lf", r);
	printf("rad: %f\n", *r);
}

void GL3::parse_shi(FILE* file, double* shi) {
	char str[100];
	fscanf_s(file, "%s", str, _countof(str));
	parse_check("shi:", str);
	fscanf_s(file, "%lf", shi);
	printf("shi: %f\n", *shi);
}

void GL3::drawScene() {
	unsigned int x, y;
	double origin[] = { 0.0, 0.0, 0.0 };
	double aspect = WIDTH / static_cast<double>(HEIGHT);
	double angle = tan(FOV * 0.5 * PI / 180);  //converting FOV/2 to radians
	glPointSize(2.0);
	glBegin(GL_POINTS);
	for (x = 0; x < WIDTH; x++) {
		for (y = 0; y < HEIGHT; y++) {
			double xndc = 2 * static_cast<double>(x) * (1 / static_cast<double>(WIDTH)) - 1;  //pixel to -1 to 1 range mapping
			double yndc = 2 * static_cast<double>(y) * (1 / static_cast<double>(HEIGHT)) - 1;
			xndc *= angle * aspect;
			yndc *= angle;
			double ray[] = { xndc, yndc, -1 };
			normalize(ray);
			double* color = raytracer(origin, ray);
			glColor3d(color[0], color[1], color[2]);
			glVertex2i(x, y);
			delete[] color;
		}
	}
	glEnd();
	glFlush();
}

double* GL3::raytracer(double origin[3], double dir[3]) {
	double closest = INFINITY_DBL;
	Sphere* ball = nullptr;
	Triangle* tri = nullptr;
	double alpha = 0.0, beta = 0.0, gamma = 0.0;
	double* color = new double[3];

	for (int i = 0; i < num_spheres; i++) {  //check spheres
		double hitdist = 0.0;
		if (intersect_sphere(origin, dir, spheres[i], hitdist)) {
			if (hitdist < closest) {
				closest = hitdist;
				ball = &spheres[i];  //save ptr to closest sphere
			}
		}
	}

	for (int i = 0; i < num_triangles; i++) {  //check triangles
		double hitdist = 0.0, alf = 0.0, bet = 0.0, gam = 0.0;
		if (intersect_triangle(origin, dir, triangles[i], hitdist, alf, bet, gam)) {
			if (hitdist < closest) {
				closest = hitdist;
				alpha = alf;
				beta = bet;
				gamma = gam;
				tri = &triangles[i];  //save ptr to closest triangle
				if (ball != nullptr) {  //if ball is behind triangle, clear sphere ptr
					ball = nullptr;
				}
			}
		}
	}

	if (ball == nullptr && tri == nullptr) {  //no intersections
		for (int i = 0; i < 3; i++) {
			color[i] = 1.0;  //hit nothing, return white background color
		}

		return color;
	}

	double impact[3], impact_norm[3];
	for (int i = 0; i < 3; i++) {
		color[i] = ambient_light[i];  //set color to ambient light
		impact[i] = origin[i] + dir[i] * closest;
		if (ball != nullptr) {
			impact_norm[i] = (impact[i] - ball->position[i]) / ball->radius;  //normal to intersectionon sphere
		}
		else {
			impact_norm[i] = alpha * tri->vert[0].normal[i] + beta * tri->vert[1].normal[i] + gamma * tri->vert[2].normal[i];
		}
	}
	normalize(impact_norm);  //the N unit vector
	double vDir[] = { -dir[0], -dir[1], -dir[2] };

	for (int i = 0; i < num_lights; i++) {
		double transmission[] = { 1.0, 1.0, 1.0 };  //0.0 if blocked, 1.0 if not
		double lDir[] = { lights[i].position[0] - impact[0], lights[i].position[1] - impact[1], lights[i].position[2] - impact[2] };  //vector from impact to light
		double lightdist = sqrt(dot(lDir, lDir));  //distance between impact and light
		double checkdist = 0.0, alf = 0.0, bet = 0.0, gam = 0.0;
		normalize(lDir);  //the L unit vector
		double dotLN = dot(lDir, impact_norm);
		double rDir[] = { 2 * dotLN * impact_norm[0] - lDir[0], 2 * dotLN * impact_norm[1] - lDir[1], 2 * dotLN * impact_norm[2] - lDir[2] };  //the R unit vector

		for (int j = 0; j < num_spheres; j++) {  //check spheres
			if (ball != nullptr) {
				if (&spheres[j] != ball) {  //don't need to recheck sphere impact is on
					if (intersect_sphere(impact, lDir, spheres[j], checkdist)) {
						if (checkdist < lightdist) {
							transmission[0] = 0.0;
							transmission[1] = 0.0;
							transmission[2] = 0.0;
							break;
						}
					}
				}
			}
			else {  //check all spheres
				if (intersect_sphere(impact, lDir, spheres[j], checkdist)) {
					if (checkdist < lightdist) {
						transmission[0] = 0.0;
						transmission[1] = 0.0;
						transmission[2] = 0.0;
						break;
					}
				}
			}
		}

		if (transmission[0] == 1.0) {  //if not blocked by a sphere
			for (int j = 0; j < num_triangles; j++) {  //check triangles
				if (tri != nullptr) {
					if (&triangles[j] != tri) {  //don't need to recheck triangle impact is on
						if (intersect_triangle(impact, lDir, triangles[j], checkdist, alf, bet, gam)) {
							if (checkdist < lightdist) {
								transmission[0] = 0.0;
								transmission[1] = 0.0;
								transmission[2] = 0.0;
								break;
							}
						}
					}
				}
				else {  //check all triangles
					if (intersect_triangle(impact, lDir, triangles[j], checkdist, alf, bet, gam)) {
						if (checkdist < lightdist) {
							transmission[0] = 0.0;
							transmission[1] = 0.0;
							transmission[2] = 0.0;
							break;
						}
					}
				}
			}
		}

		double dotRV = dot(rDir, vDir), shiny = 0.0;
		double diff[] = { 0.0, 0.0, 0.0 }, spec[] = { 0.0, 0.0, 0.0 };
		for (int j = 0; j < 3; j++) {
			if (ball != nullptr) {
				diff[j] = ball->color_diffuse[j] * max(dotLN, 0.0);  //calculate diffuse part for sphere
				spec[j] = ball->color_specular[j] * pow(max(dotRV, 0.0), ball->shininess);  //calculate specular part for sphere
			}
			else {
				diff[j] = alpha * tri->vert[0].color_diffuse[j] + beta * tri->vert[1].color_diffuse[j] + gamma * tri->vert[2].color_diffuse[j];
				diff[j] *= max(dotLN, 0.0);  //calculate diffuse part for triangle
				spec[j] = alpha * tri->vert[0].color_specular[i] + beta * tri->vert[1].color_specular[i] + gamma * tri->vert[2].color_specular[i];
				shiny = alpha * tri->vert[0].shininess + beta * tri->vert[1].shininess + gamma * tri->vert[2].shininess;
				spec[i] *= pow(max(dotRV, 0.0), shiny);  //calculate specular part for triangle
			}
		}

		double lightcontrib[] = { 0.0, 0.0, 0.0 };
		for (int j = 0; j < 3; j++) {
			lightcontrib[j] = lights[i].color[j] * transmission[j] * (diff[j] + spec[j]);  //calculate final light contribution
			color[j] += lightcontrib[j];
		}
	}

	for (int i = 0; i < 3; i++) {
		color[i] = min(color[i], 1.0);
	}

	return color;
}

bool GL3::intersect_sphere(double origin[3], double dir[3], Sphere ball, double& hitdist) {
	double line[] = { origin[0] - ball.position[0], origin[1] - ball.position[1], origin[2] - ball.position[2] };
	double a = dot(dir, dir);
	double b = 2 * dot(dir, line);
	double c = dot(line, line) - ball.radius * ball.radius;
	double hit1 = 0.0, hit2 = 0.0;

	double discriminant = b * b - 4 * a * c;
	if (discriminant < 0) {
		return false;  //no intersections
	}
	else if (discriminant == 0) {
		hit1 = hit2 = -0.5 * b / a;  //exactly one solution
	}
	else {
		double q = 0.0;
		if (b > 0) {
			q = -0.5 * (b + sqrt(discriminant));
		}
		else {
			q = -0.5 * (b - sqrt(discriminant));
		}

		hit1 = q / a;
		hit2 = c / q;
	}

	if (hit1 < 0) {
		if (hit2 < 0) {
			return false;  //both intersect points are behind ray
		}

		hitdist = hit2;  //hit1 is behind ray, use hit2
		return true;
	}
	else {
		if (hit2 < 0) {
			hitdist = hit1;  //hit2 is behind ray, use hit1
			return true;
		}
	}

	if (hit1 > hit2) {
		hitdist = hit2;  //hit2 is closer
		return true;
	}

	hitdist = hit1;
	return true;
}

bool GL3::intersect_triangle(double origin[3], double dir[3], Triangle tri, double& hitdist, double& alpha, double& beta, double& gamma) {
	double b_a[] = { tri.vert[1].position[0] - tri.vert[0].position[0], tri.vert[1].position[1] - tri.vert[0].position[1],
		tri.vert[1].position[2] - tri.vert[0].position[2] };
	double c_a[] = { tri.vert[2].position[0] - tri.vert[0].position[0], tri.vert[2].position[1] - tri.vert[0].position[1],
		tri.vert[2].position[2] - tri.vert[0].position[2] };
	double plane_normal[] = { 0.0, 0.0, 0.0 };
	cross(b_a, c_a, plane_normal);  //normal of plane containing triangle
	double baXca[] = { plane_normal[0], plane_normal[1], plane_normal[2] };  //copy used for area calculations
	normalize(plane_normal);
	double normDotRay = dot(plane_normal, dir);
	if (fabs(normDotRay) < ZERO) {  //close enough to zero, ray is parallel; no intersect
		return false;
	}

	double coefficient = dot(plane_normal, tri.vert[0].position);
	double t = (coefficient - dot(plane_normal, origin)) / normDotRay;  //distance from triangle plane
	if (t < 0) {
		return false;  //triangle is behind ray
	}

	double impact[] = { origin[0] + t * dir[0], origin[1] + t * dir[1], origin[2] + t * dir[2] };  //point where ray hits plane
	double result[] = { 0.0, 0.0, 0.0 };
	double hit_a[] = { impact[0] - tri.vert[0].position[0], impact[1] - tri.vert[0].position[1], impact[2] - tri.vert[0].position[2] };
	cross(b_a, hit_a, result);
	gamma = dot(result, plane_normal);
	if (gamma < 0) {
		return false;  //intersection is outside of triangle at this edge
	}

	double c_b[] = { tri.vert[2].position[0] - tri.vert[1].position[0], tri.vert[2].position[1] - tri.vert[1].position[1],
		tri.vert[2].position[2] - tri.vert[1].position[2] };
	double hit_b[] = { impact[0] - tri.vert[1].position[0], impact[1] - tri.vert[1].position[1], impact[2] - tri.vert[1].position[2] };
	cross(c_b, hit_b, result);
	alpha = dot(result, plane_normal);
	if (alpha < 0) {
		return false;  //intersection is outside of triangle at this edge
	}

	double a_c[] = { tri.vert[0].position[0] - tri.vert[2].position[0], tri.vert[0].position[1] - tri.vert[2].position[1],
		tri.vert[0].position[2] - tri.vert[2].position[2] };
	double hit_c[] = { impact[0] - tri.vert[2].position[0], impact[1] - tri.vert[2].position[1], impact[2] - tri.vert[2].position[2] };
	cross(a_c, hit_c, result);
	beta = dot(result, plane_normal);
	if (beta < 0) {
		return false;  //intersection is outside of triangle at this edge
	}

	hitdist = t;
	double area = dot(baXca, plane_normal);  //area of triangle
	alpha /= area;  //set barycentric coordinates
	beta /= area;
	gamma /= area;

	return true;
}

void GL3::normalize(double v[3]) {
	double len2 = dot(v, v);
	double len = sqrt(len2);
	for (int i = 0; i < 3; i++) {
		v[i] /= len;
	}
}

double GL3::dot(double a[3], double b[3]) {
	double dotprod = a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
	return dotprod;
}

void GL3::cross(double a[3], double b[3], double result[3]) {
	result[0] = a[1] * b[2] - a[2] * b[1];
	result[1] = a[2] * b[0] - a[0] * b[2];
	result[2] = a[0] * b[1] - a[1] * b[0];
}
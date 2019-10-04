#include "GL3.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

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
	static int once = 0;
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
	int num_objects = 0, count = 0, vert_count = 0;
	bool set_amb = false, set_sphere = false, set_tri = false, set_light = false, set_pos = false, set_rad = false, set_dif = false, 
		set_spe = false, set_shi = false, set_norm = false, set_col = false;
	Triangle tri;
	Sphere sph;
	Light li;
	std::ifstream file(argv);
	if (!file.is_open()) {
		std::cout << "Error opening file: " << argv << std::endl;
		glutLeaveMainLoop();
	}
	
	std::string line, word;
	std::stringstream ss;
	while (getline(file, line)) {
		ss.str(line);
		while (getline(ss, word, ' ')) {
			if (num_objects == 0) {  //get number of objects
				num_objects = std::stoi(word);
				continue;
			}
			if (set_amb) {  //set up ambient light
				if (count < 3) {
					ambient_light[count] = std::stod(word);
					count++;
					if (count == 3) {
						count = 0;
						set_amb = false;
					}
					continue;
				}
			}
			if (set_sphere) {  //set up spheres
				if (set_pos) {  //set sphere position
					if (count < 3) {
						sph.position[count] = std::stod(word);
						count++;
						if (count == 3) {
							count = 0;
							set_pos = false;
						}
						continue;
					}
				}
				if (set_rad) {	//set sphere radius
					sph.radius = std::stod(word);
					set_rad = false;
					continue;
				}
				if (set_dif) {  //set sphere color diffuse
					if (count < 3) {
						sph.color_diffuse[count] = std::stod(word);
						count++;
						if (count == 3) {
							count = 0;
							set_dif = false;
						}
						continue;
					}
				}
				if (set_spe) {  //set sphere color specular
					if (count < 3) {
						sph.color_specular[count] = std::stod(word);
						count++;
						if (count == 3) {
							count = 0;
							set_spe = false;
						}
						continue;
					}
				}
				if (set_shi) {  //set sphere shininess
					sph.shininess = std::stod(word);
					set_shi = false;
					set_sphere = false;
					spheres[num_spheres] = sph;
					num_spheres++;
					continue;
				}
				if (word == "pos:") {
					set_pos = true;
					continue;
				}
				if (word == "rad:") {
					set_rad = true;
					continue;
				}
				if (word == "dif:") {
					set_dif = true;
					continue;
				}
				if (word == "spe:") {
					set_spe = true;
					continue;
				}
				if (word == "shi:") {
					set_shi = true;
					continue;
				}
			}
			if (set_tri) {  //set up triangles
				if (vert_count < 3) {
					if (set_pos) {  //set triangle vertex position
						if (count < 3) {
							tri.vert[vert_count].position[count] = std::stod(word);
							count++;
							if (count == 3) {
								count = 0;
								set_pos = false;
							}
							continue;
						}
					}
					if (set_norm) {	//set triangle vertex normal
						if (count < 3) {
							tri.vert[vert_count].normal[count] = std::stod(word);
							count++;
							if (count == 3) {
								count = 0;
								set_norm = false;
							}
							continue;
						}
					}
					if (set_dif) {  //set triangle vertex color diffuse
						if (count < 3) {
							tri.vert[vert_count].color_diffuse[count] = std::stod(word);
							count++;
							if (count == 3) {
								count = 0;
								set_dif = false;
							}
							continue;
						}
					}
					if (set_spe) {  //set triangle vertex color specular
						if (count < 3) {
							tri.vert[vert_count].color_specular[count] = std::stod(word);
							count++;
							if (count == 3) {
								count = 0;
								set_spe = false;
							}
							continue;
						}
					}
					if (set_shi) {  //set triangle vertex shininess
						tri.vert[vert_count].shininess = std::stod(word);
						set_shi = false;
						vert_count++;
						if (vert_count == 3) {
							vert_count = 0;
							set_tri = false;
							triangles[num_triangles] = tri;
							num_triangles++;
						}
						continue;
					}
					if (word == "pos:") {
						set_pos = true;
						continue;
					}
					if (word == "nor:") {
						set_norm = true;
						continue;
					}
					if (word == "dif:") {
						set_dif = true;
						continue;
					}
					if (word == "spe:") {
						set_spe = true;
						continue;
					}
					if (word == "shi:") {
						set_shi = true;
						continue;
					}
				}
			}
			if (set_light) {
				if (set_pos) {
					if (count < 3) {
						li.position[count] = std::stod(word);
						count++;
						if (count == 3) {
							count = 0;
							set_pos = false;
						}
						continue;
					}
				}
				if (set_col) {
					if (count < 3) {
						li.color[count] = std::stod(word);
						count++;
						if (count == 3) {
							count = 0;
							set_col = false;
							set_light = false;
							lights[num_lights] = li;
							num_lights++;
						}
						continue;
					}
				}
				if (word == "pos:") {
					set_pos = true;
					continue;
				}
				if (word == "col:") {
					set_col = true;
					continue;
				}
			}
			if (word == "amb:") {
				set_amb = true;
				continue;
			}
			if (word == "sphere") {
				set_sphere = true;
				continue;
			}
			if (word == "triangle") {
				set_tri = true;
				continue;
			}
			if (word == "light") {
				set_light = true;
				continue;
			}
		}
		ss.clear();
	}
	
	if (num_objects != num_lights + num_spheres + num_triangles) {
		std::cout << "Error parsing file: " << argv << std::endl;
		glutLeaveMainLoop();
	}
	
	std::cout << "Scene file loaded." << std::endl;
	file.close();
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
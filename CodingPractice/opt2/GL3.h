#pragma once
#ifndef GL3_H
#define GL3_H
#include "GLinclude.h"

namespace GL3 {
	int GL3(int argc, char** argv);
	void init();
	void display();
	void rtclick(int val);
	void loadScene(char* argv);
}
#endif
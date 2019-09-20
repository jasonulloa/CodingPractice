#pragma once
#ifndef GL2_H
#define GL2_H
#include "GLinclude.h"

namespace GL2 {
	int GL2();
	void init();
	void display();
	void idle();
	void resizeWindow(int w, int h);
	void rtclick(int val);
};
#endif
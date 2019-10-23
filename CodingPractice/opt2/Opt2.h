#pragma once
#ifndef OPT2_H
#define OPT2_H
#include "GL1.h"
#include "GL2.h"
#include "GL3.h"

class Opt2 {
	public:
		Opt2();
		~Opt2();
		void run();

	private:
		void gl_test();
		void gl_view_test();
		void gl_raytracer();
};
#endif
#pragma once
#ifndef OPT3_H
#define OPT3_H
#include "Postfix.h"
#include "Sudoku.h"

class Opt3 {
	public:
		Opt3();
		~Opt3();
		void run();

	private:
		void postfix_calc();
		void sudoku_solver();
};
#endif
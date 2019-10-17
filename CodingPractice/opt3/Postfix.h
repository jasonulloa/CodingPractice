#pragma once
#ifndef POSTFIX_H
#define POSTFIX_H
#include "../opt1/List.h"

class Postfix {
	public:
		Postfix();
		~Postfix();
		void run();
		double calculate();

	private:
		List<double> stack;
};
#endif
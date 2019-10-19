#pragma once
#ifndef POSTFIX_H
#define POSTFIX_H
#include <vector>
#include "../opt1/List.h"

class Postfix {
	public:
		Postfix();
		~Postfix();
		void run(std::string input);
		double calculate(std::vector<std::string> inputs);

	private:
		List<double> stack;
};
#endif
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

	private:
		double calculate(std::vector<std::string> inputs, int& error);
		bool is_operator(const std::string s);
		bool is_number(const std::string s);
		double resolve(double left, double right, std::string op);

		List<double> stack;
};
#endif
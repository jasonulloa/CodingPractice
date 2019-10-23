#include <sstream>
#include <iostream>
#include <cmath>
#include "Postfix.h"

Postfix::Postfix() {

}

Postfix::~Postfix() {
	stack.clear();
}

void Postfix::run(std::string input) {
	std::stringstream in(input);
	std::string entry;
	std::vector<std::string> strvec;
	while (in >> entry) {
		if (!is_operator(entry) && !is_number(entry)) {
			std::cout << "Error: Entry \"" << entry << "\" is not allowed. Exiting...." << std::endl;
			return;
		}
		strvec.push_back(entry);
	}

	if (strvec.size() == 1) {
		if (is_number(strvec[0])) {
			std::cout << strvec[0] << std::endl;
			return;
		}
	}
	if (strvec.size() < 3) {
		std::cout << "Error: Insufficient input. Exiting...." << std::endl;
		return;
	}
	if (is_operator(strvec[0]) || is_operator(strvec[1])) {
		std::cout << "Error: Incorrect syntax. Exiting...." << std::endl;
		return;
	}

	int error = 0;
	double result = calculate(strvec, error);

	if (isnan(result)) {
		switch (error) {
			case 0: {
				std::cout << "Error: Incorrect syntax. Exiting...." << std::endl;
				break;
			}
			case 1: {
				std::cout << "Error: Divide by zero. Exiting...." << std::endl;
				break;
			}
			case 2: {
				std::cout << "Error: Insufficient operators. Exiting...." << std::endl;
				break;
			}
			case 3: {
				std::cout << "Error: Insufficient numbers. Exiting...." << std::endl;
				break;
			}
			default: {
				std::cout << "Error: Incorrect syntax. Exiting...." << std::endl;
			}
		}
		
		return;
	}

	std::cout << input << " = " << result << std::endl;
}

double Postfix::calculate(std::vector<std::string> inputs, int& error) {
	for (auto entry : inputs) {
		if (is_operator(entry)) {
			if (stack.size() < 2) {
				error = 3;  //not enough numbers
				return nan("");
			}

			double left, right, total;
			right = stack.back();
			stack.pop_back();
			left = stack.back();
			stack.pop_back();
			total = resolve(left, right, entry);
			if (isnan(total)) {
				error = 1;  //divide by zero
				return total;
			}

			stack.push_back(total);
			continue;
		}

		stack.push_back(std::stod(entry));
	}

	if (stack.size() != 1) {
		error = 2;  //not enough operators
		return nan("");
	}

	return stack.front();
}

bool Postfix::is_operator(const std::string s) {
	if ((s == "+") || (s == "-") || (s == "/") || (s == "*")) {
		return true;
	}

	return false;
}

bool Postfix::is_number(const std::string s) {
	char* end = 0;
	double val = strtod(s.c_str(), &end);
	return end != s.c_str() && *end == '\0' && val != HUGE_VAL;
}

double Postfix::resolve(double left, double right, std::string op) {
	if (op == "+") {
		return left + right;
	}
	if (op == "-") {
		return left - right;
	}
	if (op == "*") {
		return left * right;
	}
	if (right == 0.0) {
		return nan("");
	}
	return left / right;
}
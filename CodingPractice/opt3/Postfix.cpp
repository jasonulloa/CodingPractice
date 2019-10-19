#include <sstream>
#include <iostream>
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
		strvec.push_back(entry);
	}

	if (strvec.size() < 3) {
		std::cout << "Error: Insufficient input. Exiting...." << std::endl;
		return;
	}

	double result = calculate(strvec);

	std::cout << input << " = " << result << std::endl;
}

double Postfix::calculate(std::vector<std::string> inputs) {
	//TODO
	return 0.0;
}
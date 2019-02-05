#include <iostream>
#include <string>
#include <sstream>
#include "Opt1.h"
#include "List.h"

Opt1::Opt1() {

}

Opt1::~Opt1() {

}

void Opt1::run() {
	int select = 0;
	bool loop = true;

	std::ostringstream menu;
	menu << "Option #1: Data Structure Test Runs\n" << std::endl;
	menu << "1. TODO: Build Tests for List Data Structure" << std::endl;
	menu << "2. Exit" << std::endl << ">";

	while (loop) {  //loop until "Exit" is selected
		std::cout << menu.str();

		std::string input;
		while (std::getline(std::cin, input)) {  //read user input
			std::stringstream ss(input);
			if (ss >> select) {  //if the input is an int
				if (ss.eof()) {  //escape input loop if input is only an int
					break;
				}
			}
			std::cout << "Please make a valid selection." << std::endl << ">";
		}  //escape input loop

		switch (select) {
			case 1: {
				std::cout << "Normally, you'd see some tests run here. However, I haven't finished\n" <<
					"coding them yet. Please wait until then.\n" << std::endl;
				break;
			}
			case 2: {
				std::cout << "Returning to Main Menu.\n" << std::endl;
				loop = false;
				break;
			}
			default: {
				std::cout << "That option does not exist.\n" << std::endl;
				break;
			}
		}
	}  //escape main loop
}
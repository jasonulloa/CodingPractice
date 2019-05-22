#include <iostream>
#include <string>
#include <sstream>
#include "Opt2.h"

Opt2::Opt2() {

}

Opt2::~Opt2() {

}

void Opt2::run() {
	int select = 0;
	bool loop = true;

	std::ostringstream menu;
	menu << "\nOption #2: OpenGL Stuff\n" << std::endl;
	menu << "1. OpenGL Window Test" << std::endl;
	menu << "2. Return to Main Menu" << std::endl << ">";

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
				gl_test();
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

void Opt2::gl_test() {
	std::cout << "Testing...." << std::endl;
	GL1();
	std::cout << "Test complete." << std::endl;
}
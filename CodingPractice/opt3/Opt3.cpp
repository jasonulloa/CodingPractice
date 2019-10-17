#include <iostream>
#include <string>
#include <sstream>
#include "Opt3.h"

Opt3::Opt3() {

}

Opt3::~Opt3() {

}

void Opt3::run() {
	int select = 0;
	bool loop = true;

	std::ostringstream menu;
	menu << "\nOption #3: Recoded USC CS Stuff\n" << std::endl;
	menu << "1. Simple Postfix Calculator" << std::endl;
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
				postfix_calc();
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

void Opt3::postfix_calc() {
	std::cout << "Not ready yet.\n" << std::endl;
}
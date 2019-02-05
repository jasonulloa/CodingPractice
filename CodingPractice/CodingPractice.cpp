#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include "opt1/Opt1.h"

int main()
{
	std::cout << "Coding Practice: Getting the Rust Out Edition\n" << std::endl;
	int select = 0;
	bool loop = true;

	std::ostringstream menu;  //TODO: Change/add to these when I actually start my practice coding.
	menu << "1. Data Structure Test Runs" << std::endl;
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
				Opt1* option1 = new Opt1();
				option1->run();
				delete option1;
				break;
			}
			case 2: {
				std::cout << "Goodbye." << std::endl;
				loop = false;
				break;
			}
			default: {
				std::cout << "That option does not exist.\n" << std::endl;
				break;
			}
		}
	}  //escape main loop
	
    return 0;
}
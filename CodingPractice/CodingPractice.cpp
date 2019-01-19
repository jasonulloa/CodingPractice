#pragma once
#include <iostream>
#include <string>
#include <sstream>

int main()
{
	std::cout << "Coding Practice: Getting the Rust Out Edition\n" << std::endl;
	int select = 0;
	bool loop = true;

	std::ostringstream menu;  //TODO: Change/add to these when I actually start my practice coding.
	menu << "1. Option #1" << std::endl;
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
				std::cout << "You have selected Option #1. An excellent choice.\n" <<
					"Unfortunately, as this option is under construction, you'll have to make another choice.\n" <<
					std::endl;
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
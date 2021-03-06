#pragma once
#include <iostream>
#include "opt1/Opt1.h"
#include "opt2/Opt2.h"
#include "opt3/Opt3.h"

int main()
{
	std::cout << "Coding Practice: Getting the Rust Out Edition\n" << std::endl;
	int select = 0;
	bool loop = true;

	std::ostringstream menu;
	menu << "Main Menu:\n" << std::endl;
	menu << "1. Data Structure Test Runs" << std::endl;
	menu << "2. OpenGL Stuff" << std::endl;
	menu << "3. Recoded USC CS Stuff" << std::endl;
	menu << "4. Exit" << std::endl << ">";

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
				Opt2* option2 = new Opt2();
				option2->run();
				delete option2;
				break;
			}
			case 3: {
				Opt3* option3 = new Opt3();
				option3->run();
				delete option3;
				break;
			}
			case 4: {
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
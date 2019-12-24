#include <iostream>
#include <string>
#include <sstream>
#include <random>
#include "Opt3.h"
#include "SlidingTile.h"

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
	menu << "2. Sudoku Solver" << std::endl;
	menu << "3. Sliding Tile Solver" << std::endl;
	menu << "4. Return to Main Menu" << std::endl << ">";

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
				sudoku_solver();
				break;
			}
			case 3: {
				sliding_tile_solver();
				break;
			}
			case 4: {
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
	std::string input;

	std::cout << "This is a simple postfix calculator. The operator goes after the two numbers to be operated on.\n";
	std::cout << "Examples: 3 4 + = 7.\n6 5 + 8 - = 3.\n7 4 / 6 - 3 5 * + = 10.75.\n\n";
	std::cout << "Please enter the equation to be calculated. Make sure there is a space between each number and operation.\n" << std::endl;
	std::cout << ">";

	std::getline(std::cin, input);

	Postfix* pnc = new Postfix();
	pnc->run(input);
	delete pnc;
}

void Opt3::sudoku_solver() {
	std::cout << "This is a sudoku solver. Just enter the known numbers, one at a time, from left to right, top to bottom.\n";
	std::cout << "If a space is blank, enter '0' as the number.\nBe careful, because once a number is entered, it is final.\n\n";
	std::cout << "Please enter the numbers below:" << std::endl;

	int puzzle[9][9];
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			int entry = 0;
			std::string inputstr;
			std::cout << "Entry [" << i + 1 << "][" << j + 1 << "]: ";
			while (std::getline(std::cin, inputstr)) {  //read user entry

				std::stringstream sstr(inputstr);
				if (sstr >> entry) {  //if the entry is an int
					if (sstr.eof()) {  //if entry is only an int
						if (entry < 0) {  //if entry is negative, loop again
							std::cout << "Negative numbers are invalid. Please enter a valid number." << std::endl;
							continue;
						}
						if (entry > 9) {  //if entry is more than 9, loop again
							std::cout << "Numbers larger than 9 are invalid. Please enter a valid number." << std::endl;
							continue;
						}

						break;  //escape input loop if entry is between 0 and 9
					}
				}
				std::cout << "Please make a valid selection." << std::endl;
			}  //escape input loop

			puzzle[i][j] = entry;
		}
	}

	Sudoku* doki = new Sudoku(puzzle);
	doki->print();
	doki->solve();
	doki->verify();
	doki->print();
	delete doki;
}

void Opt3::sliding_tile_solver() {
	std::cout << "This is a NxN sliding tile solver. Just enter the puzzle size, the initial number of moves to scramble,\n";
	std::cout << "and an optional seed number.\n\n";

	int size = 0, moves = 0, seed = 0;
	std::string inputstr;
	std::random_device rng;
	std::cout << "Please enter puzzle size (N >= 3): " << std::endl;
	
	while (std::getline(std::cin, inputstr)) {  //read user entry
		std::stringstream sstr(inputstr);
		
		if (sstr >> size) {  //if the entry is an int
			if (sstr.eof()) {  //if entry is only an int
				if (size < 0) {  //if entry is negative
					std::cout << "Negative numbers are invalid. Defaulting to N = 3." << std::endl;
					break;
				}

				if (size < 3) {  //if entry is less than 3
					std::cout << "Numbers less than 3 are invalid. Defaulting to N = 3." << std::endl;
					break;
				}

				break;  //if entry is greater than or equal to 3
			}
		}

		std::cout << "Please make a valid entry." << std::endl;
	}  //escape input loop

	std::cout << "Please enter initial number of moves (moves > 0): " << std::endl;

	while (std::getline(std::cin, inputstr)) {  //read user entry
		std::stringstream sstr(inputstr);

		if (sstr >> moves) {  //if the entry is an int
			if (sstr.eof()) {  //if entry is only an int
				if (moves < 0) {  //if entry is negative
					std::cout << "Negative numbers are invalid. Defaulting to moves = 1." << std::endl;
					break;
				}

				if (moves == 0) {  //if entry is 0
					std::cout << "Must have at least 1 move. Defaulting to moves = 1." << std::endl;
					break;
				}

				break;  //if entry is greater than or equal to 1
			}
		}

		std::cout << "Please make a valid entry." << std::endl;
	}  //escape input loop

	std::cout << "Please enter puzzle seed, if desired (blank for random seed): " << std::endl;

	while (std::getline(std::cin, inputstr)) {  //read user entry
		std::stringstream sstr(inputstr);
		
		if (inputstr.empty()) {
			seed = std::abs(static_cast<int>(rng()));
			std::cout << "Selecting random seed. Seed is " << seed  << "." << std::endl;
			break;
		}

		if (sstr >> seed) {  //if the entry is an int
			if (sstr.eof()) {  //if entry is only an int
				if (seed < 0) {  //if entry is negative
					std::cout << "Negative numbers are invalid. Please enter a valid number." << std::endl;
					continue;
				}

				break;  //if entry is positive
			}
		}

		std::cout << "Please make a valid entry." << std::endl;
	}  //escape input loop

	SlidingTile* puzzle = new SlidingTile(size, moves, seed);
	puzzle->solve();
	delete puzzle;
}
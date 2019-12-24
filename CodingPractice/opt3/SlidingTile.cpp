#include <sstream>
#include "SlidingTile.h"
#include "PuzzleSolver.h"

SlidingTile::SlidingTile(int size, int moves, int seed) {
	puzzle = Board(size, moves, seed);
}

SlidingTile::~SlidingTile() {

}

void SlidingTile::solve() {
	while (!puzzle.solved()) {
		std::cout << puzzle << std::endl;
		std::cout << "Enter tile number to move, -1 for a cheat, or 0 to quit." << std::endl << "> ";
		int entry = 0;
		std::string inputstr;

		while (std::getline(std::cin, inputstr)) {  //read user entry
			std::stringstream sstr(inputstr);

			if (sstr >> entry) {  //if the entry is an int
				if (sstr.eof()) {  //if entry is only an int
					if (entry < -1 || entry >= puzzle.size()) {  //if less than -1 or greater than or equal to the puzzle size
						std::cout << "Invalid entry. Please enter a valid number." << std::endl;
						continue;
					}
					else if (entry > 0) {  //if entry is valid move
						puzzle.move(entry);
						break;
					}
					else if (entry < 0) {  //if entry is -1
						//--TODO
					}
					else {  //if entry is 0
						std::cout << "Quitting puzzle." << std::endl;
						return;
					}
				}
			}

			std::cout << "Please make a valid entry." << std::endl;
		}  //escape input loop
	}

	std::cout << puzzle << std::endl;
	std::cout << "Puzzle solved." << std::endl;
}
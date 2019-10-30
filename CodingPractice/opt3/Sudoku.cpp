#include "Sudoku.h"
#include <iostream>

Sudoku::Sudoku(int puzzle[9][9]) {
	board = new int* [9];

	for(int i = 0; i < 9; i++) {
		board[i] = new int[9];
		for(int j = 0; j < 9; j++) {
			board[i][j] = puzzle[i][j];
		}
	}
}

Sudoku::~Sudoku() {
	for (int i = 0; i < 9; i++) {
		delete[] board[i];
	}

	delete[] board;
}

void Sudoku::solve(){
	solveHelper(0, 0);
}

void Sudoku::print() {
	for (int row=0; row<9; row++) {
		if (row % 3== 0) {
			std::cout << "-------------------------------" << std::endl;
		}
    
		for (int col=0; col<9; col++) {
			if (col % 3 == 0) {
				std::cout << "|";
			}
    
			if (board[row][col] != 0) {
				std::cout << " " << board[row][col] << " ";
			}
			else {
				std::cout << " . ";
			}
		}
	
		std::cout << "|" << std::endl;
	}

	std::cout << "-------------------------------" << std::endl;
}

void Sudoku::verify() {
	for(int i = 0; i < 9; i++) {
		for(int j = 0; j < 9; j++) {
			if(!isValid(i, j)) {
				std::cout << "\nThis puzzle is not valid." << std::endl;
				return;
			}
		}
	}

	std::cout << "\nThis puzzle is valid." << std::endl;
}

bool Sudoku::isValid(int row, int col) {
	int value = board[row][col];

	for (int i=0; i<9; i++) {
		if (i == row) {
			continue;
		}

		int temp = board[i][col];
		if (temp == value) {
			return false;
		}
	}

	for (int i=0; i<9; i++) {
		if (i == col) {
			continue;
		}

		int temp = board[row][i];
		if (temp == value) {
			return false;
		}
	}

	int box_row = row / 3; 
	int box_col = col / 3; 

	for (int i=box_row * 3; i < box_row * 3 + 3; i++) {
		for (int j=box_col * 3; j < box_col * 3 + 3; j++) {
			if (i == row && j == col) {
				continue;
			}

			int temp = board[i][j];
			if (temp == value) {
				return false;
			}
		}
	}

	return true;
}

bool Sudoku::solveHelper(int row, int col) {
	int value = board[row][col];

	if (value != 0) {  //already filled
		if (row < 8) {  //not last line
			if (col < 8) {  //not last square in line
				if (solveHelper(row, col + 1)) {
					return true;
				}
			}
			else {  //last square in line
				if (solveHelper(row + 1, 0)) {
					return true;
				}
			}
		}
		else {  //last line
			if (col < 8) {
				if (solveHelper(8, col + 1)) {
					return true;
				}
			}
			else {  //last square, done
				return true;
			}
		}
	}
	else {  //not filled
		for (int i = 1; i < 10; i++) {
			board[row][col] = i;  //check number

			if (isValid(row, col)) {  //if valid
				if (row < 8) {  //if not last row
					if (col < 8) {  //if not last square in row
						if (solveHelper(row, col + 1)) {
							return true;
						}
					}
					else {  //if last square in row
						if (solveHelper(row + 1, 0)) {
							return true;
						}
					}
				}
				else {  //if last row
					if (col < 8) {  //if not last square
						if (solveHelper(8, col + 1)) {
							return true;
						}
					}
					else {  //if last square
						return true;
					}
				}
			}
		}

		board[row][col] = 0;  //reset square
	}

	return false;
}
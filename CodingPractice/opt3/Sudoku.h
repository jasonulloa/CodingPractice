#ifndef SUDOKU_H
#define SUDOKU_H

class Sudoku {
public:
	Sudoku(int puzzle[9][9]);
	~Sudoku();

	void solve();  //solves the puzzle
	void print();  //prints the puzzle
	void verify();  //verifies the puzzle is valid; will not work on unsolved puzzles
 
private:
	bool isValid(int row, int col);  //recursive function that performs validation
	bool solveHelper(int row, int col);  //helper function for validation
	int** board;
};
#endif
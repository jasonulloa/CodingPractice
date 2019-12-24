#pragma once
#ifndef BOARD_H
#define BOARD_H
#include <cstdlib>
#include <iostream>
#include <map>

class Board {
	public:
		Board(int side, int initMoves, int seed);  //Makes a board of size side^2, scrambled initMoves times
		Board();  //Makes a blank board
		~Board();  //Board destructor
		Board(const Board& other);  //Board copy constructor
		Board& operator=(const Board& other);  //Board assignment operator
		void move(int tile);  //moves tile by swapping with adjacent
		std::map<int, Board*> potentialMoves() const;  //generates potential moves for corresponding Board
		bool solved() const;  //returns true if board is solved
		friend std::ostream& operator<<(std::ostream& os, const Board& b);  //prints board in 2D format
		bool operator<(const Board& rhs) const;  //compares Boards by tile in numerical order, starting from 0th
		int const& operator[](int loc) const;  //lets user treat board as an array; returns value at tile location loc
		int size() const;  //returns size of tile array
		int dim() const;  //returns dimension of board, i.e. one side

	private:
		void printRowBanner(std::ostream& os) const;  //prints row banner at top, middle, and bottom
		int* _tiles;
		int _size;
};
#endif
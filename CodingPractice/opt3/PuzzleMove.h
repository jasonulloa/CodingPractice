#pragma once
#ifndef PUZZLEMOVE_H
#define PUZZLEMOVE_H
#include "Board.h"

struct PuzzleMove {
	int tileMove;  //tile moved to reach Board b
	Board* b;  //pointer to Board b
	int g;  //distance from start board
	int h;  //heuristic distance to goal
	PuzzleMove* prev;  //pointer to parent PuzzleMove

	PuzzleMove(Board* board);  //constructor for initial move
	PuzzleMove(int tile, Board* board, PuzzleMove* parent);  //constructor for subsequent moves
	~PuzzleMove();  //destructor
};

PuzzleMove::PuzzleMove(Board* board) {
	tileMove = 0;
	b = board;
	g = h = 0;
	prev = nullptr;
}

PuzzleMove::PuzzleMove(int tile, Board* board, PuzzleMove* parent) {
	tileMove = tile;
	b = board;
	g = h = 0;
	prev = parent;
}

PuzzleMove::~PuzzleMove() {
	if (b != nullptr) {
		delete b;
	}

	if (prev != nullptr) {
		delete prev;
	}
}

struct PuzzleMoveScoreComp {
	bool operator()(const PuzzleMove* m1, const PuzzleMove* m2) const {
		//code to check if m1's f-score is less than m2's. If both have the same f-score, break ties by 
		//checking if m1's h-score is less than m2's
		int m1f = m1->g + m1->h, m2f = m2->g + m2->h;

		if (m1f == m2f) {
			return m1->h < m2->h;
		}
		else {
			return m1f < m2f;
		}
	}
};

struct PuzzleMoveBoardComp {
	bool operator()(const PuzzleMove* m1, const PuzzleMove* m2) const {
		//code to check if m1's board is "less-than" m2's board by using the Board class' operator<()
		Board* b1 = m1->b, *b2 = m2->b;
		return (*b1) < (*b2);
	}
};
#endif
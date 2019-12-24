#pragma once
#ifndef PUZZLEHEURISTIC_H
#define PUZZLEHEURISTIC_H
#include "Board.h"

class PuzzleHeuristic {
	public:
		virtual ~PuzzleHeuristic() {}
		virtual int compute(const Board& b) = 0;
};

class ManhattanHeuristic : public PuzzleHeuristic {
	public:
		int compute(const Board& b);
};

int ManhattanHeuristic::compute(const Board& b) {
	int size = b.size(), side = b.dim();
	int tileRow = 0, tileCol = 0, goalRow = 0, goalCol = 0, dist = 0, h = 0;

	for (int i = 0; i < size; i++) {
		if (b[i] != i && b[i] != 0) {
			int goal = b[i];
			tileRow = i / side;
			tileCol = i % side;
			goalRow = goal / side;
			goalCol = goal % side;
			dist = abs(tileRow - goalRow) + abs(tileCol - goalCol);
			h += dist;
		}
	}

	return h;
}

class OutOfPlaceHeuristic : public PuzzleHeuristic {
	public:
		int compute(const Board& b);
};

int OutOfPlaceHeuristic::compute(const Board& b) {
	int size = b.size(), h = 0;

	for (int i = 0; i < size; i++) {
		if (b[i] != i && b[i] != 0) {
			h++;
		}
	}

	return h;
}

class BFSHeuristic : public PuzzleHeuristic {
	public:
		int compute(const Board& b);
};

int BFSHeuristic::compute(const Board& b) {
	return 0;
}
#endif
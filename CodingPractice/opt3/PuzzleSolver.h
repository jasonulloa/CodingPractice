#pragma once
#ifndef PUZZLESOLVER_H
#define PUZZLESOVER_H
#include <deque>
#include <set>
#include "../opt1/Heap.h"
#include "PuzzleHeuristic.h"
#include "PuzzleMove.h"

class PuzzleSolver {
	public:
		typedef std::set<PuzzleMove*, PuzzleMoveBoardComp> PuzzleMoveSet;

		PuzzleSolver(const Board& b, PuzzleHeuristic* ph);  //constructor takes a PuzzleHeuristic which scores boards
		~PuzzleSolver();  //destructor
		void run();  //runs an A* search and tracks number of expansions in solution
		std::deque<int> getSolution();  //returns solution deque
		int getNumExpansions();  //returns number of expansions in solution

	private:
		Board _b;
		std::deque<int> _solution;
		int _expansions;
		PuzzleHeuristic* _ph;
};

PuzzleSolver::PuzzleSolver(const Board& b, PuzzleHeuristic* ph) {
	_b = b;
	_ph = ph;
	_expansions = 0;
}

PuzzleSolver::~PuzzleSolver() {

}

void PuzzleSolver::run() {
	PuzzleMoveScoreComp boardScore;
	Board* startboard = new Board(_b);
	PuzzleMove* startmove = new PuzzleMove(startboard);
	int heur = _ph->compute(*startboard), step = 1;
	startmove->h = heur;

	Heap<PuzzleMove*, PuzzleMoveScoreComp> open_list(2, boardScore);
	PuzzleMoveSet closed_list;
	_expansions = 0;
	std::map<int, Board*> moveset = startboard->potentialMoves();  //get moves from init board

	for (std::map<int, Board*>::iterator iter = moveset.begin(); iter != moveset.end(); ++iter) {  //get initial next moves
		PuzzleMove* nextmove = new PuzzleMove(iter->first, iter->second, startmove);  //moved tile, new Board, parent PuzzleMove
		Board* newboard = iter->second;
		heur = _ph->compute(*newboard);
		nextmove->h = heur;
		nextmove->g = step;
		open_list.push(nextmove);  //place into open_list
	}

	_expansions++;
	closed_list.insert(startmove);

	while (!open_list.empty()) {
		PuzzleMove* thismove = open_list.top();  //get the next move
		closed_list.insert(thismove);  //put in searched list
		open_list.pop();  //remove from open list
		Board* scanBoard = thismove->b;  //get Board from PuzzleMove

		if (scanBoard->solved()) {  //if this board is in the solved state
			int lastmove = thismove->tileMove;
			_solution.push_front(lastmove);  //start filling the solution backwards
			PuzzleMove* previousMove = thismove->prev;  //get the Board before this one

			while (previousMove->prev != nullptr) {  //iterate backward until reaching the first move
				lastmove = previousMove->tileMove;
				_solution.push_front(lastmove);  //continue filling backwards
				previousMove = previousMove->prev;
			}

			if (!open_list.empty()) {  //solution found; clear out open_list
				PuzzleMove* dump = open_list.top();
				open_list.pop();
				delete dump;
			}

			for (auto item : closed_list) {  //clear out closed_list
				delete item;
			}

			closed_list.clear();
			return;  //memory freed; return with list of moves
		}

		step = thismove->g + 1;  //not solved; record info and place in open_list
		std::map<int, Board*> newMoveset = scanBoard->potentialMoves();

		for (auto item : newMoveset) {  //get new moves from thismove
			Board* newBoard = item.second;
			PuzzleMove* newMove = new PuzzleMove(item.first, newBoard, thismove);
			heur = _ph->compute(*newBoard);
			newMove->h = heur;
			newMove->g = step;
			bool isInClosedList = false;

			for (auto setItem : closed_list) {  //check if new board is already in closed_list, i.e. it's been expanded
				Board* b1 = setItem->b;
				Board* b2 = newMove->b;

				if ((*b1) < (*b2) || (*b2) < (*b1)) {
					isInClosedList = false;
				}
				else {  //if not < and not >, then must be ==
					isInClosedList = true;
					break;
				}
			}

			if (!isInClosedList) {  //add only if not in closed_list
				open_list.push(newMove);
			}
			else {
				delete newMove;
			}
		}

		newMoveset.clear();
		_expansions++;
	}
}

std::deque<int> PuzzleSolver::getSolution() {
	return _solution;
}

int PuzzleSolver::getNumExpansions() {
	return _expansions;
}
#endif
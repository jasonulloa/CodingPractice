#pragma once
#ifndef SLIDINGTILE_H
#define SLIDINGTILE_H
#include "Board.h"

class SlidingTile {
	public:
		SlidingTile(int size, int moves, int seed);
		~SlidingTile();
		void solve();

	private:
		Board puzzle;
};
#endif
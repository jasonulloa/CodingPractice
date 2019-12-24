#include <iomanip>
#include <cmath>
#include "Board.h"

Board::Board(int side, int initMoves, int seed) {
	int _side = side;

	if (side < 3) {  //ensures side is at least 3 and no negative sides
		_side = 3;
	}

	_size = _side * _side;
	_tiles = new int[_size];
	std::srand(seed);

	for (int i = 0; i < _size; i++) {
		_tiles[i] = i;
	}

	int blankTile = 0, _iMoves = initMoves;

	if (initMoves < 1) {  //ensures there is at least 1 initial move and no negative # of moves
		_iMoves = 1;
	}

	while (_iMoves > 0) {
		int r = std::rand() % 4, randNeighbor = 0;

		switch (r) {
			case 0: {
				int n = blankTile - _side;

				if (n >= 0) {
					randNeighbor = n;
				}

				break;
			}
			case 1: {
				int w = blankTile - 1;

				if (blankTile % _side != 0) {
					randNeighbor = w;
				}

				break;
			}
			case 2: {
				int s = blankTile + _side;

				if (s < _size) {
					randNeighbor = s;
				}

				break;
			}
			case 3: {
				int e = blankTile + 1;

				if (blankTile % _side != _side - 1) {
					randNeighbor = e;
				}

				break;
			}
			default: {
				break;
			}
		}

		if (randNeighbor > -1 && randNeighbor < _size) {
			_tiles[blankTile] = _tiles[randNeighbor];
			_tiles[randNeighbor] = 0;
			blankTile = randNeighbor;
			_iMoves--;
		}
	}
}

Board::Board() {
	_size = 0;
	_tiles = nullptr;
}

Board::~Board() {
	delete[] _tiles;
}

Board::Board(const Board& other) {
	this->_size = other._size;
	this->_tiles = new int[other._size];

	for (int i = 0; i < other._size; i++) {
		this->_tiles[i] = other._tiles[i];
	}
}

Board& Board::operator=(const Board& other) {
	if (this == &other) {
		return *this;
	}

	this->_size = other._size;
	delete[] this->_tiles;
	this->_tiles = new int[other._size];

	for (int i = 0; i < other._size; i++) {
		this->_tiles[i] = other._tiles[i];
	}

	return *this;
}

void Board::move(int tile) {
	int side = dim(), tileRow, tileCol, blankRow, blankCol;

	//find tile row and column
	int i = -1;
	while (_tiles[++i] != tile);

	tileRow = i / side;
	tileCol = i % side;

	//find blank row and column
	int j = -1;
	while (_tiles[++j] != 0);

	blankRow = j / side;
	blankCol = j % side;

	if (std::abs((static_cast<double>(tileRow) - static_cast<double>(blankRow)) + std::abs(static_cast<double>(tileCol) - 
		static_cast<double>(blankCol))) != 1) {
		std::cout << "Invalid move of tile " << tile << " at " << tileRow << "," << tileCol << " and blank spot at ";
		std::cout << blankRow << "," << blankCol << std::endl;

		return;
	}

	//swap tile and blank
	_tiles[j] = tile;
	_tiles[i] = 0;
}

//Generate new boards representing all the potential moves of tiles into the current blank tile location. The returned map 
//should have the key as the tile moved and the value as a new Board object with the configuration reflecting the move of 
//that tile into the blank spot
std::map<int, Board*> Board::potentialMoves() const {
	std::map<int, Board*> moveset;
	int blankLoc = -1, side = this->dim();

	while (_tiles[++blankLoc] != 0); //find blank tile

	int n = blankLoc - side, w = blankLoc - 1, s = blankLoc + side, e = blankLoc + 1;
	
	if (n >= 0) {
		Board* nBoard = new Board(*this);
		int nMove = (*nBoard)[n];
		nBoard->move(nMove);
		moveset.insert(std::make_pair(nMove, nBoard));
	}

	if (blankLoc % side != 0) {
		Board* wBoard = new Board(*this);
		int wMove = (*wBoard)[w];
		wBoard->move(wMove);
		moveset.insert(std::make_pair(wMove, wBoard));
	}

	if (s < _size) {
		Board* sBoard = new Board(*this);
		int sMove = (*sBoard)[s];
		sBoard->move(sMove);
		moveset.insert(std::make_pair(sMove, sBoard));
	}

	if (blankLoc % side != side - 1) {
		Board* eBoard = new Board(*this);
		int eMove = (*eBoard)[e];
		eBoard->move(eMove);
		moveset.insert(std::make_pair(eMove, eBoard));
	}

	return moveset;
}

bool Board::solved() const {
	int side = dim();

	for (int i = 0; i < side; i++) {
		for (int j = 0; j < side; j++) {
			int ij = (i * side) + j;

			if ((*this)[ij] != ij) {
				return false;
			}
		}
	}

	return true;
}

std::ostream& operator<<(std::ostream& os, const Board& b) {
	int side = b.dim();
	b.printRowBanner(os);

	for (int i = 0; i < side; i++) {
		os << "|";

		for (int j = 0; j < side; j++) {
			int ij = (i * side) + j;

			if (b[ij] == 0) {
				os << "  |";
			}
			else {
				os << std::setw(2) << b[ij] << "|";
			}
		}

		os << std::endl;
		b.printRowBanner(os);
	}

	return os;
}

bool Board::operator<(const Board& rhs) const {
	bool result = false;

	if (this->size() < rhs.size()) {
		result = true;
	}
	else if (this->size() > rhs.size()) {
		result = false;
	}
	else {
		for (int i = 0; i < this->size(); i++) {
			if ((*this)[i] < rhs[i]) {
				result = true;
				break;
			}
			if ((*this)[i] > rhs[i]) {
				result = false;
				break;
			}
		}
	}

	return result;
}

int const& Board::operator[](int loc) const {
	return _tiles[loc];
}

int Board::size() const {
	return _size;
}

int Board::dim() const {
	return static_cast<int>(sqrt(_size));
}

void Board::printRowBanner(std::ostream& os) const {
	int side = dim();
	
	if (side == 0) {
		return;
	}

	os << '+';
	
	for (int i = 0; i < side; i++) {
		os << "--+";
	}
	
	os << std::endl;
}
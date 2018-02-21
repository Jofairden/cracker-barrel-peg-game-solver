#pragma once

#include "stdafx.h"

#include <string>
#include <stdexcept>
#include <tuple>
#include <vector>

using namespace std;

// the that could be made
enum Move : int
{
	left, right,
	upleft, upright,
	downleft, downright
};

class Board
{
public:
	Board();
	//~Board();

	/*
		We store the entire game state in 16 bit uint
		This is a really small format, and only 1 bit remains unused
		We only care about the bits of this uint, not the actual number, 
		though the entire number obviously represents the board, 
		but the bits represent each slot state
		Slots get and set using bit shifting

		moveMap is a 2d bool array that stores per move,
		for each position if they can perform that move
		it is dynamically generated in the constructor
	*/
	bool moveMap[6][15];
	uint16_t game;

	bool get(const int i); // gets if there is a peg on position i
	const bool& get(const int i) const; // gets if there is a peg on position i
	void set(const int i, const bool v); // sets position i to be a peg or empty

	bool canMove(const int i, const Move m) const; // returns if move m can be made to position i
	int getPeg(const int  i, const Move m) const; // returns the peg position to i using move. using this twice lends the jumping peg, and once the peg being jumped over
	bool isInGoalState() const; // returns if the board is in the final state. e.g. 1 peg left
	void movePeg(const int i, const Move m); // performs move m on position i

	// probably not even used, just handy dandy and fun
	bool operator[] (const int k);
	const bool& operator[] (const int k) const;
};

// important overloads go here, since binary tree search is being used
inline bool operator==(const Board& lhs, const Board& rhs) 
{ 
	for (int i = 0; i < 15; ++i)
	{
		if (lhs.get(i) != rhs.get(i))
			return false;
	}
	return true;
}
inline bool operator!=(const Board& lhs, const Board& rhs) { return !operator==(lhs, rhs); }
inline bool operator< (const Board& lhs, const Board& rhs) 
{ 
	for (int i = 0; i < 15; ++i)
	{
		bool p_lhs = lhs.get(i);
		bool p_rhs = rhs.get(i);
		if (p_lhs != p_rhs)
			return p_lhs < p_rhs;
	}
	return false;
}
inline bool operator> (const Board& lhs, const Board& rhs) { return  operator< (rhs, lhs); }
inline bool operator<=(const Board& lhs, const Board& rhs) { return !operator> (lhs, rhs); }
inline bool operator>=(const Board& lhs, const Board& rhs) { return !operator< (lhs, rhs); }

inline bool Board::operator[](const int key) {
	if (key < 0 || key >= 15)
		throw out_of_range("Key was out of range");

	return get(key);
}

inline const bool& Board::operator[](const int key) const {
	if (key < 0 || key >= 15)
		throw out_of_range("Key was out of range");

	return get(key);
}
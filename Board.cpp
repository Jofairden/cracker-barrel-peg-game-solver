#include "stdafx.h"
#include "Board.h"

#include <map>

Board::Board()
{
	game = 0x7FFE;

	// autogen move map
	// go over each move
	// if the jumping and jumped over peg positions are valid
	// then the move can be performed
	// out of bounds if -1
	for (int i = 0; i < 15; ++i)
	{
		for (int j = 0; j < 6; ++j)
		{
			Move m = static_cast<Move>(j);
			int mov = getPeg(i, m);
			int mov2 = getPeg(mov, m);
			moveMap[j][i] = mov != -1 && mov2 != -1;
		}
	}
}

//Board::~Board()
//{
//	delete &game;
//}

bool Board::get(const int i)
{
	return (game >> i) & 1;
}

const bool& Board::get(const int i) const
{
	return (game >> i) & 1;
}

void Board::set(const int i, const bool v)
{
	if (v) game |= 1 << i;
	else game &= ~(1 << i);
}

bool Board::canMove(const int i, const Move move) const
{
	// is move available?
	if (moveMap[static_cast<int>(move)][i])
	{
		int peg = getPeg(i, move);
		// there are no pegs across, cant make move
		if (get(peg) && get(getPeg(peg, move)))
			return true;
	}
	return false;
}

const int rows[] = { 0, 1, 1, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 4 };
const int rowStart[] = { 0, 1, 3, 6, 10 };

// returns the peg slot based on move m and position i, uses i and the slot to move to
int Board::getPeg(const int i, const Move m) const
{
	int row = rows[i];
	switch (m) {
	case Move::left:
		if (i == rowStart[row])
			return -1;
		return i - 1;
	case Move::right:
		if (i == rowStart[row] + row)
			return -1;
		return i + 1;
	case upleft:
		if (i == rowStart[row])
			return -1;
		return i - row - 1;
	case upright:
		if (i == rowStart[row] + row)
			return -1;
		return i - row;
	case downleft:
		if (row == 4)
			return -1;
		return i + row + 1;
	case downright:
		if (row == 4)
			return -1;
		return i + row + 2;
	}
}

bool Board::isInGoalState() const
{
	uint16_t c = 0;
	for (int i = 0; i < 15; ++i)
	{
		if (get(i))
			++c;
	}
	return c == 1;
}

void Board::movePeg(const int i, const Move m)
{
	set(i, true); // set self to filled
	int p = getPeg(i, m);
	set(p, false); // set jump over to empty
	set(getPeg(p, m), false); // set jumping to empty
}

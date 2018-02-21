// Graph.h
#pragma once

#include "stdafx.h"
#include "Board.h"

#include <array>
#include <vector>
#include <iostream>
#include <functional>
#include <stack>
#include <set>

using namespace std;

using State = Board;
using Vertex = State;
using Path = vector<Vertex>;

class Graph
{
public:
	Graph();
	Graph(Board board);

	Board board;

	typename Path::const_iterator cbegin(Vertex v) const;
	typename Path::const_iterator cend() const;
private:
	mutable Path adjacents;
};

ostream &operator<<(ostream &os, const Vertex &state);

Vertex doMove(Vertex v, const Move &m, const int &pos);
Path bfs(const Graph &graph, const Vertex &start, int &bfsIt, function<bool(const Vertex &vertex)> goalTest);

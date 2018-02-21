// Graph.cpp

#include "stdafx.h"
#include "Graph.h"

#include <queue>
#include <map>

using namespace std;

Graph::Graph()
{
	this->board = Board();
}

Graph::Graph(Board board)
{
	this->board = board;
}

typename Path::const_iterator Graph::cbegin(Vertex v) const
{
	adjacents.clear();

	for (int i = 0; i < 15; ++i)
	{
		bool peg = v.get(i);
		if (!peg)
		{

			for (int j = 0; j < 6; ++j)
			{
				Move m = static_cast<Move>(j);
				if (v.canMove(i, m))
					adjacents.push_back(doMove(v, m, i));				
			}
		}
	}

	return adjacents.cbegin();
}

typename Path::const_iterator Graph::cend() const
{
	return adjacents.cend();
}

// performs the given move on given position on the given vertex
Vertex doMove(Vertex v, const Move &m, const int &pos)
{
	v.movePeg(pos, m);
	return v;
}

// will print the 1d array in pyramid style
// things that are hardcoded are the points at which rows begin
// the first row handling, and the amount of spaces = max rows in peg game
std::ostream &operator<<(std::ostream &os, const Vertex &state)
{
	int x, y, numSpaces, zpoint, zmax;

	int points[] = {
		0,1,3,6,10
	};

	// 5 = max rows
	for (x = 0; x < 5; ++x)
	{
		numSpaces = 5 - x;

		for (int i = 0; i < numSpaces; ++i)
			os << " ";

		zpoint = points[x];
		zmax = zpoint + x;

		if (zpoint == 0)
			os << noboolalpha << state[0];
		else
			for (y = zpoint; y <= zmax; ++y)
				os	<< noboolalpha << state[y]
					<< " ";

		os << endl;
	}

	return os;
}

// runs the given graph through bfs search, starting at the given vertex
// success is checked against goalTest
Path bfs(const Graph &graph, const Vertex &start, int &bfsIt, function<bool(const Vertex &vertex)> goalTest)
{
	queue<Path> queue;
	Path path;
	Vertex last;
	set<Vertex> visited;
	uint16_t len = 14;

	//begin at start, mark it visited, push it to the queue
	path.push_back(start);
	visited.insert(start);
	queue.push(path);

	// while something is in the queue.. go
	while (!queue.empty()) {
		++bfsIt;

		// take front of queue, last vertex is the last of path, pop front from queue
		path = queue.front();
		last = path.back();
		queue.pop();

		// if we mach goal, return path
		if (goalTest(last)) {
			cout << "Solution found" << endl;
			return path; 
		}

		// iterate adjacents of last vertex
		for (auto it = graph.cbegin(last); it != graph.cend(); ++it) {

			//cout << *it << endl; // cout the step
			// if adjacent not visited, push to the back of queue for next iteration and mark visited
			if (visited.find(*it) == visited.end()) {
				Path n = path;
				n.push_back(*it);
				queue.push(n);
				visited.insert(*it);
			}
		}
	}
	cout << "No solution found" << endl;
	//for (auto p : path) {
	//	cout << "game: " << p.game << endl;
	//}
	//return path;
	return Path();
}
// algoritmiek3.cpp : Defines the entry point for the console application.
// Daniël Zondervan // 2018

#include "stdafx.h"
#include "Graph.h"

#include <string>
#include <chrono>

using namespace std;

// vertex = state = board

int main()
{
	// create the starting board and attach to the graph
	Vertex start = Board(); 
	Graph graph = Graph(start);

	int count = 0;

	chrono::milliseconds stime = chrono::duration_cast<chrono::milliseconds>(
		chrono::system_clock::now().time_since_epoch()
		);

	// run bfs code, and check goal
	Path path = bfs(graph, graph.board, count, [&](Vertex v)
	{
		return v.isInGoalState();
	});

	chrono::milliseconds etime = chrono::duration_cast<chrono::milliseconds>(
		chrono::system_clock::now().time_since_epoch()
		);

	for (auto it = path.cbegin(); it != path.cend(); ++it)
	{
		cout << *it << std::endl;
	}

	cout << "paths: " << count << endl;
	cout << "done, finished in " << (etime-stime).count() << "ms" << endl;
	string str;
	getline(std::cin, str);

	return 0;
}


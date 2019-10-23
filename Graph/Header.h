#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

class GraphNode;

typedef vector<GraphNode*> GRAPH;

class GraphNode
{
public:
	int value;
	bool marked = false;
	vector<GraphNode*> nodes;

	GraphNode()
	{
		value = 0;
	}

	GraphNode(int val)
	{
		value = val;
	}

	void printAdjacencyList(vector<vector<int>> adjList);

	vector<vector<int>> readAdjacencyList();

	GRAPH graphFromAdjList(vector<vector<int>> adjList);

	void printMatrix(int** matrix, int size);

	int** readMatrix(int* size);

	GRAPH graphFromMatrix(int** matrix, int size);

	void printEdges(vector<pair<int, int>> edges);

	vector<pair<int, int>> readEdges();

	GRAPH graphFromEdges(vector<pair<int, int>> edges);

	void printGraph(GRAPH graph);
};
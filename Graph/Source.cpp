#include <queue>
#include "Header.h"

void GraphNode::printAdjacencyList(vector<vector<int>> adjList)
{
	for (auto line : adjList)
	{
		for (auto num : line)
		{
			cout << num << " ";
		}
		cout << endl;
	}
}

vector<vector<int>> GraphNode::readAdjacencyList()
{
	GraphNode* start = NULL;
	vector<vector<int>> adjList;
	ifstream file("list.txt", ios::in);
	string str;

	if (!file.good()) return adjList;

	while (getline(file, str))
	{
		istringstream ss(str);
		vector<int> temp;
		int num, i = 0;
		while (ss >> num)
		{
			temp.push_back(num);
			i++;
		}
		adjList.push_back(temp);
	}

	return adjList;
}

GRAPH GraphNode::graphFromAdjList(vector<vector<int>> adjList)
{
	GRAPH graph;

	for (unsigned int i = 0; i < adjList.size(); i++)
	{
		graph.push_back(new GraphNode(i));
		for (auto el : adjList[i])
		{
			graph[i]->nodes.push_back(new GraphNode(el));
		}
	}

	return graph;
}

void GraphNode::printMatrix(int** matrix, int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
}

int** GraphNode::readMatrix(int* size)
{
	int** matrix;

	if (size == NULL) return NULL;

	*size = 0;

	ifstream file("matrix.txt", ios::in);

	if (!file.good()) return NULL;

	file >> *size;
	matrix = (int**)malloc(sizeof(int*) * *size);
	if (matrix == NULL) return NULL;

	for (int i = 0; i < *size; i++)
	{
		matrix[i] = (int*)malloc(sizeof(int) * *size);
		if (matrix[i] == NULL) return NULL;

		for (int j = 0; j < *size; j++)
		{
			file >> matrix[i][j];
		}
	}

	return matrix;
}

GRAPH GraphNode::graphFromMatrix(int** matrix, int size)
{
	GRAPH graph;

	for (int i = 0; i < size; i++)
	{
		graph.push_back(new GraphNode(i));
		for (int j = 0; j < size; j++)
		{
			if (matrix[i][j] == 1)
			{
				graph[i]->nodes.push_back(new GraphNode(j));
			}

		}
	}

	return graph;
}

void GraphNode::printEdges(vector<pair<int, int>> edges)
{
	for (auto e : edges)
	{
		cout << e.first << " " << e.second << endl;
	}
}

vector<pair<int, int>> GraphNode::readEdges()
{
	vector<pair<int, int>> edges;
	ifstream file("edges.txt", ios::in);
	int a, b;

	if (!file.good()) return edges;

	while (file >> a >> b)
	{
		edges.push_back(make_pair(a, b));
	}

	return edges;
}

GRAPH GraphNode::graphFromEdges(vector<pair<int, int>> edges)
{
	GRAPH graph;

	for (auto p : edges)
	{
		int i = p.first;
		GraphNode* node;
		try
		{
			node = graph.at(i);
		}
		catch (exception& e)
		{
			node = new GraphNode(i);
			graph.push_back(node);
		}
		node->nodes.push_back(new GraphNode(p.second));
	}

	return graph;
}

void GraphNode::printGraph(GRAPH graph)
{
	for (auto node : graph)
	{
		cout << node->value << ": ";
		for (auto c : node->nodes)
		{
			cout << c->value << " ";
		}
		cout << endl;
	}
}

void BFS(GRAPH graph)
{
	queue<GraphNode*> Q;
	graph[0]->marked = true;
	Q.push(graph[0]);

	while (!Q.empty()) 
	{
		GraphNode* node = Q.front();
		Q.pop();
		cout << node->value << " ";
		for (const auto &n : node->nodes)
		{
			if (!n->marked)
			{
				n->marked = true;
				Q.push(n);
			}
		}
	}
}

void testAdjacencyList(GraphNode graph)
{
	vector<vector<int>> adjList = graph.readAdjacencyList();
	GRAPH adjGraph = graph.graphFromAdjList(adjList);
	cout << "Graph from adjacency list: " << endl;
	graph.printGraph(adjGraph);
	cout << endl;
}

void testMatrix(GraphNode graph)
{
	int size = 0;
	int** matrix = graph.readMatrix(&size);
	GRAPH matrixGraph = graph.graphFromMatrix(matrix, size);
	cout << "Graph from matrix: " << endl;
	graph.printGraph(matrixGraph);
	cout << endl;
}

void testEdges(GraphNode graph)
{
	vector<pair<int, int>> edges = graph.readEdges();
	GRAPH edgeGraph = graph.graphFromEdges(edges);
	cout << "Graph from edges: " << endl;
	graph.printGraph(edgeGraph);
}

void testBFS(GraphNode graph)
{
	vector<pair<int, int>> edges = graph.readEdges();
	GRAPH edgeGraph = graph.graphFromEdges(edges);
	cout << "Graph from edges: " << endl;
	graph.printGraph(edgeGraph);
	cout << "\nGraph from BFS: " << endl;
	BFS(edgeGraph);
}

void test()
{
	GraphNode graph;

	testBFS(graph);
}

int main()
{
	test();
	return 0;
}
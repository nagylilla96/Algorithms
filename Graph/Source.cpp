#include <queue>
#include <stack>
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
	int size = adjList.size();

	for (unsigned int i = 0; i < size; i++)
	{
		graph.push_back(new GraphNode(i));
	}

	for (unsigned int i = 0; i < size; i++)
	{
		for (auto el : adjList[i])
		{
			graph[i]->nodes.push_back(graph.at(el));
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
	}

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (matrix[i][j] != 0)
			{
				graph[i]->nodes.push_back(graph.at(j));
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

int getMax(vector<pair<int, int>> edges)
{
	int max = 0;

	for (auto p : edges)
	{
		if (p.first > max) max = p.first;
		if (p.second > max) max = p.second;
	}
	
	return max;
}

GRAPH GraphNode::graphFromEdges(vector<pair<int, int>> edges)
{
	GRAPH graph;
	int size = getMax(edges);

	cout << "Max = " << size << endl;

	for (int i = 0; i <= size; i++)
	{
		graph.push_back(new GraphNode(i));
	}

	for (auto p : edges)
	{
		int i = p.first;
		GraphNode* node = graph.at(i);
		node->nodes.push_back(graph.at(p.second));
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

GRAPH BFS(GRAPH graph)
{
	GRAPH results;
	queue<GraphNode*> Q;
	graph[0]->marked = true;
	Q.push(graph[0]);

	while (!Q.empty()) 
	{
		GraphNode* node = Q.front();
		Q.pop();
		results.push_back(node);
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
	return results;
}

void DFS(GraphNode* current)
{
	if (current == NULL) return;
	if (current->marked) return;
	current->marked = true;
	cout << current->value << " ";

	for (const auto& node : current->nodes)
	{
		DFS(node);
	}
}

int getMinDist(GRAPH nodes)
{
	int min = INFINITE;
	int index = -1;
	int i = 0;

	for (const auto& el : nodes)
	{
		if (el->distance < min)
		{
			min = el->distance;
			index = i;
		}
		i++;
	}
	return index;
}

int dist(int** matrix, GraphNode* nodeA, GraphNode* nodeB)
{
	int dist = nodeA->distance;
	int i = nodeA->value;
	int j = nodeB->value;
	dist += matrix[i][j];
	return dist;
}

void Dijkstra(GRAPH graph, GraphNode* source, int** matrix)
{
	// A fake queue because we can't iterate on a real one :( 
	vector<GraphNode*> Q = BFS(graph);
	source->distance = 0;

	while (!Q.empty())
	{
		int index = getMinDist(Q);
		GraphNode* node = Q.at(index);
		node->marked = false;
		Q.erase(Q.begin() + index);

		for (int j = 0; j < node->nodes.size(); j++)
		{
			GraphNode* curr = node->nodes.at(j);
			if (curr->marked == false) continue;
			int newDist = dist(matrix, node, curr);
			if (newDist < curr->distance)
			{
				curr->distance = newDist;
				curr->previous = node;
			}
		}
	}
}

void shortestPath(GraphNode* source, GraphNode* destination)
{
	stack<int> stack;
	GraphNode* current = destination;
	if (destination->previous != NULL)
	{
		while (current != NULL)
		{
			stack.push(current->value);
			current = current->previous;
		}
	}

	cout << endl;
	
	while (!stack.empty())
	{
		cout << stack.top() << " -> ";
		stack.pop();
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
	vector<vector<int>> adjList = graph.readAdjacencyList();
	GRAPH adjGraph = graph.graphFromAdjList(adjList);
	cout << "Graph from adjacency list: " << endl;
	graph.printGraph(adjGraph);
	cout << endl;
	cout << "\nGraph from BFS: " << endl;
	BFS(adjGraph);
}

void testDFS(GraphNode graph)
{
	vector<vector<int>> adjList = graph.readAdjacencyList();
	GRAPH adjGraph = graph.graphFromAdjList(adjList);
	cout << "Graph from adjacency list: " << endl;
	graph.printGraph(adjGraph);
	cout << endl;
	cout << "\nGraph from DFS: " << endl;
	DFS(adjGraph[0]);
}

void testDijkstra(GraphNode source)
{
	int size = 0;
	int** matrix = source.readMatrix(&size);
	GRAPH matrixGraph = source.graphFromMatrix(matrix, size);
	cout << "Graph from matrix: " << endl;
	source.printGraph(matrixGraph);
	cout << endl;
	Dijkstra(matrixGraph, matrixGraph[0], matrix);
	shortestPath(matrixGraph.front(), matrixGraph.back());
}

void test()
{
	GraphNode graph;

	testDijkstra(graph);
}

int main()
{
	test();
	return 0;
}
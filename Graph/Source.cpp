#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

class GraphNode
{
public:
	int value;
	vector<GraphNode*> nodes;

	GraphNode(int val)
	{
		value = val;
	}

	static void printAdjacencyList(vector<vector<int>> adjList)
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

	static GraphNode* readAdjacencyList()
	{
		GraphNode* start = NULL;
		vector<vector<int>> adjList;
		ifstream file("list.txt", ios::in);
		int nodes = 0;
		string str;

		if (!file.good()) return NULL;

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

		printAdjacencyList(adjList);
	}

	static void printMatrix(int** matrix, int size)
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

	static GraphNode* readMatrix()
	{
		int** matrix;
		int size = 0;

		ifstream file("matrix.txt", ios::in);

		if (!file.good()) return NULL;

		file >> size;
		matrix = (int**)malloc(sizeof(int*) * size);
		if (matrix == NULL) return NULL;

		for (int i = 0; i < size; i++)
		{
			matrix[i] = (int*)malloc(sizeof(int) * size);
			if (matrix[i] == NULL) return NULL;

			for (int j = 0; j < size; j++)
			{
				file >> matrix[i][j];
			}
		}

		printMatrix(matrix, size);
	}
};

void test()
{
	GraphNode::readMatrix();
}

int main()
{
	test();
	return 0;
}
#include <iostream>
#include <vector>

using namespace std;

class Node
{
public:
	vector<Node> list;
	int value;

	Node(int val)
	{
		value = val;
	}
};

class Table
{
	int hashFunc(int k)
	{
		return (k % 7);
	}

public:
	vector<Node> keys;


};

int main()
{

}
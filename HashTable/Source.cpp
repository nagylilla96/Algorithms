#include <iostream>
#include <list>
#include <random>

using namespace std;

#define TABLE_SIZE	701

// Hash table with chaining

class Node
{
public:
	list<int> nodes;
	int key;
	int value;

	Node(int val)
	{
		value = val;
	}
};

class Table
{
	Node* table[TABLE_SIZE];
	int size = 0;

public:

	Table()
	{
		for (int i = 0; i < TABLE_SIZE; i++)
		{
			table[i] = NULL;
		}
	}

	int hashFunc(int k)
	{
		return (k % TABLE_SIZE);
	}

	int addValue(int value)
	{
		Node* node = new Node(value);
		node->key = hashFunc(value);
		if (table[node->key] == NULL)
		{
			table[node->key] = node;
			this->size++;
			return node->key;
		}
		table[node->key]->nodes.push_front(value);
		this->size++;
	}

	int searchValue(int value)
	{
		int key = hashFunc(value);
		if (table[key] == NULL) return -1;
		if (table[key]->value == value) return value;
		for (const auto& n : table[key]->nodes)
		{
			if (n == value)
			{
				return value;
			}
		}
		return -1;
	}

	int deleteValue(int value)
	{
		int key = hashFunc(value);
		if (table[key] == NULL) return -1;
		list<int> tableList = table[key]->nodes;
		if (table[key]->value == value)
		{
			if (tableList.empty())
			{
				table[key] = NULL;
				return value;
			}
			table[key]->value = tableList.front();
			tableList.pop_front();
			return value;
		}
		int i = 0;
		for (const auto& el : tableList)
		{
			if (el == value)
			{
				list<int>::iterator it = tableList.begin();
				advance(it, i);
				tableList.erase(it);
				return value;
			}
			i++;
		}
	}

	int getSize()
	{
		return this->size;
	}
};

// Adds some random values to the hashtable, then verifies if they are found correctly
void test()
{
	Table* hash_table = new Table();
	hash_table->addValue(3);
	hash_table->addValue(9);
	hash_table->addValue(6);
	hash_table->addValue(8);
	hash_table->addValue(1);
	hash_table->addValue(7);
	cout << hash_table->searchValue(9) << endl;
	cout << hash_table->searchValue(5) << endl;
	cout << hash_table->searchValue(4) << endl;
	cout << hash_table->searchValue(7) << endl;
}

// Test adding 900 elements to the hash table
void stressTest()
{
	Table* table = new Table();
	// I would NEVER remember this :)) 
	// But as I understand, this generates random numbers in the range 1-1000
	random_device dev;
	mt19937 rng(dev());
	uniform_int_distribution<mt19937::result_type> distSpec(1, 1000);
	for (int i = 0; i < 900; i++)
	{
		table->addValue(distSpec(rng));
	}
	cout << "This table has " << table->getSize() << " elements" << endl;
}

int main()
{
	stressTest();
	return 0;
}
#include <iostream>

using namespace std;

// TODO: delete!

class TreeEntry
{
public:
	int value;
	TreeEntry* next = NULL;
	TreeEntry* nodes = NULL;

	TreeEntry(int val)
	{
		value = val;
	}

	static TreeEntry* insertOrderedList(TreeEntry* first, int val)
	{
		if (first == NULL)
		{
			first = new TreeEntry(val);
			return first;
		}

		TreeEntry* current = first;

		if (first->value > val)
		{
			TreeEntry* temp = new TreeEntry(val);
			temp->next = first;
			first = temp;
			return first;
		}

		while (current && current->next != NULL)
		{
			if (current->next->value > val)
			{
				TreeEntry* temp = new TreeEntry(val);
				temp->next = current->next;
				current->next = temp;
				return first;
			}
			current = current->next;
		}

		TreeEntry* temp = new TreeEntry(val);
		current->next = temp;
		return first;
	}

	static void printOrderedList(TreeEntry* first, int level)
	{
		if (first == NULL) return;
		TreeEntry* current = first;
		while (current != NULL)
		{
			cout << "[(" << level << ") " << current->value << "] ->";
			printOrderedList(current->nodes, level + 1);
			current = current->next;
		}

		cout << endl;
	}

	static TreeEntry* arrayToList(int* arr, int size)
	{
		TreeEntry* first = NULL;

		for (int i = 0; i < size; i++)
		{
			first = insertOrderedList(first, arr[i]);
		}

		return first;
	}

	static TreeEntry* findValue(TreeEntry* root, int value)
	{
		if (root == NULL) return root;

		if (root->value == value) return root;

		if (root->nodes == NULL) return NULL;

		TreeEntry* current = root->nodes;

		while (current != NULL)
		{
			if (current->value == value)
			{
				return current;
			}

			TreeEntry* temp = findValue(current->nodes, value);
			if (temp != NULL)
			{
				return temp;
			}

			current = ((TreeEntry*)current)->next;
		}

		return NULL;
	}

	static TreeEntry* addNode(TreeEntry* root, int parentValue, int childValue)
	{
		if (root == NULL)
		{
			root = new TreeEntry(childValue);
			return root;
		}

		TreeEntry* parent = findValue(root, parentValue);
		if (parent == NULL)
		{
			cout << "Parent with value " << parentValue << " not found!" << endl;
			return NULL;
		}
		TreeEntry* child = ((TreeEntry*)parent)->insertOrderedList(parent->nodes, childValue);
		if (child == NULL)
		{
			cout << "Child with value " << childValue << " not found!" << endl;
			return NULL;
		}
		parent->nodes = child;

		return root;
	}
};

void testList()
{
	int arr[6] = { 2, 7, 3, 8, 1, 9 };
	TreeEntry* first = TreeEntry::arrayToList(arr, 6);
	TreeEntry::printOrderedList(first, 0);
}

void testTree()
{
	TreeEntry* root = NULL;
	root = TreeEntry::addNode(root, 0, 1);
	root = TreeEntry::addNode(root, 1, 2);
	root = TreeEntry::addNode(root, 1, 3);
	root = TreeEntry::addNode(root, 2, 4);
	TreeEntry::printOrderedList(root, 0);
}

int main()
{
	testList();
	testTree();
	return 0;
}
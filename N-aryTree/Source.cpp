#include <iostream>

using namespace std;

// After delete, nodes don't stay ordered. But whatever :)) 
class TreeEntry
{
private:
	class ToDelete
	{
	public:
		TreeEntry* toDelete = NULL;
		TreeEntry* parent = NULL;
		TreeEntry* previous = NULL;
	};

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
			if (current->value == value) return current;

			TreeEntry* temp = findValue(current->nodes, value);
			if (temp != NULL) return temp;

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

	static ToDelete* findToDelete(TreeEntry* root, int value)
	{
		if (root == NULL) return new ToDelete();

		if (root->value == value)
		{
			ToDelete* found = new ToDelete();
			found->toDelete = root;
			return found;
		}

		TreeEntry* current = root;
		ToDelete* found = new ToDelete();
		found->previous = NULL;

		while (current != NULL)
		{
			if (current->value == value)
			{
				found->toDelete = current;
				return found;
			}
			found->previous = current;
			current = current->next;
		}

		if (root->nodes == NULL) return new ToDelete();

		found->parent = root;
		found->previous = NULL;
		current = root->nodes;

		while (current != NULL)
		{
			found->toDelete = current;

			if (current->value == value) return found;

			ToDelete* temp = findToDelete(current->nodes, value);
			if (temp != NULL && temp->toDelete != NULL)
			{
				if (temp->parent == NULL)
				{
					temp->parent = current;
				}
				return temp;
			}

			found->previous = current;
			current = ((TreeEntry*)current)->next;
		}

		return NULL;
	}

	static TreeEntry* deleteNode(TreeEntry* root, int value)
	{
		if (root == NULL) return NULL;

		ToDelete* found = findToDelete(root, value);
		if (found == NULL || found->toDelete == NULL) return NULL;

		cout << "\nParent: " << ((found->parent) ? found->parent->value : 0) <<
			" Previous: " << ((found->previous) ? found->previous->value : 0) << endl;

		if (found->parent == NULL && found->previous == NULL)
		{
			if (found->toDelete->nodes == NULL) 
			{
				root = NULL;

				return root;
			}

			root = found->toDelete->nodes;

			TreeEntry* cur = root->nodes;
			while (cur->next != NULL)
			{
				cur = cur->next;
			}

			cur->next = root->next;
			root->next = NULL;

			return root;
		}

		if (found->toDelete->nodes == NULL)
		{
			if (found->previous == NULL)
			{
				found->parent->nodes = found->toDelete->next;
				found->toDelete->next = NULL;

				return root;
			}

			found->previous->next = found->toDelete->next;
			found->toDelete->next = NULL;

			return root;
		}

		if (found->toDelete->next != NULL)
		{
			found->parent->nodes = found->toDelete->next;

			TreeEntry* cur = found->toDelete->next->nodes;
			if (cur != NULL)
			{
				while (cur != NULL && cur->next != NULL)
				{
					cur = cur->next;
				}
				cur->next = found->toDelete->nodes;

				return root;
			}			

			found->parent->nodes->nodes = found->toDelete->nodes;

			return root;
		}

		TreeEntry* cur = found->previous->nodes;
		if (cur != NULL)
		{
			while (cur != NULL && cur->next != NULL)
			{
				cur = cur->next;
			}

			cur->next = found->toDelete->nodes;
			found->previous->next = NULL;

			return root;
		}

		return NULL;
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
	root = TreeEntry::addNode(root, 2, 6);
	root = TreeEntry::addNode(root, 2, 9);
	root = TreeEntry::addNode(root, 4, 5);
	root = TreeEntry::addNode(root, 4, 7);
	TreeEntry::printOrderedList(root, 0);
	root = TreeEntry::deleteNode(root, 5);
	TreeEntry::printOrderedList(root, 0);
}

int main()
{
	testList();
	testTree();
	return 0;
}
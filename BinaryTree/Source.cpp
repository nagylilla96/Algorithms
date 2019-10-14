#include <iostream>

using namespace std;

class Node
{
public:
	int value;
	Node* left = NULL;
	Node* right = NULL;

	Node(int val)
	{
		value = val;
	}
};

Node* succ(Node* root)
{
	Node* curr = root;

	while (curr && curr->left != NULL)
	{
		curr = curr->left;
	}

	return curr;
}

Node* addNode(Node* root, int value)
{
	if (root == NULL) return new Node(value);

	if (value < root->value)
	{
		root->left = addNode(root->left, value);
		return root;
	}
	root->right = addNode(root->right, value);
	return root;
}

Node* deleteNode(Node* root, int value)
{
	if (root == NULL) return NULL;

	if (value < root->value)
	{
		root->left = deleteNode(root->left, value);
	}
	else if (value > root->value)
	{
		root->right = deleteNode(root->right, value);
	}
	else
	{
		if (root->left == NULL)
		{
			Node* temp = root->right;
			free(root);
			return temp;
		}
		else if (root->right == NULL)
		{
			Node* temp = root->left;
			free(root);
			return temp;
		}
		Node* temp = succ(root->right);
		root->value = temp->value;
		root->right = deleteNode(root->right, temp->value);
	}
	return root;
}

void printTree(Node* root, int level)
{
	if (root == NULL) return;

	printTree(root->right, level + 1);

	for (int i = 0; i < level; i++)
	{
		cout << "   ";
	}

	cout << root->value << endl;

	printTree(root->left, level + 1);
}

Node* insertArr(int* arr, int size)
{
	Node* root = NULL;
	for (int i = 0; i < size; i++)
	{
		root = addNode(root, arr[i]);
	}
	printTree(root, 0);
	return root;
}

int main()
{
	int arr[7] = { 6, 3, 8, 9, 7, 2, 1 };
	Node* root = insertArr(arr, 7);
	deleteNode(root, 6);
	printTree(root, 0);
	return 0;

}
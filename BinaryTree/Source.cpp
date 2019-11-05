#include <iostream>

using namespace std;

class Node
{
public:
	int value;
	Node* left = NULL;
	Node* right = NULL;
	int size = 1;
	int rank;

	Node(int val)
	{
		value = val;
	}

	void updateSize() {
		int s = 0;
		if (left) s += left->size;
		if (right) s += right->size;
		size = s + 1;
	}
};

Node* succ(Node* root)
{
	Node* curr = root;

	while (curr && curr->right != NULL)
	{
		curr = curr->left;
	}

	return curr;
}

Node* pred(Node* root)
{
	Node* curr = root;

	while (curr && curr->left != NULL)
	{
		curr = curr->right;
	}

	return curr;
}

Node* addNode(Node* root, int value)
{
	if (root == NULL) return new Node(value);

	if (value < root->value)
	{
		root->left = addNode(root->left, value);
		root->updateSize();

		return root;
	}

	root->right = addNode(root->right, value);
	root->updateSize();

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
	root->updateSize();


	return root;
}

void preOrder(Node* root)
{
	if (root == NULL) return;

	cout << root->value << " ";
	preOrder(root->left);
	preOrder(root->right);
}

void inOrder(Node* root) 
{
	if (root == NULL) return;

	inOrder(root->left);
	cout << root->value << " ";
	inOrder(root->right);
}

void postOrder(Node* root)
{
	if (root == NULL) return;

	postOrder(root->left);
	postOrder(root->right);
	cout << root->value << " ";
}

void printTree(Node* root, int level)
{
	if (root == NULL) return;

	printTree(root->right, level + 1);

	for (int i = 0; i < level; i++)
	{
		cout << "   ";
	}

	cout << root->value << "(" << root->size << ")" << endl;

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

void test(Node* root)
{
	cout << endl;
	preOrder(root);
	cout << endl;
	inOrder(root);
	cout << endl;
	postOrder(root);
}

int main()
{
	int arr[7] = { 6, 3, 8, 9, 7, 2, 1 };
	Node* root = insertArr(arr, 7);
	test(root);
	return 0;

}
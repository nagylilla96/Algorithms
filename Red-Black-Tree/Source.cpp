#include <iostream>

using namespace std;

// Wish me luck

class Node {
public:
	bool red = true;
	int value;
	Node* left;
	Node* right;
	Node* parent;

	Node(int value) {
		this->value = value;
	}

	Node(int value, bool red) {
		this->value = value;
		this->red = red;
	}
};

class Tree {
public:
	Node* nil = new Node(0, false);
	Node* root = nil;
};

// No matter how I write this, it's ugly!!! :( 
void leftRotate(Tree* t, Node* x) {
	if (x == t->nil) return;

	Node* y = x->right;
	x->right = y->left;

	if (y->left != t->nil) y->left->parent = x;

	y->left = x;
	y->parent = x->parent;

	if (y->parent == t->nil) t->root = y;
	else if (x == x->parent->left) x->parent->left = y;
	else x->parent->right = y;

	x->parent = y;
}

void rightRotate(Tree* t, Node* y) {
	if (y == t->nil) return;

	Node* x = y->left;
	y->left = x->right;

	if (x->right != t->nil) x->right->parent = y;

	x->right = y;
	x->parent = y->parent;

	if (x->parent == t->nil) t->root = x;
	else if (y == y->parent->right) y->parent->right = x;
	else y->parent->left = x;

	y->parent = x;
}

void fixup(Tree* t, Node* z) {
	while (z->parent != t->nil && z->parent->red) {
		if (z->parent == z->parent->parent->left) {
			Node* y = z->parent->parent->right;
			if (y->red) {
				z->parent->red = false;
				y->red = false;
				z->parent->parent->red = true;
				z = z->parent->parent;
			}
			else {
				if (z == z->parent->right) {
					z = z->parent;
					leftRotate(t, z);
				}
				z->parent->red = false;
				z->parent->parent->red = true;
				rightRotate(t, z->parent->parent);
			}
		}
		else {
			Node* y = z->parent->parent->left;
			if (y->red) {
				z->parent->red = false;
				z->parent->parent->red = true;
				y->red = false;
				z = z->parent->parent;
			}
			else {
				if (z == z->parent->left) {
					z = z->parent;
					rightRotate(t, z);
				}
				z->parent->red = false;
				z->parent->parent->red = true;
				leftRotate(t, z->parent->parent);
			}
		}
	}

	t->root->red = false;
}

void insert(Tree* t, Node* z) {
	if (z == NULL) return;
	if (t == NULL) return;

	Node* y = t->nil;
	Node* x = t->root;

	while (x != t->nil) {
		y = x;
		if (z->value < x->value) x = x->left;
		else x = x->right;
	}

	z->parent = y;

	if (y == t->nil) t->root = z;
	else if (z->value < y->value) y->left = z;
	else y->right = z;

	z->left = t->nil;
	z->right = t->nil;

	fixup(t, z);
}

int main() {
	return 0;
}
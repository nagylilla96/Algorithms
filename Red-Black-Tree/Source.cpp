#include <iostream>
#include <vector>

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

void transplant(Tree* t, Node* u, Node* v) {
	if (u->parent == t->nil) t->root = v;
	else if (u == u->parent->left) u->parent->left = v;
	else u->parent->right = v;
	
	v->parent = u->parent;
}

Node* minimum(Node* root) {
	Node* curr = root;

	while (curr->left != NULL) {
		curr = curr->left;
	}

	return curr;
}

void deleteFixup(Tree* t, Node* x) {
	Node* w;

	while (x != t->root && !x->red) {
		if (x == x->parent->left) {
			w = x->parent->right;

			if (w->red) {
				w->red = false;
				x->parent->red = true;
				leftRotate(t, x->parent);
				w = x->parent->right;
			}

			if (!w->left->red && !w->right->red) {
				w->red = true;
				x = x->parent;
			}
			else {
				if (!w->right->red) {
					w->left->red = false;
					w->red = true;
					rightRotate(t, w);
					w = x->parent->right;
				}

				w->red = x->parent->red;
				x->parent->red = false;
				w->right->red = false;
				leftRotate(t, x->parent);
				x = t->root;
			}
		}
		else {
			w = x->parent->left;

			if (w->red) {
				w->red = false;
				w->parent->red = true;
				rightRotate(t, x->parent);
				w = x->parent->left;
			}

			if (!w->right->red && !w->left->red) {
				w->red = true;
				x = x->parent;
			}
			else {
				if (!w->left->red) {
					w->right->red = false;
					w->red = true;
					leftRotate(t, w);
					w = x->parent->left;
				}

				x->red = x->parent->red;
				x->parent->red = false;
				x->left->red = false;
				rightRotate(t, x->parent);
				x = t->root;
			}
		}
	}
	x->red = false;
}

void delet(Tree* t, Node* z) {
	Node* y = z;
	Node* x;
	bool origRed = y->red;
	if (z->left == t->nil) {
		x = z->right;
		transplant(t, z, z->right);
	}
	else if (z->right == t->nil) {
		x = z->left;
		transplant(t, z, z->left);
	}
	else {
		y = minimum(z->right);
		origRed = y->red;
		x = y->right;

		if (y->parent == z) x->parent = y;
		else {
			transplant(t, y, y->right);
			y->right = z->right;
			y->right->parent = y;
		}
		
		transplant(t, z, y);
		y->left = z->left;
		y->left->parent = y;
		y->red = z->red;
	}

	if (!origRed) {
		deleteFixup(t, x);
	}
}

void prettyPrint(Node* root, int level) {
	if (root == NULL) return;

	prettyPrint(root->right, level + 1);

	for (int i = 0; i < level; i++)
	{
		cout << "   ";
	}

	if (root->red) cout << root->value << endl;
	else cout << "|" << root->value << "|" << endl;

	prettyPrint(root->left, level + 1);
}

void print(Node* root) {
	cout << "----------------------------------" << endl;
	prettyPrint(root, 0);
	cout << endl;
}

void test() {
	Tree* tree = new Tree();
	vector<Node*> nodes;

	for (int i = 1; i <= 9; i++) {
		Node* n = new Node(i);
		nodes.push_back(n);
		insert(tree, n);
		print(tree->root);
	}

	for (int i = 5; i <= 9; i++) {
		delet(tree, nodes[i - 1]);
		cout << "deleting node " << i << endl;
		print(tree->root);
	}

	delete tree;
}

int main() {
	test();

	return 0;
}
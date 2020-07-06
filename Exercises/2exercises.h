class Node
{
	int number;
	Node* next;

public: Node(int data) : number(data), next(nullptr) {};

	void addNode(int number);
	void removeDuplicatesBuffer();
	void removeDuplicatesNoBuffer();
	void printList();
};

class Module2
{
public:
	void testNode();
};
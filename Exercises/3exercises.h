namespace Ex3
{
	class Node
	{
	public:
		Node(int value, int index) : index(index), value(value), next(nullptr), prev(nullptr) {};

		int index;
		int value;
		Node* next;
		Node* prev;
	};

	class Stack
	{
	public:
		Stack() = default;
		Node* first = nullptr;
		int current = 0;

		bool push(int element);
		Node* pop();
		void printStack();
	};

	class Module3
	{
	public:
		void testTripleStack();
	};
}
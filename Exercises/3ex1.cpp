#include <iostream>
#include "3exercises.h"

int size = 0;
Ex3::Node** arr = nullptr;

bool Ex3::Stack::push(int element)
{
	Node* curr = arr[current];
	int iter = 0;
	while (arr[current] != nullptr && iter != size)
	{
		current = (current + 1) % size;
		iter++;
	}

	if (first == nullptr)
	{
		first = new Node(element, current);
		arr[current] = first;
		return true;
	}

	if (iter == size) return false;
	Node* newNode = new Node(element, current);
	curr->next = newNode;
	newNode->prev = curr;
	arr[current] = newNode;
	return true;
}

Ex3::Node* Ex3::Stack::pop()
{
	Node* curr = arr[current];
	if (curr == nullptr || curr->prev == nullptr)
	{
		first = nullptr;
		arr[current] = nullptr;
		return curr;
	}
	curr->prev->next = nullptr;
	arr[current] = nullptr;
	current = curr->prev->index;
	return curr;
}

void Ex3::Stack::printStack()
{
	Node* curr = first;
	while (curr != nullptr)
	{
		std::cout << "arr[" << curr->index << "] = " << curr->value << std::endl;
		curr = curr->next;
	}
	std::cout << std::endl;
}

void Ex3::Module3::testTripleStack()
{
	size = 9;
	arr = (Node**) malloc(size * (sizeof(Node*)));
	if (arr == nullptr)
	{
		std::cout << "Array allocation failed :(" << std::endl;
		return;
	}

	for (int i = 0; i < size; i++)
	{
		arr[i] = nullptr;
	}

	Stack* stack1 = new Stack();
	Stack* stack2 = new Stack();
	Stack* stack3 = new Stack();

	stack1->push(1);
	stack1->push(2);
	stack2->push(5);
	stack1->push(7);
	stack3->push(7);
	stack1->push(8);
	stack3->push(3);
	stack2->push(1);
	stack1->push(2);
	stack1->push(129);

	stack1->printStack();
	stack2->printStack();
	stack3->printStack();

	stack1->pop();
	stack2->push(3);

	stack1->printStack();
	stack2->printStack();

	stack3->pop();
	stack2->push(4);

	stack3->printStack();
	stack2->printStack();

	while (stack1->pop()) {};

	stack1->printStack();

	while (stack2->pop()) {};

	stack2->printStack();

	while (stack3->pop()) {};

	stack3->printStack();

	stack1->push(1);
	stack2->push(2);
	stack3->push(3);
	
	stack1->printStack();
	stack2->printStack();
	stack3->printStack();

	free(arr);
}
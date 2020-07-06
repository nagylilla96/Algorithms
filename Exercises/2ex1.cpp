#include <iostream>
#include <unordered_map>
#include "2exercises.h"

void Node::addNode(int number)
{
	Node* curr = this;
	while (curr->next != nullptr)
	{
		curr = curr->next;
	}
	curr->next = new Node(number);
}

void Node::removeDuplicatesBuffer()
{
	std::unordered_map<int, Node*> hashTable;
	Node* curr = this->next;
	Node* prev = this;
	std::pair<int, Node*> first(prev->number, prev);
	hashTable.insert(first);

	// could have been done once, while inserting
	while (curr != nullptr)
	{
		if (hashTable.count(curr->number) == 0)
		{
			std::pair<int, Node*> element(curr->number, curr);
			hashTable.insert(element);
			prev = curr;
		}
		else
		{
			prev->next = curr->next;
		}
		curr = curr->next;
	}
}

void Node::removeDuplicatesNoBuffer()
{
	Node* curr = this;
	Node* prev = this;
	Node* fast = nullptr;

	while (curr != nullptr)
	{
		fast = curr->next;
		while (fast != nullptr)
		{
			if (curr->number == fast->number)
			{
				prev->next = fast->next;
			}
			else
			{
				prev = fast;
			}
			fast = fast->next;
		}
		curr = curr->next;
		prev = curr;
	}
}

void Node::printList()
{
	Node* curr = this;
	while (curr != nullptr)
	{
		std::cout << curr->number << " ";
		curr = curr->next;
	}
	std::cout << std::endl;
}

void Module2::testNode()
{
	Node* list = new Node(1);
	list->addNode(7);
	list->addNode(7);
	list->addNode(9);
	list->addNode(3);
	list->addNode(8);
	list->addNode(1);
	list->addNode(2);

	std::cout << "Your list is: " << std::endl;
	list->printList();
	std::cout << std::endl;

	int option = 0;
	std::cout << "Choose your solution: 1. buffer 2. no buffer" << std::endl;
	std::cin >> option;

	switch (option)
	{
	case 1:
		list->removeDuplicatesBuffer();
		break;
	case 2:
		list->removeDuplicatesNoBuffer();
		break;
	case 3:
		std::cout << "Wrong option" << std::endl;
	}

	list->printList();
}
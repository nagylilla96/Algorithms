#include <iostream>
#include <string>

using namespace std;

class TrieNode
{
public:
	TrieNode* children[26] = {};
	bool isEnd = true;

	TrieNode(bool end)
	{
		isEnd = end;
		for (int i = 0; i < 26; i++)
		{
			children[i] = NULL;
		}
	}

	static int searchWord(TrieNode* root, string word)
	{
		if (root == NULL) return -1;
		if (word.length() == 0) return -1;

		TrieNode* current = root;
		for (auto s : word)
		{
			int index = tolower(s) - 'a';
			if (current->children[index] == NULL)
			{
				return -1;
			}
			current = current->children[index];
		}
		return 1;
	}

	/*
		Return:
			0 if string already existed
			1 if string was added successfully
			-1 if operation failed
	*/
	static TrieNode* addWord(TrieNode* root, string word)
	{
		if (searchWord(root, word) == 1)
		{
			return NULL;
		}

		TrieNode* current = root;
		for (auto s : word)
		{
			int index = tolower(s) - 'a';
			current->isEnd = false;
			if (current->children[index] == NULL)
			{
				current->children[index] = new TrieNode(false);
			}
			current = current->children[index];
		}
		current->isEnd = true;
		return root;
	}

	static void deleteWord(TrieNode* root, string word)
	{
		if (root == NULL) return;
		if (word == "") return;

		int lastInd = word.length() - 1;
		int last = tolower(word[lastInd]) - 'a';
		int first = tolower(word[0]) - 'a';

		deleteWord(root->children[first], word.substr(1, word.length()));

		if (root->children[last] != NULL)
		{
			root->children[last] = NULL;
			free(root->children[last]);
		}
	}
};

void search(TrieNode* root, string word)
{
	if (TrieNode::searchWord(root, word) == 1)
	{
		cout << word << " found in trie" << endl;
	}
	else
	{
		cout << word << " not found in trie" << endl;
	}
}

void test()
{
	TrieNode* root = new TrieNode(true);
	root = TrieNode::addWord(root, "alma");
	root = TrieNode::addWord(root, "ananasz");
	search(root, "alma");
	search(root, "anya");
	TrieNode::deleteWord(root, "alma");
	search(root, "alma");
	root = TrieNode::addWord(root, "uborka");
	search(root, "uborka");
}

int main()
{
	test();
	return 0;
}
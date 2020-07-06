#include <iostream>
#include <string>
#include <unordered_map>

// We can return false if the string length is bigger than the alphabet size
// If we have 26 letters in the alphabet but 27 characters in the string, there's definitely
// a duplicate
namespace ex1
{
	void hashTableAlgorithm(std::string myString)
	{
		std::unordered_map<char, bool> hashTable;
		int size = myString.length();

		for (const auto& ch : myString)
		{
			std::unordered_map<char, bool>::const_iterator it = hashTable.find(ch);
			if (it != hashTable.end())
			{
				std::cout << "Duplicate character found: " << ch << std::endl;
				return;
			}
			hashTable.insert(std::pair<char, bool>(ch, true));
		}
		std::cout << "No duplicate character found" << std::endl;
	}

	bool isBitSet(long long bits, int index, int size)
	{
		long long myBits = bits >> (size - index);
		return myBits & 1;
	}

	void setBit(long long& bits, int index, int size)
	{
		long long mask = 1 << (size - index);
		bits |= mask;
	}

	void bitVectorAlgorithm(std::string myString)
	{
		long long bitVector = 0;
		int size = 26; // the size of bitVector that we're actually using

		for (const auto& ch : myString)
		{
			if (isBitSet(bitVector, ch - 'a', size))
			{
				std::cout << "Duplicate character found: " << ch << std::endl;
				return;
			}
			setBit(bitVector, ch - 'a', size);
		}
		std::cout << "No duplicate character found" << std::endl;
	}

	int runEx1()
	{
		std::string myString;
		int algorithm = 0;

		std::cout << "Please input your string!" << std::endl;
		std::getline(std::cin, myString);

		std::cout << "Choose your algorithm: 1. for hash table, 2. for bit vector" << std::endl;
		std::cin >> algorithm;

		switch (algorithm) {
		case 1:
			hashTableAlgorithm(myString);
			return 0;
		case 2:
			bitVectorAlgorithm(myString);
			return 0;
		default:
			std::cout << "Wrong algorithm number" << std::endl;
			return -1;
		}
	}
}
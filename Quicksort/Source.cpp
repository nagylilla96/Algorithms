#include <iostream>
#include <vector>
using namespace std;

void swap(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

int partition(vector<int>& arr, int low, int high)
{
	int pivot = arr[high];
	int i = low - 1;
	for (int j = low; j < high; j++)
	{
		if (arr[j] < pivot) 
		{
			i++;
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i + 1], &arr[high]);
	return (i + 1);
}

void quickSort(vector<int>& arr, int low, int high)
{
	if (low <= high)
	{
		int p = partition(arr, low, high);
		quickSort(arr, low, p - 1);
		quickSort(arr, p + 1, high);
	}
}

void printVec(vector<int>& vec)
{
	cout << "{ ";
	for (auto const& el : vec)
	{
		cout << el << " ";
	}
	cout << "}" << endl;
}

int main()
{
	int arr[7] = { 2, 9, 3, 6, 8, 7, 1 };
	vector<int> vec(arr, arr + (sizeof(arr) / sizeof(arr[0])));
	quickSort(vec, 0, 6);
	printVec(vec);
	return 0;
}
#include <iostream>
#include <vector>

using namespace std;

void printArr(vector<int>& arr)
{
	cout << "{ ";
	for (auto const& el : arr)
	{
		cout << el << " ";
	}
	cout << "}" << endl;
}

void merge(vector<int>& arr, int low, int mid, int high)
{
	vector<int> result;

	int i = low, j = mid + 1, k = low;

	while (i <= mid && j <= high)
	{
		if (arr[i] < arr[j])
		{
			result.push_back(arr[i]);
			i++;
		}
		else
		{
			result.push_back(arr[j]);
			j++;
		}
	}

	while (i <= mid)
	{
		result.push_back(arr[i]);
		i++;
	}

	while (j <= high)
	{
		result.push_back(arr[j]);
		j++;
	}

	for (auto const& el : result)
	{
		arr[k] = el;
		k++;
	}
}

void mergeSort(vector<int>& arr, int low, int high)
{
	if (low < high)
	{
		int mid = (low + high) / 2;
		mergeSort(arr, low, mid);
		mergeSort(arr, mid + 1, high);
		merge(arr, low, mid, high);
	}
}

int main()
{
	int arr[7] = { 2, 9, 3, 6, 8, 7, 1 };
	vector<int> vec(arr, arr + (sizeof(arr) / sizeof(arr[0])));
	mergeSort(vec, 0, 6);
	printArr(vec);
	return 0;
}
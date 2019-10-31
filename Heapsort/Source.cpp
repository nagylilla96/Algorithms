#include <iostream>

using namespace std;

#define PARENT(i) ((i - 1) >> 1)
#define LEFT(i) (((i) << 1) + 1)
#define RIGHT(i) (((i) << 1) + 2)

void swap(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void maxHeapify(int* arr, int size, int i)
{
	int largest = i;
	int l = LEFT(i);
	int r = RIGHT(i);

	if (l < size && arr[l] > arr[i]) largest = l;
	else largest = i;

	if (r < size && arr[r] > arr[largest]) largest = r;

	if (largest != i)
	{
		swap(arr[i], arr[largest]);
		maxHeapify(arr, size, largest);
	}
}

void buildMaxHeap(int* arr, int size)
{
	for (int i = (size / 2); i >= 0; i--)
	{
		maxHeapify(arr, size, i);
	}
}

void heapsort(int* arr, int size)
{
	buildMaxHeap(arr, size);
	for (int i = size - 1; i >= 1; i--)
	{
		swap(arr[i], arr[0]);
		size--;
		maxHeapify(arr, size, 0);
	}
}

void printArray(int* arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		cout << arr[i] << " ";
	}
}

int heapMax(int* arr)
{
	return arr[0];
}

int heapGetMax(int* arr, int* size)
{
	if (size < 0) return -1;

	int max = heapMax(arr);
	arr[0] = arr[*size - 1];
	*size = *size - 1;
	maxHeapify(arr, *size, 0);
	return max;
}

void heapIncreaseKey(int* arr, int i, int key)
{
	if (key < arr[i]) return;

	arr[i] = key;

	while (i >= 1 && arr[PARENT(i)] < arr[i])
	{
		swap(arr[i], arr[PARENT(i)]);
		i = PARENT(i);
	}
}

void maxHeapInsert(int* arr, int* size, int key)
{
	*size = *size + 1;
	arr[*size - 1] = -1;
	heapIncreaseKey(arr, *size - 1, key);
}

int main()
{
	int numbers[] = { 2, 3, 9, 6, 8, 4, 1, 2 };
	int size = sizeof(numbers) / sizeof(int);
	buildMaxHeap(numbers, size);
	printArray(numbers, size);
	cout << endl << "Heap max: " << heapGetMax(numbers, &size) << ", size = " << size << endl;
	printArray(numbers, size);
	heapIncreaseKey(numbers, 5, 7);
	cout << endl;
	printArray(numbers, size);
	cout << endl;
	maxHeapInsert(numbers, &size, 69);
	printArray(numbers, size);
	cout << endl;
	heapsort(numbers, size);
	printArray(numbers, size);
}
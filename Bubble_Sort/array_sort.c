#include <stdio.h>

void swap(int* x, int* y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}

// A function to implement bubble sort
void bubble(int arr[], int n)
{
	int i, j;
	for (i = 0; i < n - 1; i++) //looping through the list
		for (j = 0; j < n - i - 1; j++)
			if (arr[j] > arr[j + 1]) //	if the previous element is greater than the next element
				swap(&arr[j], &arr[j + 1]); //swap the elements
}

/* Function to print an array */
void printArray(int arr[], int n)
{
	int i;
	for (i = 0; i < n; i++)
		printf("%d ", arr[i]);
	printf("\n");
}

// Driver program to test above functions
int main()
{
	int Array[] = {34,356,13245,7543,1256};
	int n = sizeof(Array) / sizeof(Array[0]); //getting the size of the array
	printf("Unsorted array: \n");
	printArray(Array, n);
	printf("Sorted array: \n");
	bubble(Array, n);
	printArray(Array, n);
	return 0;
}

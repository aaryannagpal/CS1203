#include <stdio.h>

void swap(int *a, int *b)
{
	int i = *a;
	*a = *b;
	*b = i;
}

void select(int array[], int n)
{
	int i, j, smallest;

	for (i = 0; i < n-1; i++) //traversing through the array one by one to sort
	{
		smallest = i;
		for (j = i+1; j < n; j++) //traverse the list after finding the index element
		if (array[j] < array[smallest]) //compare the element with the smallest element
			smallest = j;//if the element is smaller than the smallest element, then replace the smallest element with the element

		if(smallest != i) //if the smallest element is not the index element, then swap the elements
			swap(&array[smallest], &array[i]); //swap the elements
	}
}


void printArray(int array[], int n)
{
	int i;
	for (i=0; i < n; i++)
		printf("%d ", array[i]);
	printf("\n");
}

int main()
{
	int A[] = {3,54355,3565,234,643};
	int n = sizeof(A)/sizeof(A[0]); //calculate the size of the array

	printf("Unsorted array: \n");
	printArray(A, n);
	printf("Sorted array: \n");
	select(A, n);
	printArray(A, n);
	return 0;
}

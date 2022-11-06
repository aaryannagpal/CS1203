#include <stdio.h>

/* Function to sort an array using insertion sort*/
void insertionSort(int array[], int n)
{
	int a, current, b;
	for (a = 1; a < n; a++) {
		current = array[a]; //setting current to the next element
		b = a - 1; //setting b to the previous element
		while (b >= 0 && array[b] > current) { //while b is greater than 0 and the previous element is greater than the current element
			array[b + 1] = array[b]; //move the previous element to the next element
			b = b - 1; //decrement b
		}
		array[b + 1] = current; //move the current element to the next element
	}
}

void printArray(int array[], int n)
{
	for (int i = 0; i < n; ++i)
		printf("%d ", array[i]);
	printf("\n");
}


int main()
{
	int array[] = {3,452,4,5,33,54,63,22};
	int n = sizeof(array) / sizeof(array[0]);
    printf("Unsorted array: \n");
    printArray(array, n);
    printf("Sorted array: \n");
	insertionSort(array, n);
	printArray(array, n);

	return 0;
}

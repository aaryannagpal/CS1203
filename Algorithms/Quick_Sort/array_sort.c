#include <stdio.h>

void swap(int* x, int* y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}

int partition(int array[], int left, int right) {
  
  int pivot = array[right]; // pivot
  int i = (left - 1); // Index of smaller element
  
  for (int j = left; j < right; j++) { // If current element is smaller than or equal to pivot
    if (array[j] <= pivot) {
      i++;
      swap(&array[i], &array[j]); // swap arr[i] and arr[j]
    }
  }
  swap(&array[i + 1], &array[right]); // swap arr[i+1] and arr[right] (or pivot)
  
  return (i + 1); // return pivot index
}

// A function to implement quick sort
void quick(int array[], int left, int right) {
  if (left < right) {

    int part = partition(array, left, right); // partitioning the array
    
    quick(array, left, part - 1); // quick sort left subarray
    quick(array, part + 1, right); // quick sort right subarray
  }
}

void printArray(int arr[], int n)
{
	int i;
	for (i = 0; i < n; i++)
		printf("%d ", arr[i]);
	printf("\n");
}


int main()
{
	int Array[] = {32,5357,31,34,1,24,5,2,1345};
	int n = sizeof(Array) / sizeof(Array[0]); //getting the size of the array
	printf("Unsorted array: \n");
	printArray(Array, n);
	printf("Sorted array: \n");
	quick(Array, 0, n-1);
	printArray(Array, n);
	return 0;
}

#include <stdio.h>

void swap(int *a, int *b)
{
	int x = *a;
	*a = *b;
	*b = x;
}

void MAKE_HEAP(int array[], int N, int i)
{
	int largest = i; // Initialize largest as root
	int l = 2 * i + 1; // left = 2*i + 1
	int r = 2 * i + 2; // right = 2*i + 2

	if (l < N && array[l] > array[largest]) // If left child is larger than root
		largest = l; //largest = left


	if (r < N && array[r] > array[largest])// same for right
		largest = r; //largest = right

	if (largest != i) {
		swap(&array[i], &array[largest]); // swap

		MAKE_HEAP(array, N, largest);
	}   
}

void Heap(int array[], int N)
{
	int first = (N / 2) - 1; // first non-leaf node

	for (int i = first; i >= 0; i--) {// Build heap (rearrange array)
		MAKE_HEAP(array, N, i);
	}
}


void print(int array[], int N)
{
	printf("Heap is:\n");

	for (int i = 0; i < N; ++i)
		printf("%d ",array[i]);
	printf("\n");
}

void printMin(int array[], int N)
{    
    printf("Minimum: %d", array[N-1]);
    printf("\n");

}

void insert(int data, int array[], int N)
{
    int temp[N+1]; // temp array

    for(int i=0; i<N; i++){
        temp[i] = array[i];// copy array to temp
    }
    temp[N] = data;// insert data to temp
    Heap(temp, N+1);// heapify temp
    printf("Inserted Heap: ");
    print(temp, N+1);// print temp
}

int main()
{

	int arr[] = {234,4,26,84,3,6,8,5,35};

	int N = sizeof(arr) / sizeof(arr[0]);

	Heap(arr, N);
	print(arr, N);

    printMin(arr, N);
    insert(45,arr, N);
    

	return 0;
}

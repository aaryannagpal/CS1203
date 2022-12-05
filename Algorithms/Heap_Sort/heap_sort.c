#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b)
{
    int x = *a;
    *a = *b;
    *b = x;
}

void heapify(int array[], int N, int i)
{
    int largest = i; // Initialize largest as root
    int l = 2 * i + 1; // left = 2*i + 1
    int r = 2 * i + 2; // right = 2*i + 2

    if (l < N && array[l] > array[largest]) // If left child is larger than root
        largest = l; //largest = left

    if (r < N && array[r] > array[largest])// same for right
        largest = r; //largest = right

    if (largest != i) { // if largest is not root
        swap(&array[i], &array[largest]); // swap

        heapify(array, N, largest);
    }
}

void heapSort(int array[], int N)
{
    int first = (N / 2) - 1; // first non-leaf node

    for (int i = first; i >= 0; i--) {// Build heap (rearrange array)
        heapify(array, N, i);
    }

    for (int i = N - 1; i >= 0; i--) {
        swap(&array[0], &array[i]); // swap

        heapify(array, i, 0);
    }
}

void print(int array[], int N)
{
    printf("Heap is:\n");

    for (int i = 0; i < N; ++i)
        printf("%d ",array[i]);
    printf("\n");
}

int main()
{
    int arr[] = {234,4,26,84,3,6,8,5,35};
    int N = sizeof(arr) / sizeof(arr[0]);

    heapSort(arr, N);

    print(arr, N);

    return 0;
}

// CODE: include necessary library(s)
#include <stdio.h>
#include <string.h>
#include "mySort.h"

// Utility functions
void printArray(int arr[], int n);

// Test the sorting algorithms
int main() {
    int arr[] = {64, -134, -5, 0, 25, 12, 22, 11, 90};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    int testArr[n];
    
    // Bubble Sort
    memcpy(testArr, arr, n * sizeof(int));
    printf("Original array: ");
    printArray(testArr, n);
    bubbleSort(testArr, n);
    printf("Bubble sorted array: ");
    printArray(testArr, n);

    // insertion sort
    memcpy(testArr, arr, n * sizeof(int));
    printf("Original array: ");
    printArray(testArr, n);
    insertionSort(testArr, n);
    printf("Insertion sorted array: ");
    printArray(testArr, n);

    // merge sort
    memcpy(testArr, arr, n * sizeof(int));
    printf("Original array: ");
    printArray(testArr, n);
    mergeSort(testArr, 0, n-1);
    printf("Merge sorted array: ");
    printArray(testArr, n);

    // heap sort
    memcpy(testArr, arr, n * sizeof(int));
    printf("Original array: ");
    printArray(testArr, n);
    heapSort(testArr, n);
    printf("Heap sorted array: ");
    printArray(testArr, n);

    // counting sort
    memcpy(testArr, arr, n * sizeof(int));
    printf("Original array: ");
    printArray(testArr, n);
    countingSort(testArr, n);
    printf("Counting sorted array: ");
    printArray(testArr, n);

    return 0;
}

// Helper functions
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}



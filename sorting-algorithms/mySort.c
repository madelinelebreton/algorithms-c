// this code was written by madeline except swap and bubbleSort
#include <stdio.h>

// function to swap two numbers
void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

// bubble sort ////////////////////////////////////////////
// repeatedly steps through list, compares and swaps adjacent elements
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1])
                swap(&arr[j], &arr[j + 1]);
        }
    }
}

// insertion sort ////////////////////////////////////////////
// builds the final sorted array one item at a time
void insertionSort(int arr[], int n){
  // step through the list to each element
  for (int i=0; i<=n-1; i++){
    // compare current element to each element in sorted part
    for (int j=0; j<=i; j++){
      if (arr[i]<arr[j]){
        // swap current element with the element in sorted part
        swap(&arr[i], &arr[j]);
      }
    }
  }
}

// function to merge subarrays used in mergeSort //////////////
void merge(int arr[], int l, int split, int r){
  // make left half and right half arrays
  int n1 = split-l+1;
  int n2 = r-split;
  int arr1[n1]; // create array for the left half
  int arr2[n2]; // create array for the right half

  for (int i=0; i<n1; i++){ // copy left half of arr into arr1
    arr1[i] = arr[l+i];
  }
  for (int j=0; j<n2; j++){ // copy right half of arr into arr2
    arr2[j] = arr[split+1+j];
  }

  int i=0; int j=0; int k=l; // initialize counters
  while(i<n1 && j<n2){ 
    if(arr1[i]<arr2[j]){ //assign the smaller element to arr
      arr[k] = arr1[i]; // assign the left array element to arr
      i++; k++;
    }
    else{
      arr[k] = arr2[j]; // assign the right array element to arr
      j++; k++;
    }
  }

  while(i<n1) { // copy remaining elements from left array
    arr[k] = arr1[i];
    i++; k++;
  } while(j<n2) { // copy remaining elements from right array
    arr[k] = arr2[j];
    j++; k++;
  }
}

// merge sort ////////////////////////////////////////////
// recursively sorts each half then merges the sorted halves
void mergeSort(int arr[], int l, int r){
  // base case: 0 or 1 elements, already sorted
  if (l>=r) {
    return;
  }

  // recursive function call
  int split = (l+r)/2; // find middle index
  mergeSort(arr, l, split); // sort the left half
  mergeSort(arr, split+1, r); // sort the right half
  merge(arr, l, split, r); // merge the two halves
}


// recursive function to build max heap, used in heapSort /////////
void makeHeap(int heapArr[], int n, int i) {
  int max = i; // initialize max as current root i
  int left = 2*i+1; // left child
  int right = 2*i+2; // right child

  // update max if either child larger than root
  if (left < n && heapArr[left] > heapArr[max]) {
    max = left;
  } if (right < n && heapArr[right] > heapArr[max]) {
    max = right;
  }

  // if root is not max, swap and continue recursively
  if (max != i) {
    swap(&heapArr[i], &heapArr[max]);
    makeHeap(heapArr, n, max);
  }
}

// heap sort ////////////////////////////////////////////
// build max heap, extract max and rebuild array until heap is empty
void heapSort(int arr[], int n){
  int heapArr[n]; // build array to store heap
  for(int x = 0; x<n; x++) {
    heapArr[x] = arr[x]; // copy original array into heapArr
  }

  // rearrange to build max heap
  for (int i=(n/2)-1; i>=0; i--) {
    makeHeap(heapArr, n, i);
  }

  // extract heap elements one at a time
  for (int i=n-1; i>=0; i--) {
    // move current root (max element) to end of arr
    swap(&heapArr[0], &heapArr[i]);
    // again with the reduced heap
    makeHeap(heapArr, i, 0);
  }

  // copy sorted heap back to arr
  for (int i=0; i<n; i++) {
    arr[i] = heapArr[i];
  }
}


// counting sort ////////////////////////////////////////////
// counts occurrences of each element then calculates output position

void countingSort(int arr[], int n){
  // determine range of input values
  int max = arr[0];
  for(int i=1; i<n; i++){ // find max element
    if(arr[i]>max){
      max=arr[i];
    }
  } int min = arr[0];
  for(int i=1; i<n; i++){ // find min element
    if(arr[i]<min){
      min=arr[i];
    }
  } int range = max-min;

  // create empty array to store number of occurrences
  int countArr[range+1];
  for(int i=0; i<range+1; i++){
    countArr[i] = 0;
  }

  // count occurrences of each element
  for(int i=0; i<n; i++){
    int num = arr[i];
    countArr[num-min]++;
  }

  // rebuild array
  int index = 0;
  for (int i = 0; i <= range; i++) { // for each element in countArr
    while (countArr[i] > 0) {
      arr[index] = i + min; // update original array entries
      countArr[i]--;
      index++;
    }
  } return;
}
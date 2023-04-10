#include <stdio.h>
#include <stdlib.h>


// Function to swap the the position of two elements
  void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
  }

  void heapify(int arr[], int n, int i) {
    // Find largest among root, left child and right child
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
      largest = left;

    if (right < n && arr[right] > arr[largest])
      largest = right;

    // Swap and continue heapifying if root is not largest
    if (largest != i) {
      swap(&arr[i], &arr[largest]);
      heapify(arr, n, largest);
    }
  }

  // Main function to do heap sort
  void heapSort(int arr[], int n) {
    // Build max heap
    for (int i = n / 2 - 1; i >= 0; i--)
      heapify(arr, n, i);

    // Heap sort
    for (int i = n - 1; i >= 0; i--) {
      swap(&arr[0], &arr[i]);

      // Heapify root element to get highest element at root again
      heapify(arr, i, 0);
    }
  }


int findKthLargest(int* nums, int numsSize, int k)
{
    heapSort(nums, numsSize);
    return nums[numsSize-k];

}


int main(int argc, char **argv)
{
    
    printf("\nTest 1...\n");
    int num1[6] = {3,2,1,5,6,4};
    printf("2nd largest in [3 2 1 5 6 4]\n");
    printf("Expected: 5\n");
    printf("Actual: %d\n", findKthLargest(num1, 6, 2));

    printf("\nTest 2...\n");
    int num2[9] = {3,2,3,1,2,4,5,5,6};
    printf("4th largest in [3 2 3 1 2 4 5 5 6]\n");
    printf("Expected: 4\n");
    printf("Actual: %d\n", findKthLargest(num2, 9, 4));


    printf("\nTest 3...\n");
    int num3[5] = {10,10,10,10,10};
    printf("5th largest in [10 10 10 10 10]\n");
    printf("Expected: 10\n");
    printf("Actual: %d\n", findKthLargest(num3, 5, 5));

    printf("\nTest 4...\n");
    int num4[7] = {-10,10,-10,10,-10,10,0};
    printf("4th largest in [-10 10 -10 10 -10 10 0]\n");
    printf("Expected: 0\n");
    printf("Actual: %d\n", findKthLargest(num4, 7, 4));

    printf("\nTest 5...\n");
    int num5[10] = {10,9,8,7,6,5,4,3,2,1};
    printf("1st largest in [10 9 8 7 6 5 4 3 2 1]\n");
    printf("Expected: 10\n");
    printf("Actual: %d\n", findKthLargest(num5, 10, 1));


    return 0;
}
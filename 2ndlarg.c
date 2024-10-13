/*2(b)
Write a user-defined function to find and return the second largest number in a given array.
Function prototype 
Int find2ndMax(int numbers[],int size);*/

#include <stdio.h>
#include <limits.h>

int find2ndMax(int numbers[], int size) {
  if (size < 2) {
    // Not enough elements to have a second largest
    return INT_MIN;  // Return the smallest possible integer
  }
  // Initialize largest and second largest
  int largest = INT_MIN; 
  int secondLargest = INT_MIN;
  // Find the largest and second largest
  for (int i = 0; i < size; i++) {
    if (numbers[i] > largest) {
      secondLargest = largest;
      largest = numbers[i];
    } else if (numbers[i] > secondLargest && numbers[i] != largest) {
      secondLargest = numbers[i];
    }
  }

  return secondLargest;
}
// Main function
int main() {
  // Test array
  int arr[] = {10, 5, 25, 15, 20};
  // Calculate the size of the array
  int size = sizeof(arr) / sizeof(arr[0]);
  // Find the second largest element
  int secondMax = find2ndMax(arr, size);

  // Print the result

  if (secondMax == INT_MIN) {
    printf("There is no second largest element\n");
  } else {
    printf("The second largest element is: %d\n", secondMax);
  }

  return 0;
}
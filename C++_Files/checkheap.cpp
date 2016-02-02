// C program to check whether a given array
// represents a max-heap or not
#include <stdio.h>
#include <limits.h>
 
// Returns true if arr[i..n-1] represents a
// max-heap
bool isHeap(int arr[], int i, int n)
{
   // If a leaf node
   if (i > (n - 2)/2)
       return true;
 
   // If an internal node and is greater than its children, and
   // same is recursively true for the children
   if (arr[i] >= arr[2*i + 1]  &&  arr[i] >= arr[2*i + 2] &&
       isHeap(arr, 2*i + 1, n) && isHeap(arr, 2*i + 2, n))
       return true;
 
   return false;
}
 
// Driver program
int main()
{
    int arr[] = {90, 15, 10, 7, 12, 2, 7, 3};
    int n = sizeof(arr) / sizeof(int);
 
    isHeap(arr, 0, n)? printf("Yes"): printf("No");
 
    return 0;
}

// C++ program to find minimum number of swaps required so that
// all pairs become adjacent.
#include<bits/stdc++.h>
using namespace std;
 
// This function updates indexes of elements 'a' and 'b'
void updateindex(int index[], int a, int ai, int b, int bi)
{
    index[a] = ai;
    index[b] = bi;
}
 
// This function returns minimum number of swaps required to arrange
// all elements of arr[i..n] become aranged
int minSwapsUtil(int arr[], int pairs[], int index[], int i, int n)
{
    // If all pairs procesed so no swapping needed return 0
    if (i > n) return 0;
 
    // If current pair is valid so DO NOT DISTURB this pair
    // and move ahead.
    if (pairs[arr[i]] == arr[i+1])
         return minSwapsUtil(arr, pairs, index, i+2, n);
 
    // If we reach here, then arr[i] and arr[i+1] don't form a pair
 
    // Swap pair of arr[i] with arr[i+1] and recursively compute
    // minimum swap required if this move is made.
    int one = arr[i+1];
    int indextwo = i+1;
    int indexone = index[pairs[arr[i]]];
    int two = arr[index[pairs[arr[i]]]];
    swap(arr[i+1], arr[indexone]);
    updateindex(index, one, indexone, two, indextwo);
    int a = minSwapsUtil(arr, pairs, index, i+2, n);
 
    // Backtrack to previous configuration. Also restore the
    // previous indices, of one and two
    swap(arr[i+1], arr[indexone]);
    updateindex(index, one, indextwo, two, indexone);
    one = arr[i], indexone = index[pairs[arr[i+1]]];
 
    // Now swap arr[i] with pair of arr[i+1] and recursively
    // compute minimum swaps required for the subproblem
    // after this move
    two = arr[index[pairs[arr[i+1]]]], indextwo = i;
    swap(arr[i], arr[indexone]);
    updateindex(index, one, indexone, two, indextwo);
    int b = minSwapsUtil(arr, pairs, index, i+2, n);
 
    // Backtrack to previous configuration.  Also restore
    // the previous indices, of one and two
    swap(arr[i], arr[indexone]);
    updateindex(index, one, indextwo, two, indexone);
 
    // Return minimum of two cases
    return 1 + min(a, b);
}
 
// Returns minimum swaps required
int minSwaps(int n, int pairs[], int arr[])
{
    int index[2*n + 1]; // To store indices of array elements
 
    // Store index of each element in array index
    for (int i = 1; i <= 2*n; i++)
        index[arr[i]] = i;
 
    // Call the recursive function
    return minSwapsUtil(arr, pairs, index, 1, 2*n);
}
 
// Driver program
int main()
{
    // For simplicity, it is assumed that arr[0] is
    // not used.  The elements from index 1 to n are
    // only valid elements
    int arr[] = {0, 3, 5, 6, 4, 1, 2};
 
    // if (a, b) is pair than we have assigned elements
    // in array such that pairs[a] = b and pairs[b] = a
    int pairs[] = {0, 3, 6, 1, 5, 4, 2};
    int m = sizeof(arr)/sizeof(arr[0]);
 
    int n = m/2;  // Number of pairs n is half of total elements
 
    // If there are n elements in array, then
    // there are n pairs
    cout << "Min swaps required is " << minSwaps(n, pairs, arr);
    return 0;
}
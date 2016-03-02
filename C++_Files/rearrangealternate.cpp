// C++ program to rearrange an array in minimum maximum form
// using O(1) space.
#include <bits/stdc++.h>
using namespace std;
 
// Puts max at first position, min at second position
// second max at third position, second min at fourth
// position and so on.
void rearrange(int arr[], int n)
{
    // Traverse through all numbers
    for (int i=0; i<n; i++)
    {
        int temp = arr[i];
 
        // If number is negative then we have already
        // processed it. Else process all numbers which
        // are to be replaced by each other in cyclic way
        while (temp > 0)
        {
            // Find the index where arr[i] should go
            int j = (i < n/2)? 2*i + 1 : 2*(n-1-i);
 
            // If arr[i] is already at its correct
            // position, mark it as negative
            if (i == j)
            {
                arr[i] = -temp;
                break;
            }
 
            // Swap the number 'temp' with the current number
            // at its target position
            swap(temp, arr[j]);
 
            // Mark the number as processed
            arr[j] = -arr[j];
 
            // Next process the previous number at target position
            i = j;
        }
    }
 
    // Change the number to original value
    for (int i=0; i<n; i++)
        arr[i] = -arr[i];
}
 
// Driver program to test above function
int main()
{
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int n = sizeof(arr)/sizeof(arr[0]);
 
    cout << "Original Array\n";
    for (int i=0; i<n; i++)
       cout << arr[i] << " ";
 
    rearrange(arr, n);
 
    cout << "\nModified Array\n";
    for (int i=0; i<n; i++)
       cout << arr[i] << " ";
    return 0;
}

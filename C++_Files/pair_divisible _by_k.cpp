// A C++ program to check if arr[0..n-1] can be divided
// in pairs such that every pair is divisible by k.
#include <bits/stdc++.h>
using namespace std;
 
// Returns true if arr[0..n-1] can be divided into pairs
// with sum divisible by k.
bool canPairs(int arr[], int n, int k)
{
    // An odd length array cannot be divided into pairs
    if (n & 1)
        return false;
 
    // Create a frequency array to count occurrences
    // of all remainders when divided by k.
    map<int, int> freq;
 
    // Count occurrences of all remainders
    for (int i = 0; i < n; i++)
        freq[arr[i] % k]++;
 
    // Traverse input array and use freq[] to decide
    // if given array can be divided in pairs
    for (int i = 0; i < n; i++)
    {
        // Remainder of current element
        int rem = arr[i] % k;
 
        // If remainder with current element divides
        // k into two halves.
        if  (2*rem == k)
        {
            // Then there must be even occurrences of
            // such remainder
            if (freq[rem] % 2 != 0)
                return false;
        }
 
        // If remainder is 0, then there must be two 
        // elements with 0 remainder
        else if (rem == 0)
        {
           if (freq[rem] & 1)           
               return false;
        }        
 
        // Else number of occurrences of remainder
        // must be equal to number of occurrences of
        // k - remainder
        else if (freq[rem] != freq[k - rem])
            return false;
    }
    return true;
}
 
/* Driver program to test above function */
int main()
{
    int arr[] =  {92, 75, 65, 48, 45, 35};
    int k = 10;
    int n = sizeof(arr)/sizeof(arr[0]);
    canPairs(arr, n, k)? cout << "True": cout << "False";
    return 0;
}

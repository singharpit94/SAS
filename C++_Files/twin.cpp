// C++ program to find the smallest twin in given range
#include <bits/stdc++.h>
using namespace std;
 
void printTwins(int low, int high)
{
    // Create a boolean array "mark[0..high]" and initialize
    // all entries it as false. A value in mark[i] will finally
    // be true if i is, else false.
    bool mark[high+1];
    memset(mark, 0, sizeof(mark));
 
    // Initialize previous prime as low. Previous prime is
    // going to store first number of twin.
    int prev = low;
 
    //  Look for the smallest twin
    for (int p=2; p<=high; p++)
    {
        // If p is not marked, then it is a prime
        if (!mark[p])
        {
            // Check if p forms twin with prev
            if (p>=low && p-prev == 2)
            {
                cout << "Smallest twins in given range: (" 
                     << prev << ", " << p <<  ")";
                return;
            }
 
            // Update all multiples of p
            for (int i=p; i<=high; i += p)
                mark[i] = true;
 
             // Updated prev
             prev =  p;
        }
    }
}
 
// Driver program
int main()
{
    printTwins(10, 100);
    return 0;
}

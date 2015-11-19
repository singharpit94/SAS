// A Dynamic programming based C++ program to count derangements
#include <bits/stdc++.h>
using namespace std;
 
int countDer(int n)
{
    // Create an array to store counts for subproblems
    int der[n + 1];
 
    // Base cases
    der[0] = 1;
    der[1] = 0;
    der[2] = 1;
 
    // Fill der[0..n] in bottom up manner using above
    // recursive formula
    for (int i=3; i<=n; ++i)
        der[i] = (i-1)*(der[i-1] + der[i-2]);
 
    // Return result for n
    return der[n];
}
 
// Driver program
int main()
{
    int n = 4;
    cout << "Count of Derangements is " << countDer(n);
    return 0;
}

// C++ program to find XOR of XOR's of all subsets
#include <iostream>
using namespace std;
 
// Returns XOR of all XOR's of given subset
int findXOR(int Set[], int n)
{
    // XOR is 1 only when n is 1, else 0
    if (n == 1)
       return Set[0];
    else
       return 0;
}
 
// Driver program
int main()
{
    int Set[] = {1, 2, 3};
    int n = sizeof(Set)/sizeof(Set[0]);
    cout << "XOR of XOR's of all subsets is "
         << findXOR(Set, n);
    return 0;
}

// C++ program to find XOR without using ^
#include <iostream>
using namespace std;
 
// Returns XOR of x and y
int myXOR(int x, int y)
{
   return (x | y) & (~x | ~y);
}
 
// Driver program to test above function
int main()
{
   int x = 3, y = 5;
   cout << "XOR is " << myXOR(x, y);
   return 0; 
}

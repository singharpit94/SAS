// C++ program to count squares in a rectangle of
// size m x n
#include<iostream>
using namespace std;
 
// Returns count of all squares in a rectangle
// of size m x n
int countSquares(int m, int n)
{
   // If m is smaller, swap m and n
   if (m < n)
      swap(m, n);
 
   // Now m is greater dimension, apply formula
   return  m*(m+1)*(2*m+1)/6 + (n-m)*m*(m+1)/2;
}
 
// Driver method
int main()
{
   int m = 4, n = 3;
   cout << "Count of squares is " << countSquares(m, n);
}

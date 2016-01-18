// C++ program to find the smallest values of x and y that
// satisfy "ax - by = 0"
#include <iostream>
using namespace std;
 
// To find GCD using Eculcid's algorithm
int gcd(int a,int b)
{
    if (b==0)
       return a;
    return(gcd(b,a%b));
}
 
// Prints smallest values of x and y that
// satisfy "ax - by = 0"
void findSmallest(int a, int b)
{
    // Find LCM
    int lcm = (a*b)/gcd(a, b);
 
    cout << "x = " << lcm/a
         << "\ny = " << lcm/b;
}
 
// Driver program
int main()
{
   int a = 25, b = 35;
   findSmallest(a, b);
   return 0;
}

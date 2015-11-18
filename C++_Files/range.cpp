#include <iostream>
using namespace std;
 
// Returns true if x is in range [low..high], else false
bool inRange(int low, int high, int x)
{
    return ((x-high)*(x-low) <= 0);
}
 
int main()
{
    inRange(10, 100, 30)? cout << "Yes\n":  cout  <<"No\n";
    inRange(10, 100, 5)?  cout << "Yes\n":  cout  <<"No\n";
}

// Finds and prints all jumping numbers smaller than or
// equal to x.
#include<bits/stdc++.h>
using namespace std;
 
// Prints all jumping numbers smaller than or equal to x starting
// with 'num'. It mainly does BFS starting from 'num'.
void bfs(int x, int num)
{
    // Create a queue and enqueue 'i' to it
    queue<int > q;
    q.push(num);
 
    // Do BFS starting from i
    while (!q.empty())
    {
        num = q.front();
        q.pop();
 
        if (num <= x)
        {
            cout << num << " ";
            int last_dig = num % 10;
 
            // If last digit is 0, append next digit only
            if (last_dig == 0)
                q.push((num*10) + (last_dig+1));
 
 
            // If last digit is 9, append previous digit only
            else if (last_dig == 9)
                q.push( (num*10) + (last_dig-1) );
 
            // If last digit is neighter 0 nor 9, append both 
            // previous and next digits
            else
            {
                q.push((num*10) + (last_dig-1));
                q.push((num*10) + (last_dig+1));
            }
        }
    }
}
 
// Prints all jumping numbers smaller than or equal to
// a positive number x
void printJumping(int x)
{
    cout << 0 << " ";
    for (int i=1; i<=9 && i<=x; i++)
       bfs(x, i);
}
 
// Driver program
int main()
{
    int x = 40;
    printJumping(x);
    return 0;
}

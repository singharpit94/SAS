// A Dynamic Programming based solution to count number
// of ways to represent n as sum of four numbers
#include<bits/stdc++.h>
using namespace std;
int dp[5001][5001][5];
 
// "parts" is number of parts left, n is the value left
// "nextPart" is starting point from where we start trying
// for next part.
int countWaysUtil(int n, int parts, int nextPart)
{
    // Base cases
    if (parts == 0 && n == 0) return 1;
    if (n <= 0 || parts <= 0) return 0;
 
    // If this subproblem is already solved
    if (dp[n][nextPart][parts] != -1)
       return dp[n][nextPart][parts];
 
    int ans = 0; // Initialize result
 
    // Count number of ways for remaining number n-i
    // remaining parts "parts-1", and for all part
    // varying from 'nextPart' to 'n'
    for (int i = nextPart; i <= n; i++)
        ans += countWaysUtil(n-i, parts-1, i);
 
    // Store computed answer in table and return
    // result
    return (dp[n][nextPart][parts] = ans);
}
 
// This function mainly initializes dp table and
// calls countWaysUtil()
int countWays(int n)
{
    memset(dp, -1, sizeof(dp));
    return countWaysUtil(n, 4, 1);
}
 
// Driver program
int main()
{
   int n = 8;
   cout << countWays(n) << endl;
   return 0;
}

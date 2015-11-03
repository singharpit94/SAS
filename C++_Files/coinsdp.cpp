// A Dynamic Programming based C++ program to find maximum
// number of coins that can be collected before hitting a
// dead end
#include<bits/stdc++.h>
using namespace std;
#define R 5
#define C 5
 
// to check whether current cell is out of the grid or not
bool isValid(int i, int j)
{
    return (i >=0 && i < R && j >=0 && j < C);
}
 
// dir = 0 for left, dir = 1 for right.  This function returns
// number of maximum coins that can be collected starting from
// (i, j).
int maxCoinsUtil(char arr[R][C],  int i, int j, int dir,
                 int dp[R][C][2])
{
    // If this is a invalid cell or if cell is a blocking cell
    if (isValid(i,j) == false || arr[i][j] == '#')
        return 0;
 
    // If this subproblem is already solved than return the
    // already evaluated answer.
    if (dp[i][j][dir] != -1)
       return dp[i][j][dir];
 
    // Check if this cell contains the coin 'C' or if its 'E'.
    dp[i][j][dir] = (arr[i][j] == 'C')? 1: 0;
 
    // Get the maximum of two cases when you are facing right
    // in this cell
    if (dir == 1) // Direction is right
       dp[i][j][dir] += max(maxCoinsUtil(arr, i+1, j, 0, dp), // Down
                            maxCoinsUtil(arr, i, j+1, 1, dp)); // Ahead in rught
 
    // Get the maximum of two cases when you are facing left
    // in this cell
    if (dir == 0) // Direction is left
       dp[i][j][dir] += max(maxCoinsUtil(arr, i+1, j, 1, dp),  // Down
                            maxCoinsUtil(arr, i, j-1, 0, dp)); // Ahead in left
 
    // return the answer
    return dp[i][j][dir];
}
 
// This function mainly creates a lookup table and calls
// maxCoinsUtil()
int maxCoins(char arr[R][C])
{
    // Create lookup table and initialize all values as -1
    int dp[R][C][2];
    memset(dp, -1, sizeof dp);
 
    // As per the question initial cell is (0, 0) and direction
    // is right
    return maxCoinsUtil(arr, 0, 0, 1, dp);
}
 
// Driver program to test above function
int main()
{
    char arr[R][C] = { {'E', 'C', 'C', 'C', 'C'},
                       {'C', '#', 'C', '#', 'E'},
                       {'#', 'C', 'C', '#', 'C'},
                       {'C', 'E', 'E', 'C', 'E'},
                       {'C', 'E', '#', 'C', 'E'}
                     };
 
 
    cout << "Maximum number of collected coins is "
         << maxCoins(arr);
 
    return 0;
}

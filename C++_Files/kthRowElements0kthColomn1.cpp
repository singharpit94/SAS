// C++ program to find i such that all entries in i'th row are 0
// and all entries in i't column are 1
#include <iostream>
using namespace std;
#define n 5
 
int find(bool arr[n][n])
{
    // Start from top-most rightmost corner
    // (We could start from other corners also)
    int i=0, j=n-1;
 
    // Initialize result
    int res = -1;
 
    // Find the index (This loop runs at most 2n times, we either
    // increment row number or decrement column number)
    while (i<n && j>=0)
    {
        // If current element is 0, then this row may be a solution
        if (arr[i][j] == 0)
        {
            // Check for all elements in this row
            while (j >= 0 && (arr[i][j] == 0 || i == j))
                j--;
 
            // If all values are 0, then store this row as result
            if (j == -1)
            {
                res = i;
                break;
            }
 
            // We reach here if we found a 1 in current row, so this
            //  row cannot be a solution, increment row number
            else i++;
        }
        else // If current element is 1
        {
            // Check for all elements in this column
            while (i<n && (arr[i][j] == 1 || i == j))
                i++;
 
            // If all elements are 1
            if (i == n)
            {
                res = j;
                break;
            }
 
            // We reach here if we found a 0 in current column, so this
            // column cannot be a solution, increment column number
            else j--;
        }
    }
 
    // If we could not find result in above loop, then result doesn't exist
    if (res == -1)
       return res;
 
    // Check if above computed res is valid
    for (int i=0; i<n; i++)
       if (res != i && arr[i][res] != 1)
          return -1;
    for (int j=0; j<n; j++)
       if (res != j && arr[res][j] != 0)
          return -1;
 
    return res;
}
 
 
/* Driver program to test above functions */
int main()
{
    bool mat[n][n] = {{0, 0, 1, 1, 0},
                      {0, 0, 0, 1, 0},
                      {1, 1, 1, 1, 0},
                      {0, 0, 0, 0, 0},
                      {1, 1, 1, 1, 1}};
    cout << find(mat);
 
    return 0;
}


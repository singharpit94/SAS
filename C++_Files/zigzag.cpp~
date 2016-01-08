// C++ program to print string obtained by concatenation
// of different rows of Zig-Zag fashion
#include<bits/stdc++.h>
using namespace std;
 
// Prints concatenation of all rows of str's Zig-Zag fasion
void printZigZagConcat(string str, int n)
{
    // Corner Case (Only one row)
    if (n == 1)
    {
        cout << str;      
        return;
    }   
 
    // Find length of string
    int len = str.length();
 
    // Create an array of strings for all n rows
    string arr[n];
 
    // Initialize index for array of strings arr[]
    int row = 0;
    bool down; // True if we are moving down in rows, 
               // else false
 
    // Travers through given string
    for (int i = 0; i < len; ++i)
    {
        // append current character to current row
        arr[row].push_back(str[i]);
 
        // If last row is reached, change direction to 'up'
        if (row == n-1)
          down = false;
 
        // If 1st row is reached, change direction to 'down'
        else if (row == 0)
          down = true;
 
        // If direction is down, increment, else decrement
        (down)? (row++): (row--);
    }
 
    // Print concatenation of all rows
    for (int i = 0; i < n; ++i)
        cout << arr[i];
}
 
// Driver program
int main()
{
    string str = "GEEKSFORGEEKS";
    int n = 3;
    printZigZagConcat(str, n);
    return 0;
}

// Finds maximum occurring digit without using any array/string
#include <iostream>
using namespace std;
 
// Simple function to count occurrences of digit d in x
int countOccurrences(long int x, int d)
{
    int count = 0;  // Initialize count of digit d
    while (x)
    {
        // Increment count if current digit is same as d
        if (x%10 == d)
           count++;
        x = x/10;
    }
    return count;
}
 
// Returns the max occurring digit in x
int maxOccurring(long int x)
{
   // Handle negative number
   if (x < 0)
      x = -x;
 
   int result = 0; // Initialize result which is a digit
   int max_count = 1; // Initialize count of result
 
   // Traverse through all digits
   for (int d=0; d<=9; d++)
   {
      // Count occurrences of current digit
      int count = countOccurrences(x, d);
 
      // Update max_count and result if needed
      if (count >= max_count)
      {
         max_count = count;
         result = d;
      }
   }
   return result;
}
 
// Driver program
int main()
{
    long int x = 1223355;
    cout << "Max occurring digit is " << maxOccurring(x);
    return 0;
}

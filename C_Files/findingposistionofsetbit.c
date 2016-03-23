#include <stdio.h>
 
unsigned int Log2n(unsigned int n)
{
   return (n > 1)? 1 + Log2n(n/2): 0;
}
 
int isPowerOfTwo(unsigned n)
{
    return n && (! (n & (n-1)) );
}
 
int findPosition(unsigned n)
{
    if (!isPowerOfTwo(n))
        return -1;
    return Log2n(n) + 1;
}
 
// Driver program to test above function
int main(void)
{
    int n = 0;
    int pos = findPosition(n);
    (pos == -1)? printf("n = %d, Invalid number\n", n):
                 printf("n = %d, Position %d \n", n, pos);
 
    n = 12;
    pos = findPosition(n);
    (pos == -1)? printf("n = %d, Invalid number\n", n):
                 printf("n = %d, Position %d \n", n, pos);
 
    n = 128;
    pos = findPosition(n);
    (pos == -1)? printf("n = %d, Invalid number\n", n):
                 printf("n = %d, Position %d \n", n, pos);
 
    return 0;
}

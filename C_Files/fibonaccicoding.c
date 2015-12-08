/* C program for Fibonacci Encoding of a positive integer n */
 
#include<stdio.h>
#include<stdlib.h>
 
// To limit on the largest Fibonacci number to be used
#define N 30 
 
/* Array to store fibonacci numbers.  fib[i] is going
   to store (i+2)'th Fibonacci number*/
int fib[N];
 
// Stores values in fib and returns index of the largest
// fibonacci number smaller than n. 
int largestFiboLessOrEqual(int n)
{
    fib[0] = 1;  // Fib[0] stores 2nd Fibonacci No.
    fib[1] = 2;  // Fib[1] stores 3rd Fibonacci No.
 
    // Keep Generating remaining numbers while previously
    // generated number is smaller
    int i;
    for (i=2; fib[i-1]<=n; i++)
        fib[i] = fib[i-1] + fib[i-2];
 
    // Return index of the largest fibonacci number
    // smaller than or equal to n. Note that the above
    // loop stopped when fib[i-1] became larger.
    return (i-2);
}
 
/* Returns pointer to the char string which corresponds to
   code for n */
char* fibonacciEncoding(int n)
{
    int index = largestFiboLessOrEqual(n);
 
    //allocate memory for codeword
    char *codeword = (char*)malloc(sizeof(char)*(index+3));
 
    // index of the largest Fibonacci f <= n
    int i = index;
 
    while (n)
    {
        // Mark usage of Fibonacci f (1 bit)
        codeword[i] = '1';
 
        // Subtract f from n
        n = n - fib[i];
 
        // Move to Fibonacci just smaller than f
        i = i - 1;
 
        // Mark all Fibonacci > n as not used (0 bit), 
        // progress backwards
        while (i>=0 && fib[i]>n)
        {
            codeword[i] = '0';
            i = i - 1;
        }
    }
 
    //additional '1' bit
    codeword[index+1] = '1';
    codeword[index+2] = '\0';
 
    //return pointer to codeword
    return codeword;
}
 
/* driver function */
int main()
{
    int n = 143;
    printf("Fibonacci code word for %d is %s\n", n, fibonacciEncoding(n));
    return 0;
}


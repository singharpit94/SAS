// C++ program to find if a given number is fancy or not.
#include<bits/stdc++.h>
using namespace std;
 
bool isFancy(string& num)
{
    // To store mappings of fancy pair characters. For example
    // 6 is paired with 9 and 9 is paired with 6.
    map<char, char> fp;
    fp['0'] = '0';
    fp['1'] = '1';
    fp['6'] = '9';
    fp['8'] = '8';
    fp['9'] = '6';
 
    // Find number of digits in given number
    int n = num.length();
 
    // Traverse from both ends, and compare characters one by one
    int l = 0, r = n-1;
    while (l<=r)
    {
        // If current characters at both ends are not fancy pairs
        if (fp.find(num[l]) == fp.end() || fp[num[l]] != num[r])
            return false;
        l++;
        r--;
    }
    return true;
}
 
// Driver program
int main()
{
    string str = "9088806";
    isFancy(str)? cout << "Yes": cout << "No";
    return 0;
}

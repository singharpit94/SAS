#include<bits/stdc++.h>
using namespace std;
#define mod 1000000007

int main()
{
    long long int ans[1000001],t,n,i;
    ans[1]=1;ans[2]=2;
    for(i=3;i<=1000000;i++)
    {
        ans[i]=(ans[i-1]+ans[i-2]*((i-1)%mod))%mod;
    }
    scanf("%lld",&t);
    while(t--)
    {
        scanf("%lld",&n);
        printf("%lld\n",ans[n]);
    }
    return 0;
}

#include<bits/stdc++.h>
using namespace std;

#define ll long long int
int main()
{
    ll t,n,a[100005],ans,check;
    scanf("%lld",&t);
    while(t--)
    {
        ans=0;check=0;
        scanf("%lld",&n);
        for(ll i=0;i<n;i++)
            scanf("%lld",&a[i]);
        for(ll i=0;i<n;i++)
        {
            if(check==0)
            {
                check=1;
                continue;
            }
            if(a[i]<a[i-1])
            {
                ans=ans+(check*(check+1))/2;
                check=1;
            }
            else
                check++;

        }
        ans=ans+(check*(check+1))/2;
        printf("%lld\n",ans);
    }
    return 0;

}

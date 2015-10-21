#include<bits/stdc++.h>
using namespace std;

#define ll long long int

int main()
{
    ll t,n,w[1005],max=0,flag=0;
    char str1[1005],str2[1005];
    scanf("%lld",&t);
    while(t--)
    {
        scanf("%lld",&n);
        scanf("%s",str1);
        scanf("%s",str2);
        flag=0;
        for(ll i=0;i<n+1;i++)
            scanf("%lld",&w[i]);
        max=w[0];
        for(ll i=0;i<n;i++)
        {
            if(str1[i]==str2[i])
            {
                flag++;
            }
        }
        if(flag==n)
            max=w[n];
        else
        {
            for(ll i=1;i<=flag;i++)
                if(w[i]>max)
                    max=w[i];
        }
        printf("%lld\n",max);
    }
    return 0;
}

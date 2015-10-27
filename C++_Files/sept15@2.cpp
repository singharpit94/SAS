#include<bits/stdc++.h>
using namespace std;
#define ll long long int
bool compare(ll a,ll b)
{
    return a>b;
}
int main()
{
        ll t,st,en,co,n,ch[20005],m;
        scanf("%lld",&t);
        while(t--)
        {
            scanf("%lld %lld",&n,&m);
            for(ll i=0;i<m;i++)
                scanf("%lld",&ch[i]);
            sort(ch,ch+m,compare);
            st=0;en=m-1;co=0;
            for(ll i=0;i<m;i++)
            {
                if(ch[st]==n)
                    break;
                while(ch[en]==0)
                    en--;
                ch[en]--;
                ch[st+1]=ch[st]+ch[st+1]+1;
                st++;co++;
            }
            printf("%lld\n",co);
        }
        return 0;
}

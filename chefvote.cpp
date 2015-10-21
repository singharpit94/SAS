#include<bits/stdc++.h>
using namespace std;

struct v
{
    long long int index;
    long long int votes;
};

bool compare(v a,v b)
{
    if(a.votes>b.votes)
        return 1;
    else
        return 0;
}
int main()
{
    long long int t,n,flag,a[100],check[100],sum,co,p;
    scanf("%lld",&t);
    while(t--)
    {
        scanf("%lld",&n);
        v v1[n+4];
        sum=0;flag=0;
        for(int i=0;i<n;i++)
        {
            scanf("%lld",&v1[i].votes);
            v1[i].index=i;
            sum=sum+v1[i].votes;
            if(v1[i].votes>(n-1))
                flag=1;
        }
        if(sum==n && flag==0)
        {
            memset(check,0,sizeof(check));
            sort(v1,v1+n,compare);
            /*for(int i=0;i<n;i++)
            {
                printf("%lld %lld\n",v1[i].index,v1[i].votes);
            }*/
            p=1;
            for(int i=0;i<n;i++)
            {
                co=v1[i].votes;
                while(co--)

                 {
                     check[v1[p].index]=v1[i].index+1;
                     p++;
                     if(p==n)
                     p=0;

                }




            }
            for(int i=0;i<n;i++)
                printf("%lld ",check[i]);
            printf("\n");
        }
        else
            printf("-1\n");

    }
    return 0;

}

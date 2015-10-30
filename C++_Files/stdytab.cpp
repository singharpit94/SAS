#include<bits/stdc++.h>
using namespace std;
#define M 1000000000
 
 
void scanint(long long int &x)
{
    register int c = getchar_unlocked();
    x = 0;
    int neg = 0;
    for(;((c<48 || c>57) && c != '-');c =  getchar_unlocked());
    if(c=='-') {neg=1;c=getchar_unlocked();}
    for(;c>47 && c<58;c = getchar_unlocked()) {x = (x<<1) + (x<<3) + c - 48;}
    if(neg) x=-x;
}
 
long long int gcd(long long int a,long long int b)
{
    if(b==0)
        return a;
    else return gcd(b,a%b);
}
 
long long int fact[3000],cway[5000],dp[5000][5000];
 
int main()
{
    long long int i,j,t,m,n,temp,l,p,q,low;
    scanint(t);
    while(t--)
    {
        scanint(n);
        scanint(m);
        for(i=1;i<=m;i++)
        {
            fact[i]=m+i-1;
        }
        for(i=0;i<=m;i++)
            cway[i]=1;
        for(i=1;i<=m;i++)
        {
            if(i==1)
                cway[i]=fact[i];
            else
            {
                low=i;
                for(j=1;j<=i;j++)
                {
                    if(fact[j]==1)
                        continue;
                    p=gcd(low,fact[j]);
                    fact[j]=fact[j]/p;
                    low=low/p;
                    cway[i]=(cway[i]*(fact[j]))%M;
                }
 
            }
        }
        dp[0][0]=cway[0];
        for(i=1;i<=m;i++)
        {
            dp[0][i]=(dp[0][i-1]+cway[i])%M;
        }
        for(i=1;i<n;i++)
        {
            for(j=0;j<=m;j++)
            {
                dp[i][j]=(dp[i-1][j])*(cway[j]);
                if(j!=0)
                    dp[i][j]+=(dp[i][j-1]);
                dp[i][j]=dp[i][j]%M;
            }
        }
        printf("%lld\n",dp[n-1][m]);
 
    }
    return 0;
}

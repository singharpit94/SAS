#include<bits/stdc++.h>
#define ll long long int
using namespace std;


ll pw(ll a, ll b){
  ll r;
  if(b==0) return 1;
  r = pw(a,b/2);
  r = (r*r);
  if(b%2) r = (r*a);
  return r;
}
int main()
{
	long long int n,a[1000],i,j,k,m,t;
	for(i=0;i<=30;i++)
	{
		a[i]=pw(2,i);
	}
	cin>>t;
	while(t--)
	{
		cin>>n;
		
		if((n&(n-1))==0)
		{
		
	      printf("%lld\n",n);
    	}
    	else
    	{
    		  if(n==1)
    		  { j=1;
    		  	printf("%lld\n",j);
			  }
			  else{
			  
    		for(i=0;i<=30;i++)
		{
			if(n<a[i])break;
		}
		j=(n-a[i-1])*2;
		printf("%lld\n",j);
		}
	}
	}
	return 0;
	
}

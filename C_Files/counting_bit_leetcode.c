/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* countBits(int num, int* returnSize) {
   int *dp,n,i,k;
  *returnSize=num+1;
    dp=(int *)malloc((num+1)*sizeof(int));
    dp[0]=0;
    dp[1]=1;
    for(i=2;i<=num;i++)
		{
			if((i & (i-1))==0)
			{
				n=i;
				dp[i]=1;
			}
			else
			{
				dp[i]=dp[n]+dp[i-n];
			}
		}
		return dp;
    
}

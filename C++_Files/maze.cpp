#include <stdio.h>
#include <iostream>
#include<vector>
 
using namespace std;
 
struct node
{
	int x, y;
};
 
/*
maze : it is simple matrix to store the maze.(m * n)
visited : it is a matrix to store information about the branch the DFS is currently in.
*/
 
int m, n;
int maze[100][100];

void printpath(	vector <struct node> st)
{	
      int l=st.size();
      cout<<"{";
      for(int i=0;i<l;i++)
      if(i==l-1)
      cout<<"("<<st[i].x<<","<<st[i].y<<")"<<"}";
		else
      cout<<"("<<st[i].x<<","<<st[i].y<<")"<<",";
		printf("\n");
}

bool recFun(int x1, int y1 ,vector <struct node> st,int visited[100][100])
{
	struct node p;
	
		if(x1 == m - 1 && y1 == n - 1)
		{
			p.x = x1;
			p.y = y1;
			st.push_back(p);
		//	cout<<"Yes"<<endl;
			printpath(st);
		
			return true;		
		}	
		else
		{
			p.x = x1;
			p.y = y1;
			st.push_back(p);
			visited[x1][y1] = 1;
		
			//cout<<p.x<<" "<<p.y<<"\n";
			if(y1 + 1 < n && !visited[x1][y1+1] && maze[x1][y1 + 1])
				 recFun(x1, y1 + 1,st,visited);	
			if(x1 + 1 < m && !visited[x1+1][y1] && maze[x1 + 1][y1])
				recFun(x1 + 1, y1,st,visited);
			if((y1 - 1) >= 0  && !visited[x1][y1-1] && maze[x1][y1- 1])
				 recFun(x1, y1 - 1,st,visited);
			if((x1 - 1) >= 0 && !visited[x1-1][y1] && maze[x1 - 1][y1])
				recFun(x1 - 1, y1,st,visited);

			//backtrack
			visited[x1][y1]=0;
		}
		
		return false;
}

void fun()
 {   
 	vector <struct node> st;
 	int visited[100][100];
 	for(int i = 0 ; i < 100 ; i++)
		for(int j = 0 ; j < 100 ; j++)
			visited[i][j] = 0;
			
  	recFun(0,0,st,visited);
 }
 
int main()
{
	int i, j;
 	
	scanf("%d %d", &m, &n);
	for(i = 0 ; i < m ; i++)
		for(j = 0 ; j < n ; j++)
			scanf("%d", &maze[i][j]);
	
	fun();	
	return 0;
}

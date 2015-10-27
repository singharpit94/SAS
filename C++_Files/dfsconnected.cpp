#include<bits/stdc++.h>
using namespace std;

class Graph
{
    int V;
    list<int> *adj;
    long long int DFSUtil(int v, bool visited[],long long int bananas[],long long int sum);
public:
    long long int maxx;
    Graph(int V);
    void addEdge(int v, int w);
    void DFS();
};

Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[V];
}

void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w);
    adj[w].push_back(v);
}

long long int Graph::DFSUtil(int v, bool visited[], long long int bananas[], long long int sum)
{
    visited[v] = true;
    sum=sum+bananas[v];
    list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
        if (!visited[*i])
           sum=DFSUtil(*i, visited,bananas,sum);
    return sum;
}


void Graph::DFS()
{
    bool *visited = new bool[V];
    long long int*bananas= new long long int[V];

    for(int i=0;i<V;i++)
        scanf("%lld",&bananas[i]);

    for (int i = 0; i < V; i++)
        visited[i] = false;

    long long int sum=0;
    maxx=0;
    for(int i=0;i<V;i++)
    {
        if(!visited[i])
        {
            sum=0;
            sum=DFSUtil(i, visited,bananas,sum);
            if(sum>maxx)
                maxx=sum;
        }

    }
}

int main()
{
    long long int t,n,m,u,v;
    scanf("%lld",&t);
    while(t--)
    {
        scanf("%lld %lld",&n,&m);
        Graph g(n);
        for(int i=0;i<m;i++)
        {
            scanf("%lld %lld",&u,&v);
            u--;v--;
            g.addEdge(u,v);
        }
        g.DFS();
        printf("%lld\n",g.maxx);
    }
    return 0;
}

//Koustav Chowdhury 17CS10059

#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
using namespace std;

typedef struct _node {
        int vno;             /* vertex Id */
        struct _node *next;  /* Pointer to the next node in the adjacency list */
} node;
typedef struct _vertex {
        node *adj; 
} vertex;

typedef vertex *graph;

int mini(int a, int b)
{
        return (a<b) ? a: b;
}

void dfsvisit(graph g, int v, int x, int vis[])
{
        vis[v]=1;
        
        node *t=g[v].adj;
        
        while (t!=NULL)
        {
                if (t->vno==x)
                {
                        t=t->next;
                        continue;
                }
                
                int u=t->vno;
                
                if (!vis[u])
                {
                        dfsvisit(g,u,x,vis);
                }
                t=t->next;
        }
        
}

int dfscomp(graph g, int rem , int n)
{
        int *vis=new int[n];
        for (int i=0;i<n;i++)
                vis[i]=0;
        
        int cnt=0;
        for (int i=0;i<n;i++)
        {
                if (i==rem)
                        continue;
                if (!vis[i])
                {
                        dfsvisit(g,i,rem,vis);
                        ++cnt;
                }
        }
        delete []vis;
        return cnt;
}

void findCritical (graph g, int n)
{
        cout<<"Critical junctions using the simple algorithm\n";
        for (int i=0;i<n;i++)
        {
                int comp=dfscomp(g,i,n);
                //cout<<comp<<"$\n";
                if (comp>1)
                        cout<<"Vertex "<<i<<": "<<comp<<" components\n";
        }
}

void dfs(graph g, int dis[],int low[], int vis[],int time, int v, int p ,int n)
{
        vis[v]=1;
        dis[v]=low[v]=time++;
        
        node *t=g[v].adj;
        int child=0;
        
        //cout<<"Edge :"<<v<<" "<<p<<"\n";
        while (t!=NULL)
        {
                int u=t->vno;
                
                if (u==p){ t=t->next;      continue;}
                
                if (vis[u])
                        low[v]=mini(low[v],dis[u]);
                
                
                if (!vis[u])
                {
                        dfs(g,dis,low,vis,time,u,v,n);
                        
                        low[v]=mini(low[v],low[u]);
                
                
                if (low[u]>=dis[v] && p!=-1)
                {
                        cout<<"Vertex "<<v<<" is a critical point\n";
                }
                        ++child;
                }
                
                t=t->next;
                
                
        }
        
        if (p==-1 && child >1)
             cout<<"Vertex "<<v<<" is a critical point\n";   
        
        
}


void findCriticalfast(graph g, int n)
{
        int *dis=new int[n];
        int *low=new int[n];
        int *vis=new int[n];
        for (int i=0;i<n;i++)
                vis[i]=0;
        int time=0;
        dfs(g,dis,low,vis,time,0,-1,n);
}

int main()
{
        int n,e,d,x;
        cin>>n>>e;
        
        vertex *g=new vertex[n];
        
        for (int i=0;i<n;i++)
        {
                cout<<"Degree of vertex "<<i<<":";
                cin>>d;
                node *t=new node;
                cout<<"Neighbours of "<<i<<" : ";
                cin>>x;
                t->vno=x;
                t->next=NULL;
                g[i].adj=t;
                for (int j=1;j<d;j++)
                {
                        cin>>x;
                        t->next=new node;
                        t=t->next;
                        t->vno=x;
                        t->next=NULL;
                }
        }
        
        cout<<"Adjacency list of the graph:\n";
        
        for (int i=0;i<n;i++)
        {
                cout<<"Vertex "<<i<<" : ";
                node *t=g[i].adj;
                
                while (t->next!=NULL)
                {
                        cout<<t->vno<<" ";
                        t=t->next;
                }
                
                cout<<t->vno<<"\n";
        }
        
        findCritical (g,n);
        
        findCriticalfast(g,n);
        

        
}

//Koustav Chowdhury 17CS10059

#include <iostream>
#include <stdlib.h>
using namespace std;

#define INF 1000000007

typedef int **graph;

struct node{
        int data;
        node *next;
};

struct edges
{
        int u,v,w;
};

typedef struct {
struct node *head, *tail ;
} QUEUE ;
void init(QUEUE **qP);//initializes the front and rear pointers
int isempty(QUEUE *qP);//prints 1 if the queue is empty, else 0
void enqueue(QUEUE **qP, int data);
int dequeue(QUEUE **qP);


void init(QUEUE **q)
{
    (*q)=new QUEUE();
    (*q)->head=(*q)->tail=NULL;
}

int isempty(QUEUE *q)
{
    if (q->head==NULL)
        return 1;
    return 0;
}


void enqueue(QUEUE **q, int data)
{
    node *t=new node();
    t->data=data;
    t->next=NULL;
    if ((*q)->head==NULL)
        (*q)->head=(*q)->tail=t;
    else
    {
        (*q)->tail->next=t;
        (*q)->tail=t;
    }
}

int dequeue(QUEUE **q)
{
    //Assumming Queue is never empty
    node *t=(*q)->head;
    (*q)->head=(*q)->head->next;
    if ((*q)->head==NULL)
        (*q)->tail=NULL;
    int x=t->data;
    free(t);
    return x;
}

int isconnected(graph g, int n)
{
        QUEUE *q;
        init(&q);
        
        int visited[n];
        
        for (int i=0;i<n;i++)
                visited[i]=0;
       
        enqueue(&q,0);
        
        while (!isempty(q))
        {
                int v=dequeue(&q);
                if (visited[v]) continue;
                visited[v]=1;
                
                for (int i=0;i<n;i++)
                {
                        if (visited[i])continue;
                        if (g[v][i]!=0)
                        {
                                enqueue(&q,i);
                        }
                }
        }
        
        int ans=1;
        
        for (int i=0;i<n;i++)
                if (!visited[i])
                {
                        ans=0;break;
                } 
        //delete []visited;
        
        return ans;
}

void combine(edges A[],int l,int m,int r)
{
        int s1=m-l+1;
        int s2=r-m;
        
        edges *P=new edges[s1];//first half
        edges *Q=new edges[s2];//second half
        
        for (int i=l;i<=m;i++)
                P[i-l]=A[i];
        
        for (int i=m+1;i<=r;i++)
                Q[i-m-1]=A[i];
                
        edges *C=new edges[s1+s2];
        
        int i=0,j=0,k=0;
        
        while (i<s1 && j<s2)
        {
                if (P[i].w>Q[j].w)
                        C[k++]=P[i++];
                else
                        C[k++]=Q[j++];
        }
        
        while (i<s1)
        {
                C[k++]=P[i++];
        }
        
        while (j<s2)
        {
                C[k++]=Q[j++];
        }
        
        for (i=l;i<=r;i++)
                A[i]=C[i-l];       
        
        delete []P;
        delete []Q;
        delete []C;
}

void superbsort(edges A[],int l,int r)
{
        if (l<r)
        {
                int m=l+(r-l)/2;
                superbsort(A,l,m);
                superbsort(A,m+1,r);
                combine(A,l,m,r);
        }
}

void superbSorting(edges A[],int sizeOfA)
{
        superbsort(A,0,sizeOfA-1);
}

void findMST(graph g, int n)
{
        
        int c=0;
        for (int i=0;i<n;i++)
                for (int j=0;j<i;j++)
                        if (g[i][j]!=0)
                                c++;
        //cout<<c<<":D\n";
        int ne=c;
        edges ed[c];
        c=0;
        for (int i=0;i<n;i++)
                for (int j=0;j<i;j++)
                        if (g[i][j]!=0)
                        {
                                ed[c].w=g[i][j];
                                ed[c].u=i;
                                ed[c].v=j;
                                c++;
                        }
        
        superbSorting(ed,ne);
        
        //for (int i=0;i<ne;i++)
        //        cout<<ed[i].w<<"->"<<ed[i].u<<","<<ed[i].v<<"\n";
        //cout<<"\n";
        for (int i=0;i<ne;i++)
        {
                //searching the required weight if it's not deleted
                int x=ed[i].u,y=ed[i].v;
                g[x][y]=0,g[y][x]=0;//deleting the edges
                if (isconnected(g,n))continue;
                g[x][y]=g[y][x]=ed[i].w;//else restore the edge;
        }
        
        /*c=0;
        for (int i=0;i<n;i++)
                for (int j=0;j<i;j++)
                        if (g[i][j]!=0)
                                c++;
        cout<<c<<":D\n";*/
        
        cout<<"The neighbors of each node of MST and corresponding weights\n";
        
        for (int i=0;i<n;i++)
        {
                cout<<"Vertex "<<i<<" : ";
                for (int j=0;j<n;j++)
                        if (g[i][j]!=0)
                                cout<<j<<" "<<g[i][j]<<" ";
                cout<<"\n";                        
                      
        }
        
        
}

int main()
{
        int n,m,deg,u,v,w;
        cout<<"Enter the number of nodes and edges:\n";
        cin>>n>>m;
        
        graph A=new int*[n];
        for (int i=0;i<n;i++)
                A[i]=new int[n];
        
        //graph A;
        
        for (int i=0;i<n;i++)
                for (int j=0;j<n;j++)
                        A[i][j]=0;
        
        for (int i=0;i<n;i++)
        {
                cout<<"Enter the degree of the vertex "<<i<<" : ";
                cin>>deg;
                
                cout<<"The neighbours of the vertex "<<i<<" : ";
                for (int j=0;j<deg;j++)
                        cin>>v>>w, A[i][v]=w;
                
        }
        
        cout<<"The neighbors of each node in the input graph and corresponding weights\n";
        
        for (int i=0;i<n;i++)
        {
                cout<<"Vertex "<<i<<" : ";
                for (int j=0;j<n;j++)
                        if (A[i][j]!=0)
                                cout<<j<<" "<<A[i][j]<<" ";
                cout<<"\n";                        
                      
        }
        
        /*cout<<"Adjacency matrix A : \n";
        for (int i=0;i<n;i++)
        {
                for (int j=0;j<n;j++)
                        cout<<A[i][j]<<" ";
                cout<<"\n";
        }
        */
        
        /*
        if (isconnected(A,n))
                cout<<"Connected!!!\n";
        else
                cout<<"Not Connected :( \n";
        */        
                
        findMST(A,n);
}

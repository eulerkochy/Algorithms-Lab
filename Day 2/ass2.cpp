#include <iostream>
#include <stdlib.h>
using namespace std;
typedef struct rm {
        int x;
        int y;
} room;
struct node {
        room data;
        node *next;
};
typedef struct node node, *list;
list maze[20][20];
void createmaze(list maze[][20], int n, int H[][20], int V[][21]);

typedef struct {
struct node *head ;
} STACK ;
void init(STACK **s);//initializes the head pointer
int isempty(STACK s);//returns 1 if the stack is empty, 0 otherwise
void push(STACK **s, room data);
void pop(STACK **s);
int strategy1(list maze[][20], int n, room start, room end);

typedef struct {
struct node *head, *tail ;
} QUEUE ;
void init(QUEUE **qP);//initializes the front and rear pointers
int isempty(QUEUE *qP);//prints 1 if the queue is empty, else 0
void enqueue(QUEUE **qP, room data);
room dequeue(QUEUE **qP);
int strategy2(list maze[][20], int n, room start, room end);

void init(STACK **s)
{
        (*s)=new STACK();
        (*s)->head=NULL;
}

int isempty(STACK *s)
{
        if ((s->head)==NULL)
                return 1;
         return 0;
}

void push(STACK **s, room data)
{
        node *t=new node();
        t->data=data;
        t->next=(*s)->head;
        (*s)->head=t;
}

void pop(STACK **s)
{
    //Assummming stack is not empty
        node *t=(*s)->head;
        (*s)->head=(*s)->head->next;
        free(t);
}

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


void enqueue(QUEUE **q, room data)
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

room dequeue(QUEUE **q)
{
    //Assumming Queue is never empty
    node *t=(*q)->head;
    (*q)->head=(*q)->head->next;
    if ((*q)->head==NULL)
        (*q)->tail=NULL;
    room x=t->data;
    free(t);
    return x;
}

void printmaze(int H[][20],int V[][21],int n)
{
        for (int i=0;i<=n;i++)
        {
               
                for (int j=0;j<n;j++)
                {
                        if (H[i][j]==1)
                                cout<<"+   ";
                        else
                                cout<<"+---";       
                }
                cout<<"+\n";
                if (i!=n)
                {
                        for (int j=0;j<=n;j++)
                        {
                           if (V[i][j]==1)
                                cout<<"    ";
                                else
                                cout<<"|   ";        
                        }
                }
                cout<<"\n";
        }
}

void createmaze(list maze[][20], int n, int H[][20], int V[][21])
{
    for (int i=0;i<n;i++)
    {
            for (int j=0;j<n;j++)
            {
                    maze[i][j]=NULL;
                    }
             }

    for (int i=0;i<n;i++)
    {
            for (int j=0;j<n;j++)
            {
                  if (H[i][j])
                  {
                    node *t=new node();
                    (t->data).x=i-1;
                    (t->data).y=j;
                    t->next=NULL;
                    if (maze[i][j]==NULL)
                    maze[i][j]=t;
                    else
                    {
                            t->next=maze[i][j];
                            maze[i][j]=t;
                    }   
                  } 
                  if (H[i+1][j])
                  {
                    node *t=new node();
                    (t->data).x=i+1;
                    (t->data).y=j;
                    t->next=NULL;
                    if (maze[i][j]==NULL)
                    maze[i][j]=t;
                    else
                    {
                            t->next=maze[i][j];
                            maze[i][j]=t;
                    }
                  }
                  if (V[i][j])
                  {
                    node *t=new node();
                    (t->data).x=i;
                    (t->data).y=j-1;
                    t->next=NULL;
                    if (maze[i][j]==NULL)
                    maze[i][j]=t;
                    else
                    {
                            t->next=maze[i][j];
                            maze[i][j]=t;
                    }
                  }
                  if (V[i][j+1])
                  {
                    node *t=new node();
                    (t->data).x=i;
                    (t->data).y=j+1;
                    t->next=NULL;
                    if (maze[i][j]==NULL)
                    maze[i][j]=t;
                    else
                    {
                            t->next=maze[i][j];
                            maze[i][j]=t;
                    }
                  }                  
            }
    }


    for(int i=0;i<n;i++)
    {
            for (int j=0;j<n;j++)
            {
                    cout<<"("<<i<<","<<j<<")::-->";
                    
                    node *tmp=maze[i][j];
                    if (tmp!=NULL)
                    {
                    while (tmp->next!=NULL)
                    {
                            cout<<"("<<(tmp->data).x<<","<<(tmp->data).y<<")-->";
                            tmp=tmp->next;
                    }
                    cout<<"("<<(tmp->data).x<<","<<(tmp->data).y<<")\n";
                    }
                    else
                            cout<<endl;
            }
    }

}

int strategy1(list maze[][20], int n, room start, room end)
{
        STACK *s;
        init(&s);
        
        int visited[n][n];
        for (int i=0;i<n;i++)
        {
                for (int j=0;j<n;j++)
                {
                        visited[i][j]=0;
                }
        }
        
        push(&s,start);
        int found=0;
        
        while (!isempty(s) && !found)
        {
            room r=s->head->data;

            //cout<<"("<<(r).x<<","<<(r).y<<")\n";

            if (r.x==end.x && r.y==end.y)
            {
              found=1;
              continue;
            }
            pop(&s);
            node *q=maze[r.x][r.y];
            visited[r.x][r.y]=1;
            

            while (q!=NULL)
            {
              room tm=q->data;
              if (!visited[tm.x][tm.y])
                {
                    push(&s,tm);
                }  
              q=q->next;
            }


        }

        if (!isempty(s))
            free(s);
        

        return (found);   
}

int strategy2(list maze[][20], int n, room start, room end)
{
    QUEUE *q;
    init(&q);

    int visited[n][n];
    for (int i=0;i<n;i++)
    {
            for (int j=0;j<n;j++)
            {
                    visited[i][j]=0;
            }
    }
    
    enqueue(&q,start);
    int found=0;

    while (!isempty(q) && !found)
    {
        room r=dequeue(&q);
        if (r.x==end.x && r.y==end.y)
            {
              found=1;
              continue;
            }

        node *p=maze[r.x][r.y];
        visited[r.x][r.y]=1;
        while (p!=NULL)
        {
          room tm=p->data;
          if (!visited[tm.x][tm.y])
            {
                enqueue(&q,tm);
                //visited[tm.x][tm.y]=1;
            }  
          p=p->next;
        }
    }

    if (!isempty(q))
        free(q);

    return found;

}


int main()
{
        int n;
        //cout<<"Enter the value of n\n";
        cin>>n;
        int H[21][20],V[20][21];
        //cout<<"Enter the horizontal doors H\n";
        for (int i=0;i<=n;i++)
        {
                for (int j=0;j<n;j++)
                        cin>>H[i][j];
        }
        //cout<<"Enter the vertical doors V\n";
        for (int i=0;i<n;i++)
        {
                for (int j=0;j<=n;j++)
                        cin>>V[i][j];
        }
        
        room start,end;
        cin>>start.x>>start.y;
        cin>>end.x>>end.y;
        
        cout<<"The maze looks like:\n\n";
        printmaze(H,V,n);
        cout<<"\n\n";

        cout<<"The linked list representation looks like:\n\n";
        createmaze(maze,n,H,V);
        cout<<"\n\n";

        cout<<"Using Strategy 1 ...\n\n";
        if (strategy1(maze,n,start,end))
          cout<<"A path is found using strategy 1 from ("<<start.x<<","<<start.y<<") to ("<<end.x<<","<<end.y<<")\n";
        else
          cout<<"No path is found using strategy 1 from ("<<start.x<<","<<start.y<<") to ("<<end.x<<","<<end.y<<")\n";
        cout<<"\n\n";

        cout<<"Using Strategy 2 ...\n\n";
        if (strategy2(maze,n,start,end))
          cout<<"A path is found using strategy 2 from ("<<start.x<<","<<start.y<<") to ("<<end.x<<","<<end.y<<")\n";
        else
          cout<<"No path is found using strategy 2 from ("<<start.x<<","<<start.y<<") to ("<<end.x<<","<<end.y<<")\n";
        cout<<"\n\n";

      return 0;
        
}
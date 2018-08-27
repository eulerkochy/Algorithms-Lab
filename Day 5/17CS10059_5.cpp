//Koustav Chowdhury 17CS100059
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
using namespace std;


typedef struct _wordR { 
  char word[100]; 
  double x, y; 
} wordR; 
typedef struct _node{ 
  wordR w; 
  struct _node *next; 
} node, *nodePointer; 
typedef nodePointer **hashTable;    

void insertH(hashTable T, int m, wordR a)
{
        int hx=floor(m*a.x);
        int hy=floor(m*a.y);
        node *tmp=new node();
        
        tmp->w=a;
        tmp->next=NULL;
        
        if (T[hx][hy]==NULL)
        {
                T[hx][hy]=tmp;
        }
        else
        {
                tmp->next=T[hx][hy];
                T[hx][hy]=tmp;
        }
}

void printH(hashTable T, int m)
{
        for (int i=0;i<m;i++)
        {
                for (int j=0;j<m;j++)
                {
                        nodePointer t=T[i][j];
                        cout<<"["<<i<<","<<j<<"]::(";
                        while (t!=NULL)
                        {
                                cout<<(t->w).word<<" ";
                                t=t->next;
                        }
                        cout<<")\n";
                }
        }
}

bool isvalid(int i,int j,int m)
{
        if (i<m && i>=0 && j>=0 && j<m)
                return true;
        return false;
}

double calc(wordR a, wordR b)
{
        return sqrt(pow((a.x-b.x),2)+pow((a.y-b.y),2));
}

void findNN(hashTable H,int m,wordR w)
{
        int i=floor(m*w.x);
        int j=floor(m*w.y);
        int dist=9999;
        nodePointer r=NULL;//THE WORD
        if (H[i][j]!=NULL)
        {
                nodePointer t=H[i][j];
                
                while (t!=NULL)
                {       
                        if (strcmp((t->w).word,w.word)==0)
                                t=t->next;
                        else
                        {
                                double d1=calc(t->w,w);
                                if (d1<dist && d1>0)
                                {
                                           dist=d1;  
                                           r=t;
                                }   
                                t=t->next;    
                        }    
                }
                
                if (dist==9999)
                        goto squ;
                else
                {
                         //the circle wala case
                         //goto circle;              
                }
                
                
                
        }
        else
        {
                //Adjacent squares case
                squ:
                int k=1;
                bool found=false;
                nodePointer *X=new nodePointer[8];//array of found pointers
                int x=0;
                //checking condition
                while (!found)
                {
                        if (isvalid(i-k,j-k,m))
                                if (H[i-k][j-k]!=NULL)
                                {
                                        found=true;
                                        X[x++]=H[i-k][j-k];     
                                }
                        if (isvalid(i-k,j,m))
                                if (H[i-k][j]!=NULL)
                                {
                                        found=true;
                                        X[x++]=H[i-k][j];     
                                }
                        if (isvalid(i-k,j+k,m))
                                if (H[i-k][j+k]!=NULL)
                                {
                                        found=true;
                                        X[x++]=H[i-k][j+k];     
                                }
                         if (isvalid(i,j-k,m))
                                if (H[i][j-k]!=NULL)
                                {
                                        found=true;
                                        X[x++]=H[i][j-k];     
                                }
                         if (isvalid(i,j+k,m))
                                if (H[i][j+k]!=NULL)
                                {
                                        found=true;
                                        X[x++]=H[i][j+k];     
                                }
                         if (isvalid(i+k,j-k,m))
                                if (H[i+k][j-k]!=NULL)
                                {
                                        found=true;
                                        X[x++]=H[i+k][j-k];     
                                }
                        if (isvalid(i+k,j,m))
                                if (H[i+k][j]!=NULL)
                                {
                                        found=true;
                                        X[x++]=H[i+k][j];     
                                }
                        if (isvalid(i+k,j+k,m))
                                if (H[i+k][j+k]!=NULL)
                                {
                                        found=true;
                                        X[x++]=H[i+k][j+k];     
                                }
                       k++;      
                }
                for (int p=0;p<x;p++)
                {
                        nodePointer g=X[p];
                        while (g!=NULL)
                        {
                        
                                if (strcmp((g->w).word,w.word)==0)
                                {
                                        g=g->next;
                                        continue;
                                }
                                double d1=calc(g->w,w);
                                if (d1<dist)
                                {
                                           dist=d1;  
                                           r=g;
                                }
                                g=g->next;     
                        }      
                }
                
                cout<<dist<<" :: The word is ("<<(r->w).word<<" , "<<(r->w).x<<" , "<<(r->w).y<<" )\n"; 
                
                //the circle wala case
                /*circle:
                nodePointer *Y=new nodePointer[24];
                k=1;
                i=floor(m*(r-))
                */    
                
                 
                
        }
        
        
}

int main()
{
        freopen("input.txt","r",stdin);
        freopen("output.txt","w",stdout);
        int n;
        char tempW[100];
        double tempX,tempY;
        cin>>n;
        
        int m=ceil(sqrt(n));
        int    i, j; 
        hashTable H; 

        H = (nodePointer **)malloc(m * sizeof(nodePointer *)); 
        for (i=0; i<m; i++) { 
                H[i] = (nodePointer *)malloc(m * sizeof(nodePointer)); 
                for (j=0; j<m; ++j) H[i][j] = NULL; 
        }
        
        cout<<n<<"\n"; 
 
        for (i=0; i<n; i++) { 
        cin>>tempW>>tempX>>tempY;
        wordR a;
        strcpy(a.word,tempW);
        a.x=tempX;
        a.y=tempY;
        insertH(H,m,a);
        //fprintf(outf, “%s    %lf  %lf\n”, tempW, tempX, tempY); 
        }
        cout<<"Finished inserting the elements\n";
        printH(H,m);
        
        cout<<"Enter the number of words to be searched :: ";
        int s;
        cin>>s;
        cout<<s<<"\n\n";
        
        for (i=0;i<s;i++)
        {
                cin>>tempW>>tempX>>tempY;
                wordR a;
                strcpy(a.word,tempW);
                a.x=tempX;
                a.y=tempY;
                findNN(H,m,a);
        }
        
        
        
        
}

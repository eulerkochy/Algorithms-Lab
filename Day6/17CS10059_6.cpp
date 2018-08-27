// Koustav Chowdhury 17CS10059

#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
using namespace std;

void combine(int A[],int l,int m,int r)
{
        int s1=m-l+1;
        int s2=r-m;
        
        int *P=new int[s1];//first half
        int *Q=new int[s2];//second half
        
        for (int i=l;i<=m;i++)
                P[i-l]=A[i];
        
        for (int i=m+1;i<=r;i++)
                Q[i-m-1]=A[i];
                
        int *C=new int[s1+s2];
        
        int i=0,j=0,k=0;
        
        while (i<s1 && j<s2)
        {
                if (P[i]<Q[j])
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

void superbsort(int A[],int l,int r)
{
        if (l<r)
        {
                int m=l+(r-l)/2;
                superbsort(A,l,m);
                superbsort(A,m+1,r);
                combine(A,l,m,r);
        }
}

void superbSorting(int A[],int sizeOfA)
{
        superbsort(A,0,sizeOfA-1);
}

int compare1(int X[],int n,int x,int y) //n is the sizeOfX
{
        int id_x,id_y;//index of x and y
        
        for (int i=0;i<n;i++)
        {
                if (X[i]==x)
                        id_x=i;
                if (X[i]==y)
                        id_y=i;
        }
        
        if (id_x<id_y)
                return 1;
        else
                return -1;
}


void combine1(int A[],int l,int m,int r,int B[],int n)
{
        int s1=m-l+1;
        int s2=r-m;
        
        int *P=new int[s1];//first half
        int *Q=new int[s2];//second half
        
        for (int i=l;i<=m;i++)
                P[i-l]=A[i];
        
        for (int i=m+1;i<=r;i++)
                Q[i-m-1]=A[i];
                
        int *C=new int[s1+s2];
        
        int i=0,j=0,k=0;
        
        while (i<s1 && j<s2)
        {
                if (compare1(B,n,P[i],Q[j])==1)
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

void superbsort1(int A[],int l,int r,int B[],int n)
{
        if (l<r)
        {
                int m=l+(r-l)/2;
                superbsort1(A,l,m,B,n);
                superbsort1(A,m+1,r,B,n);
                combine1(A,l,m,r,B,n);
        }
}

void superbSorting1(int A[],int sizeOfA,int B[],int sizeOfB)
{
        superbsort1(A,0,sizeOfA-1,B,sizeOfB);
}

void process(int B[],int n,int D[])
{
        for (int i=0;i<n;i++)
                D[B[i]]=i;
}

void combine2(int A[],int l,int m,int r,int B[],int n,int D[])
{
        process(B,n,D);
        int s1=m-l+1;
        int s2=r-m;
        
        int *P=new int[s1];//first half
        int *Q=new int[s2];//second half
        
        for (int i=l;i<=m;i++)
                P[i-l]=A[i];
        
        for (int i=m+1;i<=r;i++)
                Q[i-m-1]=A[i];
                
        int *C=new int[s1+s2];
        
        int i=0,j=0,k=0;
        
        while (i<s1 && j<s2)
        {
                if (D[P[i]]<D[Q[j]])
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

void superbsort2(int A[],int l,int r,int B[],int n,int D[])
{
        if (l<r)
        {
                int m=l+(r-l)/2;
                superbsort2(A,l,m,B,n,D);
                superbsort2(A,m+1,r,B,n,D);
                combine2(A,l,m,r,B,n,D);
        }
}

void superbSorting2(int A[],int sizeOfA,int B[],int sizeOfB)
{
        int *D=new int[10*sizeOfB+1];//elements of B to be in range 0..10*sizeOfB
        for (int i=0;i<=10*sizeOfB;i++)
                D[i]=0;
        superbsort2(A,0,sizeOfA-1,B,sizeOfB,D);
        delete []D;
}

int main()
{
        int n;
        cout<<"Enter the size of A :: ";
        cin>>n;
        int A[n];
        cout<<"Enter the array A :: ";
        for (int i=0;i<n;i++)
                cin>>A[i];
                
        superbSorting(A,n);
        
        cout<<"The sorted array A :: ";
        for (int i=0;i<n;i++)
                cout<<A[i]<<" ";
        cout<<"\n";
        
        cout<<"Enter the array A :: ";
        for (int i=0;i<n;i++)
                cin>>A[i];
        
        int m;
        cout<<"Enter the size of B :: ";
        cin>>m;
        int *B=new int [m];
        cout<<"Enter the array B :: ";
        for (int i=0;i<m;i++)
                cin>>B[i];
                
        superbSorting1(A,n,B,m);
        
        cout<<"A after rearranging :: ";
        for (int i=0;i<n;i++)
                cout<<A[i]<<" ";
        cout<<"\n";
        
        delete []B;
        
        cout<<"Enter the array A :: ";
        for (int i=0;i<n;i++)
                cin>>A[i];
        
        cout<<"Enter the size of B :: ";
        cin>>m;
        B=new int [m];
        cout<<"Enter the array B :: ";
        for (int i=0;i<m;i++)
                cin>>B[i];
        
        superbSorting2(A,n,B,m);
        cout<<"A after rearranging :: ";
        for (int i=0;i<n;i++)
                cout<<A[i]<<" ";
        cout<<"\n";
        
        
                
}


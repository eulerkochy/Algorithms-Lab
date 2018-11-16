//Koustav Chowdhury 17CS10059

#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
using namespace std;

typedef struct _rwd {
        int st;//start_time
        int len;//service_time
} reqWD;

typedef struct _rsd {
        int st;//service_time
        int tt;//target_time
} reqSD;

void combine(reqWD A[],int l,int m,int r,int jid[])
{
        int s1=m-l+1;
        int s2=r-m;
        
        reqWD *P=new reqWD[s1];//first half
        int *j1=new int[s1];
        reqWD *Q=new reqWD[s2];//second half
        int *j2=new int[s2];
        
        for (int i=l;i<=m;i++)
        {
                P[i-l]=A[i];
                j1[i-l]=jid[i];
        }
        
        for (int i=m+1;i<=r;i++)
        {
                Q[i-m-1]=A[i];
                j2[i-m-1]=jid[i];
        }
                
        reqWD *C=new reqWD[s1+s2];
        int *j3=new int[s1+s2];
        
        int i=0,j=0,k=0;
        
        while (i<s1 && j<s2)
        {
                if (P[i].st+P[i].len<Q[j].st+Q[j].len)
                {
                        C[k]=P[i];
                        j3[k++]=j1[i++];
                 }
                else
                {
                        j3[k]=j2[j];
                        C[k++]=Q[j++];
                }
        }
        
        while (i<s1)
        {
                j3[k]=j1[i];
                C[k++]=P[i++];
                
        }
        
        while (j<s2)
        {
                j3[k]=j2[j];
                C[k++]=Q[j++];
        }
        
        for (i=l;i<=r;i++)
        {
                A[i]=C[i-l];
                jid[i]=j3[i-l];
        }       
        
        delete []P;
        delete []Q;
        delete []C;
        delete []j1;
        delete []j2;
        delete []j3;
}

void superbsort(reqWD A[],int l,int r,int jid[])
{
        if (l<r)
        {
                int m=l+(r-l)/2;
                superbsort(A,l,m,jid);
                superbsort(A,m+1,r,jid);
                combine(A,l,m,r,jid);
        }
}

void superbSorting(reqWD A[],int sizeOfA,int jid[])
{
        superbsort(A,0,sizeOfA-1,jid);
}

void combine(reqSD A[],int l,int m,int r,int jid[])
{
        int s1=m-l+1;
        int s2=r-m;
        
        reqSD *P=new reqSD[s1];//first half
        int *j1=new int[s1];
        reqSD *Q=new reqSD[s2];//second half
        int *j2=new int[s2];
        
        for (int i=l;i<=m;i++)
        {
                P[i-l]=A[i];
                j1[i-l]=jid[i];
        }
        
        for (int i=m+1;i<=r;i++)
        {
                Q[i-m-1]=A[i];
                j2[i-m-1]=jid[i];
        }
                
        reqSD *C=new reqSD[s1+s2];
        int *j3=new int[s1+s2];
        
        int i=0,j=0,k=0;
        
        while (i<s1 && j<s2)
        {
                if (P[i].tt<Q[j].tt)
                {
                        C[k]=P[i];
                        j3[k++]=j1[i++];
                 }
                else
                {
                        j3[k]=j2[j];
                        C[k++]=Q[j++];
                }
        }
        
        while (i<s1)
        {
                j3[k]=j1[i];
                C[k++]=P[i++];
                
        }
        
        while (j<s2)
        {
                j3[k]=j2[j];
                C[k++]=Q[j++];
        }
        
        for (i=l;i<=r;i++)
        {
                A[i]=C[i-l];
                jid[i]=j3[i-l];
        }       
        
        delete []P;
        delete []Q;
        delete []C;
        delete []j1;
        delete []j2;
        delete []j3;
}

void superbsort(reqSD A[],int l,int r,int jid[])
{
        if (l<r)
        {
                int m=l+(r-l)/2;
                superbsort(A,l,m,jid);
                superbsort(A,m+1,r,jid);
                combine(A,l,m,r,jid);
        }
}

void superbSorting(reqSD A[],int sizeOfA,int jid[])
{
        superbsort(A,0,sizeOfA-1,jid);
}

void schedule1(reqWD jb[],int n, int jid[])
{
        superbSorting(jb,n,jid);
        
        //for (int i=0;i<n;i++)
        //        cout<<jid[i]<<"::";
        //cout<<"\n";
        
        bool visited[n];
        
        for (int i=0;i<n;i++)
                visited[i]=false;
        int count=0,it=0; 
        while (count!=n)
        {
                cout<<"Counter "<<it++<<"\n";
                int prev=0;
                int i=0;
                while (visited[i])
                        i++;
                prev=jb[i].st+jb[i].len;
                cout<<jid[i]<<" "<<jb[i].st<<" "<<prev<<"\n";
                visited[i]=true;
                i++;
                count++;
                for (;i<n;i++)
                {
                        if (!visited[i])
                        {
                                if (jb[i].st>=prev)
                                {
                                        prev=jb[i].st+jb[i].len;
                                        cout<<jid[i]<<" "<<jb[i].st<<" "<<prev<<"\n";
                                        visited[i]=true;
                                        count++;
                                }
                        }
                }
        }
}

void schedule2(reqSD job[],int m,int jid1[])
{ 
        superbSorting(job,m,jid1);
        
        int diff=0,time=0;
        for (int i=0;i<m;i++)
        {
                //time+=job[i].st;
                if (time>job[i].tt)
                        diff+=(time-job[i].tt);
                cout<<jid1[i]<<" "<<time<<" "<<time+job[i].st<<"\n";
                time+=job[i].st;
        }     
}

int main()
{
        int n;
        cout<<"Enter the number of requests over weekday:";
        cin>>n;
        reqWD *jb=new reqWD[n];
        int jid[n];
        int st,len;
        cout<<"Enter the start time and length for each of the requests\n";
        for (int i=0;i<n;i++)
        {
                cout<<"request "<<i<<" :: ";
                cin>>st>>len;
                jb[i].st=st;
                jb[i].len=len;
                jid[i]=i;
        }
        
        schedule1(jb,n,jid); 

        int m;
        cout<<"Enter the number of requests over Saturday:";
        cin>>m;
        reqSD *job=new reqSD[m];
        int jid1[m];
        int tt;
        cout<<"Enter the length and deadline for each of the requests\n";
        for (int i=0;i<m;i++)
        {
                cout<<"request "<<i<<" :: ";
                cin>>st>>tt;
                job[i].st=st;
                job[i].tt=tt;
                jid1[i]=i;
        }     
        
        schedule2(job,m,jid1);
}
